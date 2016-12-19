/**
 * @file   Slime.cpp
 * @brief  Slime
 * @author Maeda Takumi
 */
#include "Slime.h"

Slime::Slime()
: Enemy("S", 1, 0x7700ff00) {
    mName = "スライム";

    mExperience = 16;

    mHP = mMaxHP = 10;
}

void Slime::update(const KVector& aPlayer) {
    if (mTurn) {
        // 移動方向の決定
        if (aPlayer != mBody.mPosition) {
            KVector eyeDir = (aPlayer - mBody.mPosition).normalization();
            KQuaternion rotate = mDirection.roundAngle(eyeDir);
            mSphere->rotate(rotate);
            mDirection = mDirection.rotate(rotate);
        }
    }
    Enemy::move(mDirection);
    Enemy::update(aPlayer);
}

