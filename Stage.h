/**
 * @file   Stage.h
 * @brief  Stage
 * @author Maeda Takumi
 */
#ifndef STAGE_H
#define STAGE_H

#include "Map.h"

class Stair;
class Tile;

/**
 * @brief \~english  Stage of game
 * @brief \~japanese ステージ
 * @author \~ Maeda Takumi
 */
class Stage : public KNonCopy {
protected:
    /**
     * @brief \~english  array of Map information
     * @brief \~japanese マップ情報配列
     */
    Map mMap;

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
    Vector<Tile*> mTiles;

    /**
     * @brief \~english  gernerate object of stage.
     * @brief \~japanese ステージのオブジェクトを生成します。
     */
    void generate();
public:
    Stage(const Map& aMap);
    virtual ~Stage();

    /**
     * \~english
     * @brief  get respawnable coordinate.
     * @return respawnable coordinate
     * \~japanese
     * @brief  リスポーン可能座標を取得します。
     * @return リスポーン可能座標
     */
    KVector respawn() const;

    /**
     * \~english
     * @brief  get stair reference.
     * @return stair reference
     * \~japanese
     * @brief  階段の参照を取得します。
     * @return 階段の参照
     */
    const Stair& stair() const;
};

#endif /* STAGE_H */

