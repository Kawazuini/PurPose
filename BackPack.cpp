/**
 * @file   BackPack.cpp
 * @brief  BackPack
 * @author Maeda Takumi
 */
#include "BackPack.h"

#include "Item.h"

BackPack::BackPack() :
mCursor(0) {
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
    String name(aItem->mParameter.mName);
    for (Stack<Item*>* i : mBackPack) {
        // すでにバッグに入っている
        if (i->top()->mParameter.mName == name) {
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
    if (!mBackPack.empty()) {
        Stack<Item*>* cursor = mBackPack[mCursor];
        if (!cursor->empty()) {
            Item* item = cursor->top();
            cursor->pop();
            if (cursor->empty()) { // アイテム使い切り
                mBackPack.erase(mBackPack.begin() + mCursor);
                // カーソルが末尾
                if (!(mBackPack.size() - mCursor))
                    mCursor = Math::max(0, mCursor - 1);
            }
            return item;
        }
        return NULL;
    }
}

Item* BackPack::lookAt() {
    if (!mBackPack.empty()) {
        return mBackPack[mCursor]->top();
    } else return NULL;
}

const Item* BackPack::lookAt() const {
    if (!mBackPack.empty()) {
        return mBackPack[mCursor]->top();
    } else return NULL;
}

void BackPack::draw(KGLUI& aGLUI, const KRect& aRect) const {
    static const color BASE = 0xff00ff00;
    aGLUI.screen().clearRect(aRect);
    aGLUI.screen().drawClearRect(aRect, BASE);
    aGLUI.screen().drawClearRect(KRect(aRect.x + 2, aRect.y + 2, aRect.width - 4, aRect.height - 4), BASE);
    aGLUI.screen().drawRect(KRect(aRect.x + 5, aRect.y + 5 + mCursor * 16, aRect.width - 8, 16), BASE);

    int count = 0;
    for (Stack<Item*>* i : mBackPack) {
        aGLUI.screen().drawText(CHARSET_MINI, i->top()->mParameter.mName, KVector(aRect.x + 5, aRect.y + count * 16 + 5), 0);
        aGLUI.screen().drawText(CHARSET_MINI, toString(i->size()), KVector(aRect.right() - 32 - 5, aRect.y + count * 16 + 5), 0);
        ++count;
    }
}

