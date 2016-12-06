/**
 * @file   BackPack.cpp
 * @brief  BackPack
 * @author Maeda Takumi
 */
#include "BackPack.h"

const int BackPack::MAX_CAPACITY;
const int BackPack::MAX_PER_CAPACITY;

BackPack::BackPack() {
    mCursor = mStack = 0;
    for (int i = MAX_PER_CAPACITY; i >= 0; --i) {
        mPerStack[i] = 0;
    }
}

void BackPack::add(Item * const aItem) {
    String name = aItem->name();
    for (int i = 0; i < mStack; ++i) {
        if (name == mItemList[i][0]->name()) {
            mItemList[i][mPerStack[i]] = aItem;
            ++mPerStack[i];
            return;
        }
    }
    mItemList[mStack][0] = aItem;
    ++mPerStack[mStack];
    ++mStack;
}

void BackPack::selectChange(const int& aAmount) {
    mCursor += aAmount;
    if (mCursor > mStack - 1) mCursor = 0;
    else if (mCursor < 0) mCursor = mStack - 1;
}

Item* BackPack::takeOut() {
    if (mPerStack[mCursor] > 0) {
        --mPerStack[mCursor];
        if (mPerStack[mCursor] <= 0) { // アイテム使い切り
            --mStack;
            for (int i = 0; i < mStack - mCursor; ++i) {
                // アイテムの遷移
                for (int j = 0; j < mPerStack[mCursor + i + 1]; ++j) {
                    mItemList[mCursor + i][j] = mItemList[mCursor + i + 1][j];
                }
                // アイテム個数の遷移
                mPerStack[mCursor + i] = mPerStack[mCursor + i + 1];
            }
            // カーソルが末尾
            if (!(mStack - mCursor)) mCursor = Math::max(0, mCursor - 1);
        }
        Item* take = mItemList[mCursor][mPerStack[mCursor]];
        mItemList[mCursor][mPerStack[mCursor]] = NULL;
        return take;
    }
    return NULL;
}

Item* BackPack::lookAt() {
    return mItemList[mCursor][mPerStack[mCursor] - 1];
}

void BackPack::draw(KGLUI& aGLUI, const KRect& aRect) const {
    static const color BASE = 0xff00ff00;
    aGLUI.mScreen->clearRect(aRect);
    aGLUI.mScreen->drawClearRect(aRect, BASE);
    aGLUI.mScreen->drawClearRect(KRect(aRect.x + 2, aRect.y + 2, aRect.width - 4, aRect.height - 4), BASE);
    aGLUI.mScreen->drawRect(KRect(aRect.x + 5, aRect.y + 5 + mCursor * 16, aRect.width - 8, 16), BASE);

    for (int i = 0; i < mStack; ++i) {
        aGLUI.mScreen->drawText(CHARSET_MINI, mItemList[i][0]->name(), KVector(aRect.x + 5, aRect.y + i * 16 + 5), 0);
        aGLUI.mScreen->drawText(CHARSET_MINI, toString(mPerStack[i]), KVector(aRect.right() - 32 - 5, aRect.y + i * 16 + 5), 0);
    }
}
