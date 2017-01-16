/**
 * @file   Device.h
 * @brief  Device
 * @author Maeda Takumi
 */
#ifndef DEVICE_H
#define DEVICE_H

#include "Bulletin.h"
#include "Object.h"

class Command;

/**
 * @brief  \~english  UI construction System
 * @brief  \~japanese UI構築システム
 * @author \~ Maeda Takumi
 */
class Device : public KDrawer, public Object {
private:
    /**
     * @brief \~english  Block size of UI building
     * @brief \~japanese UI構築のブロックサイズ
     */
    static const int UI_SIZE;

    /**
     * @brief \~english  mapping drawing area
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
     * @brief \~english  
     * @brief \~japanese マップ描画更新頻度
     */
    int mMappingUpdatePeriod;
public:
    Device();
    virtual ~Device() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;

    /**
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態の情報
     */
    void update(const GameState& aState) override;


    void refresh(const GameState& aState);

    /***/
    void drawHP(const Hero& aPlayer);
    /***/
    void drawCommand(const Command& aChoice);
};

#endif /* DEVICE_H */

