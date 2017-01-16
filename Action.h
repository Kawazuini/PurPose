/**
 * @file   Action.h
 * @brief  Action
 * @author Maeda Takumi
 */
#ifndef ACTION_H
#define ACTION_H

#include "main.h"

#include "ActionType.h"
#include "Character.h"

class Character;

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
     * @brief \~english  direction of Action
     * @brief \~japanese アクションの方向
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


    const ActionType& type() const;
    const KVector& position() const;
};

#endif /* ACTION_H */

