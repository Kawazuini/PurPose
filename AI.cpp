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
        case AI_SLOTH: return Action(ACTION_WAIT);
        case AI_BERSERK:
        {
            // 攻撃できるときは攻撃
            if ((aState.mPlayer.position() - aCharacter.position()).length()
                    <= (aState.mPlayer.size() + aCharacter.size() + aCharacter.mCharacterParameter.mAttackRange)) {
                return Action(ACTION_ATTACK);
            }
            return Action(ACTION_MOVE, aState.mPlayer.position()); // 直進で突っ込む
        }
        case AI_PLAYER: return Action(ACTION_NOTHING);
    }
}

