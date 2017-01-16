/**
 * @file   Slime.cpp
 * @brief  Slime
 * @author Maeda Takumi
 */
#include "Slime.h"

#include "GameState.h"

Slime::Slime()
: Enemy("S", 0.3, 0x7700ff00) {
    mAIType = Berserk;

    mParameter.mSpeed = 0.6f;

    mParameter.mName = "スライム";

    mParameter.mExperience = 16;

    mParameter.mHP = mParameter.mMaxHP = 10;
}

void Slime::update(GameState& aState) {
    if (mTurn) {
        lookAt((aState.mPlayer.position() - mBody.mPosition).normalization());
    }
    Character::update(aState);
}

