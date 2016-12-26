/**
 * @file   MapGenerator.cpp
 * @brief  MapGenerator
 * @author Maeda Takumi
 */
#include "MapGenerator.h"

const int MapGenerator::RANDOM_MAX_WIDTH = 20;
const int MapGenerator::RANDOM_MAX_HEIGHT = 20;
const int MapGenerator::RANDOM_MIN_WIDTH = 10;
const int MapGenerator::RANDOM_MIN_HEIGHT = 10;

void MapGenerator::STRING_MAP(Map& aDist, const Vector<String>& aMap) {
    int x = 0, y = 0;
    for (String i : aMap) {
        Vector<String> column = split(i, ",");
        y = 0;
        for (String j : column) {
            switch (toInt(j)) {
                case _START: aDist[x][y] = START;
                    break;
                case _ROOM: aDist[x][y] = ROOM;
                    break;
                case _WALL: aDist[x][y] = WALL;
                    break;
                default: aDist[x][y] = LOAD;
            }
            ++y;
        }
        ++x;
    }
}

void MapGenerator::RANDOM_MAP(Map& aDist) {
    int width = random(RANDOM_MAX_WIDTH - RANDOM_MIN_WIDTH) + RANDOM_MIN_WIDTH;
    int height = random(RANDOM_MAX_HEIGHT - RANDOM_MIN_HEIGHT) + RANDOM_MIN_HEIGHT;

    MapDocument pole{width, height}; // 支点情報
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j) {
            pole.mMap[i][j] = LOAD;
        }
    }

    MapDocument map{width * 2 + 3, height * 2 + 3};
    for (int i = map.mWidth - 1; i >= 0; --i) {
        for (int j = map.mHeight - 1; j >= 0; --j) {
            map.mMap[i][j] = LOAD;
        }
    }

    // 外壁生成
    for (int i = 0, i_e = map.mWidth; i < i_e; ++i) {
        for (int j = 0, j_e = map.mHeight; j < j_e; ++j) {
            if (i == 0 || i == i_e - 1 || j == 0 || j == j_e - 1)map.mMap[i][j] = WALL;
        }
    }

    // 支点抽選番号の準備(順に番号を振る)
    int _pole[MAP_MAX_WIDTH * MAP_MAX_HEIGHT];
    for (int i = 0, i_e = width * height; i < i_e * height; ++i) _pole[i] = i;

    // 壁伸ばし法
    int leftPole = width * height; // 支点の残り数
    while (leftPole) { // 支点がなくなるまで続ける
        // 次の支点の決定
        int next = _pole[random(leftPole)];
        KVector point(next / height, next % height);

        // 壁伸ばし探索
        bool hit[4] = {false, false, false, false};
        bool grow = wallGrow(map, pole, point, hit);
        // 壁の決定 or 取り消し
        for (int i = map.mWidth - 1; i >= 0; --i) {
            for (int j = map.mHeight - 1; j >= 0; --j) {
                if (map.mMap[i][j] == OTHER) map.mMap[i][j] = (grow ? WALL : LOAD);
            }
        }

        // 未使用支点情報の更新
        for (int i = 0, rest = 0; i < width; ++i) {
            for (int j = 0; j < height; ++j) {
                if (pole.mMap[i][j] == WALL) rest++; // 使用支点数
                if (pole.mMap[i][j] == OTHER) {
                    if (grow) {
                        pole.mMap[i][j] = WALL;
                        // 支点抽選番号をずらす
                        for (int k = i * height + j - rest; k < leftPole; ++k) _pole[k] = _pole[k + 1];
                        ++rest;
                        --leftPole;
                    } else pole.mMap[i][j] = LOAD;
                }
            }
        }
    }

    makeRoom(map);
    clean(map);

    // 階段座標の確定
    Vector<KVector> result;
    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            if (map.mMap[i][j] == ROOM) result.push_back(KVector(i, j));
        }
    }
    KVector stair = result[random(result.size())];
    map.mMap[(int) stair.x][(int) stair.y] = STAIR;

    for (int i = MAP_MAX_WIDTH - 1; i >= 0; --i) {
        for (int j = MAP_MAX_HEIGHT - 1; j >= 0; --j) {
            aDist[i][j] = map.mMap[i][j];
        }
    }

    for (int i = 0; i < map.mWidth; ++i) {
        for (int j = 0; j < map.mHeight; ++j) {
            if (map.mMap[i][j] == WALL) print("壁");
            else if (map.mMap[i][j] == ROOM) print("　");
            else print("　");
        }
        println("");
    }
}

