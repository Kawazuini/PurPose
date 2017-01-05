/**
 * @file   Stage.cpp
 * @brief  Stage
 * @author Maeda Takumi
 */
#include "Stage.h"

#include "Stair.h"
#include "Tile.h"

Stage::Stage() {
    mStart = NULL;
    mStair = NULL;
}

Stage::~Stage() {
    reset();
}

void Stage::set(const Map& aMap) {
    reset();

    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            mMap[i][j] = aMap[i][j];
        }
    }

    generate();
}

void Stage::reset() {
    if (mStart) delete mStart;
    if (mStair) delete mStair;
    for (Tile* i : mTiles) delete i;
    mTiles.clear();
}

void Stage::generate() {
    static const KVector CEILING(0, CEILING_HEIGHT, 0);
    static const KVector FLOOR(0, FLOOR_HEIGHT, 0);

    static const int WALL_U = 1 << 0;
    static const int WALL_D = 1 << 1;
    static const int WALL_L = 1 << 2;
    static const int WALL_R = 1 << 3;

    int wallType[MAP_MAX_WIDTH][MAP_MAX_HEIGHT];

    // 空間に接する壁の確定
    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            wallType[i][j] = 0;
            if (mMap[i][j] == WALL) {
                if (j != 0) if (mMap[i][j - 1] & (LOAD | ROOM)) wallType[i][j] += WALL_U;
                if (j != MAP_MAX_HEIGHT - 1) if (mMap[i][j + 1] & (LOAD | ROOM)) wallType[i][j] += WALL_D;
                if (i != 0) if (mMap[i - 1][j] & (LOAD | ROOM)) wallType[i][j] += WALL_L;
                if (i != MAP_MAX_WIDTH - 1) if (mMap[i + 1][j] & (LOAD | ROOM))wallType[i][j] += WALL_R;
            }
        }
    }

    // 壁情報の接続 & 生成
    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            if (wallType[i][j] & WALL_U) {
                for (int k = 0;; ++k) {
                    if (wallType[i + k][j] & WALL_U) wallType[i + k][j] -= WALL_U;
                    else {
                        KVector ver[4] = {
                            KVector(i + 0, 0, j) * MAP_SCALE + FLOOR,
                            KVector(i + 0, 0, j) * MAP_SCALE + CEILING,
                            KVector(i + k, 0, j) * MAP_SCALE + CEILING,
                            KVector(i + k, 0, j) * MAP_SCALE + FLOOR,
                        };
                        mTiles.push_back(new Tile(ver, k, 1));
                        break;
                    }
                }
            }
            if (wallType[i][j] & WALL_D) {
                for (int k = 0;; ++k) {
                    if (wallType[i + k][j] & WALL_D) wallType[i + k][j] -= WALL_D;
                    else {
                        KVector ver[4] = {
                            KVector(i + 0, 0, j + 1) * MAP_SCALE + CEILING,
                            KVector(i + 0, 0, j + 1) * MAP_SCALE + FLOOR,
                            KVector(i + k, 0, j + 1) * MAP_SCALE + FLOOR,
                            KVector(i + k, 0, j + 1) * MAP_SCALE + CEILING,
                        };
                        mTiles.push_back(new Tile(ver, k, 1));
                        break;
                    }
                }
            }
            if (wallType[i][j] & WALL_L) {
                for (int k = 0;; ++k) {
                    if (wallType[i][j + k] & WALL_L) wallType[i][j + k] -= WALL_L;
                    else {
                        KVector ver[4] = {
                            KVector(i, 0, j + 0) * MAP_SCALE + FLOOR,
                            KVector(i, 0, j + k) * MAP_SCALE + FLOOR,
                            KVector(i, 0, j + k) * MAP_SCALE + CEILING,
                            KVector(i, 0, j + 0) * MAP_SCALE + CEILING,
                        };
                        mTiles.push_back(new Tile(ver, 1, k));
                        break;
                    }
                }
            }
            if (wallType[i][j] & WALL_R) {
                for (int k = 0;; ++k) {
                    if (wallType[i][j + k] & WALL_R) wallType[i][j + k] -= WALL_R;
                    else {
                        KVector ver[4] = {
                            KVector(i + 1, 0, j + 0) * MAP_SCALE + CEILING,
                            KVector(i + 1, 0, j + k) * MAP_SCALE + CEILING,
                            KVector(i + 1, 0, j + k) * MAP_SCALE + FLOOR,
                            KVector(i + 1, 0, j + 0) * MAP_SCALE + FLOOR,
                        };
                        mTiles.push_back(new Tile(ver, 1, k));
                        break;
                    }
                }
            }
        }
    }

    KVector ceiling[4] = {
        KVector(0x00000000000, 0, 0x000000000000) * MAP_SCALE + CEILING,
        KVector(MAP_MAX_WIDTH, 0, 0x000000000000) * MAP_SCALE + CEILING,
        KVector(MAP_MAX_WIDTH, 0, MAP_MAX_HEIGHT) * MAP_SCALE + CEILING,
        KVector(0x00000000000, 0, MAP_MAX_HEIGHT) * MAP_SCALE + CEILING,
    };
    mTiles.push_back(new Tile(ceiling, MAP_MAX_HEIGHT, MAP_MAX_WIDTH));
    KVector floor[4] = {
        KVector(0x00000000000, 0, 0x000000000000) * MAP_SCALE + FLOOR,
        KVector(0x00000000000, 0, MAP_MAX_HEIGHT) * MAP_SCALE + FLOOR,
        KVector(MAP_MAX_WIDTH, 0, MAP_MAX_HEIGHT) * MAP_SCALE + FLOOR,
        KVector(MAP_MAX_WIDTH, 0, 0x000000000000) * MAP_SCALE + FLOOR,
    };
    mTiles.push_back(new Tile(floor, MAP_MAX_WIDTH, MAP_MAX_HEIGHT));

    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            if (mMap[i][j] == STAIR) {
                mStair = new Stair(KVector(i, 0.5, j) * MAP_SCALE + MAP_OFFSET);
                return;
            }
        }
    }
}

KVector Stage::respawn() const {
    Vector<KVector> result;
    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {

            if (mMap[i][j] == ROOM) result.push_back(KVector(i * MAP_SCALE, 0, j * MAP_SCALE));
        }
    }
    return result[random(result.size())] + MAP_OFFSET;
}

const Stair& Stage::stair() const {
    return *mStair;
}

