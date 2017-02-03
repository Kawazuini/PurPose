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

/**
 * @brief  AI
 * @author Maeda Takumi
 */
class AI {
public:
    /**
     * @brief \~english  type of AI
     * @brief \~japanese AIの種類
     */
    AIType mType;

    /**
     * \~english
     * @brief generate AI.
     * @param aType AI type
     * \~japanese
     * @brief AIを生成します。
     * @param aType AIの種類
     */
    AI(const AIType& aType = AI_SLOTH);
    /**
     * \~english
     * @brief generate AI.
     * @param aType AI type
     * \~japanese
     * @brief AIを生成します。
     * @param aType AIの種類
     */
    AI(const String& aType);
    virtual ~AI() = default;

    /**
     * \~english
     * @brief get next action.
     * @param aState     state of game
     * @param aCharacter act Character
     * @return 
     * \~japanese
     * @brief 次に行う行動を取得します。
     * @param aState     ゲーム状態
     * @param aCharacter 行動を行うキャラクター
     * @return 
     */
    Action nextAction(GameState& aState, const Character& aCharacter);
};

#endif /* AI_H */