bool MapGenerator::wallGrow(MapDocument& aMap, MapDocument& aPole, KVector& aPoint, bool aHit[]) {
    static const int UP = 0;
    static const int DOWN = 1;
    static const int LEFT = 2;
    static const int RIGHT = 3;

    int x = aPoint.x, y = aPoint.y;
    int width = aPole.mWidth, height = aPole.mHeight;

    // 乱数による壁伸ばし方向の決定
    int notHitCount = 0;
    int safeDir[4];
    for (int i = 0; i < 4; ++i) {
        if (!aHit[i]) {
            safeDir[notHitCount] = i;
            ++notHitCount;
        }
    }
    int dir = notHitCount != 1 ? safeDir[random(notHitCount - 1) + 1] : safeDir[0];

    int sX = x * 2 + 2, sY = y * 2 + 2;

    aMap.mMap[sX][sY] = aPole.mMap[x][y] = OTHER;

    switch (dir) {
        case UP:
            if (y == 0) { // 配列外阻止
                aMap.mMap[sX][sY - 1] = OTHER;
                return true;
            }
            if (aPole.mMap[x][y - 1] == OTHER) aHit[0] = true;
            else {
                if (aMap.mMap[sX][sY - 2] == WALL) {
                    aMap.mMap[sX][sY - 1] = OTHER;
                    return true;
                }
                aPole.mMap[x][y - 1] = aMap.mMap[sX][sY - 1] = aMap.mMap[sX][sY - 2] = OTHER;
                aPoint -= Y;
            }
            break;
        case DOWN:
            if (y == height - 1) { // 配列外阻止
                aMap.mMap[sX][sY + 1] = OTHER;
                return true;
            }
            if (aPole.mMap[x][y + 1] == OTHER) aHit[1] = true;
            else {
                if (aMap.mMap[sX][sY + 2] == WALL) {
                    aMap.mMap[sX][sY + 1] = OTHER;
                    return true;
                }
                aPole.mMap[x][y + 1] = aMap.mMap[sX][sY + 1] = aMap.mMap[sX][sY + 2] = OTHER;
                aPoint += Y;
            }
            break;
        case LEFT:
            if (x == 0) { // 配列外阻止
                aMap.mMap[sX - 1][sY] = OTHER;
                return true;
            }
            if (aPole.mMap[x - 1][y] == OTHER) aHit[2] = true;
            else {
                if (aMap.mMap[sX - 2][sY] == WALL) {
                    aMap.mMap[sX - 1][sY] = OTHER;
                    return true;
                }
                aPole.mMap[x - 1][y] = aMap.mMap[sX - 1][sY] = aMap.mMap[sX - 2][sY] = OTHER;
                aPoint -= X;
            }
            break;
        case RIGHT:
            if (x == width - 1) { // 配列外阻止
                aMap.mMap[sX + 1][sY] = OTHER;
                return true;
            }
            if (aPole.mMap[x + 1][y] == OTHER) aHit[3] = true;
            else {
                if (aMap.mMap[sX + 2][sY] == WALL) {
                    aMap.mMap[sX + 1][sY] = OTHER;
                    return true;
                }
                aPole.mMap[x + 1][y] = aMap.mMap[sX + 1][sY] = aMap.mMap[sX + 2][sY] = OTHER;
                aPoint += X;
            }
            break;
    }
    if (aPoint.x < 0 || width - 1 < aPoint.x || aPoint.y < 0 || height - 1 < aPoint.y) return true;
    if (wallGrow(aMap, aPole, aPoint, aHit)) return true;
    return false;
}

void MapGenerator::makeRoom(MapDocument& aInfo) {
    int minRoomCount = 3, maxRoomCount = 9;
    int minRoomSize = 5;
    bool loop;
    int unLoop = 20;
    int width = aInfo.mWidth, height = aInfo.mHeight;

    int count = random(maxRoomCount - minRoomCount) + minRoomCount;

    MapChip* tmp;

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
            for (int j = x, j_e = j + rW; j < j_e; ++j) {
                for (int k = y, k_e = k + rH; k < k_e; ++k) {
                    if (aInfo.mMap[j][k] == ROOM) {
                        if (miss <= unLoop) {
                            loop = true;
                            ++miss;
                        }
                    }
                }
            }
        }
        if (miss <= unLoop) {
            for (int j = x, j_e = j + rW; j < j_e; ++j)
                for (int k = y, k_e = k + rH; k < k_e; ++k) {
                    aInfo.mMap[j][k] = ROOM;
                }
        }
    }
}

void MapGenerator::clean(MapDocument& aInfo) {
    static const int UP = 0;
    static const int DOWN = 1;
    static const int LEFT = 2;
    static const int RIGHT = 3;

    int x, y;
    int length, loadCount;
    int loading;
    bool room;
    int width = aInfo.mWidth, height = aInfo.mHeight;

    for (int i = 1, i_e = width - 1; i < i_e; ++i) {
        for (int j = 1, j_e = height - 1; j < j_e; ++j) {
            if (aInfo.mMap[i][j] == LOAD) { // START !
                x = i;
                y = j;
                length = 0;
                while (true) {
                    loadCount = room = 0;

                    if (0 < y) { // ↑
                        if (aInfo.mMap[x][y - 1] == LOAD) {
                            ++loadCount;
                            loading = UP;
                        } else if (aInfo.mMap[x][y - 1] == ROOM) room = true;
                    }
                    if (y < height - 1) { // ↓
                        if (aInfo.mMap[x][y + 1] == LOAD) {
                            ++loadCount;
                            loading = DOWN;
                        } else if (aInfo.mMap[x][y + 1] == ROOM) room = true;
                    }
                    if (0 < x) { // ←
                        if (aInfo.mMap[x - 1][y] == LOAD) {
                            ++loadCount;
                            loading = LEFT;
                        } else if (aInfo.mMap[x - 1][y] == ROOM) room = true;
                    }
                    if (x < width - 1) { // →
                        if (aInfo.mMap[x + 1][y] == LOAD) {
                            ++loadCount;
                            loading = RIGHT;
                        } else if (aInfo.mMap[x + 1][y] == ROOM) room = true;
                    }

                    if (loadCount == 1 && !room) { // 一本道を辿る
                        aInfo.mMap[x][y] = OTHER;
                        length++;
                        switch (loading) {
                            case UP: y--;
                                break;
                            case DOWN: y++;
                                break;
                            case LEFT: x--;
                                break;
                            case RIGHT: x++;
                        }
                    } else { // END !
                        if (room) aInfo.mMap[x][y] = OTHER;
                        for (int k = 1; k < i_e; ++k) {
                            for (int l = 1; l < j_e; ++l) {
                                if (aInfo.mMap[k][l] == OTHER) {
                                    if (length && length != 7) aInfo.mMap[k][l] = WALL; // 長さ7以上の片道を塗りつぶす
                                    else aInfo.mMap[k][l] = LOAD;
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

