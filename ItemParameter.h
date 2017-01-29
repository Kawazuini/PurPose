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
    static const int ITEM_INDEX_TYPE;
    static const int ITEM_INDEX_NAME;
    static const int ITEM_INDEX_USABLE;
    static const int ITEM_INDEX_EQUIPPABLE;
    static const int ITEM_INDEX_THROWABLE;
    static const int ITEM_INDEX_PICKABLE;
    static const int ITEM_INDEX_WEIGHT;
    static const int ITEM_INDEX_SPECIAL;
    static const int ITEM_INDEX_SPPOINT;
    static const int ITEM_INDEX_LAST;
    static const int ITEM_INDEX_ATTACK;
    static const int ITEM_INDEX_DEFENSE;
    static const int ITEM_INDEX_ERANGE;
    static const int ITEM_INDEX_EANGLE;
public:
    /**
     * @brief \~english  parameter table(able to manage additional information)
     * @brief \~japanese パラメータテーブル(追加情報を管理できます。)
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
     * @brief \~english  whether throwable
     * @brief \~japanese 投擲可能か
     */
    bool mThrowable;
    /**
     * @brief \~english  whether able to pick up
     * @brief \~japanese 拾えるか
     */
    bool mPickable;

    /**
     * @brief \~english  Item weight
     * @brief \~japanese アイテム重量
     */
    float mWeight;

    /**
     * @brief \~english  special effect
     * @brief \~japanese 特殊効果
     */
    Special mSpecial;

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
     * \~english
     * @brief generate parameters from resource ID.
     * @param aID resource ID
     * \~japanese
     * @brief リソースIDからパラメータを生成します。
     * @param aID リソースID
     */
    ItemParameter(const int& aID);
    virtual ~ItemParameter() = default;
};

#endif /* ITEMPARAMETER_H */

