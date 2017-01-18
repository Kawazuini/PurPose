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
    /**
     * @brief \~english  AI possessed Character
     * @brief \~japanese AI所持キャラクター
     */
    const Character& mCharacter;

    AI(const AIType& aType, const Character& aCharacter);
    virtual ~AI() = default;

    /***/
    Action nextAction(GameState& aState);
};

#endif /* AI_H */

