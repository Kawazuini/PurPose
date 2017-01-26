/**
 * @file   PhysicalPoint.cpp
 * @brief  PhysicalPoint
 * @author Maeda Takumi
 */
#include "PhysicalPoint.h"

#include "GameState.h"
#include "Tile.h"

PhysicalPoint::PhysicalPoint(const float& aMass) :
mPosition(mDummy),
mMass(aMass),
mGravity(true),
mCollider(true),
mOnWall(false) {
}

PhysicalPoint::PhysicalPoint(KVector& aPoint, const float& aMass) :
mPosition(aPoint),
mPrePosition(aPoint),
mMass(aMass),
mGravity(true),
mCollider(true),
mOnWall(false) {
}

void PhysicalPoint::update(GameState& aState) {
    if (mGravity) mForce += (aState.mGravity * mMass); // 重力を受ける
    { // 物理運動(順番大事)
        mForce -= mVelocity * aState.mAirResistance; // 空気抵抗(大分簡略化)
        mVelocity += mForce / mMass;
        translate(mPosition + mVelocity);
    }

    if (mCollider) resolveConflicts(); // 衝突判定

    mPrePosition = mPosition;
    mForce = KVector(); // 力は慣性により保存されない
}

void PhysicalPoint::resolveConflicts() {
    static const float HALF_PI = Math::PI / 2;
    static float e = 0.5; // 衝突が起きた面の反発係数

    KVector diff(mPosition - mPrePosition); // 移動量

    mOnWall = false;

    for (KPolygon* i : Tile::polyList()) {
        KVector normal(i->mNormal);
        KVector veloP(diff.extractParallel(normal));
        KSegment moveSeg(mPrePosition, mPrePosition + veloP);
        KVector hitPoint(i->hitPoint(moveSeg));
        if (i->operator*(hitPoint)) { // 衝突が起きた
            translate(hitPoint + normal * Math::EPSILON);

            // 衝突が起きた場合速度ベクトルを反射させる
            if (HALF_PI < mVelocity.angle(normal)) { // 入射角が鋭角の時のみ反射
                float a = (-mVelocity).dot(normal); // 反射量
                mVelocity += (normal * 2 * a);
                mVelocity *= e;
            }
            mOnWall = true;
            break;
        }
    }
}

void PhysicalPoint::applyForce(const KVector& aForce) {
    mForce += aForce;
}

const KVector& PhysicalPoint::position() const {
    return mPosition;
}

void PhysicalPoint::translate(const KVector& aPosition) {
    mPosition = aPosition;
}

void PhysicalPoint::setPosition(const KVector& aPosition) {
    mPosition = aPosition;
    mPrePosition = aPosition;
}

const bool& PhysicalPoint::isOnWall() const {
    return mOnWall;
}

