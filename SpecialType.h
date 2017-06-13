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
    /** ミス               */ SPECIAL_MISS,
    /** ダメージ           */ SPECIAL_DAMAGE,
    /** 防御無視のダメージ */ SPECIAL_DAMAGE_IGNORE,
    /** スタミナダメージ   */ SPECIAL_DAMAGE_STAMINA,
    /** 回復               */ SPECIAL_HEAL,
    /** スタミナ回復       */ SPECIAL_HEAL_STAMINA,
    /** 成長               */ SPECIAL_GROW,
    /** レベルアップ       */ SPECIAL_LEVELUP,
    /** 爆発               */ SPECIAL_EXPLOSION,
    /** 殺害               */ SPECIAL_KILL,
} SpecialType;

static inline SpecialType toSpecialType(const String& aType) {
    if (aType == "Miss") return SPECIAL_MISS;
    if (aType == "Damage") return SPECIAL_DAMAGE;
    if (aType == "IgnoreDamage") return SPECIAL_DAMAGE_IGNORE;
    if (aType == "StaminaDamage") return SPECIAL_DAMAGE_STAMINA;
    if (aType == "Heal") return SPECIAL_HEAL;
    if (aType == "StaminaHeal") return SPECIAL_HEAL_STAMINA;
    if (aType == "Grow") return SPECIAL_GROW;
    if (aType == "LevelUp") return SPECIAL_LEVELUP;
    if (aType == "Explosion") return SPECIAL_EXPLOSION;
    if (aType == "Kill") return SPECIAL_KILL;
    return SPECIAL_MISS;
}

#endif /* SPECIALTYPE_H */

