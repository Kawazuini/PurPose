/**
 * @file   Bulletin.cpp
 * @brief  Bulletin
 * @author Maeda Takumi
 */
#include "Bulletin.h"

const int Bulletin::MESSAGE_SIZE(36);
const KRect Bulletin::MESSAGE_AREA(KVector(1, 3) * 16, KVector(40, 3 + Bulletin::MESSAGE_SIZE) * 16);
const int Bulletin::MESSAGE_WAIT(30);
const int Bulletin::LOG_SIZE(100);

Bulletin::Bulletin(const KCamera& aCamera) :
mFrameCount(0),
mUpdated(false),
mDrawLog(false),
mMessageUI(aCamera),
mLogUI(aCamera),
mDraw(false) {
    KDrawer::remove();
}

void Bulletin::draw() const {
    if (mDraw) {
        if (!mDrawLog) mMessageUI.draw();
        else mLogUI.draw();
    }
}

void Bulletin::update() {
    const int size(Math::max((int) mSource.size(), 1));
    if (mFrameCount++ >= MESSAGE_WAIT / size) {
        mFrameCount = 0;
        if (!mSource.empty()) {
            mUpdated = true;
            // 表示が埋まっているときはログに移動
            if (mMessage.size() >= MESSAGE_SIZE) message2log();

            // source -> message
            mMessage.push_back(mSource.front());
            mSource.pop();
        } else if (!mMessage.empty()) message2log();
    } else mUpdated = false;

    if (mUpdated) {
        { // メッセージ更新
            KTexture & screen(mMessageUI.screen());
            screen.clearRect(MESSAGE_AREA);

            for (int i = 0, i_e(Math::min(MESSAGE_SIZE, (int) mMessage.size())); i < i_e; ++i) {
                screen.drawText(
                        CHARSET_SMALL, mMessage[i].mMessage,
                        MESSAGE_AREA.begin() + KVector(0, CHARSET_SMALL.mSize * 2) * i,
                        mMessage[i].mColor
                        );
            }
            mMessageUI.refrect();
        }
        { // ログ更新
            KTexture & screen(mLogUI.screen());
            screen.clearRect(MESSAGE_AREA);

            int line(Math::min((int) mLog.size(), MESSAGE_SIZE));
            int logBegin(mLog.size() - line); // 描画開始位置を探す
            for (int i = 0; i < line; ++i) {
                int log(i + logBegin);
                screen.drawText(
                        CHARSET_SMALL, mLog[log].mMessage,
                        MESSAGE_AREA.begin() + KVector(0, CHARSET_SMALL.mSize * 2) * i,
                        mLog[log].mColor
                        );
            }
            mLogUI.refrect();
        }
    }

    mDrawLog = false;
}

void Bulletin::clear() {
    while (!mSource.empty()) mSource.pop();
    mMessage.clear();
    mLog.clear();
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

