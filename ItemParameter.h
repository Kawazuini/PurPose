/**
 * @file   ItemParameter.h
 * @brief  ItemParameter
 * @author Maeda Takumi
 */
#ifndef ITEMPARAMETER_H
#define ITEMPARAMETER_H

#include "Special.h"
#include "ItemType.h"

/**
 * @brief  \~english  Parameter of Item
 * @brief  \~japanese アイテムパラメータ
 * @author \~ Maeda Takumi
 */
class ItemParameter {
private:

    enum ItemIndex {
        ITEM_INDEX_TYPE,
        ITEM_INDEX_NAME,
        ITEM_INDEX_SIZE,
        ITEM_INDEX_WEIGHT,
        ITEM_INDEX_USABLE,
        ITEM_INDEX_EQUIPPABLE,
        ITEM_INDEX_REFLECT,
        ITEM_INDEX_SPECIAL,
        ITEM_INDEX_SPPOINT,
        ITEM_INDEX_COST,
        ITEM_INDEX_ATTACK,
        ITEM_INDEX_DEFENSE,
        ITEM_INDEX_ERANGE,
        ITEM_INDEX_EANGLE,
        ITEM_INDEX_STACK,
        ITEM_INDEX_MAGAZINE_ID,
    };
    /**
     * @brief \~english  parameter table
     * @brief \~japanese パラメータテーブル
     */
    Vector<String> mParameterTable;

    int mID; ///< ID
    /**
     * @brief \~english  type of Item
     * @brief \~japanese アイテム種別
     */
    ItemType mItemType;
    /**
     * @brief \~english  Item name
     * @brief \~japanese アイテム名
     */
    String mName;
    /**
     * @brief \~english  Item size
     * @brief \~japanese アイテムサイズ
     */
    float mSize;
    /**
     * @brief \~english  Item weight
     * @brief \~japanese アイテム重量
     */
    float mWeight;
    /**
     * @brief \~english  whether usable
     * @brief \~japanese 使用可能か
     */
    bool mUsable;
    /**
     * @brief \~english  whether equippable
     * @brief \~japanese 装備可能か
     */
    bool mEquippable;
    /**
     * @brief \~english  whether reflectable
     * @brief \~japanese 反射可能か
     */
    bool mReflectable;
    /**
     * @brief \~english  special effect
     * @brief \~japanese 特殊効果
     */
    Special mSpecial;
    /**
     * @brief \~english  Item const
     * @brief \~japanese コスト
     */
    int mCost;
    /**
     * @brief \~english  attack power
     * @brief \~japanese 攻撃力
     */
    float mAttackPower;
    /**
     * @brief \~english  defence power
     * @brief \~japanese 防御力
     */
    float mDefencePower;
    /**
     * @brief \~english  effective range
     * @brief \~japanese 有効射程
     */
    float mEffectiveRange;
    /**
     * @brief \~english  effective angle
     * @brief \~japanese 有効角度
     */
    float mEffectiveAngle;

    /**
     * @brief \~english  stackable number
     * @brief \~japanese スタック可能数
     */
    int mStack;
    /**
     * @brief \~english  satckable Item ID
     * @brief \~japanese スタックできるアイテムID
     */
    int mMagazineID;
public:
    /**
     * @brief \~english  whether able to pick up
     * @brief \~japanese 拾えるか
     */
    bool mPickable;
    /**
     * @brief \~english  whether equipped
     * @brief \~japanese 装備されているか
     */
    bool mEquipped;
    /**
     * @brief \~english  whether able to take off
     * @brief \~japanese 装備を外せるか
     */
    bool mTakeoffable;

    /**
     * \~english
     * @brief generate parameters from resource ID.
     * @param aID resource ID
     * \~japanese
     * @brief リソースIDからパラメータを生成します。
     * @param aID リソースID
     */
    ItemParameter(const int& aID);
    virtual ~ItemParameter() = default;

    /**
     * \~english
     * @brief  get ID.
     * @return ID
     * \~japanese
     * @brief  IDを取得します。
     * @return ID
     */
    const int& id() const;
    /**
     * \~english
     * @brief  get ItemType.
     * @return ItemType
     * \~japanese
     * @brief  アイテム種別を取得します。
     * @return アイテム種別
     */
    const ItemType& type() const;
    /**
     * \~english
     * @brief  get name.
     * @return name
     * \~japanese
     * @brief  名前を取得します。
     * @return 名前
     */
    const String& name() const;
    /**
     * \~english
     * @brief  get size.
     * @return size
     * \~japanese
     * @brief  大きさを取得します。
     * @return 大きさ
     */
    const float& size() const;
    /**
     * \~english
     * @brief  get weight.
     * @return weight
     * \~japanese
     * @brief  重さを取得します。
     * @return 重さ
     */
    const float& weight() const;
    /**
     * \~english
     * @brief  get whether usable.
     * @return whether usable
     * \~japanese
     * @brief  使用可能かを取得します。
     * @return 使用可能か
     */
    const bool& usable() const;
    /**
     * \~english
     * @brief  get whether equppable.
     * @return whether equippable
     * \~japanese
     * @brief  装備可能かを取得します。
     * @return 装備可能か
     */
    const bool& equippable() const;
    /**
     * \~english
     * @brief  get whether reflectable.
     * @return whether reflectable
     * \~japanese
     * @brief  反射可能かを取得します。
     * @return 反射可能か
     */
    const bool& reflec() const;
    /**
     * \~english
     * @brief  get Special efffective.
     * @return Special effective
     * \~japanese
     * @brief  特殊効果を取得します。
     * @return 特殊効果
     */
    const Special& special() const;
    /**
     * \~english
     * @brief  get Item cost
     * @return cost
     * \~japanese
     * @brief  アイテムコストを取得します。
     * @return アイテムコスト
     */
    const int& cost() const;
    /**
     * \~english
     * @brief  get attack power.
     * @return attack power
     * \~japanese
     * @brief  攻撃力を取得します。
     * @return 攻撃力
     */
    const float& attackPower() const;
    /**
     * \~english
     * @brief  get defence power.
     * @return defence power
     * \~japanese
     * @brief  防御力を取得します。
     * @return 防御力
     */
    const float& defencePower() const;
    /**
     * \~english
     * @brief  get effective range.
     * @return effective range
     * \~japanese
     * @brief  有効射程を取得します。
     * @return 有効射程
     */
    const float& effectRange() const;
    /**
     * \~english
     * @brief  get effective angle.
     * @return effective angle
     * \~japanese
     * @brief  有効角を取得します。
     * @return 有効角
     */
    const float& effectAngle() const;
    /**
     * \~english
     * @brief  get stackable number.
     * @return stackable number
     * \~japanese
     * @brief  スタック可能数を取得します。
     * @return スタック可能数
     */
    const int& stack();
    /**
     * \~english
     * @brief  get magazine ID.
     * @return magazine ID
     * \~japanese
     * @brief  マガジンIDを取得します。
     * @return マガジンID
     */
    const int& magazineID();
};

#endif /* ITEMPARAMETER_H */

