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

PhysicalCube::PhysicalCube(const float& aScale, const KVector& aPosition) :
KDrawCube(aScale, aPosition),
mMass(1),
mPrePosition(aPosition),
mHitIndex(CENTROID),
mRotation(KVector(0, 1, 0), 0),
mMove(true),
mGravity(true),
mCollider(true),
mRotatable(true) {
}

void PhysicalCube::update(GameState& aState) {
    if (mGravity) mForce += (aState.mGravity * mMass); // 重力を受ける
    { // 回転を含まない物理運動
        translate(mVertex[CENTROID] + mVelocity);
        mForce -= mVelocity * aState.mAirResistance; // 空気抵抗(大分簡略化)
        mVelocity += mForce / mMass;
    }
    if (mCollider) resolveConflicts(); // 衝突判定
    if (mRotatable) gyro(aState); // 回転運動

    // 衝突キャラクターの探索
    Vector<Character*> hitCharacter; // 衝突キャラクター
    Vector<float> distance; // 移動原点とキャラクター座標との距離
    KSegment move(mPrePosition, mVertex[CENTROID]); // 移動線分
    for (Character* i : aState.mCharacters) {
        KVector p(i->position());
        KVector dir(move.direction());
        KVector vec(p - move.mVec1); // 移動原点からキャラクター座標へのベクトル
        float dist; // キャラクター座標と移動線分の最短距離
        float t(vec.dot(dir) / move.length()); // キャラクター座標から移動線分の垂線との交点の線分上の割合
        if (t > 0) {
            dist = (dir * t - vec).length();
        } else {
            dist = Math::min(vec.length(), (p - move.mVec2).length());
        }
        if (dist < mRadius + i->size()) { // キャラクターと衝突
            hitCharacter.push_back(i);
            distance.push_back(dist);
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
        if (end) break;
    }
    hitCharacter.swap(mHitCharacter);

    static const float E = Math::EPSILON / 10; // 処理中断条件
    if ((mPrePosition - mVertex[CENTROID]).lengthSquared() < E) {
        Object::remove();
        mMove = false;
    }

    mPrePosition = mVertex[CENTROID];
    mForce = KVector(); // 力は慣性により保存されない
}

void PhysicalCube::resolveConflicts() {
    static float e = 0.5; // 衝突が起きた面の反発係数

    KVector centroid(mVertex[CENTROID]);
    KVector moveDiff(centroid - mPrePosition); // 移動量

    List<KPolygon*> walls = Tile::polyList();
    for (KPolygon* i : walls) {
        KVector normal(i->mNormal);
        KVector veloP(moveDiff.extractParallel(normal));
        if (i->operator*(KSegment(
                mPrePosition + (normal * mRadius),
                mPrePosition - (normal * mRadius) + veloP
                ))) {
            KVector outward[8]; // 中心座標からの各頂点へのベクトル
            for (int j = 0; j < 8; ++j) {
                outward[j] = mVertex[j] - centroid;
            }

            float r = 0; // 頂点の内で最も面に近い距離
            for (int j = 0; j < 8; ++j) {
                float d = outward[j].dot(-normal); // 頂点と面との距離
                if (r < d) {
                    r = d;
                    mHitIndex = j;
                    mHitPolygon = *i;
                }
            }

            float s = (centroid - i->mVertex[0]).dot(normal); // 重心から面までの距離
            if (s < r) { // 面にめり込んでいる
                // 面に沿うように修正
                translate(centroid + normal * (r - s));

                // 衝突が起きた場合速度ベクトルを反射させる
                if (Math::PI / 2 < mVelocity.angle(normal)) { // 入射角が鋭角の時のみ反射
                    float a = (-mVelocity).dot(normal); // 反射量
                    mVelocity += (normal * 2 * a);
                    mVelocity *= e;
                }
                break;
            } else mHitIndex = CENTROID;
        }
    }
}

void PhysicalCube::gyro(const GameState& aState) {
    static float q = 0.5; // 摩擦係数

    if (mHitIndex != CENTROID) { // 衝突している
        KVector centroid(mVertex[CENTROID]);

        KVector diff((centroid - mPrePosition).extractVertical(mHitPolygon.mNormal)); // 移動差分(慣性)
        KVector friction(-diff.normalization() * (q * mMass * aState.mGravity.length())); // 摩擦
        KVector rotateAxis = diff.cross(mHitPolygon.mNormal); // 回転軸
        float rotateMoment = (diff - friction).length() / (mRadius * (1.0_s * 1.0_s)); // 回転量
        mRotation *= KQuaternion(rotateAxis, rotateMoment);


        if (Math::approximately(mRotation.t, 1.0f)) { // 回転が弱い場合、衝突面に沿う
            int nearIndex; // 衝突面から最も近い頂点番号
            float nearSquare = 0xfffffff;
            for (int i = 0; i < 3; ++i) {
                float dist = (mVertex[DIAGONAL_POINT_ON_SURFACE[mHitIndex][i]] - mVertex[mHitIndex]).extractParallel(mHitPolygon.mNormal).lengthSquared();
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

const Vector<Character*>& PhysicalCube::hitCharacter() const {
    return mHitCharacter;
}

