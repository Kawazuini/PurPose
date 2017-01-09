/**
 * @file   Device.h
 * @brief  Device
 * @author Maeda Takumi
 */
#ifndef DEVICE_H
#define DEVICE_H

#include "Bulletin.h"

#include "GameState.h"

/**
 * @brief  \~english  UI construction System
 * @brief  \~japanese UI構築システム
 * @author \~ Maeda Takumi
 */
class Device : public KDrawer, public KUpdater {
private:
    /**
     * @brief \~english  Block size of UI building
     * @brief \~japanese UI構築のブロックサイズ
     */
    static const int UI_SIZE;

    /**
     * @brief \~english  Stage drawing area
     * @brief \~japanese マップ描画領域
     */
    static const KRect MAP_AREA;
    /**
     * @brief \~english  BackPack drawing area
     * @brief \~japanese アイテム欄描画領域
     */
    static const KRect BACKPACK_AREA;
    /**
     * @brief \~english  Bulletin drawing area
     * @brief \~japanese メッセージ描画領域
     */
    static const KRect BULLETIN_AREA;
    /**
     * @brief \~english  Character HP drawing area
     * @brief \~japanese キャラHP描画領域
     */
    static const KRect HPBAR_AREA;
    static const color HPBAR_COLOR;
    static const color MAXHP_COLOR;
    static const color MIDHP_COLOR;
    static const color MINHP_COLOR;

    KGLUI mUI; ///< UI

    /**
     * @brief \~english  information of game state
     * @brief \~japanese ゲーム状態の情報
     */
    const GameState& mGameInfo;
public:
    /**
     * @brief \~english  message system
     * @brief \~japanese メッセージシステム
     */
    static Bulletin sBulletin;

    Device(const GameState& aGameInfo);
    virtual ~Device() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;
    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    void update() override;
};

#endif /* DEVICE_H */

