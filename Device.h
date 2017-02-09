/**
 * @file   Device.h
 * @brief  Device
 * @author Maeda Takumi
 */
#ifndef DEVICE_H
#define DEVICE_H

#include "Bulletin.h"
#include "Object.h"

class BackPack;
class Command;
class Hero;
class Mapping;

/**
 * @brief  \~english  UI construction System
 * @brief  \~japanese UI構築システム
 * @author \~ Maeda Takumi
 */
class Device : public KDrawer, public Object {
public:
    /**
     * @brief \~english  Block size of UI building
     * @brief \~japanese UI構築のブロックサイズ
     */
    static const int UI_SIZE;
private:
    /**
     * @brief \~english  Bulletin drawing area
     * @brief \~japanese メッセージ描画領域
     */
    static const KRect AREA_BULLETIN;
    /**
     * @brief \~english  mapping drawing area
     * @brief \~japanese マップ描画領域
     */
    static const KRect AREA_MAP;
    /**
     * @brief \~english  BackPack drawing area
     * @brief \~japanese アイテム欄描画領域
     */
    static const KRect AREA_BACKPACK;
    /**
     * @brief \~english  Character HP drawing area
     * @brief \~japanese キャラHP描画領域
     */
    static const KRect AREA_HPBAR;
    static const KRect AREA_FLOAR;
    static const KRect AREA_BULLET;
    static const color COLOR_HPBAR;
    static const color COLOR_MAXHP;
    static const color COLOR_MIDHP;
    static const color COLOR_MINHP;

    KGLUI mUI; ///< UI

    /**
     * @brief \~english  
     * @brief \~japanese マップ描画更新頻度
     */
    int mMappingUpdatePeriod;
public:
    Device(const KCamera& aCamera);
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
    void update(GameState& aState) override;

    /**
     * \~english
     * @brief forced drawing.
     * @param aState state of game
     * \~japanese
     * @brief 強制敵に描画を行います。
     * @param aState ゲーム状態
     */
    void refresh(GameState& aState);

    /**
     * \~english
     * @brief draw mapping information
     * @param aMapping mapping information
     * @param aPlayer  player
     * \~japanese
     * @brief マッピング情報の描画
     * @param aMapping マッピング情報
     * @param aPlayer  プレイヤー
     */
    void drawMap(const Mapping& aMapping, const Hero& aPlayer);
    /**
     * \~english
     * @brief drawing HP of player
     * @param aPlayer player
     * \~japanese
     * @brief プレイヤーのHPを描画します。
     * @param aPlayer プレイヤー
     */
    void drawHP(const Hero& aPlayer);
    /**
     * \~english
     * @brief draw backpack information.
     * @param aBackPack backpack information
     * \~japanese
     * @brief バックパック情報を描画します。
     * @param aBackPack バックパック情報
     */
    void drawBackPack(const BackPack& aBackPack);
    /**
     * \~english
     * @brief draw message log.
     * @param aBulletin bulletin system
     * \~japanese
     * @brief メッセージログを描画します。
     * @param aBulletin 掲示板システム
     */
    void drawMessageLog(Bulletin& aBulletin);
    /**
     * \~english
     * @brief drawing command.
     * @param aCommand command
     * \~japanese
     * @brief コマンドを描画します。
     * @param aCommand コマンド
     */
    void drawCommand(const Command& aCommand);

    /**
     * \~english
     * @brief draw floar number.
     * @param aState state of game
     * \~japanese
     * @brief 階層数を描画します。
     * @param aState ゲーム状態
     */
    void drawFloar(const GameState& aState);
    /**
     * \~english
     * @brief draw remain bullet number.
     * @param aPlayer player
     * \~japanese
     * @brief 残弾数を描画します。
     * @param aPlayer プレイヤー
     */
    void drawBullet(const Hero& aPlayer);

    /***/
    KGLUI& UI();
};

#endif /* DEVICE_H */

