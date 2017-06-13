/**
 * @file   Money.h
 * @brief  Money
 * @author Maeda Takumi
 */
#ifndef MONEY_H
#define MONEY_H

#include "Event.h"
#include "Haribote.h"

/**
 * @brief  \~english  Money
 * @brief  \~japanese お金
 * @author \~ Maeda Takumi
 */
class Money : public Event {
private:
    /* 設置位置           */ KVector mPosition;

    /* テクスチャサイズ */ static const int TEX_SIZE;
    /* テクスチャ画像   */ KImage mImage;
    /* テクスチャ       */ KTexture mTexture;
    /* ハリボテ         */ Haribote mHaribote;
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
    Money(
            GameManager& aManager,
            const EventFunction& aFunction,
            const KVector& aPosition
            );
    virtual ~Money() = default;

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
};

#endif /* MONEY_H */

