/**
 * @file MapCreater.cpp
 * @brief Map
 */
#include "Map.h"

#include "Wall.h"

void Map::createWall() {
    static const int WALL_U = 1;
    static const int WALL_D = 2;
    static const int WALL_L = 4;
    static const int WALL_R = 8;

    int mW = mMap->mWidth, mH = mMap->mHeight;
    int chipX = mMap->mIndexX, chipY = mMap->mIndexY;

    Info<int> wallType(mW, mH);
    wallType.init(0);

    MapChip* chip = mMap->mInfo;
    int* type = wallType.mInfo;


    // 空間に接する壁の確定
    for (int i = 0, i_e = mMap->mSize; i < i_e; ++i, ++chip, ++type) {
        if (*chip == WALL) {
            if (i % mH != 0) if (*(chip - chipY) & (LOAD | ROOM)) *type += WALL_U;
            if (i % mH < mH - 1) if (*(chip + chipY) & (LOAD | ROOM)) *type += WALL_D;
            if (i / mH != 0) if (*(chip - chipX) & (LOAD | ROOM)) *type += WALL_L;
            if (i / mH < mW - 1) if (*(chip + chipX) & (LOAD | ROOM)) *type += WALL_R;
        }
    }

    int* pri = wallType.mInfo;
    for (int x = 0; x < wallType.mWidth; ++x) {
        for (int y = 0; y < wallType.mHeight; ++y, ++pri) {
            printf("%2d", *pri);
        }
        println("");
    }
    println("");

    // 壁情報の接続
    type = wallType.mInfo;
    for (int i = 0, i_e = wallType.mWidth; i < i_e; ++i) {
        for (int j = 0, j_e = wallType.mHeight; j < j_e; ++j, ++type) {
            KRect wall; // (startX, startY, width, surface) or (startX, startY, surface, height)
            if (*type & WALL_U) {
                for (int k = 0;; ++k) {
                    int* target = type + chipX * k;
                    if (*target & WALL_U) *target -= WALL_U;
                    else {
                        mWallInfo.push_back(KRect(i, j, k, -1));
                        break;
                    }
                }
            }
            if (*type & WALL_D) {
                for (int k = 0;; ++k) {
                    int* target = type + chipX * k;
                    if (*target & WALL_D) *target -= WALL_D;
                    else {
                        mWallInfo.push_back(KRect(i, j, k, 0));
                        break;
                    }
                }
            }
            if (*type & WALL_L) {
                for (int k = 0;; ++k) {
                    int* target = type + chipY * k;
                    if (*target & WALL_L) *target -= WALL_L;
                    else {
                        mWallInfo.push_back(KRect(i, j, -1, k));
                        break;
                    }
                }
            }
            if (*type & WALL_R) {
                for (int k = 0;; ++k) {
                    int* target = type + chipY * k;
                    if (*target & WALL_R) *target -= WALL_R;
                    else {
                        mWallInfo.push_back(KRect(i, j, 0, k));
                        break;
                    }
                }
            }
        }
    }
    println(mWallInfo.size());
}

void Map::define() {
    createWall();

    for (KRect i : mWallInfo) mWalls.push_back(new Wall(*this, i));
    MapChip* chip = mMap->mInfo;

    KVector vertex[4] = {
        KVector(0, -0.5, 0) * mScale,
        KVector(0, -0.5, mMap->mHeight) * mScale,
        KVector(mMap->mWidth, -0.5, mMap->mHeight) * mScale,
        KVector(mMap->mWidth, -0.5, 0) * mScale,
    };
   // new KTile(vertex, mMap->mWidth * 4, mMap->mHeight * 4);

    KVector vertex2[4] = {
        KVector(0, 0.5, 0) * mScale,
        KVector(mMap->mWidth, 0.5, 0) * mScale,
        KVector(mMap->mWidth, 0.5, mMap->mHeight) * mScale,
        KVector(0, 0.5, mMap->mHeight) * mScale,
    };
   // new KTile(vertex2, mMap->mHeight * 4, mMap->mWidth * 4);
}

