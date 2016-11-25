/**
 * @file Item.h
 * @brief Item
 */
#ifndef ITEM_H
#define ITEM_H

#include "main.h"

class Item {
protected:
    String mName;
    int mCost;
public:
    Item();
    Item(const Item& orig) = delete;
    virtual ~Item();

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
