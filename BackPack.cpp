/**
 * @file BackPack.cpp
 * @brief BackPack
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

BackPack::~BackPack() {
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

void BackPack::selectChange(const int& aMoment) {
    mCursor += aMoment;
}

void BackPack::draw(KGLUI& aGLUI, const KRect& aRect) {
    static const color BASE = 0xff00ff00;
    aGLUI.mScreen->clearRect(aRect);
    aGLUI.mScreen->drawClearRect(aRect, BASE);
    aGLUI.mScreen->drawClearRect(KRect(aRect.x + 2, aRect.y + 2, aRect.width - 4, aRect.height - 4), BASE);
    aGLUI.mScreen->drawRect(KRect(aRect.x + 5, aRect.y + 5 + mCursor * 16, aRect.width - 8, 16), BASE);

    for (int i = 0; i < mStack; ++i) {
        aGLUI.mScreen->drawText(CHARSET_MINI, mItemList[i][0]->name(), KVector(aRect.x + 5, i * 16 + 5), 0);
        aGLUI.mScreen->drawText(CHARSET_MINI, toString(mPerStack[i]), KVector(aRect.right() - 32 - 5, i * 16 + 5), 0);
    }
}
