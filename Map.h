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

/** @brief マップの構成要素 */
typedef enum {
    /** 道       */ LOAD = 1,
    /** 壁       */ WALL = LOAD * 2,
    /** 部屋     */ ROOM = WALL * 2,
    /** 階段     */ STAIR = ROOM * 2 | ROOM,
    /** スタート */ START = ROOM * 4 | ROOM,

    /** どれでもない(処理用) */ OTHER = ROOM * 4,
} MapChip;

static const float MAP_SCALE = 16.0f;
static const int MAP_MAX_WIDTH = 100;
static const int MAP_MAX_HEIGHT = 100;
static const KVector MAP_OFFSET(MAP_SCALE / 2.0f, 0, MAP_SCALE / 2.0f);

typedef MapChip Map[MAP_MAX_WIDTH][MAP_MAX_HEIGHT];

#endif /* MAP_H */

