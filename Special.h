/**
 * @file   Special.h
 * @brief  Special
 * @author Maeda Takumi
 */
#ifndef SPECIAL_H
#define SPECIAL_H

#include "main.h"

#include "SpecialType.h"

class GameState;
class Object;

/**
 * @brief  \~english  Special effective
 * @brief  \~japanese 特殊効果
 * @author \~ Maeda Takumi
 */
class Special : private KNonCopy {
private:
    /**
     * @brief \~english  List of Special(invocation in order from the top.)
     * @brief \~japanese 特殊効果リスト(先頭から順に発動します。)
     */
    static List<Special*> sSpecials;

    /**
     * @brief \~english  ID distributor
     * @brief \~japanese ID分配用変数
     */
    static int sIDDistributor;
    const int mID; ///< @brief ID

    /**
     * @brief \~english  type of Special effective
     * @brief \~japanese 特殊効果の種類
     */
    SpecialType mType;

    /**
     * @brief \~english  Special effect principal object
     * @brief \~japanese 特殊効果主体オブジェクト
     */
    Object& mSubject;
    /**
     * @brief \~english  Special effect target object
     * @brief \~japanese 特殊効果対象オブジェクト
     */
    Object& mObject;

    /* variable for Special effective */
    int mValueI1;
    double mValueD1;

    Special(
            const SpecialType aType,
            Object& aSubject,
            Object& aObject,
            const int& aValue = 0
            );
    Special(
            const SpecialType aType,
            Object& aSubject,
            const int& aValue = 0
            );
    Special(
            const SpecialType aType,
            Object& aSubject,
            const double& aValue = 0.0
            );
    virtual ~Special() = default;

    /**
     * @brief \~english  invocate effect.
     * @brief \~japanese 効果を発動させます。
     */
    virtual void special(GameState& aState);

    /**
     * \~english
     * @brief add a special effect at the end of the list.
     * @param aSpecial Special effect added
     * \~japanese
     * @brief リストの最後に特殊効果を追加します。
     * @param aSpecial 追加する特殊効果
     */
    static void add(Special& aSpecial);
    /**
     * \~english
     * @brief add a special effect at the top of the list.
     * @param aSpecial Special effect added
     * \~japanese
     * @brief リストの先頭に特殊効果を追加します。
     * @param aSpecial 追加する特殊効果
     */
    static void cutin(Special& aSpecial);
public:
    /**
     * @brief \~english  invocate all the Special effects in the List.
     * @brief \~japanese リスト内全ての特殊効果を発動させます。
     */
    static void invocation(GameState& aState);

    static void Damage(Object& aSubject, Object& aObject, const int& aDamage);
    static void Grow(Object& aSubject, const int& aExp);
    static void Heal(Object& aSubject, Object& aObject, const int& aHeal);
    static void LevelUp(Object& aSubject, const int& aLevel);
};

#endif /* SPECIAL_H */

