/**
 * @file   Bulletin.cpp
 * @brief  Bulletin
 * @author Maeda Takumi
 */
#include "Bulletin.h"

const int Bulletin::MESSAGE_WAIT(30);
const int Bulletin::MESSAGE_SIZE(33);
const int Bulletin::LOG_SIZE(100);

Bulletin::Bulletin() :
mFrameCount(0),
mUpdated(false),
mDrawLog(false) {
}

void Bulletin::update() {
    int size(Math::max((int) mSource.size(), 1));
    if (mFrameCount++ >= MESSAGE_WAIT / size) {
        mFrameCount = 0;
        if (!mSource.empty()) {
            mUpdated = true;
            // 表示が埋まっているときはログに移動
            if (mMessage.size() + 1 > MESSAGE_SIZE) {
                // ログが埋まっているときはログから削除
                if (mLog.size() + 1 > LOG_SIZE) {
                    mLog.erase(mLog.begin()); // log -> 
                }
                // message -> log
                mLog.push_back(mMessage.front());
                mMessage.erase(mMessage.begin());
            }
            // source -> message
            mMessage.push_back(mSource.front());
            mSource.pop();
        } else {
            if (!mMessage.empty()) {
                mUpdated = true;
                // ログが埋まっているときはログから削除
                if (mLog.size() + 1 > LOG_SIZE) {
                    mLog.erase(mLog.begin()); // log -> 
                }
                // message -> log
                mLog.push_back(mMessage.front());
                mMessage.erase(mMessage.begin());
            }
        }
    } else mUpdated = false;
    mDrawLog = false;
}

void Bulletin::clear() {
    while (!mSource.empty()) mSource.pop();
    mMessage.clear();
    mLog.clear();
}

void Bulletin::draw(KGLUI& aGLUI, const KCharset& aCharset, const KRect & aArea) const {
    if (mUpdated && !mDrawLog) {
        KTexture & screen(aGLUI.screen());
        screen.clearRect(aArea);

        int line(aArea.height / (aCharset.mSize * 2)); // 描画ライン数

        for (int i = 0, i_e = Math::min((int) mMessage.size(), line); i < i_e; ++i) {
            screen.drawText(
                    aCharset, mMessage[i].mMessage,
                    aArea.begin() + KVector(0, aCharset.mSize * 2) * i,
                    mMessage[i].mColor
                    );
        }
    }
}

void Bulletin::forcedDraw(KGLUI& aGLUI, const KCharset& aCharset, const KRect& aArea) {

    mUpdated = true;
    draw(aGLUI, aCharset, aArea);
}

void Bulletin::drawLog(KGLUI& aGLUI, const KCharset& aCharset, const KRect& aArea) {
    mDrawLog = true;
    KTexture & screen(aGLUI.screen());
    screen.clearRect(aArea);

    int line(aArea.height / (aCharset.mSize * 2)); // 描画ライン数

    int logBegin(mLog.size() - Math::min((int) mLog.size(), line)); // 描画開始位置を探す
    for (int i = 0, i_e = Math::min((int) mLog.size(), line); i < i_e; ++i) {
        int log(i + logBegin);
        screen.drawText(
                aCharset, mLog[log].mMessage,
                aArea.begin() + KVector(0, aCharset.mSize * 2) * i,
                mLog[log].mColor
                );
    }
}

void Bulletin::write(const String& aMessage) {

    mSource.push(Message(aMessage));
}

void Bulletin::write(const Message& aMessage) {

    mSource.push(aMessage);
}

void Bulletin::flush() {
    while (!mSource.empty()) {
        mFrameCount = MESSAGE_WAIT;
        update();
    }
    mFrameCount = MESSAGE_WAIT;
}

