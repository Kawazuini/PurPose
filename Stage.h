/**
 * @file   Stage.h
 * @brief  Stage
 * @author Maeda Takumi
 */
#ifndef STAGE_H
#define STAGE_H

#include "Map.h"

class GameState;
class Stair;
class Tile;

/**
 * @brief  \~english  Stage of game
 * @brief  \~japanese ステージ
 * @author \~ Maeda Takumi
 */
class Stage : public KNonCopy {
protected:
    /**
     * @brief \~english  start position coordinate
     * @brief \~japanese 開始座標
     */
    KVector* mStart;
    /** 
     * @brief  \~english  rogue's stair
     * @brief  \~japanese 階段
     */
    Stair* mStair;
    /**
     * @brief \~english  Tile objects
     * @brief \~japanese 壁オブジェクト
     */
    List<Tile*> mTiles;
public:
    Stage();
    virtual ~Stage();

    /**
     * @brief \~english  reset Stage.
     * @brief \~japanese ステージをリセットします。
     */
    void reset();
    /**
     * \~english
     * @brief gernerate object of Stage.
     * @param aMap Map info
     * \~japanese
     * @brief ステージのオブジェクトを生成します。
     * @param aMap マップ情報
     */
    void generate(GameState& aState);

    /**
     * \~english
     * @brief  get stair reference.
     * @return stair reference
     * \~japanese
     * @brief  階段の参照を取得します。
     * @return 階段の参照
     */
    Stair& stair();
};

#endif /* STAGE_H */

