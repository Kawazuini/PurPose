/**
 * @file   PhysicalCube.cpp
 * @brief  PhesicalCube
 * @author Maeda Takumi
 */
#include "PhysicalCube.h"

#include "GameState.h"
#include "Tile.h"

const int PhysicalCube::DIAGONAL_POINT_ON_SURFACE[8][3] = {
    {3, 5, 6},
    {2, 4, 7},
    {1, 4, 7},
    {0, 5, 6},
    {1, 2, 7},
    {0, 3, 6},
    {0, 3, 5},
    {1, 2, 4},
};

PhysicalCube::PhysicalCube(
        const float& aScale,
        const float& aMass,
        const KVector& aPosition
        ) :
KDrawCube(aScale, aPosition),
mMass(aMass),
mPrePosition(aPosition),
mHitIndex(CENTROID),
mRotation(KVector(0, 1, 0), 0),
mMove(false),
mGravity(true),
mCollider(true),
mRotatable(true),
mReflect(true) {
}

void PhysicalCube::update(GameState& aState) {
    if (mGravity) mForce += (aState.mGravity * mMass); // 重力を受ける
    { // 回転を含まない物理運動(順番重要)
        mForce -= mVelocity * aState.mAirResistance; // 空気抵抗(体積無視)
        mVelocity += mForce / mMass;
        translate(mVertex[CENTROID] + mVelocity);
    }
    if (mCollider) resolveConflict(); // 衝突判定
    if (mRotatable) gyro(aState); // 回転運動

    KSegment ray(mPrePosition, mVertex[CENTROID]); // 射線

    // 衝突キャラクターの探索
    Vector<Character*> hitCharacter; // 衝突キャラクター
    Vector<float> distance; // 移動原点とキャラクター座標との距離
    for (Character* i : aState.charList()) {
        KVector p(i->position());
        KVector dir(ray.direction());
        KVector vec(p - ray.mVec1); // 移動原点からキャラクター座標へのベクトル
        float dist; // キャラクター座標と移動線分の最短距離
        float t(vec.dot(dir) / ray.length()); // キャラクター座標から移動線分への垂線との交点の線分上の割合
        if (t < 0) dist = vec.length();
        else if (t > 1) dist = (p - ray.mVec2).length();
        else dist = ((ray.mVec2 - ray.mVec1) * t - vec).length();

        if (dist < mRadius + i->size()) { // キャラクターと衝突
            hitCharacter.push_back(i);
            distance.push_back(vec.lengthSquared());
        }
    }
    // クイックソート書くのめんどくさい
    for (int i = 0, i_e = hitCharacter.size() - 1; i < i_e; ++i) {
        bool end(true);
        for (int j = i_e; j > i; --j) {
            if (distance[j] < distance[j - 1]) {
                float dist(distance[j]);
                distance[j] = distance[j - 1];
                distance[j - 1] = dist;

                Character * tmp(hitCharacter[j]);
                hitCharacter[j] = hitCharacter[j - 1];
                hitCharacter[j - 1] = hitCharacter[j];
                end = false;
            }
        }
        if (end) break; // 一回も更新されなかったら終了
    }
    hitCharacter.swap(mHitCharacter);

    static const float E(Math::EPSILON / 10); // 処理中断条件
    if (mHitIndex != CENTROID && Math::approximately(mRotation.t, 1.0f) && (mPrePosition - mVertex[CENTROID]).lengthSquared() < E) {
        Object::remove();
        mMove = false;
    }

    mPrePosition = mVertex[CENTROID];
    mForce = KVector(); // 力は慣性により保存されない
}

