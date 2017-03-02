/**
 * @file   Hero.h
 * @brief  Hero
 * @author Maeda Takumi
 */
#ifndef HERO_H
#define HERO_H

#include "BackPack.h"
#include "Character.h"

/**
 * @brief  \~english  Player Character
 * @brief  \~japanese プレイヤーキャラクター
 * @author \~ Maeda Takumi
 */
class Hero : public Character {
private:
    /* アイテム袋       */ BackPack mBackPack;
    /* 殴れる角度       */ float mPunchAngle;
    /* フロアクリア状態 */ bool mClear;
    /* 武器構え状態     */ bool mHold;
public:
    /**
     * @brief \~english  max of stamina
     * @brief \~japanese スタミナの最大値
     */
    int mMAXStamina;
    /**
     * @brief \~english  stamina
     * @brief \~japanese スタミナ
     */
    int mStamina;

    Hero();
    ~Hero() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;

    /**
     * @brief \~english  start turn.
     * @brief \~japanese ターンを開始します。
     */
    void turnStart() override;

    /**
     * @brief \~english  reset status.
     * @brief \~japanese 状態を初期化します。
     */
    void reset();

    /**
     * \~english
     * @brief processing when a new floor is reached.
     * @param aState state of game
     * \~japanese
     * @brief 新しい階層に到達したときの処理を記述します。
     * @param aState ゲーム状態
     */
    void newFloor(GameState& aState);

    /**
     * \~english
     * @brief level up
     * @param aState state of game
     * @param aLevel increased value
     * \~japanese
     * @brief レベルアップ
     * @param aState ゲーム状態
     * @param aLevel 上昇レベル
     */
    void levelUp(GameState& aState, const int& aLevel) override;

    /**
     * \~english
     * @brief move position of player.
     * @param aState state of game
     * @param aDirection moving direction
     * \~japanese
     * @brief プレイヤーを移動させます。
     * @param aState ゲーム状態
     * @param aDirection 移動方向
     */
    void move(GameState& aState, const KVector& aDirection) override;

    /**
     * @brief \~english  hold weapon.
     * @brief \~japanese 武器を構えます。
     */
    void arm();
    /**
     * @brief \~english  disarm.
     * @brief \~japanese 武装解除します。
     */
    void disarm();

    /**
     * \~english
     * @brief attacking.
     * @param aState state of game
     * \~japanese
     * @brief 攻撃
     * @param aState ゲーム状態
     */
    void attack(GameState& aState) override;

    /**
     * \~english
     * @brief punch!
     * @param aState state of game
     * \~japanese
     * @brief 殴る!
     * @param aState ゲーム状態
     */
    void punch(GameState& aState);

    /**
     * \~english
     * @brief reload bullet.
     * @param aState state of game
     * \~japanese
     * @brief 弾丸を再装填します。
     * @param aState ゲーム状態
     */
    void reload(GameState& aState);

    /**
     * \~english
     * @brief pick up Item.
     * @param aState state of game
     * @param aItem picked Item
     * \~japanese
     * @brief アイテムを拾います。
     * @param aState ゲーム状態
     * @param aItem 拾うアイテム
     */
    void pickUp(GameState& aState, Item * const aItem);
    /**
     * \~english
     * @brief change selected Item.
     * @param aAmount change amount
     * \~japanese
     * @brief 選択アイテムを変更します。
     * @param aAmount 選択変更量
     */
    void fumble(const int& aAmount);
    /**
     * \~english
     * @brief use selected Item.
     * @param aState state of game
     * \~japanese
     * @brief 選択されているアイテムを使用します。
     * @param aState ゲーム状態
     */
    void useItem(GameState& aState);
    /**
     * \~english
     * @brief equip selected Item.
     * @param aState state of game
     * \~japanese
     * @brief 選択されているアイテムを装備します。
     * @param aState ゲーム状態
     */
    void equipItem(GameState& aState);
    /**
     * \~english
     * @brief take off selected Item.
     * @param aState state of game
     * \~japanese
     * @brief 選択されているアイテムを装備から外します。
     * @param aState ゲーム状態
     */
    void takeoffItem(GameState& aState);
    /**
     * \~english
     * @brief throw selected Item.
     * @param aState state of game
     * \~japanese
     * @brief 選択されているアイテムを投擲します。
     * @param aState ゲーム状態
     */
    void throwItem(GameState& aState);
    /**
     * \~english
     * @brief put selected Item.
     * @param aState state of game
     * \~japanese
     * @brief 選択されているアイテムを置きます。
     * @param aState ゲーム状態
     */
    void putItem(GameState& aState);

    /**
     * \~english
     * @brief  get whether clear.
     * @return whether clear current floor
     * \~japanese
     * @brief  クリア状態を取得します。
     * @return 現在フロアのクリア状況
     */
    const bool& isClear() const;
    /**
     * \~english
     * @brief  get reference of backpack.
     * @return reference of backpack
     * \~japanese
     * @brief  バックパックの参照を取得します。
     * @return バックパックの参照
     */
    const BackPack& backPack() const;
};

#endif /* HERO_H */

