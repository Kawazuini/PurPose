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
    /** 道       */ LOAD = 1 << 0,
    /** 壁       */ WALL = 1 << 1,
    /** 部屋     */ ROOM = 1 << 2,
    /** 階段     */ STAIR = 1 << 3 | ROOM,
    /** スタート */ START = 1 << 4 | ROOM,

    /** どれでもない(処理用) */
    OTHER = 1 << 5,
} MapChip;

static const float MAP_SCALE = 5.0f;
static const float CEILING_HEIGHT = MAP_SCALE;
static const float FLOOR_HEIGHT = 0.0f;
static const int MAP_MAX_WIDTH = 100;
static const int MAP_MAX_HEIGHT = 100;
static const KVector MAP_OFFSET(MAP_SCALE / 2.0f, 0, MAP_SCALE / 2.0f);

/**
 * @brief \~english  Map information
 * @brief \~japanese マップ情報
 */
using Map = MapChip[MAP_MAX_WIDTH][MAP_MAX_HEIGHT];

#endif /* MAP_H */

