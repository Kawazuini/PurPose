/**
 * @file   Bulletin.cpp
 * @brief  Bulletin
 * @author Maeda Takumi
 */
#include "Bulletin.h"

const int Bulletin::LOG_SIZE;

Bulletin::Bulletin() {
    mSize = mTail = 0;
}

Bulletin::Bulletin(const Bulletin& orig) {
    for (int i = LOG_SIZE - 1; i >= 0; --i) {
        mMessage[i] = orig.mMessage[i];
    }
    mSize = orig.mSize;
    mTail = orig.mTail;
}

Bulletin::~Bulletin() {
}

void Bulletin::draw(KGLUI& aGLUI, const KCharset& aCharset, const KRect & aArea) const {
    static int pTail = 0;
    if (pTail != mTail) {
        pTail = mTail;

        aGLUI.mScreen->clearRect(aArea);
        aGLUI.mScreen->drawRect(aArea, 0x40000000);

        int line = aArea.height / (aCharset.mSize * 2);
        for (int i = 0; i < line; ++i) {
            int index = (mSize < line ? 0 : mTail - line) + i;
            // 0 ~ LOG_SIZEでループ
            index = index < 0 ? LOG_SIZE + index : (index >= LOG_SIZE ? index - LOG_SIZE : index);
            aGLUI.mScreen->drawText(
                    aCharset, mMessage[index],
                    aArea.start() + KVector(0, aCharset.mSize * 2) * i,
                    0xffffffff
                    );
        }
    }
}

void Bulletin::write(const String & aMessage) {
    if (mSize < 100) ++mSize;
    mMessage[mTail++] = aMessage;
    if (mTail >= 100) mTail = 0;
}

