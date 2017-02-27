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
    if (mCollider) resolveConflict(aState); // 衝突判定
    if (mRotatable) gyro(aState); // 回転運動


    // 衝突キャラクターの探索
    Vector<HitCharacter> HitChar;
    KSegment ray(mPrePosition, mVertex[CENTROID]); // 射線
    KVector rayDirection(ray.direction()); // 射線方向
    for (Character* i : aState.charList()) {
        KVector pos(i->position());
        KVector vec(pos - ray.mVec1);

        float t(vec.dot(rayDirection) / ray.length()); // 移動線分のキャラクター座標からの垂線との交点による内分比
        float dist(((ray.mVec2 - ray.mVec1) * t - vec).length()); // キャラクター座標と移動線分の最短距離
        if (t < 0) dist = vec.length();
        if (t > 1) dist = (pos - ray.mVec2).length();

        if (dist < mRadius + i->size()) { // キャラクターと衝突
            HitChar.push_back(HitCharacter{i, vec.lengthSquared()});
        }
    }
    // 移動原点から近い順に並べる
    std::sort(HitChar.begin(), HitChar.end(),
            [](const HitCharacter& x, const HitCharacter & y) -> bool {
                return x.mDistance < y.mDistance;
            }
    );
    // 衝突キャラクターリストに反映
    mHitCharacter.clear();
    for (HitCharacter i : HitChar) {
        mHitCharacter.push_back(i.mCharacter);
    }

    static const float E(Math::EPSILON / 10); // 処理中断条件
    if (mHitIndex != CENTROID && Math::approximately(mRotation.t, 1.0f) && (mPrePosition - mVertex[CENTROID]).lengthSquared() < E) {
        Object::remove();
        mMove = false;
    }

    mPrePosition = mVertex[CENTROID];
    mForce = KVector(); // 力は慣性により保存されない
}

void PhysicalCube::resolveConflict(const GameState& aState) {
    static const float HALF_PI(Math::PI / 2);
    static float e(0.5); // 衝突が起きた面の反発係数

    KVector centroid(mVertex[CENTROID]);
    KVector diff(centroid - mPrePosition); // 移動差分

    bool hit(false); // 衝突有無
    for (KPolygon* i : aState.wallList()) {
        KVector normal(i->mNormal);
        KVector rad(normal * mRadius); // 法線方向への半径
        KVector diffRad(diff.normalization() * mRadius); // 移動方向への半径

        // 1.立方体を内包する球での衝突判定
        KVector confPoint; // 衝突位置
        bool correct(false); // 補正の必要性
        if (normal.dot(diff) < 0) { // 衝突判定(法線と進行方向が鋭角の時のみ判定を行う)
            // 半径を考慮した3つの移動線分により判定を行う
            if (i->operator*(confPoint = i->hitPoint(KSegment(mPrePosition - diffRad, centroid + diffRad)))) correct = true;
            else if (i->operator*(confPoint = i->hitPoint(KSegment(mPrePosition + rad, centroid + rad))));
            else if (i->operator*(confPoint = i->hitPoint(KSegment(mPrePosition - rad, centroid - rad))));
            else continue; // 衝突していない
        } else continue;

        // 2.厳密な立方体との衝突判定およびめり込みの解消
        float r(0); // 重心から各頂点へのベクトルと面法線との射影(めり込み具合)で最大のもの
        int hitIndex(0);
        for (int j = 0; j < 8; ++j) {
            float d((mVertex[j] - centroid).dot(-normal));
            if (r < d) {
                r = d;
                hitIndex = j;
            }
        }
        float s((centroid - i->mVertex[0]).dot(normal)); // 重心から面までの距離
        if (s < r) { // 面にめり込んでいる
            KVector newPos(confPoint + normal * r);
            // 補正をかける
            if (correct) newPos -= diff.extractVertical(normal).normalization() * r * tan(diff.angle(-normal));
            translate(newPos); // 面に沿うように修正

            // 座標と差分の更新
            centroid = mVertex[CENTROID];
            diff = centroid - mPrePosition;
            mHitIndex = hitIndex;
            mHitPolygon = *i;
            hit = true;
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
