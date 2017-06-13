/**
 * @file   Event.h
 * @breif  Event
 * @author Maeda Takumi
 */
#ifndef EVENT_H
#define EVENT_H

#include "Object.h"

class GameManager;

/**
 * @brief  \~english  Event
 * @brief  \~japanese イベント
 * @author \~ Maeda Takumi
 */
class Event : public Object {
public:
    /**
     * @brief \~english  function for Event processing
     * @brief \~japanese イベント処理関数
     */
    using EventFunction = void (GameManager::*)();
private:
    /* 処理対象           */ GameManager& mGameManager;
    /* イベント処理関数   */ EventFunction mFunction;
    /* イベント有効フラグ */ bool mActive;
protected:
    /**
     * \~english
     * @param aManager  target of event function
     * @param aFunction  execution function when event occurrence
     * \~japanese
     * @param aManager  イベント対象
     * @param aFunction  イベント発生時実行関数
     */
    Event(
            GameManager& aManager,
            const EventFunction& aFunction
            );
    virtual ~Event() = default;
public:
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
    virtual bool condition(const GameState& aState) const {
    };

    /**
     * @brief \~english  enable Event
     * @brief \~japanese イベントを有効化します。
     */
    void enable();
    /**
     * @brief \~english  disable Event
     * @brief \~japanese イベントを無効化します。
     */
    void disable();

    /**
     * \~english
     * @brief  get flag of event activate.
     * @return flag of event activate
     * \~japanese
     * @brief  イベントの有効フラグを取得します。
     * @return イベントの有効フラグ
     */
    const bool& isActive() const;
};

#endif /* EVENT_H */

