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
class Bulletin : public KUpdater {
private:
    static const int MESSAGE_WAIT;
    static const int MESSAGE_SIZE;
    static const int LOG_SIZE;

    int mFrameCount;
    bool mUpdated;
    bool mDrawLog;

    Queue<Message> mSource;
    Vector<Message> mMessage;
    Vector<Message> mLog;
public:
    Bulletin();
    virtual ~Bulletin() = default;

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    void update() override;

    /**
     * \~english
     * @brief drawing processing
     * @param aGLUI    drawing UI
     * @param aCharset drawing charset
     * @param aArea    drawing area
     * \~japanese
     * @brief 描画処理
     * @param aGLUI    描画UI
     * @param aCharset 描画文字セット
     * @param aArea    描画領域
     */
    void draw(KGLUI& aGLUI, const KCharset& aCharset, const KRect& aArea) const;
    /**
     * \~english
     * @brief forced drawing
     * @param aGLUI    drawing UI
     * @param aCharset drawing charset
     * @param aArea    drawing area
     * \~japanese
     * @brief 強制描画
     * @param aGLUI    描画UI
     * @param aCharset 描画文字セット
     * @param aArea    描画領域
     */
    void forcedDraw(KGLUI& aGLUI, const KCharset& aCharset, const KRect& aArea);
    /**
     * \~english
     * @brief draw log.
     * @param aGLUI    drawing UI
     * @param aCharset drawing charset
     * @param aArea    drawing area
     * \~japanese
     * @brief ログを描画します。
     * @param aGLUI    描画UI
     * @param aCharset 描画文字セット
     * @param aArea    描画領域
     */
    void drawLog(KGLUI& aGLUI, const KCharset& aCharset, const KRect& aArea);
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
    /**
     * @brief \~english  refrect message context.
     * @brief \~japanese メッセージ内容を即座に反映します。
     */
    void flush();
};

#endif /* BULLETIN_H */

