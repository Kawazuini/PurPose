/**
 * @file   Hero.h
 * @brief  Hero
 * @author Maeda Takumi
 */
#ifndef HERO_H
#define HERO_H

#include "BackPack.h"
#include "Character.h"

class Device;

/**
 * @brief  \~english  Player Character
 * @brief  \~japanese プレイヤーキャラクター
 * @author \~ Maeda Takumi
 */
class Hero : public Character {
private:
    KFPSCamera mEyeCamera;
    KHandLight light;

    /**
     * @brief \~english  backpack of Item
     * @brief \~japanese アイテム袋
     */
    BackPack mBackPack;

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
    Hero(List<Character*>& aList);
    virtual ~Hero();

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
     * @brief \~english  reset status
     * @brief \~japanese 状態を初期化します。
     */
    void reset();

    /**
     * \~english
     * @brief processing when a new floar is reached.
     * @param aState state of game
     * \~japanese
     * @brief 新しい階層に到達したときの処理を記述します。
     * @param aState ゲーム状態
     */
    void newFloar(GameState& aState);

    /**
     * \~english
     * @brief move position of player
     * @param aDirection moving direction
     * \~japanese
     * @brief プレイヤーを移動させます。
     * @param aDirection 移動方向
     */
    void move(GameState& aState, const KVector& aDirection) override;
    /**
     * @brief \~english  synchronize position.
     * @brief \~japanese 位置を同期します。
     */
    virtual void syncPosition();
    /**
     * @brief \~english  
     * @brief \~japanese 攻撃
     */
    void attack(GameState& aState) override;

    /**
     * @brief \~english  punch!
     * @brief \~japanese 殴る!
     */
    void punch(GameState& aState);

    /**
     * @brief 首を振る
     * @param aAngleV 上下角度
     * @param aAngleH 左右角度
     */
    void swivel(const float& aAngleV, const float& aAngleH);

    /**
     * \~english
     * @brief pick up Item.
     * @param aItem picked Item
     * \~japanese
     * @brief アイテムを拾います。
     * @param aItem 拾うアイテム
     */
    void pickUp(GameState& aState, Item * const aItem);
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
    void useItem(GameState& aState);
    /**
     * @brief \~english  equip selected Item.
     * @brief \~japanese 選択されているアイテムを装備します。
     */
    void equipItem(GameState& aState);
    /**
     * @brief \~english  throw selected Item.
     * @brief \~japanese 選択されているアイテムを投擲します。
     */
    void throwItem(GameState& aState);

    /**
     * \~english
     * @brief  get whether clear.
     * @return whether clear current floar
     * \~
     * @brief  クリア状態を取得します。
     * @return 現在フロアのクリア状況
     */
    bool isClear() const;

    const BackPack& backPack() const;
};

#endif /* HERO_H */

