/**
 * @file   Stair.h
 * @brief  Stair
 * @author Maeda Takumi
 */
#ifndef STAIR_H
#define STAIR_H

#include "Event.h"

/**
 * @brief  \~english  rogue's stair
 * @brief  \~japanese 階段
 * @author \~ Maeda Takumi
 */
class Stair final : public KDrawer, public Event {
private:
    /* 位置座標 */ KVector mPosition;
    /* 描画頂点 */ Vector<KVector> mVertex;
    /* 描画模様 */ KTexture mTexture;

    /* 描画頂点を回転させます。 */ void rotate(const KQuaternion& aQuater);
public:
    /**
     * \~english
     * @param aManager  target of event function
     * @param aFunction  execution function when event occurrence
     * @param aPosition specified position
     * \~japanese
     * @param aManager  イベント対象
     * @param aFunction  イベント発生時実行関数
     * @param aPosition 配置座標
     */
    Stair(
            GameManager& aManager,
            const Event::EventFunction& aFunction,
            const KVector& aPosition
            );
    virtual ~Stair() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;
    /**
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態の情報
     */
    void update(GameState& aState) override;

    /**
     * \~english
     * @brief  calculate whether event occurrence condition is satisfied.
     * @param  aState information of game state
     * @return whether event occurrence condition is satisfied
     * \~japanese
     * @brief  イベント発生条件を満たしているかを計算します。
     * @param  aState ゲーム状態の情報
     * @return イベント発生条件を満たしているか
     */
    bool condition(const GameState& aState) const override;

    /**
     * \~english
     * @brief  get position coordinate.
     * @return position coordinate
     * \~japanese
     * @brief  位置座標を取得します。
     * @return 位置座標
     */
    const KVector& position() const;
};

#endif /* STAIR_H */

