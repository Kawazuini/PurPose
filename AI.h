/**
 * @file   AI.h
 * @brief  AI
 * @author Maeda Takumi
 */
#ifndef AI_H
#define AI_H

#include "AIType.h"

class Action;
class Character;
class GameState;

class AI {
public:
    /**
     * @brief \~english  type of AI
     * @brief \~japanese AIの種類
     */
    AIType mType;

    AI(const AIType& aType = Sloth);
    AI(const String& aType);
    virtual ~AI() = default;

    /***/
    Action nextAction(GameState& aState, const Character& aCharacter);
};

#endif /* AI_H */

