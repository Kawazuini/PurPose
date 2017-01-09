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
    /* 待機 */ WAIT,
    /* 移動 */ MOVE,
    /* 攻撃 */ ATACK,
} ActionType;

#endif /* ACTIONTYPE_H */

