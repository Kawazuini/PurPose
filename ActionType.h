/**
 * @file   ActionType.h
 * @brief  ActionType
 * @author Maeda Takumi
 */
#ifndef ACTIONTYPE_H
#define ACTIONTYPE_H

/**
 * @brief \~english  type of Action
 * @brief \~japanese アクションの種類
 */
typedef enum {
    ACTION_WAIT,
    ACTION_MOVE,
    ACTION_ATTACK,
    ACTION_NOTHING,
} ActionType;

#endif /* ACTIONTYPE_H */

