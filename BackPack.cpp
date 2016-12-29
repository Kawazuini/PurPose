/**
 * @file   BackPack.cpp
 * @brief  BackPack
 * @author Maeda Takumi
 */
#include "BackPack.h"

#include "Device.h"
#include "Item.h"

BackPack::BackPack() {
    mCursor = 0;
}

BackPack::~BackPack() {
    for (Stack<Item*>* i : mBackPack) {
        while (!i->empty()) {
            delete i->top();
            i->pop();
        }
        delete i;
    }
}

bool BackPack::add(Item * const aItem) {
    String name = aItem->name();
    for (Stack<Item*>* i : mBackPack) {
        // すでにバッグに入っている
        if (i->top()->name() == name) {
            i->push(aItem);
            return true;
        }
    }
    // 新規アイテム登録
    Stack<Item*>* tmp = new Stack<Item*>();
    tmp->push(aItem);
    mBackPack.push_back(tmp);
    return true;
}

void BackPack::selectChange(const int& aAmount) {
    mCursor += aAmount;
    if (mCursor > (int) (mBackPack.size() - 1)) mCursor = 0;
    else if (mCursor < 0) mCursor = mBackPack.size() - 1;
}

Item* BackPack::takeOut() {
    Stack<Item*>* cursor = *(mBackPack.begin() + mCursor);
    if (cursor->size() > 0) {
        Item* item = cursor->top();
        cursor->pop();
        if (cursor->size() <= 0) { // アイテム使い切り
            mBackPack.erase(mBackPack.begin() + mCursor);
            // カーソルが末尾
            if (!(mBackPack.size() - mCursor)) mCursor = Math::max(0, mCursor - 1);
        }
        return item;
    }
    return NULL;
}

Item* BackPack::lookAt() {
    return mBackPack[mCursor]->top();
}

void BackPack::draw(KGLUI& aGLUI, const KRect& aRect) const {
    static const color BASE = 0xff00ff00;
    aGLUI.mScreen->clearRect(aRect);
    aGLUI.mScreen->drawClearRect(aRect, BASE);
    aGLUI.mScreen->drawClearRect(KRect(aRect.x + 2, aRect.y + 2, aRect.width - 4, aRect.height - 4), BASE);
    aGLUI.mScreen->drawRect(KRect(aRect.x + 5, aRect.y + 5 + mCursor * 16, aRect.width - 8, 16), BASE);

    int count = 0;
    for (Stack<Item*>* i : mBackPack) {
        aGLUI.mScreen->drawText(CHARSET_MINI, i->top()->name(), KVector(aRect.x + 5, aRect.y + count * 16 + 5), 0);
        aGLUI.mScreen->drawText(CHARSET_MINI, toString(i->size()), KVector(aRect.right() - 32 - 5, aRect.y + count * 16 + 5), 0);
        ++count;
    }
}

