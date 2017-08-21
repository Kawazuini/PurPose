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
#include "GameState.h"
#include "Haribote.h"

class Character;

/**
 * @brief  \~english  base of Item
 * @brief  \~japanese アイテム基底
 * @author \~ Maeda Takumi
 */
class Item final : private KDrawer, public Object {
public:
    /// @brief \~english  pickable range
    /// @brief \~japanese 取得可能範囲
    static const float PICKABLE_RANGE;
private:
    /* アイテムパラメータ */ ItemParameter mItemParameter;

    /* テクスチャサイズ   */ static const int TEX_SIZE;
    /* テクスチャ         */ KTexture mTexture;
    /* ハリボテオフセット */ KVector mOffset;
    /* ハリボテ           */ Haribote mHaribote;
    /* 描画するか         */ bool mDraw;
public:
    /// @brief \~english  entity
    /// @brief \~japanese 実体
    PhysicalCube mEntity;
    /// @brief \~english  Character of throwing
    /// @brief \~japanese 投擲キャラクター
    Character* mOwener;

    /// @brief \~english  Item Stack(Arrow and Bullet)
    /// @brief \~japanese アイテムスタック(矢と弾丸)
    List<Item*> mMagazine;

    /// @brief \~english  whether able to pick up
    /// @brief \~japanese 拾えるか
    bool mPickable;
    /// @brief \~english  whether equipped
    /// @brief \~japanese 装備されているか
    bool mEquipped;
    /// @brief \~english  whether able to take off
    /// @brief \~japanese 装備を外せるか
    bool mTakeoffable;

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
     * @param aID        resource ID
     * @param aPosition  generating coordinate
     * \~japanese
     * @param aID        リソースID
     * @param aPosition  生成座標
     */
    Item(const int& aID, const KVector& aPosition);
    virtual ~Item();

    void draw() const override;
    void update(GameState& aState) override;

    /**
     * \~english
     * @brief activate special effects.
     * @param aSCharacter subject Character
     * @param aOCharacter object  Character
     * \~japanese
     * @brief 特殊効果を発動させます。
     * @param aSCharacter 主体キャラクター
     * @param aOCharacter 対象キャラクター
     */
    void special(Character* aSCharacter = nullptr, Character* aOCharacter = nullptr);

    /// @brief \~english  embodying.
    /// @brief \~japanese 具現化します。
    void embody();
    /// @brief \~english  hide entity.
    /// @brief \~japanese 実体を隠します。
    void hide();

    /**
     * \~english
     * @brief  calculate whether able to pick up.
     * @return whether able to pick up
     * \~japanese
     * @brief  拾えるかどうかを計算します。
     * @return 拾えるかどうか
     */
    const bool pickable() const;

    const ItemParameter& param() const;
};

#endif /* ITEM_H */

