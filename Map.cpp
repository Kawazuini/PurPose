/**
 * @file Map.cpp
 * @brief Map
 */
#include "Map.h"

#include "Wall.h"

const int Map::MAX_WIDTH = 20;
const int Map::MAX_HEIGHT = 20;
const int Map::MIN_WIDTH = 10;
const int Map::MIN_HEIGHT = 10;

const KVector Map::X(1, 0, 0);
const KVector Map::Y(0, 1, 0);
const KVector Map::Z(0, 0, 1);

const int Map::M_START, Map::M_ROOM, Map::M_WALL;

Map::Map(Map::MapInfo& aMap, const int& aChipSize) :
mScale(aChipSize) {
    mColors.mPlayer = 0x77ee0000;
    mColors.mWall = 0x7700ee00;
    mColors.mFloar = 0x770000ee;
    mColors.mGrid = 0xff555555;

    mStart = NULL;

    mMap = &aMap;

    mMapping = new Info<bool>(aMap.mWidth, aMap.mHeight, 5);
    bool* map = mMapping->mInfo;
    for (int i = 0, i_e = mMapping->mSize; i < i_e; ++i, ++map) *map = false;
}

Map::~Map() {
    if (mMap) delete mMap;
    if (mMapping) delete mMapping;
    if (mStart) delete mStart;

    for (Wall* i : mWalls) delete i;
}

