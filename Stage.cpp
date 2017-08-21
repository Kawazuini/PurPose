/**
 * @file   Stage.cpp
 * @brief  Stage
 * @author Maeda Takumi
 */
#include "Stage.h"

#include "GameState.h"
#include "Stair.h"
#include "Tile.h"

Stage::Stage() :
mStart(nullptr),
mStair(nullptr) {
}

Stage::~Stage() {
    reset();
}

void Stage::reset() {
    if (mStart) delete mStart;
    if (mStair) delete mStair;
    while (!mTiles.empty()) {
        delete mTiles.front();
        mTiles.pop_front();
    }
}

void Stage::generate(
        GameState& aState,
        GameManager& aManager,
        const Event::EventFunction& aFunc
        ) {
    static const KVector CEILING(0, CEILING_HEIGHT, 0);
    static const KVector FLOOR(0, FLOOR_HEIGHT, 0);

    static const int WALL_U(1 << 0);
    static const int WALL_D(1 << 1);
    static const int WALL_L(1 << 2);
    static const int WALL_R(1 << 3);

    int wallType[MAP_MAX_WIDTH][MAP_MAX_HEIGHT];

    // 空間に接する壁の確定
    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            wallType[i][j] = 0;
            if (aState.mMap[i][j] == WALL) {
                if (j != 0) if (aState.mMap[i][j - 1] & (LOAD | ROOM)) wallType[i][j] += WALL_U;
                if (j != MAP_MAX_HEIGHT - 1) if (aState.mMap[i][j + 1] & (LOAD | ROOM)) wallType[i][j] += WALL_D;
                if (i != 0) if (aState.mMap[i - 1][j] & (LOAD | ROOM)) wallType[i][j] += WALL_L;
                if (i != MAP_MAX_WIDTH - 1) if (aState.mMap[i + 1][j] & (LOAD | ROOM))wallType[i][j] += WALL_R;
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
                        Vector<KVector> ver{
                            KVector(i + 0, 0, j) * MAP_SCALE + FLOOR,
                            KVector(i + 0, 0, j) * MAP_SCALE + CEILING,
                            KVector(i + k, 0, j) * MAP_SCALE + CEILING,
                            KVector(i + k, 0, j) * MAP_SCALE + FLOOR,
                        };
                        aState.addWall(*(new KPolygon(ver)));
                        mTiles.push_back(new Tile(ver, k, 1));
                        break;
                    }
                }
            }
            if (wallType[i][j] & WALL_D) {
                for (int k = 0;; ++k) {
                    if (wallType[i + k][j] & WALL_D) wallType[i + k][j] -= WALL_D;
                    else {
                        Vector<KVector> ver{
                            KVector(i + 0, 0, j + 1) * MAP_SCALE + CEILING,
                            KVector(i + 0, 0, j + 1) * MAP_SCALE + FLOOR,
                            KVector(i + k, 0, j + 1) * MAP_SCALE + FLOOR,
                            KVector(i + k, 0, j + 1) * MAP_SCALE + CEILING,
                        };
                        aState.addWall(*(new KPolygon(ver)));
                        mTiles.push_back(new Tile(ver, k, 1));
                        break;
                    }
                }
            }
            if (wallType[i][j] & WALL_L) {
                for (int k = 0;; ++k) {
                    if (wallType[i][j + k] & WALL_L) wallType[i][j + k] -= WALL_L;
                    else {
                        Vector<KVector> ver{
                            KVector(i, 0, j + 0) * MAP_SCALE + FLOOR,
                            KVector(i, 0, j + k) * MAP_SCALE + FLOOR,
                            KVector(i, 0, j + k) * MAP_SCALE + CEILING,
                            KVector(i, 0, j + 0) * MAP_SCALE + CEILING,
                        };
                        aState.addWall(*(new KPolygon(ver)));
                        mTiles.push_back(new Tile(ver, 1, k));
                        break;
                    }
                }
            }
            if (wallType[i][j] & WALL_R) {
                for (int k = 0;; ++k) {
                    if (wallType[i][j + k] & WALL_R) wallType[i][j + k] -= WALL_R;
                    else {
                        Vector<KVector> ver{
                            KVector(i + 1, 0, j + 0) * MAP_SCALE + CEILING,
                            KVector(i + 1, 0, j + k) * MAP_SCALE + CEILING,
                            KVector(i + 1, 0, j + k) * MAP_SCALE + FLOOR,
                            KVector(i + 1, 0, j + 0) * MAP_SCALE + FLOOR,
                        };
                        aState.addWall(*(new KPolygon(ver)));
                        mTiles.push_back(new Tile(ver, 1, k));
                        break;
                    }
                }
            }
        }
    }

    Vector<KVector> ceiling{
        KVector(0x00000000000, 0, 0x000000000000) * MAP_SCALE + CEILING,
        KVector(MAP_MAX_WIDTH, 0, 0x000000000000) * MAP_SCALE + CEILING,
        KVector(MAP_MAX_WIDTH, 0, MAP_MAX_HEIGHT) * MAP_SCALE + CEILING,
        KVector(0x00000000000, 0, MAP_MAX_HEIGHT) * MAP_SCALE + CEILING,
    };
    aState.addWall(*(new KPolygon(ceiling)));
    mTiles.push_back(new Tile(ceiling, MAP_MAX_HEIGHT, MAP_MAX_WIDTH));
    Vector<KVector> floor{
        KVector(0x00000000000, 0, 0x000000000000) * MAP_SCALE + FLOOR,
        KVector(0x00000000000, 0, MAP_MAX_HEIGHT) * MAP_SCALE + FLOOR,
        KVector(MAP_MAX_WIDTH, 0, MAP_MAX_HEIGHT) * MAP_SCALE + FLOOR,
        KVector(MAP_MAX_WIDTH, 0, 0x000000000000) * MAP_SCALE + FLOOR,
    };
    aState.addWall(*(new KPolygon(floor)));
    mTiles.push_back(new Tile(floor, MAP_MAX_WIDTH, MAP_MAX_HEIGHT));

    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            if (aState.mMap[i][j] == STAIR) {
                mStair = new Stair(aManager, aFunc, KVector(i, 0.5, j) * MAP_SCALE + MAP_OFFSET);
                return;
            }
        }
    }
}

Stair& Stage::stair() {
    return *mStair;
}