Map::MapInfo& Map::STRING_MAP(const Array<String>& aMap) {
    int width = split(aMap[0], ",").size(), height = aMap.size();
    MapInfo* map = new MapInfo(width, height);

    MapChip* chip = map->mInfo;
    for (String i : aMap) {
        Array<String> column = split(i, ",");
        for (String j : column) {
            switch (toInt(j)) {
                case M_START: *chip = START;
                    break;
                case M_ROOM: *chip = ROOM;
                    break;
                case M_WALL: *chip = WALL;
                    break;
                default: *chip = LOAD;
            }
            chip++;
        }
    }
    return *map;
}

Map::MapInfo& Map::RANDOM_MAP() {
    int width = random(MAX_WIDTH - MIN_WIDTH) + MIN_WIDTH;
    int height = random(MAX_HEIGHT - MIN_HEIGHT) + MIN_HEIGHT;

    MapInfo pole(width, height); // 支点情報
    pole.init(LOAD);
    MapInfo* map = new MapInfo(width * 2 + 3, height * 2 + 3);
    map->init(LOAD);

    // 外壁生成
    MapChip* tmp = map->mInfo;
    int mW = map->mWidth, mH = map->mHeight;
    for (int i = 0, i_e = map->mSize; i < i_e; ++i, ++tmp) {
        if (i / mH == 0 || i / mH == mW - 1 || i % mH == 0 || i % mH == mH - 1) *tmp = WALL;
    }

    // 支点抽選番号の準備    
    Info<int> _pole(width, height); // 支点抽選番号
    int* points = _pole.mInfo;
    for (int i = 0; i < _pole.mSize; ++i, ++points) *points = i;

    // 壁伸ばし法
    int leftPole = _pole.mSize; // 支点の残り数
    while (leftPole) { // 支点がなくなるまで続ける
        // 次の支点の決定
        int next = *(_pole.mInfo + random(leftPole));
        KVector point = KVector(next / height, next % height);

        // 壁伸ばし探索
        bool hit[4] = {false, false, false, false};
        bool grow = wallGrow(map, pole, point, hit);
        // 壁の決定 or 取り消し
        tmp = map->mInfo;
        for (int i = 0, i_e = map->mSize; i < i_e; ++i, ++tmp) if (*tmp == OTHER) *tmp = (grow ? WALL : LOAD);

        // 未使用支点情報の更新
        tmp = pole.mInfo;
        for (int i = 0, i_e = pole.mSize, rest = 0; i < i_e; ++i, ++tmp) {
            if (*tmp == WALL) rest++; // 使用支点数
            if (*tmp == OTHER) {
                if (grow) {
                    *tmp = WALL;
                    // 支点抽選番号をずらす
                    points = _pole.mInfo + i - rest;
                    for (int j = i - rest; j < leftPole; ++j, ++points) *points = *(points + 1);
                    rest++;
                    leftPole--;
                } else *tmp = LOAD;
            }
        }
    }

    makeRoom(map);
    clean(map);

    // 開始座標の確定
    tmp = map->mInfo;
    for (int i = 0, i_e = map->mSize; i < i_e; ++i, ++tmp) {
        if (*tmp == ROOM) {
            *tmp = START;
            break;
        }
    }

    MapChip* te = map->mInfo;
    for (int i = 0; i < map->mWidth; ++i) {
        for (int j = 0; j < map->mHeight; ++j, ++te) {
            if (*te == WALL) print("壁");
            else if (*te == ROOM) print("　");
            else print("　");
        }
        println("");
    }

    return *map;
}

