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

    void draw() const override;
    void update(GameState& aState) override;

    /**
     * \~english
     * @brief  simultaneous draw of Haribote.(considering camera position)
     * @param  aState state of game
     * \~japanese
     * @brief  ハリボテを一斉描画します。(カメラ位置を考慮)
     * @param  aState ゲーム状態
     */
    static const void HARIBOTE_DRAW(const GameState& aState);

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

