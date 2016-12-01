/**
 * @file   MessageWindow.h
 * @brief  MessageWindow
 * @author Maeda Takumi
 */
#ifndef MESSAGEWINDOW_H
#define MESSAGEWINDOW_H

#include "main.h"

/**
 * @brief  \~english  Message Text System
 * @brief  \~japanese メッセージシステム
 * @author \~ Maeda Takumi
 */
class MessageWindow {
private:
    static const int LOG_SIZE = 100;
    String mMessage[LOG_SIZE];
    int mSize;
    int mTail;
public:
    MessageWindow();
    MessageWindow(const MessageWindow& orig);
    virtual ~MessageWindow();

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
     * @brief add message.
     * @param aMessage additional message
     * \~japanese
     * @brief メッセージを追加します。
     * @param aMessage 追加メッセージ
     */
    void push(const String& aMessage);
};

#endif /* MESSAGEWINDOW_H */

