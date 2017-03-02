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
        ITEM_INDEX_BRIEF,
        ITEM_INDEX_SIZE,
        ITEM_INDEX_WEIGHT,
        ITEM_INDEX_USABLE,
        ITEM_INDEX_EQUIPPABLE,
        ITEM_INDEX_REFLECT,
        ITEM_INDEX_SPECIALS,
        ITEM_INDEX_COST,
        ITEM_INDEX_POWER,
        ITEM_INDEX_ERANGE,
        ITEM_INDEX_EANGLE,
        ITEM_INDEX_BURST,
        ITEM_INDEX_STACK,
        ITEM_INDEX_MAGAZINE_ID,
    };
    /* パラメータテーブル */ Vector<String> mParameterTable;

public:
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
     * @brief \~english  brief explanation
     * @brief \~japanese 概要説明
     */
    String mBrief;
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
    List<Special> mSpecials;
    /**
     * @brief \~english  Item const
     * @brief \~japanese コスト
     */
    int mCost;

    /**
     * @brief \~english  equip power
     * @brief \~japanese 装備値
     */
    float mPower;
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
     * @brief \~english  burst number
     * @brief \~japanese 発射数
     */
    int mBurst;
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

    /**
     * \~english
     * @brief generate parameters from resource ID.
     * @param aID resource ID
     * \~japanese
     * @brief リソースIDからパラメータを生成します。
     * @param aID リソースID
     */
    ItemParameter(const int& aID);
    ~ItemParameter() = default;
};

#endif /* ITEMPARAMETER_H */

