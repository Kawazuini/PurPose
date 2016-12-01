/**
 * @file   MessageWindow.cpp
 * @brief  MessageWindow
 * @author Maeda Takumi
 */
#include "MessageWindow.h"

const int MessageWindow::LOG_SIZE;

MessageWindow::MessageWindow() {
    mSize = 0;
    mTail = 0;
}

MessageWindow::MessageWindow(const MessageWindow & orig) {
}

MessageWindow::~MessageWindow() {
}

void MessageWindow::draw(KGLUI& aGLUI, const KCharset& aCharset, const KRect & aArea) const {
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

void MessageWindow::push(const String & aMessage) {
    if (mSize < 100) ++mSize;
    mMessage[mTail++] = aMessage;
    if (mTail >= 100) mTail = 0;
}

