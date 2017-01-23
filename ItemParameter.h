/**
 * @file   ItemParameter.h
 * @brief  ItemParameter
 * @author Maeda Takumi
 */
#ifndef ITEMPARAMETER_H
#define ITEMPARAMETER_H

#include "Special.h"

/**
 * @brief  \~english  Parameter of Item
 * @brief  \~japanese アイテムパラメータ
 * @author \~ Maeda Takumi
 */
class ItemParameter {
private:
    static const int ITEM_PARAMETER_INDEX_NAME;
    static const int ITEM_PARAMETER_INDEX_USABLE;
    static const int ITEM_PARAMETER_INDEX_EQUIPPABLE;
    static const int ITEM_PARAMETER_INDEX_THROWABLE;
    static const int ITEM_PARAMETER_INDEX_PICKABLE;
    static const int ITEM_PARAMETER_INDEX_WEIGHT;
    static const int ITEM_PARAMETER_INDEX_SPECIAL;
    static const int ITEM_PARAMETER_INDEX_SPPOINT;
public:
    /**
     * @brief \~english  parameter table(able to manage additional information)
     * @brief \~japanese パラメータテーブル(追加情報を管理できます。)
     */
    Vector<String> mParameterTable;

    int mID; ///< ID

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
     * @brief \~english  special effect
     * @brief \~japanese 特殊効果
     */
    Special mSpecial;

    /**
     * @brief \~english  Item weight
     * @brief \~japanese アイテム重量
     */
    float mWeight;

    ItemParameter() = default;
    ItemParameter(const int& aID);
    virtual ~ItemParameter() = default;
};

#endif /* ITEMPARAMETER_H */

