/**
 * @file   Mapping.cpp
 * @brief  Mapping
 * @author Maeda Takumi
 */
#include "Mapping.h"

#include "Character.h"
#include "GameState.h"

const int Mapping::TEX_SIZE(128);

Mapping::Mapping(const KCamera& aCamera) :
mColors{
    0xff762f07, // 栗色
    0xff316745, // 千歳緑
    0xffa22041, // 濃紅
}

,
mCamera(aCamera),
mCanvas(TEX_SIZE),
mAngle(0),
mScale(4) {
    KDrawer::remove();
}

void Mapping::draw() const {
    mCanvas.reflect();

    const KCamera::ViewCorner & vc(mCamera.viewCorner());
    KVector dl((vc[2] + vc[3] * 3) / 4);
    KVector ur((vc[1] + vc[3] * 2) / 3);
    KVector up((vc[3] - ur) / 2);
    KVector center((dl + ur) / 2);

    KShading::ColorShading->ON();

    const KVector & direct(mCamera.direction());

    glDisable(GL_DEPTH_TEST); // 絶対描画
    glNormal3f(DEPLOY_VEC(-direct));
    mCanvas.bindON();
    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
    glBegin(GL_TRIANGLE_FAN);

    for (int i = 0; i < 32; ++i) {
        float angle(Math::PI * 2 / 32 * i);
        glTexCoord2f((sin(angle) + 1) / 2, (cos(angle) + 1) / 2);
        KVector tmp(up.rotate(KQuaternion(direct, angle - mAngle)) + center + mCamera.position());
        glVertex3f(DEPLOY_VEC(tmp));
    }

    glEnd();
    mCanvas.bindOFF();
    glEnable(GL_DEPTH_TEST);
}