void Map::draw(
        KGLUI& aGLUI,
        const MapPlayer& aPlayer,
        const KRect& aRect,
        const int& aSize
        ) {
    using namespace Math;

    static int prePlayerX = 0, prePlayerY = 0;
    static KVector preDirection;

    int width = mMap->mWidth, height = mMap->mHeight;
    int chipX = mMap->mIndexX, chipY = mMap->mIndexY;
    int mapX = mMapping->mIndexX, mapY = mMapping->mIndexY;

    int playerX = aPlayer.mPosition.x / mScale, playerY = aPlayer.mPosition.y / mScale;
    if (playerX < 0 || width < playerX || playerY < 0 || height < playerY) return;

    // 変更が起きた場合のみ描画更新
    if (aPlayer.mDirection != preDirection || playerX != prePlayerX || playerY != prePlayerY) {
        prePlayerX = playerX;
        prePlayerY = playerY;
        preDirection = aPlayer.mDirection;

        aGLUI.mScreen->clearRect(aRect);
        aGLUI.mScreen->drawRect(aRect, 0x40000000);

        MapChip* chip;
        bool* map;

        int startX = aRect.x, startY = aRect.y; // 描画開始位置(px)
        int w = min(aRect.width / aSize, width), h = min(aRect.height / aSize, height); // 描画マス数(マップの大きさを超えない)

        // 描画開始マス数(マップからはみ出ない)
        int beginX = min(max(0, playerX - w / 2), width - w), beginY = min(max(0, playerY - h / 2), height - h);

        map = mMapping->mInfo + (playerX * mapX) + (playerY * mapY); // プレイヤー位置
        if (!*(map + mMapping->mIndexY + mMapping->mIndexX + 4)) { // 未踏破
            room(playerX, playerY);
            chip = mMap->mInfo;
            for (int i = 0; i < mMap->mSize; ++i, ++chip) // 元に戻す
                if (*chip & OTHER) *chip = static_cast<MapChip> (*chip & ~OTHER);
        }

        // 壁情報の描画
        int chipD = chipX - h * chipY, mapD = mapX - h * mapY; // yの変位
        chip = mMap->mInfo + (beginX * chipX) + (beginY * chipY);
        map = mMapping->mInfo + (beginY * mapY) + (beginX * mapX);
        for (int i = 0; i < w; ++i, chip += chipD, map += mapD) {
            for (int j = 0; j < h; ++j, chip += chipY, map += mapY) {
                KVector lt = KVector(i * aSize + startX, j * aSize + startY);
                KVector rt = lt + KVector(aSize, 0), lb = lt + KVector(0, aSize), rb = (rt + lb) - lt;

                if (*(map + 4)) {
                    if (*(map + 0)) { // ↑
                        aGLUI.mScreen->drawLine(lt, rt, mColors.mWall);
                    } else if (!*(map - mapY + 4)) {
                        if (*(map - mapY + 2)) aGLUI.mScreen->drawLine(lt, lt + KVector(0, -aSize), mColors.mWall); // ←
                        if (*(map - mapY + 3)) aGLUI.mScreen->drawLine(rt, rt + KVector(0, -aSize), mColors.mWall); // →
                    }
                    if (*(map + 1)) { // ↓
                        aGLUI.mScreen->drawLine(lb, rb, mColors.mWall);
                    } else if (!*(map + mapY + 4)) {
                        if (*(map + mapY + 2)) aGLUI.mScreen->drawLine(lb, lb + KVector(0, aSize), mColors.mWall); // ←
                        if (*(map + mapY + 3)) aGLUI.mScreen->drawLine(rb, rb + KVector(0, aSize), mColors.mWall); // →
                    }
                    if (*(map + 2)) { // ←
                        aGLUI.mScreen->drawLine(lt, lb, mColors.mWall);
                    } else if (!*(map - mapX + 4)) {
                        if (*(map - mapX + 0)) aGLUI.mScreen->drawLine(lt, lt + KVector(-aSize, 0), mColors.mWall); // ↑
                        if (*(map - mapX + 1)) aGLUI.mScreen->drawLine(lb, lb + KVector(-aSize, 0), mColors.mWall); // ↓
                    }
                    if (*(map + 3)) { // →
                        aGLUI.mScreen->drawLine(rt, rb, mColors.mWall);
                    } else if (!*(map + mapX + 4)) {
                        if (*(map + mapX + 0)) aGLUI.mScreen->drawLine(rt, rt + KVector(aSize, 0), mColors.mWall); // ↑
                        if (*(map + mapX + 1)) aGLUI.mScreen->drawLine(rb, rb + KVector(aSize, 0), mColors.mWall); // ↓
                    }
                }
            }
        }
        KVector position = aPlayer.mPosition / mScale * aSize; // + KVector(startX, startY);
        KVector direction = aPlayer.mDirection * aSize;
        KVector origin = position + direction; // 矢印先端
        KVector origin2 = position - direction;
        KVector wide = KVector(-direction.y, direction.x);
        aGLUI.mScreen->drawLine(origin, origin2 + wide, mColors.mPlayer);
        aGLUI.mScreen->drawLine(origin, origin2 - wide, mColors.mPlayer);
        aGLUI.mScreen->drawLine(position - direction / 2, origin2 + wide, mColors.mPlayer);
        aGLUI.mScreen->drawLine(position - direction / 2, origin2 - wide, mColors.mPlayer);
    }
}

void Map::drawAllow(KGLUI& aGLUI, const MapPlayer& aPlayer, const int& aSize) {
}

