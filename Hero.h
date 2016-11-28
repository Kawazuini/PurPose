/**
 * @file Hero.h
 * @brief Hero
 */
#ifndef HERO_H
#define HERO_H

#include "Character.h"

#include "BackPack.h"

/** @brief 主人公 */
class Hero : public Character {
private:
    KFPSCamera* mEyeCamera;
    KGLUI* mDevice;
    KHandLight light;

    /** @brief バックパック */ BackPack mBackPack;

    /** @brief 移動可能サークルテクスチャ */ KTexture* mCircleTexture;

    void drawCircle() const;
public:
    Hero();
    virtual ~Hero();

    /** @brief 更新処理 */ virtual void draw() override;
    /** @brief 描画処理 */ virtual void update() override;

    /**
     * @brief WASD移動
     * @param aMovement 視点からの移動ベクトル
     * @return 移動できたか
     */
    bool move(const KVector& aMovement) override;
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
