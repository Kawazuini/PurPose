/**
 * @file   Haribote.cpp
 * @brief  Haribote
 * @author Maeda Takumi
 */
#ifndef HARIBOTE_H
#define HARIBOTE_H

#include "Object.h"

/**
 * @brief  \~english  Haribote
 * @brief  \~japanese ハリボテ
 * @author \~ Maeda Takumi
 */
class Haribote final : public KDrawer, public Object {
private:
    /* 描画リスト         */ static Vector<Haribote*> sDrawList;
    /* カメラからの距離   */ float mDistance;

    /* ハリボテ           */ KDrawBoard mBoard;
public:
    /**
     * \~english
     * @param aPosition placement position
     * @param aSize     size
     * @param aTexture  texture
     * \~japanese
     * @param aPosition 配置位置
     * @param aSize     大きさ
     * @param aTexture  テクスチャ
     */
    Haribote(
            const KVector& aPosition,
            const float& aSize,
            const KTexture& aTexture
            );
    virtual ~Haribote();

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;
    /**
     * \~english
     * @brief  simultaneous draw of Items.(considering camera position)
     * @param  aState state of game
     * \~japanese
     * @brief  アイテムを一斉描画します。(カメラ位置を考慮)
     * @param  aState ゲーム状態
     */
    static const void HARIBOTE_DRAW(const GameState& aState);

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
     * @brief \~english  add myself to list.
     * @brief \~japanese リストに自分を追加します。
     */
    void add();
    /**
     * @brief \~english  remove myself form list.
     * @brief \~japanese リストから自分を消します。
     */
    void remove();

    /**
     * \~english
     * @brief translate the Haribote.
     * @param aVec destination coordinates
     * \~japanese
     * @brief ハリボテを移動させます。
     * @param aVec 移動先座標
     */
    void translate(const KVector& aVec);

    /**
     * \~english
     * @brief  get normal vector.
     * @return normal vector
     * \~japanese
     * @brief  法線ベクトルを取得します。
     * @return 法線ベクトル
     */
    const KVector& normal() const;
};

#endif /* HARIBOTE_H */

