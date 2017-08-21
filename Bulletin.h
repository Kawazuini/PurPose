/**
 * @file   Bulletin.cpp
 * @brief  Bulletin
 * @author Maeda Takumi
 */
#ifndef BULLETIN_H
#define BULLETIN_H

#include "Message.h"

/**
 * @brief  \~english  Bulletin System
 * @brief  \~japanese 掲示板システム
 * @author \~ Maeda Takumi
 */
class Bulletin : public KDrawer, private KUpdater {
private:
    /* メッセージ表示行数 */ static const int MESSAGE_SIZE;
    /* メッセージ表示領域 */ static const KRect MESSAGE_AREA;
    /* メッセージ更新頻度 */ static const int MESSAGE_WAIT;
    /* メッセージログ数   */ static const int LOG_SIZE;

    /* フレームカウント */ int mFrameCount;
    /* 更新の必要性     */ bool mUpdated;

    /* 表示待ちメッセージ */ Queue<Message> mSource;
    /* 表示中メッセージ   */ Vector<Message> mMessage;
    /* 表示済みメッセージ */ Vector<Message> mLog;

    /* メッセージ表示用UI */ KGLUI mMessageUI;
    /* ログ表示用UI       */ KGLUI mLogUI;

    inline void message2log() { // message -> log
        mUpdated = true;
        // ログが埋まっているときはログから削除
        if (mLog.size() >= LOG_SIZE) mLog.erase(mLog.begin()); // log -> 

        mLog.push_back(mMessage.front());
        mMessage.erase(mMessage.begin());
    }
public:
    /// @brief \~english  whether drawing of log
    /// @brief \~japanese ログの描画を行うか
    bool mDrawLog;

    Bulletin(const KCamera& aCamera);
    virtual ~Bulletin() = default;

    void draw() const override;
    void update() override;

    /// @brief \~english  clear message
    /// @brief \~japanese メッセージの消去
    void clear();

    /**
     * \~english
     * @brief write message.
     * @param aMessage additional message
     * \~japanese
     * @brief メッセージを追加します。
     * @param aMessage 追加メッセージ
     */
    void write(const String& aMessage);
    /**
     * \~english
     * @brief write message.
     * @param aMessage additional message
     * \~japanese
     * @brief メッセージを追加します。
     * @param aMessage 追加メッセージ
     */
    void write(const Message& aMessage);
    /// @brief \~english  refrect message context.
    /// @brief \~japanese メッセージ内容を即座に反映します。
    void flush();
};

#endif /* BULLETIN_H */