bool Map::wallGrow(MapInfo* aMap, MapInfo& aPole, KVector& aPoint, bool aHit[4]) {
    int x = aPoint.x, y = aPoint.y;
    int width = aPole.mWidth, height = aPole.mHeight;

    // 乱数による壁伸ばし方向の決定
    Direction dir;
    switch (random(4)) {
        case 0:
            dir = UP;
            if (!aHit[0]) break;
        case 1:
            dir = DOWN;
            if (!aHit[1]) break;
        case 2:
            dir = LEFT;
            if (!aHit[2]) break;
        case 3:
            dir = RIGHT;
            if (!aHit[3]) break;
            else {
                dir = UP;
                if (!aHit[0]) break;
                dir = DOWN;
                if (!aHit[1]) break;
                dir = LEFT;
                if (!aHit[2]) break;
                return false;
            }
    }

    int chipX = aMap->mIndexX, chipY = aMap->mIndexY;
    MapChip* chip = aMap->mInfo + (x * 2 + 2) * chipX + (y * 2 + 2) * chipY;
    int pointX = aPole.mIndexX, pointY = aPole.mIndexY;
    MapChip* point = aPole.mInfo + x * pointX + y * pointY;

    *chip = *point = OTHER;

    MapChip* tmp;
    switch (dir) {
        case UP:
            if (y == 0) { // 配列外阻止
                *(chip - chipY) = OTHER;
                return true;
            }
            tmp = point - pointY;
            if (*tmp == OTHER) aHit[0] = true;
            else {
                if (*(chip - chipY * 2) == WALL) {
                    *(chip - chipY) = OTHER;
                    return true;
                }
                *tmp = *(chip - chipY) = *(chip - chipY * 2) = OTHER;
                aPoint -= Y;
            }
            break;
        case DOWN:
            if (y == height - 1) { // 配列外阻止
                *(chip + chipY) = OTHER;
                return true;
            }
            tmp = point + pointY;
            if (*tmp == OTHER) aHit[1] = true;
            else {
                if (*(chip + chipY * 2) == WALL) {
                    *(chip + chipY) = OTHER;
                    return true;
                }
                *tmp = *(chip + chipY) = *(chip + chipY * 2) = OTHER;
                aPoint += Y;
            }
            break;
        case LEFT:
            if (x == 0) { // 配列外阻止
                *(chip - chipX) = OTHER;
                return true;
            }
            tmp = point - pointX;
            if (*tmp == OTHER) aHit[2] = true;
            else {
                if (*(chip - chipX * 2) == WALL) {
                    *(chip - chipX) = OTHER;
                    return true;
                }
                *tmp = *(chip - chipX) = *(chip - chipX * 2) = OTHER;
                aPoint -= X;
            }
            break;
        case RIGHT:
            if (x == width - 1) { // 配列外阻止
                *(chip + chipX) = OTHER;
                return true;
            }
            tmp = point + pointX;
            if (*tmp == OTHER) aHit[3] = true;
            else {
                if (*(chip + chipX * 2) == WALL) {
                    *(chip + chipX) = OTHER;
                    return true;
                }
                *tmp = *(chip + chipX) = *(chip + chipX * 2) = OTHER;
                aPoint += X;
            }
            break;
    }
    if (aPoint.x < 0 || width - 1 < aPoint.x || aPoint.y < 0 || height - 1 < aPoint.y) return true;
    if (wallGrow(aMap, aPole, aPoint, aHit)) return true;
    return false;
}

