/**
 * @file   AI.cpp
 * @brief  AI
 * @author Maeda Takumi
 */
#include "AI.h"

#include "Action.h"
#include "GameState.h"

AI::AI(const AIType& aType, const Character& aCharacter) :
mType(aType),
mCharacter(aCharacter) {
}

Action AI::nextAction(GameState& aState) {
    switch (mType) {
        case Sloth: return Action::Wait();
        case Berserk:
        {
            // 攻撃できるときは攻撃
            if ((aState.mPlayer.position() - mCharacter.position()).length()
                    <= (aState.mPlayer.size() + mCharacter.size() + mCharacter.mParameter.mAttackRange)) {
                return Action::Attack();
            }
            return Action::Move(aState.mPlayer.position()); // 直進で突っ込む            
        }
    }
}

