/**
 * @file   Bulletin.cpp
 * @brief  Bulletin
 * @author Maeda Takumi
 */
#ifndef BULLETIN_H
#define BULLETIN_H

#include "main.h"

/**
 * @brief  \~english  Bulletin System
 * @brief  \~japanese 掲示板システム
 * @author \~ Maeda Takumi
 */
class Bulletin {
private:
    static const int LOG_SIZE = 100;
    String mMessage[LOG_SIZE];
    int mSize;
    int mTail;
public:
    Bulletin();
    Bulletin(const Bulletin& orig);
    virtual ~Bulletin();

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
     * @brief write message.
     * @param aMessage additional message
     * \~japanese
     * @brief メッセージを追加します。
     * @param aMessage 追加メッセージ
     */
    void write(const String& aMessage);
};

#endif /* BULLETIN_H */