void Map::makeRoom(MapInfo * const aInfo) {
    int minRoomCount = 3, maxRoomCount = 9;
    int minRoomSize = 5;
    bool loop;
    int unLoop = 20;
    int width = aInfo->mWidth, height = aInfo->mHeight;

    int count = random(maxRoomCount - minRoomCount) + minRoomCount;

    MapChip* tmp;
    int tmX = aInfo->mIndexX, tmY = aInfo->mIndexY;

    for (int i = 0; i < count; ++i) {
        loop = true;

        int x, y, rW, rH, miss;
        x = y = rW = rH = miss = 0;

        while (loop) {
            loop = false;
            x = random((width - minRoomSize) / 2) * 2 + 1; // 奇数にする
            y = random((height - minRoomSize) / 2) * 2 + 1;
            rW = random(8) * 2 + minRoomSize;
            rW = (x + rW >= width - 1) ? minRoomSize : rW;
            rH = random(8) * 2 + minRoomSize;
            rH = (y + rH >= height - 1) ? minRoomSize : rH;

            // すでに部屋でないか確認
            tmp = aInfo->mInfo + y * tmY + x * tmX;
            for (int j = x, j_e = j + rW; j < j_e; ++j, tmp += tmX - rH) {
                for (int k = y, k_e = k + rH; k < k_e; ++k, ++tmp) {
                    if (*tmp == ROOM) {
                        if (miss <= unLoop) {
                            loop = true;
                            ++miss;
                        }
                    }
                }
            }
        }
        if (miss <= unLoop) {
            tmp = aInfo->mInfo + x * tmX + y * tmY;
            for (int j = x, j_e = j + rW; j < j_e; ++j, tmp += tmX - rH)
                for (int k = y, k_e = k + rH; k < k_e; ++k, ++tmp) {
                    *(aInfo->mInfo + j * aInfo->mIndexX + k * aInfo->mIndexY) = ROOM;
                }
        }
    }
}

void Map::clean(MapInfo * const aInfo) {
    int x, y;
    int length, loadCount;
    Direction loading;
    bool room;
    int width = aInfo->mWidth, height = aInfo->mHeight;
    int tmX = aInfo->mIndexX, tmY = aInfo->mIndexY;
    MapChip* tmp;

    for (int i = 1, i_e = height - 1; i < i_e; ++i) {
        for (int j = 1, j_e = width - 1; j < j_e; ++j) {
            tmp = aInfo->mInfo + i * tmY + j * tmX;
            if (*tmp == LOAD) { // START !
                x = j;
                y = i;
                length = 0;
                while (true) {
                    loadCount = room = 0;

                    if (0 <= y - 1) { // ↑
                        if (*(tmp - tmY) == LOAD) {
                            ++loadCount;
                            loading = UP;
                        } else if (*(tmp - tmY) == ROOM) room = true;
                    }
                    if (y + 1 <= height - 1) { // ↓
                        if (*(tmp + tmY) == LOAD) {
                            ++loadCount;
                            loading = DOWN;
                        } else if (*(tmp + tmY) == ROOM) room = true;
                    }
                    if (0 <= x - 1) { // ←
                        if (*(tmp - tmX) == LOAD) {
                            ++loadCount;
                            loading = LEFT;
                        } else if (*(tmp - tmX) == ROOM) room = true;
                    }
                    if (x + 1 <= width - 1) { // →
                        if (*(tmp + tmX) == LOAD) {
                            ++loadCount;
                            loading = RIGHT;
                        } else if (*(tmp + tmX) == ROOM) room = true;
                    }

                    if (loadCount == 1 && !room) { // 一本道を辿る
                        *tmp = OTHER;
                        length++;
                        switch (loading) {
                            case UP: y--;
                                tmp -= tmY;
                                break;
                            case DOWN: y++;
                                tmp += tmY;
                                break;
                            case LEFT: x--;
                                tmp -= tmX;
                                break;
                            case RIGHT: x++;
                                tmp += tmX;
                        }
                    } else { // END !
                        if (room) *tmp = OTHER;
                        for (int k = 1; k < i_e; ++k) {
                            for (int l = 1; l < j_e; ++l) {
                                if (*(tmp = aInfo->mInfo + k * tmY + l * tmX) == OTHER) {
                                    if (length && length != 7) * tmp = WALL; // 長さ7以上の片道を塗りつぶす
                                    else *tmp = LOAD;
                                }
                            }
                        }
                        break;
                    }
                }
            }
        }
    }
}
