/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#ifndef ITEM_H
#define ITEM_H

#include "ItemParameter.h"
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
     * @brief \~english  entity
     * @brief \~japanese 実体
     */
    PhysicalCube mEntity;
    /**
     * @brief \~english  Character of throwing
     * @brief \~japanese 投擲キャラクター
     */
    Character* mOwener;
public:
    /**
     * @brief \~english  entity size
     * @brief \~japanese 実体の大きさ
     */
    static const float ITEM_SCALE;

    /**
     * @brief \~english  Item parameter
     * @brief \~japanese アイテムパラメータ
     */
    ItemParameter mItemParameter;

    /**
     * \~english
     * @brief generate Item from resource ID.
     * @param aID resource ID
     * \~japanese
     * @brief リソースIDからアイテムを生成します。
     * @param aID リソースID
     */
    Item(const int& aID);
    /**
     * \~english
     * @brief generate Item from resource ID.
     * @param aID       resource ID
     * @param aPosition generating coordinate
     * \~japanese
     * @brief リソースIDからアイテムを生成します。
     * @param aID       リソースID
     * @param aPosition 生成座標
     */
    Item(const int& aID, const KVector& aPosition);
    virtual ~Item() = default;

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
     * @brief throw Item.
     * @param aChar Character of throwing
     * \~japanese
     * @brief アイテムを投擲します。
     * @param aChar 投擲キャラクター
     */
    virtual void throwing(Character& aChar);

    /**
     * \~english
     * @brief  get whether able to pick up.
     * @return whether able to pick up
     * \~japanese
     * @brief  拾えるかどうかを取得します。
     * @return 拾えるか
     */
    const bool pickable() const;
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

