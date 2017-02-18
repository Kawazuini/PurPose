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
    float mValue;

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
    void special(GameState& aState);
public:
    /**
     * \~english
     * @brief generate special effect.
     * @param aType    type of special effect
     * @param aValue   effective value
     * @param aSubject principal object
     * @param aObject  target object
     * \~japanese
     * @brief 特殊効果を生成します。
     * @param aType    特殊効果種類
     * @param aValue   効果値
     * @param aSubject 特殊効果源
     * @param aObject  特殊効果対象
     */
    Special(
            const SpecialType& aType = SPECIAL_MISS,
            const double aValue = 0,
            Character * const aSubject = NULL,
            Character * const aObject = NULL
            );
    /**
     * \~english
     * @brief copy constructor that can change the target
     * @param aSpecial original special effect
     * @param aSubject principal object
     * @param aObject  target object
     * \~japanese
     * @brief 対象を変更できるコピーコンストラクタ
     * @param aSpecial 元の特殊効果
     * @param aSubject 特殊効果源
     * @param aObject  特殊効果対象
     */
    Special(
            const Special& aSpecial,
            Character * const aSubject,
            Character * const aObject = NULL
            );
    ~Special() = default;

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
     * \~english
     * @brief invocate all the Special effects in the List.
     * @param aState state of game
     * \~japanese
     * @brief リスト内全ての特殊効果を発動させます
     * @param aState ゲーム状態
     */
    static void invocation(GameState& aState);

    /**
     * \~english
     * @brief  get SpecialType.
     * @return SpecialType
     * \~japanese
     * @brief  特殊効果種別を取得します。
     * @return 特殊効果種別
     */
    const SpecialType& type() const;
    /**
     * \~english
     * @brief  get effective value.
     * @return effective value
     * \~japanese
     * @brief  特殊効果値を取得します。
     * @return 特殊効果値
     */
    const float& value() const;
};

#endif /* SPECIAL_H */

