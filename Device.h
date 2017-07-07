/**
 * @file   Device.h
 * @brief  Device
 * @author Maeda Takumi
 */
#ifndef DEVICE_H
#define DEVICE_H

#include "Object.h"

class BackPack;
class Bulletin;
class Character;
class Command;
class Hero;
class Mapping;
class Wallet;

/**
 * @brief  \~english  UI construction System
 * @brief  \~japanese UI構築システム
 * @author \~ Maeda Takumi
 */
class Device final : public Object {
public:
    /**
     * @brief \~english  Block size of UI building
     * @brief \~japanese UI構築のブロックサイズ
     */
    static const int UI_SIZE;
private:
    /* ----- 描画領域 ----- */
    static const KRect AREA_BULLETIN;
    static const KRect AREA_BACKPACK;
    static const KRect AREA_STATUS;
    static const KRect AREA_SEEING;
    static const KRect AREA_FLOOR;
    static const KRect AREA_WEAPON;
    static const KRect AREA_BULLET;

    /* ----- 描画色   ----- */
    static const color COLOR_STATUS_BAR;
    static const color COLOR_HP_MAX;
    static const color COLOR_HP_MID;
    static const color COLOR_HP_MIN;
    static const color COLOR_STAMINA;

    KGLUI& mUI;
    KTexture& mScreen;

    // HPバーを描画します。
    void drawHPBar(const Character& aCharacter, const KRect& aRect);
public:
    /**
     * \~english
     * @param aWindow window for drawing
     * @param aCamera camera for drawing
     * \~japanese
     * @param aWindow 描画対象のウィンドウ
     * @param aCamera 描画対象のカメラ
     */
    Device(KGLUI& aUI);
    virtual ~Device() = default;

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
     * @brief draw status of player.
     * @param aPlayer player
     * \~japanese
     * @brief プレイヤーのステータスを描画します。
     * @param aPlayer プレイヤー
     */
    void drawPlayerStatus(const Hero& aPlayer);
    /**
     * \~english
     * @brief draw status of Character who Hero is seeing.
     * @param aState game state
     * \~japanese
     * @brief 視認キャラクターのステータスを描画します。
     * @param aState ゲーム状態
     */
    void drawCharacterStatus(const GameState& aState);
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
     * @brief draw floor number.
     * @param aState state of game
     * \~japanese
     * @brief 階層数を描画します。
     * @param aState ゲーム状態
     */
    void drawFloor(const GameState& aState);

    /**
     * \~english
     * @brief draw equipment of weapon.
     * @param aState state of game
     * \~japanese
     * @brief 武器装備を描画します。
     * @param aState ゲーム状態
     */
    void drawWeapon(const GameState& aState);
    /**
     * \~english
     * @brief draw remain bullet number.
     * @param aPlayer player
     * \~japanese
     * @brief 残弾数を描画します。
     * @param aPlayer プレイヤー
     */
    void drawBullet(const Hero& aPlayer);

    KGLUI& UI();
    const KGLUI& UI() const;
    KTexture& screen();
};

#endif /* DEVICE_H */

