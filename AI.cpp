/**
 * @file   AI.cpp
 * @brief  AI
 * @author Maeda Takumi
 */
#include "AI.h"

#include "Action.h"
#include "Character.h"
#include "GameState.h"

const float AI::VIEW_ANGLE(Math::PI / 4.0f);

const Vector<AI::AIFunction> AI::AI_FUNCTION{
    player,
    merchant,
    sloth,
    berserk,
    coward,
};

AI::AI(const Type& aType) :
mState(STATE_SEARCH),
mType(aType) {
}

AI::AI(const String& aType) :
AI(toAIType(aType)) {
}

Action AI::nextAction(const GameState& aState, Character& aCharacter) {
    return (this->*AI_FUNCTION[mType])(aState, aCharacter);
}

bool AI::checkPlayer(const GameState& aState, const Character& aCharacter) {
    KSegment eye(aCharacter.position(), aState.mPlayer.position());
    if (eye.direction().angle(aCharacter.direction()) < VIEW_ANGLE) {
        const List<KPolygon*>& walls(aState.wallList());
        for (KPolygon* i : walls) {
            if (i->operator*(eye)) {
                return false;
            }
        }
        return true;
    } else return false;
}

