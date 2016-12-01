/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#ifndef ITEM_H
#define ITEM_H

#include "main.h"

class Item : private KNonCopy {
protected:
    /**
     * @brief \~english  name of Item
     * @brief \~japanese アイテム名
     */
    String mName;
    /**
     * @brief \~english  weight of Item
     * @brief \~japanese アイテム重量
     */
    float mWeight;
    /**
     * @brief \~english  using cost of Item
     * @brief \~japanese アイテム使用コスト
     */
    int mCost;
public:
    Item() = default;
    virtual ~Item() = default;

    /**
     * @brief 使用
     * @return 使用できたか
     */
    virtual bool use() {
    };

    /**
     * @brief 名前の取得
     * @return 名前
     */
    String name() const;
    /**
     * @brief コストの取得
     * @return コスト
     */
    int cost() const;
};

#endif /* ITEM_H */

