/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#ifndef ITEM_H
#define ITEM_H

#include "main.h"

class Character;

class Item {
protected:
    /**
     * @brief \english  whether usable
     * @brief \japanese 使用可能か
     */
    bool mUsable;
    /**
     * @brief \english  whether equippable
     * @brief \japanese 装備可能か
     * @see   \~ Equipment
     */
    bool mEquippable;

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
    int mUseCost;
    /**
     * @brief \~english  equipping cost of Item
     * @brief \~japanese アイテム装備コスト
     */
    int mEquipCost;
public:
    Item();
    Item(const Item& orig) = default;
    virtual ~Item() = default;

    /**
     * \~english
     * @brief use Item.
     * @param aChar Character of using
     * \~japanese
     * @brief アイテムを使用します。
     * @param aChar 使用キャラクター
     */
    virtual void use(Character& aChar);

    /**
     * \~english
     * @brief equip Item.
     * @param aChar Character of equipping
     * \~japanese
     * @brief アイテムを装備します。
     * @param aChar 装備キャラクター
     */
    virtual void equip(Character& aChar) {
    };

    
    /**
     * \~english
     * @brief  get whether usable.
     * @return whether usable
     * \~japanese
     * @brief  使用可能かどうかを取得します。
     * @return 使用可能か
     */
    bool usable() const;
    /**
     * \~english
     * @brief  get whether equippable.
     * @return whether equippable
     * \~japanese
     * @brief  使用可能かどうかを取得します。
     * @return 使用可能か
     */
    bool equippable() const;
    /**
     * \~english
     * @brief  get name of Item.
     * @return name of Item
     * \~japanese
     * @brief  アイテム名を取得します。
     * @return アイテム名
     */
    String name() const;
    /**
     * \~english
     * @brief  get using cost.
     * @return using cost
     * \~japanese
     * @brief  使用コストを取得します。
     * @return 使用コスト
     */
    int useCost() const;
    /**
     * \~english
     * @brief  get equipping cost.
     * @return equipping cost
     * \~japanese
     * @brief  装備コストを取得します。
     * @return 装備コスト
     */
    int equipCost() const;
};

#endif /* ITEM_H */

