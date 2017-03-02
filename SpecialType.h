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
    /** ミス         */ SPECIAL_MISS,
    /** ダメージ     */ SPECIAL_DAMAGE,
    /** 回復         */ SPECIAL_HEAL,
    /** 成長         */ SPECIAL_GROW,
    /** レベルアップ */ SPECIAL_LEVELUP,
    /** 爆発         */ SPECIAL_EXPLOSION,
    /* 殺害          */ SPECIAL_KILL,
} SpecialType;

static inline SpecialType toSpecialType(const String& aType) {
    if (aType == "Miss") return SPECIAL_MISS;
    if (aType == "Damage") return SPECIAL_DAMAGE;
    if (aType == "Heal") return SPECIAL_HEAL;
    if (aType == "Grow") return SPECIAL_GROW;
    if (aType == "LevelUp") return SPECIAL_LEVELUP;
    if (aType == "Explosion") return SPECIAL_EXPLOSION;
    if (aType == "Kill") return SPECIAL_KILL;
    return SPECIAL_MISS;
}

#endif /* SPECIALTYPE_H */

