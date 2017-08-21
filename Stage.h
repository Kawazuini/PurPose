/**
 * @file   Stage.h
 * @brief  Stage
 * @author Maeda Takumi
 */
#ifndef STAGE_H
#define STAGE_H

#include "Event.h"
#include "Map.h"

class GameState;
class GameManager;
class Stair;
class Tile;

/**
 * @brief  \~english  Stage of game
 * @brief  \~japanese ステージ
 * @author \~ Maeda Takumi
 */
class Stage final : public KNonCopy {
private:
    /* 開始座標       */ KVector* mStart;
    /* 階段           */ Stair* mStair;
    /* 壁オブジェクト */ List<Tile*> mTiles;
public:
    Stage();
    virtual ~Stage();

    /// @brief \~english  reset Stage.
    /// @brief \~japanese ステージをリセットします。
    void reset();
    /**
     * \~english
     * @brief gernerate object of Stage.
     * @param aState   game state
     * @param aManager geme info
     * @param aFunc    stair event processing function
     * \~japanese
     * @brief ステージのオブジェクトを生成します。
     * @param aState   ゲーム状態
     * @param aManager ゲーム情報
     * @param aFunc    階段イベント処理関数
     */
    void generate(
            GameState& aState,
            GameManager& aManager,
            const Event::EventFunction& aFunc
            );

    Stair& stair();
};

#endif /* STAGE_H */

