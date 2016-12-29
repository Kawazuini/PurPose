/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#ifndef ITEM_H
#define ITEM_H

#include "main.h"

class Character;
class Cube;

class Item {
protected:
    /**
     * @brief \~english  Item List
     * @brief \~japanese アイテムリスト
     */
    static List<Item*> sItems;

    /**
     * @brief \~english  entity
     * @brief \~japanese 実体
     */
    Cube* mEntity;
    /**
     * @brief \~english  whether picked up
     * @brief \~japanese 拾われているかどうか
     */
    bool mPickedUp;

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
public:
    /**
     * @brief \~english  entity size
     * @brief \~japanese 実体の大きさ
     */
    static const float ITEM_SCALE;

    Item();
    Item(const KVector& aPosition);
    Item(const Item& orig) = default;
    virtual ~Item();

    /**
     * @brief \~english  add myself to List.
     * @brief \~japanese リストに自分を追加。
     */
    void add();
    /**
     * @brief \~english  erase myself form List.
     * @brief \~japanese リストから自分を消す。
     */
    void remove();
    /**
     * \~english
     * @brief  get reference of Item List
     * @return reference of Item List
     * \~japanese
     * @brief  アイテムリストの参照を取得します。
     * @return アイテムリストの参照
     */
    static const List<Item*>& itemList();

    /**
     * @brief \~english  pick up Item.
     * @brief \~japanese アイテムを拾います。
     */
    virtual void pickUp();

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
     * @brief  get positon of Item.
     * @return position of Item
     * \~japanese
     * @brief  アイテム座標を取得します。
     * @return アイテム座標
     */
    KVector position() const;
};

#endif /* ITEM_H */

