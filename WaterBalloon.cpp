/**
 * @file   WaterBalloon.cpp
 * @brief  WaterBalloon
 * @author Maeda Takumi
 */
#include "WaterBalloon.h"
#include "GameState.h"

WaterBalloon::WaterBalloon(
        const KVector& aPosition,
        const float& aRadius,
        const int& aStack,
        const int& aSlice
        ) :
KDrawSphere(aPosition, aRadius, aStack, aSlice),
mPoints(aStack + 1, Vector<PhysicalPoint*>(aSlice, NULL)),
mVolume(4 / 3 * Math::PI * aRadius * aRadius * aRadius),
mElasticity(1.5f),
mFluctuation(true),
mFrame(0) {
    for (int i = 0; i <= mStack; ++i) {
        for (int j = 0; j < mSlice; ++j) {
            if (validIndex(i, j)) {
                mPoints[i][j] = new PhysicalPoint(mVertex[i][j], 0.3f);
            }
        }
    }
}

WaterBalloon::~WaterBalloon() {
    for (Vector<PhysicalPoint*>i : mPoints) {
        for (PhysicalPoint* j : i) {
            if (j) delete j;
        }
    }
}

void WaterBalloon::update(GameState& aState) {
    if (mFluctuation) {
        if (mFrame++ > 360) mFrame = 0;
        mPosition += aState.mGravity * sin(Math::PI / 180 * mFrame);
    }

    float sma(mRadius / mElasticity);
    float big(mRadius * mElasticity);

    for (int i = 0; i <= mStack; ++i) {
        for (int j = 0; j < mSlice; ++j) {
            if (validIndex(i, j)) {
                KVector force(mVertex[i][j] - mPosition - mNormal[i][j]); // 外向きの力
                float forceLen(force.length());
                if (!mPoints[i][j]->mOnWall) {
                    if (forceLen < sma) { // 原型より小さいとき
                        mPoints[i][j]->applyForce(force / 200);
                    } else if (big < forceLen) { // 最大値より大きいとき
                        mPoints[i][j]->applyForce(-force / 200);
                    }
                } else { // 壁に当たっているときは他の頂点を押し上げる
                    force /= (2500 * mVertexSize);
                    if (forceLen < sma) { // 原型より小さいとき
                        for (int k = 0; k <= mStack; ++k) {
                            for (int l = 0; l < mSlice; ++l) {
                                if (validIndex(k, l) && (i != k || j != l)) {
                                    mPoints[i][j]->applyForce(force);
                                }
                            }
                        }
                    } else if (big < forceLen) { // 最大値より大きいとき
                        for (int k = 0; k <= mStack; ++k) {
                            for (int l = 0; l < mSlice; ++l) {
                                if (validIndex(k, l) && (i != k || j != l)) {
                                    mPoints[i][j]->applyForce(-force);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

float WaterBalloon::calcVolume() const {
    KVector axis(mVertex[mStack][0] - mVertex[0][0]);

    float volume(0);
    float tArea(0); // 上面積
    float bArea(0); // 底面積

    for (int i = 1; i <= mStack; ++i) {
        bArea = 0;
        if (i != mStack) {
            for (int j = 0; j < mSlice; ++j) {

                KVector point(getVertex(i, j));
                bArea += (point - getVertex(i, j + 1)).length() // 円周
                        * (point - mPosition).length(); // 半径
            }
        }
        KVector height((mVertex[i][0] - mVertex[i - 1][0]).extractParallel(axis));
        bArea /= 2; // 三角形
        volume += (tArea + bArea) / (tArea && bArea ? 2 : 3) // 平均面積
                * height.length() * Math::sign(height.dot(axis)); // 高さ
        tArea = bArea;
    }
    return volume / 1.514835364; // 謎の値で割ります。(要考察)
}

void WaterBalloon::translate(const KVector & aPosition) {
    KVector move(aPosition - mPosition);
    for (int i = 0; i <= mStack; ++i) {
        for (int j = 0; j < mSlice; ++j) {
            if (validIndex(i, j)) {
                mPoints[i][j]->setPosition(mPoints[i][j]->position() + move);
            }
        }
    }
    mPosition = aPosition;
}

