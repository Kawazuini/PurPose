/**
 * @file   AI.h
 * @brief  AI
 * @author Maeda Takumi
 */
#ifndef AI_H
#define AI_H

#include "AIType.h"

class Action;
class GameState;

class AI {
private:
    AIType mType;
public:
    AI(const AIType& aType);
    virtual ~AI();

    /***/
    Action nextAction(const GameState& aState);
};

#endif /* AI_H */

