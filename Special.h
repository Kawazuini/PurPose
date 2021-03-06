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
class Item;

/**
 * @brief  \~english  Special effective
 * @brief  \~japanese 特殊効果
 * @author \~ Maeda Takumi
 */
class Special final {
private:
    /* 特殊効果関数   */ using SpecialFunction = void (Special::*)(GameState& aState);
    /* 特殊効果関数群 */ static const Vector<SpecialFunction> SPECIAL_FUNCTION;

    /* 特殊効果リスト(先頭から順に発動) */
    static List<Special> sSpecials;

    /* 特殊効果の種類 */ SpecialType mType;
    /* 特殊効果値     */ float mValue;
    /* 特殊効果主体   */ Character* mSCharacter;
    /* 特殊効果対象   */ Character* mOCharacter;
    /* 特殊効果対象   */ Item* mOItem;

    /* 特殊効果の発動 */ void special(GameState& aState);

    /* ----- 特殊効果関数 ----- */
    void miss(GameState& aState);
    void damage(GameState& aState);
    void damage_ignore(GameState& aState);
    void damage_stamina(GameState& aState);
    void heal(GameState& aState);
    void heal_stamina(GameState& aState);
    void grow(GameState& aState);
    void levelup(GameState& aState);
    void explosion(GameState& aState);
    void kill(GameState& aState);
public:
    /**
     * \~english
     * @param aType    type of special effect
     * @param aValue   effective value
     * @param aSubject principal object
     * @param aObject  target object
     * \~japanese
     * @param aType    特殊効果種類
     * @param aValue   効果値
     * @param aSubject 特殊効果源
     * @param aObject  特殊効果対象
     */
    Special(
            const SpecialType& aType = SPECIAL_MISS,
            const float aValue = 0.0f,
            Character* aSubject = nullptr,
            Character* aObject = nullptr
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
            Character* aSubject,
            Character* aObject = nullptr
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
            Character* aSubject,
            Item* aObject
            );
    ~Special() = default;

    /**
     * \~english
     * @brief  generate multiple special effects.
     * @param  aSpecials generating strings
     * @return multiple special effects
     * \~japanese
     * @brief  特殊効果を複数生成します。
     * @param  aSpecials 生成文字列の配列
     * @return 複数の特殊効果
     */
    static List<Special> Specials(const Vector<String>& aSpecials);

    bool operator==(const Special& aSpecial) const;
    bool operator!=(const Special& aSpecial) const;

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

    /// @brief \~english  clear list content.
    /// @brief \~japanese リストを消去します。
    static void clear();

    const SpecialType& type() const;
    const float& value() const;
};

#endif /* SPECIAL_H */

