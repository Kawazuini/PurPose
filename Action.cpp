/**
 * @file   Action.cpp
 * @brief  Action
 * @author Maeda Takumi
 */
#include "Action.h"

#include "Character.h"

Action::Action(
        const ActionType& aType,
        const KVector& aPosition
        ) :
mActionType(aType),
mPosition(aPosition) {
}

const Action Action::Wait() {
    return Action(WAIT);
}

const Action Action::Move(const KVector& aPosition) {
    return Action(MOVE, aPosition);
}

const Action Action::Attack() {
    return Action(ATTACK);
}

const ActionType& Action::type() const {
    return mActionType;
}

const KVector& Action::position() const {
    return mPosition;
}

