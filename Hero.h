/**
 * @file   Hero.h
 * @brief  Hero
 * @author Maeda Takumi
 */
#ifndef HERO_H
#define HERO_H

#include "Character.h"

#include "BackPack.h"

class Device;

/**
 * @brief  \~english  Player Character
 * @brief  \~japanese プレイヤーキャラクター
 * @author \~ Maeda Takumi
 */
class Hero : public Character {
    friend class Device;
private:
    KFPSCamera mEyeCamera;
    Device* mDevice;
    KHandLight light;

    /**
     * @brief \~english  backpack of Item
     * @brief \~japanese アイテム袋
     */
    BackPack mBackPack;

    /**
     * @brief \~english  reach of punchable
     * @brief \~japanese 殴れる距離
     */
    float mPunchReach;
    /**
     * @brief \~english  anble of punchable
     * @brief \~japanese 殴れる角度
     */
    float mPunchAngle;

    /**
     * @brief \~english  whether clear current floar
     * @brief \~japanese 現在フロアをクリアしているか
     */
    bool mClear;
public:
    Hero();
    virtual ~Hero();

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

    /**
     * @brief \~english  processing when a new floar is reached.
     * @brief \~japanese 新しい階層に到達したときの処理を記述します。
     */
    void newFloar();

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
     * @brief \~english  die.
     * @brief \~japanese 死にます。
     */
    void die() override;

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
     * @brief \~english  equip selected Item.
     * @brief \~japanese 選択されているアイテムを装備します。
     */
    void equipItem();

    /**
     * @brief プレイヤー座標の設定
     * @param aPosition プレイヤー座標
     */
    void setPosition(const KVector& aPosition) override;

    /**
     * \~english
     * @brief  get whether clear.
     * @return whether clear current floar
     * \~
     * @brief  クリア状態を取得します。
     * @return 現在フロアのクリア状況
     */
    bool isClear() const;
};

#endif /* HERO_H */