void Map::room(const int& ax, const int& ay) {
    using namespace Math;

    const int mapX = mMap->mIndexX, mapY = mMap->mIndexY;
    const int mappingX = mMapping->mIndexX, mappingY = mMapping->mIndexY;

    Info<KVector> stack(mMap->mSize, 1);

    int stackCount = 0;
    KVector nowVector = KVector(ax, ay);
    bool pushed = false;
START:
    if (!pushed) *(stack.mInfo + stackCount++) = nowVector; // push
    pushed = false;

    int x = max(1, min((int) nowVector.x, mMap->mWidth - 1)), y = max(1, min((int) nowVector.y, mMap->mHeight - 1));
    MapChip* map = mMap->mInfo + (x * mapX) + (y * mapY);
    bool* mapping = mMapping->mInfo + (x * mappingX) + (y * mappingY), *tmp;

    *map = static_cast<MapChip> (*map | OTHER); // 検索対象から除外
    MapChip* U = map - mapY;
    MapChip* D = map + mapY;
    MapChip* L = map - mapX;
    MapChip* R = map + mapX;

    *(mapping + 4) = true;

    *(mapping + 0) = *U & WALL; // ↑
    *(mapping + 1) = *D & WALL; // ↓
    *(mapping + 2) = *L & WALL; // ←
    *(mapping + 3) = *R & WALL; // →

    // 出口の確認
    if (*U & LOAD) { // ↑
        tmp = mapping - mappingY;
        *(tmp + 4) = true;
        *(tmp + 0) = *(U - mapY) & WALL; // ↑
        *(tmp + 2) = *(U - mapX) & WALL; // ←
        *(tmp + 3) = *(U + mapX) & WALL; // →
    }
    if (*D & LOAD) { // ↓
        tmp = mapping + mappingY;
        *(tmp + 4) = true;
        *(tmp + 1) = *(D + mapY) & WALL; // ↓
        *(tmp + 2) = *(D - mapX) & WALL; // ←
        *(tmp + 3) = *(D + mapX) & WALL; // →
    }
    if (*L & LOAD) { // ←
        tmp = mapping - mappingX;
        *(tmp + 4) = true;
        *(tmp + 2) = *(L - mapX) & WALL; // ←
        *(tmp + 0) = *(L - mapY) & WALL; // ↑
        *(tmp + 1) = *(L + mapY) & WALL; // ↓
    }
    if (*R & LOAD) { // →
        tmp = mapping + mappingX;
        *(tmp + 4) = true;
        *(tmp + 3) = *(R + mapX) & WALL; // →
        *(tmp + 0) = *(R - mapY) & WALL; // ↑
        *(tmp + 1) = *(R + mapY) & WALL; // ↓
    }

    // 部屋を広げる
    if (!(*U & OTHER) && *U & ROOM) { // ↑
        nowVector -= Y;
        goto START;
    }
    if (!(*D & OTHER) && *D & ROOM) { // ↓
        nowVector += Y;
        goto START;
    }
    if (!(*L & OTHER) && *L & ROOM) { // ←
        nowVector -= X;
        goto START;
    }
    if (!(*R & OTHER) && *R & ROOM) {// →
        nowVector += X;
        goto START;
    }
    if (stackCount) { // スタックが残ってる
        pushed = true; // すでに追加済み
        stackCount--;
        nowVector = *(stack.mInfo + stackCount); // pop
        goto START;
    }
}

KVector Map::start() const {
    return *mStart;
}

KVector Map::respawn() const {
    Array<KVector> result;
    MapChip* tmp = mMap->mInfo;
    for (int i = 0, i_e = mMap->mWidth; i < i_e; ++i) {
        for (int j = 0, j_e = mMap->mHeight; j < j_e; ++j, ++tmp) {
            if (*tmp == ROOM) result.push_back(KVector(i * mScale, j * mScale));
        }
    }
    return result[random(result.size())];
    /*
    int width = mMap->mWidth, height = mMap->mHeight;
    List<KRect> result;

    MapChip* tmp = mMap->mInfo, *room;
    for (int i = 0; i < width; ++i) {
        for (int j = 0; j < height; ++j, ++tmp) {
            if (*tmp == ROOM) {
                int rHeight = 0, rWidth = 1;
                room = tmp;
                for (int k = j; k < height; ++k, ++room) {
                    if (*room == ROOM) {
                        ++rHeight;
     *room = OTHER;
                    } else break;
                }
                room = tmp + mMap->mIndexX;
                for (int k = i; k < width; ++k, room += mMap->mIndexX - rHeight) {
                    if (*room == ROOM) {
                        ++rWidth;
                        for (int l = j; l < j + rHeight; ++l, ++room) *room = OTHER;
                    } else break;
                }
                result.push_back(KRect(i * mScale, j * mScale, rWidth * mScale, rHeight * mScale));
            }
        }
    }
    tmp = mMap->mInfo;
    for (int i = 0; i < mMap->mSize; ++i, ++tmp) if (*tmp == OTHER) *tmp = ROOM;

    return result.at(random(result.size()));
     */
}

KRect Map::warp() const {
    return warpzone;
}

float Map::scale() const {
    return mScale;
}
