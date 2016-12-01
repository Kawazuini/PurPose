/**
 * @file   Hero.h
 * @brief  Hero
 * @author Maeda Takumi
 */
#ifndef HERO_H
#define HERO_H

#include "Character.h"

#include "BackPack.h"

/**
 * @brief  \~english  Character of Player
 * @brief  \~japanese プレイヤーキャラクター
 * @author \~ Maeda Takumi
 */
class Hero : public Character {
private:
    KFPSCamera* mEyeCamera;
    KGLUI* mDevice;
    KHandLight light;

    /** @brief バックパック */ BackPack mBackPack;

    /** @brief 移動可能サークルテクスチャ */ KTexture* mCircleTexture;

    /**
     * @brief \~english  reach of punch
     * @brief \~japanese 殴れる距離
     */
    float mPunchReach;

    void drawCircle() const;
public:
    Hero();
    virtual ~Hero();

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    virtual void draw() override;
    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    virtual void update() override;

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
     * @breif 選択アイテムの変更
     * @param aMoment 選択変更量
     */
    void fumble(const int& aMoment);

    /**
     * @brief プレイヤー座標の設定
     * @param aPosition プレイヤー座標
     */
    void setPosition(const KVector& aPosition) override;
};

#endif /* HERO_H */

