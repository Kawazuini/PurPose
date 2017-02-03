/**
 * @file   Action.h
 * @brief  Action
 * @author Maeda Takumi
 */
#ifndef ACTION_H
#define ACTION_H

#include "main.h"

#include "ActionType.h"

/**
 * @brief  \~english  base of all Action
 * @brief  \~japanese 全てのアクションの基底
 * @author \~ Maeda Takumi
 */
class Action {
private:
    /**
     * @brief \~english  type of Action
     * @brief \~japanese アクションの種類
     */
    ActionType mActionType;
    /**
     * @brief \~english  Action position
     * @brief \~japanese アクション位置
     */
    KVector mPosition;
public:
    /**
     * \~english
     * @brief generate Action
     * @param aActionType action type
     * @param aPosition   act coordinate
     * \~japanese
     * @brief アクションを生成します。
     * @param aActionType アクション種別
     * @param aPosition   アクション座標
     */
    Action(
            const ActionType& aActionType = ACTION_WAIT,
            const KVector& aPosition = KVector()
            );
    virtual ~Action() = default;

    /**
     * \~english
     * @brief  get action type
     * @return action type
     * \~japanese
     * @brief  アクション種別を取得します。
     * @return アクション種別
     */
    const ActionType& type() const;
    /**
     * \~english
     * @brief  get action coordinate
     * @return action coordinate
     * \~japanese
     * @brief  アクション座標を取得します。
     * @return アクション座標
     */
    const KVector& position() const;
};

#endif /* ACTION_H */

