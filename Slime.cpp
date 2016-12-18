/**
 * @file   Slime.cpp
 * @brief  Slime
 * @author Maeda Takumi
 */
#include "Slime.h"

Slime::Slime()
: Enemy("S", 0x7700ff00) {
    mName = "スライム";
    mBody.mRadius = 1.0f;

    mExperience = 16;

    mHP = mMaxHP = 10;
}

void Slime::update(const KVector& aPlayer) {
    Enemy::update(aPlayer);
    Enemy::move(mDirection);
}

