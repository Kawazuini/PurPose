/**
 * @file   Slime.cpp
 * @brief  Slime
 * @author Maeda Takumi
 */
#include "Slime.h"
#include "PurPose.h"
#include "Bulletin.h"
#include "Device.h"

Slime::Slime()
: Enemy("S", 0x7700ff00) {
    mHP = mMaxHP = 10;

    mAgility = 7;
    mMoveCost = 1;
    mActionPoint = 0;

    mName = "スライム";
    mSize = 1.0f;
}

Slime::~Slime() {
    delete mTexture;
}

void Slime::update(const KVector& aPlayer) {
    Enemy::update(aPlayer);
    Enemy::move(mDirection);
}

