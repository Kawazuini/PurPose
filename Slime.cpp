/**
 * @file   Slime.cpp
 * @brief  Slime
 * @author Maeda Takumi
 */
#include "Slime.h"

#include "GameState.h"

Slime::Slime(GameState& aState)
: Enemy(1, aState, "S", 0.3, 0x7700ff00) {
}

void Slime::update(GameState& aState) {
    if (mTurn) {
        lookAt((aState.mPlayer.position() - mBody.mPosition).normalization());
    }
    Enemy::update(aState);
}