void PhysicalCube::resolveConflict() {
    static const float HALF_PI(Math::PI / 2);
    static float e(0.5); // 衝突が起きた面の反発係数

    KVector centroid(mVertex[CENTROID]);
    KVector diff(centroid - mPrePosition); // 移動差分

    bool hit(false); // 衝突有無
    for (KPolygon* i : Tile::polyList()) {
        KVector normal(i->mNormal);
        KVector veloP(diff.extractParallel(normal));
        KVector rad(normal * mRadius);
        if (normal.dot(veloP) < 0 && i->operator*(KSegment(mPrePosition + rad, mPrePosition - rad + veloP))) {
            float r(0); // 重心から各頂点へのベクトルと面法線との射影(めり込み具合)で最大のもの
            int hitIndex(0);
            for (int j = 0; j < 8; ++j) {
                float d((mVertex[j] - centroid).dot(-normal));
                if (r < d) {
                    r = d;
                    hitIndex = j;
                }
            }
            // 点から面までの距離
            float s1((centroid - i->mVertex[0]).dot(normal));
            float s2((mPrePosition - i->mVertex[0]).dot(normal));
            if (s1 < r) { // 面にめり込んでいる
                KVector newPos;
                if (s1 * s2 < 0) {
                    float conflict(r / veloP.length());
                    newPos = centroid - diff * (conflict - s1 / (-s1 + s2));
                } else {
                    float conflict((r - s1) / veloP.length());
                    newPos = centroid - diff * conflict;
                }
                translate(newPos); // 面に沿うように修正

                // 座標と差分の更新
                centroid = mVertex[CENTROID];
                diff = centroid - mPrePosition;
                mHitIndex = hitIndex;
                mHitPolygon = *i;
                hit = true;
            }
        }
    }
    if (hit) { // 衝突が起きた場合速度ベクトルを反射させる
        if (mReflect) {
            if (HALF_PI < mVelocity.angle(mHitPolygon.mNormal)) { // 入射角が鋭角の時のみ反射
                float a((-mVelocity).dot(mHitPolygon.mNormal)); // 反射量
                mVelocity = (mVelocity + (mHitPolygon.mNormal * 2 * a)) * e;
            }
        }
    } else mHitIndex = CENTROID;
}

void PhysicalCube::gyro(const GameState& aState) {
    static float q(0.5); // 摩擦係数

    if (mHitIndex != CENTROID) { // 衝突している
        KVector centroid(mVertex[CENTROID]);

        KVector diff((centroid - mPrePosition).extractVertical(mHitPolygon.mNormal)); // 移動差分(慣性)
        KVector friction(-diff.normalization() * (q * mMass * aState.mGravity.length())); // 摩擦
        KVector rotateAxis(friction.cross(mHitPolygon.mNormal)); // 回転軸
        float rotateMoment((friction - diff).length() / (mRadius * (1.0_s * 1.0_s))); // 回転量
        mRotation *= KQuaternion(rotateAxis, rotateMoment);

        if (Math::approximately(mRotation.t, 1.0f)) { // 回転が弱い場合、衝突面に沿う
            int nearIndex; // 衝突面から最も近い頂点番号
            float nearSquare(0xfffffff);
            for (int i = 0; i < 3; ++i) {
                float dist((mVertex[DIAGONAL_POINT_ON_SURFACE[mHitIndex][i]] - mVertex[mHitIndex]).extractParallel(mHitPolygon.mNormal).lengthSquared());
                if (dist < nearSquare) {
                    nearIndex = DIAGONAL_POINT_ON_SURFACE[mHitIndex][i];
                    nearSquare = dist;
                }
            }
            KVector diagonal(mVertex[nearIndex] - mVertex[mHitIndex]);
            KVector hitLine(diagonal.extractVertical(mHitPolygon.mNormal));
            rotate(mVertex[mHitIndex], diagonal.roundAngle(hitLine) / Math::PI);
        }
    }
    mRotation *= -mRotation / 1.0_s; // 回転減衰
    rotate(mVertex[mHitIndex], mRotation);
}

void PhysicalCube::applyForce(const KVector& aForce) {
    Object::add();
    mMove = true;
    mForce += aForce;
}

void PhysicalCube::setPosition(const KVector& aPosition) {
    mPrePosition = aPosition;
    translate(aPosition);
}

const bool& PhysicalCube::isMove() const {
    return mMove;
}

bool PhysicalCube::isHitWall() const {
    return mHitIndex != CENTROID;
}

const Vector<Character*>& PhysicalCube::hitCharacter() const {
    return mHitCharacter;
}

float PhysicalCube::speed() const {
    return mVelocity.length();
}

float PhysicalCube::impulse() const {
    return mMass * mVelocity.length();
}
