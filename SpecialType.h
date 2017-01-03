/**
 * @file   SpecialType.h
 * @brief  SpecialType
 * @author Maeda Takumi
 */
#ifndef SPECIALTYPE_H
#define SPECIALTYPE_H

/**
 * @brief \~english  type of Special effective
 * @brief \~japanese 特殊効果の種類
 */
typedef enum {
    /* ダメージ     */ DAMAGE,
    /* 成長         */ GROW,
    /* 回復         */ HEAL,
    /* レベルアップ */ LEVELUP,
} SpecialType;

#endif /* SPECIALTYPE_H */

