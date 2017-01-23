/**
 * @file   Special.h
 * @brief  Special
 * @author Maeda Takumi
 */
#ifndef SPECIAL_H
#define SPECIAL_H

#include "main.h"

#include "SpecialType.h"

class Character;
class GameState;

/**
 * @brief  \~english  Special effective
 * @brief  \~japanese 特殊効果
 * @author \~ Maeda Takumi
 */
class Special {
private:
    /**
     * @brief \~english  List of Special(invocation in order from the top.)
     * @brief \~japanese 特殊効果リスト(先頭から順に発動します。)
     */
    static List<Special> sSpecials;

    /**
     * @brief \~english  type of Special effective
     * @brief \~japanese 特殊効果の種類
     */
    SpecialType mType;
    /**
     * @brief \~english  effective value
     * @brief \~japanese 効果値
     */
    double mValue;

    /**
     * @brief \~english  Special effect principal object
     * @brief \~japanese 特殊効果主体オブジェクト
     */
    Character* mSubject;
    /**
     * @brief \~english  Special effect target object
     * @brief \~japanese 特殊効果対象オブジェクト
     */
    Character* mObject;

    /**
     * @brief \~english  invocate effect.
     * @brief \~japanese 効果を発動させます。
     */
    virtual void special(GameState& aState);
public:
    Special(
            const SpecialType& aType = MISS,
            const double aValue = 0,
            Character * const aSubject = NULL,
            Character * const aObject = NULL
            );
    Special(
            const Special& aSpecial,
            Character * const aSubject,
            Character * const aObject = NULL
            );
    virtual ~Special() = default;

    /**
     * \~english
     * @brief add a special effect at the end of the list.
     * @param aSpecial Special effect added
     * \~japanese
     * @brief リストの最後に特殊効果を追加します。
     * @param aSpecial 追加する特殊効果
     */
    static void add(const Special& aSpecial);
    /**
     * \~english
     * @brief add a special effect at the top of the list.
     * @param aSpecial Special effect added
     * \~japanese
     * @brief リストの先頭に特殊効果を追加します。
     * @param aSpecial 追加する特殊効果
     */
    static void cutin(const Special& aSpecial);

    /**
     * @brief \~english  invocate all the Special effects in the List.
     * @brief \~japanese リスト内全ての特殊効果を発動させます。
     */
    static void invocation(GameState& aState);

    static void Damage(Character& aSubject, Character& aObject, const int& aDamage);
    static void Grow(Character& aSubject, const int& aExp);
    static void Heal(Character& aSubject, Character& aObject, const int& aHeal);
    static void LevelUp(Character& aSubject, const int& aLevel);
};

#endif /* SPECIAL_H */

