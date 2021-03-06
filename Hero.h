/**
 * @file   Hero.h
 * @brief  Hero
 * @author Maeda Takumi
 */
#ifndef HERO_H
#define HERO_H

#include "BackPack.h"
#include "Character.h"

class GameState;

/**
 * @brief  \~english  Player Character
 * @brief  \~japanese プレイヤーキャラクター
 * @author \~ Maeda Takumi
 */
class Hero final : public Character {
private:
    /* 最大所持可能重量 */ static const int MAX_WEIGHT;

    struct HitCharacter { // 視認キャラクター割り出し用構造体
        /* 視認キャラクター */ Character* mCharacter;
        /* 視点からの距離   */ float mDistance;
    };

    /* ターン数         */ int mTurnCount;
    /* アイテム袋       */ BackPack mBackPack;
    /* 所持可能重量     */ float mMuscle;
    /* 重量の危険通知   */ bool mWeightArerm;
    /* 殴れる角度       */ float mPunchAngle;
    /* フロアクリア状態 */ bool mClear;
    /* 武器構え状態     */ bool mHold;
public:
    Hero(const KCamera& aCamera);
    ~Hero() = default;

    void draw() const override;
    void update(GameState& aState) override;
    void turnStart() override;

    void syncPosition() override {
    };

    /// @brief \~english  reset status.
    /// @brief \~japanese 状態を初期化します。
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
     * @brief move position of player.
     * @param aState state of game
     * @param aDirection moving direction
     * \~japanese
     * @brief プレイヤーを移動させます。
     * @param aState ゲーム状態
     * @param aDirection 移動方向
     */
    void move(GameState& aState, const KVector& aDirection) override;

    /// @brief \~english  hold weapon.
    /// @brief \~japanese 武器を構えます。
    void arm();
    /// @brief \~english  disarm.
    /// @brief \~japanese 武器の構えを解除します。
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
     * @brief change selected equipment of weapon.
     * @param aAmount change amount
     * \~japanese
     * @brief 選択武器装備を変更します。
     * @param aAmount 選択変更量
     */
    void weaponFumble(const int& aAmount);

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
     * @brief put some selected Item.
     * @param aState state of game
     * @param aCount number of putted item
     * \~japanese
     * @brief 選択されているアイテムを複数置きます。
     * @param aState ゲーム状態
     * @param aCount 置くアイテムの個数
     */
    void putItem(GameState& aState, const int& aCount = 1);
    /// @brief \~english  Organize backpack.
    /// @brief \~japanese アイテム欄を整理する。
    void sortItem();

    /**
     * \~english
     * @brief  calculate Character who I am seeing.
     * @return Character who I am seeing
     * \~japanese
     * @brief  見ているキャラクターを計算します。
     * @return 見ているキャラクター
     */
    const Character* whoIamSeeing(const GameState& aState) const;

    const bool& isClear() const;
    const BackPack& backPack() const;
};

#endif /* HERO_H */

