/**
 * @file   Bulletin.cpp
 * @brief  Bulletin
 * @author Maeda Takumi
 */
#include "Bulletin.h"

const int Bulletin::MESSAGE_WAIT = 20;
const int Bulletin::MESSAGE_SIZE = 10;
const int Bulletin::LOG_SIZE = 100;

Bulletin::Bulletin() {
    mFrameCount = 0;
    mUpdated = false;
}

void Bulletin::update() {
    if (mFrameCount++ > MESSAGE_WAIT) {
        // オーバーフロー予防
        if (mFrameCount > 0xfffffff) mFrameCount = 0;
        if (!mSource.empty()) {
            mUpdated = true;
            mFrameCount = 0;

            if (mMessage.size() + 1 > MESSAGE_SIZE) {
                if (mLog.size() + 1 > LOG_SIZE) {
                    // log -> 
                    mLog.pop();
                }
                // message -> log
                mLog.push(mMessage.front());
                mMessage.erase(mMessage.begin());
            }
            // source -> message
            mMessage.push_back(mSource.front());
            mSource.pop();
        }
    } else mUpdated = false;
}

void Bulletin::draw(KGLUI& aGLUI, const KCharset& aCharset, const KRect & aArea) const {
    if (mUpdated) {
        aGLUI.screen().clearRect(aArea);
        aGLUI.screen().drawRect(aArea, 0x40000000);

        int line = aArea.height / (aCharset.mSize * 2);

        for (int i = 0, i_e = Math::min((int) mMessage.size(), line); i < i_e; ++i) {
            aGLUI.screen().drawText(
                    aCharset, mMessage[i],
                    aArea.start() + KVector(0, aCharset.mSize * 2) * i,
                    0xffffffff
                    );
        }
    }
}

void Bulletin::forcedDraw(KGLUI& aGLUI, const KCharset& aCharset, const KRect& aArea) {
    mUpdated = true;
    draw(aGLUI, aCharset, aArea);
}

void Bulletin::write(const String & aMessage) {
    mSource.push(aMessage);
}

void Bulletin::flush() {
    while (!mSource.empty() && mSource.size() != 1) {
        if (mMessage.size() + 1 > MESSAGE_SIZE) {
            if (mLog.size() + 1 > LOG_SIZE) {
                // log -> 
                mLog.pop();
            }
            // message -> log
            mLog.push(mMessage.front());
            mMessage.erase(mMessage.begin());
        }
        // source -> message
        mMessage.push_back(mSource.front());
        mSource.pop();
    }
    mFrameCount = MESSAGE_WAIT;
}

