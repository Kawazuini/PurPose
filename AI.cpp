/**
 * @file   AI.cpp
 * @brief  AI
 * @author Maeda Takumi
 */
#include "AI.h"

#include "Action.h"
#include "GameState.h"

AI::AI(const AIType& aType) :
mType(aType) {
}

Action AI::nextAction(GameState& aState) {
    switch (mType) {
        case Sloth: return Action::Wait();
        case Berserk:
        {
            return Action::Move(aState.mPlayer.position()); // 直進で突っ込む            
        }
    }
}

