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
mType(aType),
mPosition(aPosition) {
}

