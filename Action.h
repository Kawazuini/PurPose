/**
 * @file   Action.h
 * @brief  Action
 * @author Maeda Takumi
 */
#ifndef ACTION_H
#define ACTION_H

#include "main.h"

/**
 * @brief  \~english  Action
 * @brief  \~japanese 行動
 * @author \~ Maeda Takumi
 */
class Action final {
public:

    /**
     * @brief \~english  Type of Action
     * @brief \~japanese アクションの種類
     */
    enum ActionType {
        /** \~japanese 待機 */ TYPE_WAIT,
        /** \~japanese 移動 */ TYPE_MOVE,
        /** \~japanese 攻撃 */ TYPE_ATTACK,

        /** \~japanese プレイヤー移譲 */
        TYPE_NOTHING,
    } mType;
    /**
     * @brief \~english  Action position
     * @brief \~japanese アクション位置
     */
    KVector mPosition;

    /**
     * @param aActionType ActionType
     * \~english  @param aPosition act coordinate
     * \~japanese @param aPosition アクション座標
     */
    Action(
            const ActionType& aActionType = TYPE_WAIT,
            const KVector& aPosition = KVector()
            );
    virtual ~Action() = default;
};

#endif /* ACTION_H */

