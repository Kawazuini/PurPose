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
    /* ミス         */ MISS,
    /* ダメージ     */ DAMAGE,
    /* 回復         */ HEAL,
    /* 成長         */ GROW,
    /* レベルアップ */ LEVELUP,
} SpecialType;

static inline SpecialType toSpecialType(const String& aType) {
    if (aType == "Damage") return DAMAGE;
    if (aType == "Heal") return HEAL;
    if (aType == "Grow") return GROW;
    if (aType == "LevelUp") return LEVELUP;
    return MISS;
}

#endif /* SPECIALTYPE_H */