void Mapping::update(GameState& aState) {
    static const KVector NORTH(0, 1, 0);
    static const KVector EAST(1, 0, 0);
    static const KRect MAPPING(TEX_SIZE, TEX_SIZE);

    KVector dir(aState.mPlayer.direction());
    mAngle = KVector(dir.x, dir.z).angle(NORTH) * (dir.dot(EAST) < 0 ? -1 : 1);

    room(aState.mPlayer.position());
    draw(aState, MAPPING, mScale, true);
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

void Mapping::zoom(const int& aAmount) {
    mScale = Math::max(Math::min(32, mScale + aAmount), 3);
}

void Mapping::draw(
        const GameState& aState,
        const KRect& aRect,
        const int& aSize,
        const bool& aCentering
        ) {
    using namespace Math;
    static const int W(MAP_MAX_WIDTH - 1);
    static const int H(MAP_MAX_HEIGHT - 1);

    int playerX(aState.mPlayer.position().x / MAP_SCALE);
    int playerY(aState.mPlayer.position().z / MAP_SCALE);
    if (playerX < 0 || W < playerX || playerY < 0 || H < playerY) return;

    static int pPlayerX(-1);
    static int pPlayerY(-1);
    if (playerX == pPlayerX && playerY == pPlayerY) return; // 移動無し
    pPlayerX = playerX;
    pPlayerY = pPlayerY;

    mCanvas.clearRect(aRect);
    mCanvas.drawRect(aRect, 0x40000000);

    // 描画開始位置(px)
    int startX(aRect.x), startY(aRect.y);
    int w, h, beginX, beginY;
    if (aCentering) {
        w = aRect.width / aSize;
        h = aRect.height / aSize;
        beginX = playerX - w / 2;
        beginY = playerY - h / 2;
    } else {
        // 描画マス数(マップの大きさを超えない)
        w = min(aRect.width / aSize, W);
        h = min(aRect.height / aSize, H);
        // 描画開始マス数(マップからはみ出ない)
        beginX = min(max(0, playerX - w / 2), W - w);
        beginY = min(max(0, playerY - h / 2), H - h);
    }

    KVector mapX(X * aSize);
    KVector mapY(Y * aSize);

    // 壁情報の描画
    for (int i = 0; i < w; ++i) {
        for (int j = 0; j < h; ++j) {
            KVector lt(i * aSize + startX, j * aSize + startY);
            KVector rt(lt + KVector(aSize, 0)), lb(lt + KVector(0, aSize)), rb(lt + KVector(aSize, aSize));

            int x(beginX + i);
            int y(beginY + j);

            if (x >= MAP_MAX_WIDTH - 1 || y >= MAP_MAX_HEIGHT - 1) continue;

            if (mMapping[x][y][4]) {
                if (mMap[x][y] == STAIR) {
                    mCanvas.drawRect(KRect(lt, rb), mColors.mStair);
                }

                if (mMapping[x][y][0]) { // ↑
                    mCanvas.drawLine(lt, rt, mColors.mWall);
                } else if (!mMapping[x][y - 1][4]) {
                    if (mMapping[x][y - 1][2]) mCanvas.drawLine(lt, lt - mapY, mColors.mWall); // ←
                    if (mMapping[x][y - 1][3]) mCanvas.drawLine(rt, rt - mapY, mColors.mWall); // →
                }
                if (mMapping[x][y][1]) { // ↓
                    mCanvas.drawLine(lb, rb, mColors.mWall);
                } else if (!mMapping[x][y + 1][4]) {
                    if (mMapping[x][y + 1][2]) mCanvas.drawLine(lb, lb + mapY, mColors.mWall); // ←
                    if (mMapping[x][y + 1][3]) mCanvas.drawLine(rb, rb + mapY, mColors.mWall); // →
                }
                if (mMapping[x][y][2]) { // ←
                    mCanvas.drawLine(lt, lb, mColors.mWall);
                } else if (!mMapping[x - 1][y][4]) {
                    if (mMapping[x - 1][y][0]) mCanvas.drawLine(lt, lt - mapX, mColors.mWall); // ↑
                    if (mMapping[x - 1][y][1]) mCanvas.drawLine(lb, lb - mapX, mColors.mWall); // ↓
                }
                if (mMapping[x][y][3]) { // →
                    mCanvas.drawLine(rt, rb, mColors.mWall);
                } else if (!mMapping[x + 1][y][4]) {
                    if (mMapping[x + 1][y][0]) mCanvas.drawLine(rt, rt + mapX, mColors.mWall); // ↑
                    if (mMapping[x + 1][y][1]) mCanvas.drawLine(rb, rb + mapX, mColors.mWall); // ↓
                }
            }
        }
    }
    int pX, pY;
    if (aCentering) {
        pX = w / 2;
        pY = h / 2;
    } else {
        pX = playerX < w / 2 ? playerX : W - 1 - w / 2 < playerX ? playerX - W + w : w / 2;
        pY = playerY < h / 2 ? playerY : H - 1 - h / 2 < playerY ? playerY - H + h : h / 2;
    }
    KVector position(KVector(pX, pY) * aSize + aRect.begin() + KVector(aSize, aSize) / 2);
    KVector direction(KVector(aState.mPlayer.direction().x, aState.mPlayer.direction().z).normalization() * aSize);
    KVector origin(position + direction); // 矢印先端
    KVector origin2(position - direction);
    KVector wide(KVector(-direction.y, direction.x));
    mCanvas.drawLine(origin, origin2 + wide, mColors.mPlayer);
    mCanvas.drawLine(origin, origin2 - wide, mColors.mPlayer);
    mCanvas.drawLine(position - direction / 2, origin2 + wide, mColors.mPlayer);
    mCanvas.drawLine(position - direction / 2, origin2 - wide, mColors.mPlayer);
}

void Mapping::room(const KVector& aPlayer) {
    using namespace Math;
    static const int W(MAP_MAX_WIDTH - 1);
    static const int H(MAP_MAX_HEIGHT - 1);

    Stack<KVector> stack;
    KVector nowVector(KVector(aPlayer.x, aPlayer.z) / MAP_SCALE);

    bool pushed = false;

    while (true) {
        if (!pushed) stack.push(nowVector); // push
        pushed = false;

        int x(max(1, min((int) nowVector.x, W)));
        int y(max(1, min((int) nowVector.y, H)));

        mMap[x][y] = static_cast<MapChip> (mMap[x][y] | OTHER); // 検索対象から除外
        MapChip U(mMap[x][y - 1]);
        MapChip D(mMap[x][y + 1]);
        MapChip L(mMap[x - 1][y]);
        MapChip R(mMap[x + 1][y]);

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
    for (int i = W; i >= 0; --i) {
        for (int j = H; j >= 0; --j) {
            if (mMap[i][j] & OTHER) mMap[i][j] = static_cast<MapChip> (mMap[i][j] & ~OTHER);
        }
    }
}

