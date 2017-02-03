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
class GameState;

/**
 * @brief  \~english  Player Character
 * @brief  \~japanese プレイヤーキャラクター
 * @author \~ Maeda Takumi
 */
class Hero : public Character, public KDrawer {
private:
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

    /**
     * @brief \~english  whether arm weapon
     * @brief \~japanese 武器構え状態
     */
    bool mHold;
public:
    Hero();
    virtual ~Hero() = default;

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
     * @brief attack by weapon
     * @param aState state of game
     * \~japanese
     * @brief 武器による攻撃
     * @param aState ゲーム状態
     */
    void weaponAttack(GameState& aState);

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
     * @return whether clear current floar
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

