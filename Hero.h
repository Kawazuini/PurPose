/**
 * @file   Hero.h
 * @brief  Hero
 * @author Maeda Takumi
 */
#ifndef HERO_H
#define HERO_H

#include "Character.h"

#include "Device.h"

#include "BackPack.h"

/**
 * @brief  \~english  Player Character
 * @brief  \~japanese プレイヤーキャラクター
 * @author \~ Maeda Takumi
 */
class Hero : public Character {
    friend class Device;
private:
    KFPSCamera* mEyeCamera;
    Device* mDevice;
    KHandLight light;

    /** @brief バックパック */ BackPack mBackPack;

    /**
     * @brief \~english  reach of punch
     * @brief \~japanese 殴れる距離
     */
    float mPunchReach;
public:
    Hero();
    virtual ~Hero();

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;

    void drawHP();
    void drawActionPoint();

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    void update() override;

    /**
     * \~english
     * @brief move position of player
     * @param aDirection moving direction
     * \~japanese
     * @brief プレイヤーを移動させます。
     * @param aDirection 移動方向
     */
    void move(const KVector& aDirection) override;
    /**
     * @brief \~english  
     * @brief \~japanese 攻撃
     */
    void attack() override;

    /**
     * @brief \~english  punch!
     * @brief \~japanese 殴る!
     */
    void punch();

    /**
     * @brief 首を振る
     * @param aAngleV 上下角度
     * @param aAngleH 左右角度
     */
    void swivel(const float& aAngleV, const float& aAngleH);

    /**
     * \~english
     * @brief change selected Item.
     * @param aAmount change amount
     * \~japanese
     * @breif 選択アイテムを変更します。
     * @param aAmount 選択変更量
     */
    void fumble(const int& aAmount);
    /**
     * @brief \~english  use selected Item.
     * @brief \~japanese 選択されているアイテムを使用します。
     */
    void useItem();

    /**
     * @brief プレイヤー座標の設定
     * @param aPosition プレイヤー座標
     */
    void setPosition(const KVector& aPosition) override;
};

#endif /* HERO_H */

