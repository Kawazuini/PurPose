/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#ifndef ITEM_H
#define ITEM_H

#include "Object.h"
#include "PhysicalCube.h"

class Character;

/**
 * @brief  \~english  base of Item
 * @brief  \~japanese アイテム基底
 * @author \~ Maeda Takumi
 */
class Item : public Object {
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
    PhysicalCube mEntity;

    /**
     * @brief \english  whether usable
     * @brief \japanese 使用可能か
     */
    bool mUsable;
    /**
     * @brief \english  whether equippable
     * @brief \japanese 装備可能か
     */
    bool mEquippable;
    /**
     * @brief \english  whether throwable
     * @brief \japanese 投擲可能か
     */
    bool mThrowable;
    /**
     * @brief \~english  whether able to pick up
     * @brief \~japanese 拾えるか
     */
    bool mPickable;

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
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態
     */
    void update(GameState& aState) override;

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
     * @brief \~english  embodying.
     * @brief \~japanese 具現化します。
     */
    void embody();
    /**
     * @brief \~english  hide entity.
     * @brief \~japanese 実体を隠します。
     */
    void hide();

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
     * @brief throw Item.
     * @param aChar Character of throwing
     * \~japanese
     * @brief アイテムを投擲します。
     * @param aChar 投擲キャラクター
     */
    virtual void throwing(Character& aChar);

    /**
     * \~english
     * @brief  get whether usable.
     * @return whether usable
     * \~japanese
     * @brief  使用可能かどうかを取得します。
     * @return 使用可能か
     */
    const bool& usable() const;
    /**
     * \~english
     * @brief  get whether equippable.
     * @return whether equippable
     * \~japanese
     * @brief  装備可能かどうかを取得します。
     * @return 装備可能か
     */
    const bool& equippable() const;
    /**
     * \~english
     * @brief  get whether throwable.
     * @return whether throwable
     * \~japanese
     * @brief  投擲可能かどうかを取得します。
     * @return 投擲可能か
     */
    const bool& throwable() const;
    /**
     * \~english
     * @brief  get whether able to pick up.
     * @return whether able to pick up
     * \~japanese
     * @brief  拾えるかどうかを取得します。
     * @return 拾えるか
     */
    const bool& pickable() const;
    /**
     * \~english
     * @brief  get positon of Item.
     * @return position of Item
     * \~japanese
     * @brief  アイテム座標を取得します。
     * @return アイテム座標
     */
    const KVector& position() const;
};

#endif /* ITEM_H */

