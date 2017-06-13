/**
 * @file   Merchant.h
 * @brief  Merchant
 * @author Maeda Takumi
 */
#ifndef MERCHANT_H
#define MERCHANT_H

#include "BackPack.h"
#include "Character.h"
#include "Event.h"

/**
 * @brief  \~english  Character of Merchant
 * @brief  \~japanese 商人
 * @author \~ Maeda Takumi
 */
class Merchant final : public Character, public Event {
private:
    /* 商品袋 */ BackPack mBackPack;
public:
    /**
     * \~english
     * @param aManager  target of event function
     * @param aFunction  execution function when event occurrence
     * \~japanese
     * @param aManager  イベント対象
     * @param aFunction  イベント発生時実行関数
     */
    Merchant(
            GameManager& aManager,
            const EventFunction& aFunction
            );
    virtual ~Merchant() = default;

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

#endif /* MERCHANT_H */

