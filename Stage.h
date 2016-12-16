/**
 * @file   Stage.h
 * @brief  Stage
 * @author Maeda Takumi
 */
#ifndef STAGE_H
#define STAGE_H

#include "Map.h"

class Wall;

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
     * @brief \~english  scale of entity from information
     * @brief \~japanese 情報に対する実体の倍率
     */
    const float mScale;

    /**
     * @brief \~english  start position coordinate
     * @brief \~japanese 開始座標
     */
    KVector* mStart;
    /**
     * @brief \~english  Wall objects
     * @brief \~japanese 壁オブジェクト
     */
    Vector<Wall*> mWalls;

    /**
     * @brief \~english  gernerate object of stage.
     * @brief \~japanese ステージのオブジェクトを生成します。
     */
    void generate();
public:
    Stage(const Map& aMap, const float& aScale);
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
};

#endif /* STAGE_H */

