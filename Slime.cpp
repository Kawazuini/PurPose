/**
 * @file   Slime.cpp
 * @brief  Slime
 * @author Maeda Takumi
 */
#include "Slime.h"

Slime::Slime()
: Enemy("S", 0.3, 0x7700ff00) {
    mParameter.mSpeed = 0.6f;

    mParameter.mName = "スライム";

    mParameter.mExperience = 16;

    mParameter.mHP = mParameter.mMaxHP = 10;
}

void Slime::update(const KVector& aPlayer) {
    if (mTurn) {
        // 移動方向の決定
        if (aPlayer != mBody.mPosition) {
            KVector eyeDir = (aPlayer - mBody.mPosition).normalization();
            lookAt(eyeDir);
        }
    }
    move(mDirection);
    Enemy::update(aPlayer);
}

