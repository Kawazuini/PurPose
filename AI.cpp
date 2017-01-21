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

AI::AI(const String& aType) :
AI(toAIType(aType)) {
}

Action AI::nextAction(GameState& aState, const Character& aCharacter) {
    switch (mType) {
        case Sloth: return Action::Wait();
        case Berserk:
        {
            // 攻撃できるときは攻撃
            if ((aState.mPlayer.position() - aCharacter.position()).length()
                    <= (aState.mPlayer.size() + aCharacter.size() + aCharacter.mCharacterParameter.mAttackRange)) {
                return Action::Attack();
            }
            return Action::Move(aState.mPlayer.position()); // 直進で突っ込む            
        }
    }
}

