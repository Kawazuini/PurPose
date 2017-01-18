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
    Action(
            const ActionType& aActionType = WAIT,
            const KVector& aPosition = KVector()
            );
    virtual ~Action() = default;

    static const Action Wait();
    static const Action Move(const KVector& aPosition);
    static const Action Attack();

    const ActionType& type() const;
    const KVector& position() const;
};

#endif /* ACTION_H */

