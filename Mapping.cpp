/**
 * @file   Mapping.cpp
 * @brief  Mapping
 * @author Maeda Takumi
 */
#include "Mapping.h"

Mapping::Mapping() {
    mColors.mPlayer = 0x77ee0000;
    mColors.mWall = 0x7700ee00;
    mColors.mFloar = 0x770000ee;
    mColors.mGrid = 0xff555555;
}

void Mapping::set(const Map& aMap) {
    reset();
    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            mMap[i][j] = aMap[i][j];
        }
    }
}

void Mapping::reset() {
    for (int i = MAP_MAX_WIDTH - 1; i >= 0; --i) {
        for (int j = MAP_MAX_HEIGHT - 1; j >= 0; --j) {
            for (int k = 4; k >= 0; --k) {
                mMapping[i][j][k] = false;
            }
        }
    }
}

void Mapping::draw(
        KGLUI& aGLUI,
        const MappingPlayer& aPlayer,
        const KRect& aRect,
        const int& aSize
        ) {
    using namespace Math;
    static const int width = MAP_MAX_WIDTH - 1;
    static const int height = MAP_MAX_HEIGHT - 1;

    static int prePlayerX = 0, prePlayerY = 0;
    static KVector preDirection;

    int playerX = aPlayer.mPosition.x / MAP_SCALE, playerY = aPlayer.mPosition.y / MAP_SCALE;
    if (playerX < 0 || width < playerX || playerY < 0 || height < playerY) return;

    // 変更が起きた場合のみ描画更新
    if (aPlayer.mDirection != preDirection || playerX != prePlayerX || playerY != prePlayerY) {
        prePlayerX = playerX;
        prePlayerY = playerY;
        preDirection = aPlayer.mDirection;

        aGLUI.mScreen->clearRect(KRect(aRect.x - 5, aRect.y - 5, aRect.width + 10, aRect.height + 10));
        aGLUI.mScreen->drawRect(aRect, 0x40000000);

        MapChip* chip;

        int startX = aRect.x, startY = aRect.y; // 描画開始位置(px)
        int w = min(aRect.width / aSize, width), h = min(aRect.height / aSize, height); // 描画マス数(マップの大きさを超えない)

        // 描画開始マス数(マップからはみ出ない)
        int beginX = min(max(0, playerX - w / 2), width - w), beginY = min(max(0, playerY - h / 2), height - h);

        if (!mMapping[playerX][playerY][4]) room(playerX, playerY);

        // 壁情報の描画
        for (int i = 0; i < w; ++i) {
            for (int j = 0; j < h; ++j) {
                KVector lt = KVector(i * aSize + startX, j * aSize + startY);
                KVector rt = lt + KVector(aSize, 0), lb = lt + KVector(0, aSize), rb = (rt + lb) - lt;

                if (mMapping[beginX + i][beginY + j][4]) {
                    if (mMapping[beginX + i][beginY + j][0]) { // ↑
                        aGLUI.mScreen->drawLine(lt, rt, mColors.mWall);
                    } else if (!mMapping[beginX + i][beginY + j - 1][4]) {
                        if (mMapping[beginX + i][beginY + j - 1][2]) aGLUI.mScreen->drawLine(lt, lt + KVector(0, -aSize), mColors.mWall); // ←
                        if (mMapping[beginX + i][beginY + j - 1][3]) aGLUI.mScreen->drawLine(rt, rt + KVector(0, -aSize), mColors.mWall); // →
                    }
                    if (mMapping[beginX + i][beginY + j][1]) { // ↓
                        aGLUI.mScreen->drawLine(lb, rb, mColors.mWall);
                    } else if (!mMapping[beginX + i][beginY + j + 1][4]) {
                        if (mMapping[beginX + i][beginY + j + 1][2]) aGLUI.mScreen->drawLine(lb, lb + KVector(0, aSize), mColors.mWall); // ←
                        if (mMapping[beginX + i][beginY + j + 1][3]) aGLUI.mScreen->drawLine(rb, rb + KVector(0, aSize), mColors.mWall); // →
                    }
                    if (mMapping[beginX + i][beginY + j][2]) { // ←
                        aGLUI.mScreen->drawLine(lt, lb, mColors.mWall);
                    } else if (!mMapping[beginX + i - 1][beginY + j][4]) {
                        if (mMapping[beginX + i - 1][beginY + j][0]) aGLUI.mScreen->drawLine(lt, lt + KVector(-aSize, 0), mColors.mWall); // ↑
                        if (mMapping[beginX + i - 1][beginY + j][1]) aGLUI.mScreen->drawLine(lb, lb + KVector(-aSize, 0), mColors.mWall); // ↓
                    }
                    if (mMapping[beginX + i][beginY + j][3]) { // →
                        aGLUI.mScreen->drawLine(rt, rb, mColors.mWall);
                    } else if (!mMapping[beginX + i + 1][beginY + j][4]) {
                        if (mMapping[beginX + i + 1][beginY + j][0]) aGLUI.mScreen->drawLine(rt, rt + KVector(aSize, 0), mColors.mWall); // ↑
                        if (mMapping[beginX + i + 1][beginY + j][1]) aGLUI.mScreen->drawLine(rb, rb + KVector(aSize, 0), mColors.mWall); // ↓
                    }
                }
            }
        }
        int pX = playerX < w / 2 ? playerX : width - 1 - w / 2 < playerX ? playerX - width + w : w / 2;
        int pY = playerY < h / 2 ? playerY : height - 1 - h / 2 < playerY ? playerY - height + h : h / 2;
        KVector position = KVector(pX, pY) * aSize + aRect.start() + KVector(aSize, aSize) / 2;
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

void Mapping::room(const int& ax, const int& ay) {
    using namespace Math;
    static const int width = MAP_MAX_WIDTH - 1;
    static const int height = MAP_MAX_HEIGHT - 1;

    Stack<KVector> stack;
    KVector nowVector = KVector(ax, ay);

    bool pushed = false;

    while (true) {
        if (!pushed) stack.push(nowVector); // push
        pushed = false;

        int x = max(1, min((int) nowVector.x, width));
        int y = max(1, min((int) nowVector.y, height));

        mMap[x][y] = static_cast<MapChip> (mMap[x][y] | OTHER); // 検索対象から除外
        MapChip U = mMap[x][y - 1];
        MapChip D = mMap[x][y + 1];
        MapChip L = mMap[x - 1][y];
        MapChip R = mMap[x + 1][y];

        mMapping[x][y][4] = true;
        mMapping[x][y][0] = U & WALL; // ↑
        mMapping[x][y][1] = D & WALL; // ↓
        mMapping[x][y][2] = L & WALL; // ←
        mMapping[x][y][3] = R & WALL; // →

        // 出口の確認
        if (U & LOAD) { // ↑
            mMapping[x][y - 1][4] = true;
            mMapping[x][y - 1][0] = mMap[x][y - 2] & WALL; // ↑
            mMapping[x][y - 1][2] = mMap[x - 1][y - 1] & WALL; // ←
            mMapping[x][y - 1][3] = mMap[x + 1][y - 1] & WALL; // →
        }
        if (D & LOAD) { // ↓
            mMapping[x][y + 1][4] = true;
            mMapping[x][y + 1][1] = mMap[x][y + 2] & WALL; // ↓
            mMapping[x][y + 1][2] = mMap[x - 1][y + 1] & WALL; // ←
            mMapping[x][y + 1][3] = mMap[x + 1][y + 1] & WALL; // →
        }
        if (L & LOAD) { // ←
            mMapping[x - 1][y][4] = true;
            mMapping[x - 1][y][2] = mMap[x - 2][y] & WALL; // ←
            mMapping[x - 1][y][0] = mMap[x - 1][y - 1] & WALL; // ↑
            mMapping[x - 1][y][1] = mMap[x - 1][y + 1] & WALL; // ↓
        }
        if (R & LOAD) { // →
            mMapping[x + 1][y][4] = true;
            mMapping[x + 1][y][3] = mMap[x + 2][y] & WALL; // →
            mMapping[x + 1][y][0] = mMap[x + 1][y - 1] & WALL; // ↑
            mMapping[x + 1][y][1] = mMap[x + 1][y + 1] & WALL; // ↓
        }

        // 部屋を広げる
        if (!(U & OTHER) && U & ROOM) nowVector -= Y; // ↑
        else if (!(D & OTHER) && D & ROOM) nowVector += Y; // ↓
        else if (!(L & OTHER) && L & ROOM) nowVector -= X; // ←
        else if (!(R & OTHER) && R & ROOM) nowVector += X; // →
        else if (!stack.empty()) { // スタックが残ってる
            pushed = true; // すでに追加済み
            nowVector = stack.top();
            stack.pop();
        } else break;
    }

    // 元に戻す
    for (int i = MAP_MAX_WIDTH - 1; i >= 0; --i) {
        for (int j = MAP_MAX_HEIGHT - 1; j >= 0; --j) {
            if (mMap[i][j] & OTHER) mMap[i][j] = static_cast<MapChip> (mMap[i][j] & ~OTHER);
        }
    }
}

