/**
 * @file   Device.h
 * @brief  Device
 * @author Maeda Takumi
 */
#ifndef DEVICE_H
#define DEVICE_H

#include "Bulletin.h"

class Hero;

/**
 * @brief  \~english  UI construction System
 * @brief  \~japanese UI構築システム
 * @author \~ Maeda Takumi
 */
class Device {
private:
    KGLUI mUI; ///< UI

    /**
     * @brief \~english  user information
     * @brief \~japanese ユーザー情報
     */
    const Hero* mUser;
public:
    /**
     * @brief \~english  message system
     * @brief \~japanese メッセージシステム
     */
    static Bulletin sBulletin;

    Device(const KCamera& aCamera, const Hero& aUser);
    virtual ~Device() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw();
};

#endif /* DEVICE_H */

