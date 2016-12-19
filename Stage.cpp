/**
 * @file   Stage.h
 * @brief  Stage
 * @author Maeda Takumi
 */
#include "Stage.h"

#include "Stair.h"
#include "Wall.h"

Stage::Stage(const Map& aMap, const float& aScale) : mScale(aScale) {
    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            mMap[i][j] = aMap[i][j];
        }
    }

    generate();
}

Stage::~Stage() {
    delete mStair;
    for (Wall* i : mWalls) delete i;
}

void Stage::generate() {
    static const int WALL_U = 1;
    static const int WALL_D = 2;
    static const int WALL_L = 4;
    static const int WALL_R = 8;

    int wallType[MAP_MAX_WIDTH][MAP_MAX_HEIGHT];

    // 空間に接する壁の確定
    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            wallType[i][j] = 0;
            if (mMap[i][j] == WALL) {
                if (j != 0) if (mMap[i][j - 1] & (LOAD | ROOM)) wallType[i][j] += WALL_U;
                if (j != MAP_MAX_HEIGHT) if (mMap[i][j + 1] & (LOAD | ROOM)) wallType[i][j] += WALL_D;
                if (i != 0) if (mMap[i - 1][j] & (LOAD | ROOM)) wallType[i][j] += WALL_L;
                if (i != MAP_MAX_WIDTH) if (mMap[i + 1][j] & (LOAD | ROOM))wallType[i][j] += WALL_R;
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
                        mWalls.push_back(new Wall(mScale, KRect(i, j, k, -1)));
                        break;
                    }
                }
            }
            if (wallType[i][j] & WALL_D) {
                for (int k = 0;; ++k) {
                    if (wallType[i + k][j] & WALL_D) wallType[i + k][j] -= WALL_D;
                    else {
                        mWalls.push_back(new Wall(mScale, KRect(i, j, k, 0)));
                        break;
                    }
                }
            }
            if (wallType[i][j] & WALL_L) {
                for (int k = 0;; ++k) {
                    if (wallType[i][j + k] & WALL_L) wallType[i][j + k] -= WALL_L;
                    else {
                        mWalls.push_back(new Wall(mScale, KRect(i, j, -1, k)));
                        break;
                    }
                }
            }
            if (wallType[i][j] & WALL_R) {
                for (int k = 0;; ++k) {
                    if (wallType[i][j + k] & WALL_R) wallType[i][j + k] -= WALL_R;
                    else {
                        mWalls.push_back(new Wall(mScale, KRect(i, j, 0, k)));
                        break;
                    }
                }
            }
        }
    }
    println(mWalls.size());

    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            if (mMap[i][j] == STAIR)
                mStair = new Stair(KVector(i * mScale, 0, j * mScale) + MAP_OFFSET);
        }
    }

    //KVector vertex[4] = {
    //    KVector(0, -0.5, 0) * mScale,
    //    KVector(0, -0.5, mMap->mHeight) * mScale,
    //    KVector(mMap->mWidth, -0.5, mMap->mHeight) * mScale,
    //    KVector(mMap->mWidth, -0.5, 0) * mScale,
    //};
    // new KTile(vertex, mMap->mWidth * 4, mMap->mHeight * 4);

    //KVector vertex2[4] = {
    //    KVector(0, 0.5, 0) * mScale,
    //    KVector(mMap->mWidth, 0.5, 0) * mScale,
    //    KVector(mMap->mWidth, 0.5, mMap->mHeight) * mScale,
    //    KVector(0, 0.5, mMap->mHeight) * mScale,
    //};
    // new KTile(vertex2, mMap->mHeight * 4, mMap->mWidth * 4);
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

