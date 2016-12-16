/**
 * @file   Map.h
 * @brief  Map
 * @author Maeda Takumi
 */
#ifndef MAP_H
#define MAP_H

#include "main.h"

static const KVector X(1, 0, 0); ///< x軸の単位ベクトル
static const KVector Y(0, 1, 0); ///< y軸の単位ベクトル

/** @brief 方向 */
typedef enum {
    UP = 0,
    DOWN = 1,
    LEFT = 2,
    RIGHT = 3,
} Direction;

/** @brief マップの構成要素 */
typedef enum {
    /** @brief 道       */ LOAD = 1,
    /** @brief 壁       */ WALL = LOAD * 2,
    /** @brief 部屋     */ ROOM = WALL * 2,
    /** @brief スタート */ START = ROOM * 2 | ROOM,

    /** @brief どれでもない(処理用) */ OTHER = ROOM * 4,
} MapChip;

static const int MAP_MAX_WIDTH = 100;
static const int MAP_MAX_HEIGHT = 100;

typedef MapChip Map[MAP_MAX_WIDTH][MAP_MAX_HEIGHT];

#endif /* MAP_H */

