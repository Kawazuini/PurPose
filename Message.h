/**
 * @file   Message.h
 * @brief  Message
 * @author Maeda Takumi
 */
#ifndef MESSAGE_H
#define MESSAGE_H

#include "main.h"

/**
 * @brief \~english  have color and string
 * @brief \~japanese 色と文字列を持つ
 * @author \~ Maeda Takumi
 */
class Message {
public:
    /**
     * @brief \~english  message context
     * @brief \~japanese メッセージ内容
     */
    String mMessage;
    /**
     * @brief \~english  drawing color
     * @brief \~japanese 描画色
     */
    color mColor;

    /**
     * \~english
     * @param aMessage content of message
     * @param aColor   drawing color
     * \~japanese
     * @param aMessage メッセージ内容
     * @param aColor   描画色
     */
    Message(
            const String& aMessage = "",
            const color& aColor = 0xffffffff
            ) :
    mMessage(aMessage),
    mColor(aColor) {
    };
    virtual ~Message() = default;
};

#endif /* MESSAGE_H */

