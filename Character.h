/**
 * @file   Character.h
 * @brief  Character
 * @author Maeda Takumi
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include "AI.h"
#include "CharacterParameter.h"
#include "Object.h"

class GameState;
class Item;

/**
 * @brief  \~english  Base of Character
 * @brief  \~japanese キャラクター基底
 * @author \~ Maeda Takumi
 */
class Character : public KDrawer, public Object {
    friend class GameState;
private:
    /* 円構成頂点数     */ static const int CIRCLE_QUALITY;
    /* ダメージン判定円 */ Vector<KVector> mBodyCircle;
    /* 攻撃可能範囲円   */ Vector<KVector> mAttackCircle;
public:
    /// @brief CharacterParameter
    CharacterParameter mCharacterParameter;
    /// @brief \~english  The Character who killed me
    /// @brief \~japanese 私を殺したキャラクター
    Character* mWhoKilleMe;
protected:
    /// @brief \~english  whether my turn
    /// @brief \~japanese 自分のターンか
    bool mTurn;
    /// @brief \~english  not act turn
    /// @brief \~japanese 待機ターン
    int mWaitTurn;

    /// @brief \~english  Character size
    /// @brief \~japanese キャラクターサイズ
    float mSize;
    /// @brief \~english  Character coordinate
    /// @brief \~japanese キャラクター座標
    KVector mPosition;
    /// @brief \~english  coordinate before 1F
    /// @brief \~japanese 1F前の座標
    KVector mPrePosition;
    /// @brief \~english  direction of Character
    /// @brief \~japanese キャラクター方向
    KVector mDirection;

    /* ----- 装備 ----- */
    /// @brief \~english  Equipment of weapon
    /// @brief \~japanese 武器装備
    Item* mWeapon[3];
    /// @brief \~english  index of equipment of weapon
    /// @brief \~japanese 装備武器指定添え字
    int mWeaponIndex;
    /// @brief \~english  Equipment of shield
    /// @brief \~japanese 縦装備
    Item* mShield;
    /// @brief \~english  Equipment on head
    /// @brief \~japanese 頭装備
    Item* mHeadEquipment;
    /// @brief \~english  Equipment on body
    /// @brief \~japanese 胴装備
    Item* mBodyEquipment;
    /// @brief \~english  Equipment on foot
    /// @brief \~japanese 足装備
    Item* mFootEquipment;

    /// @param \~english  aID resource ID
    /// @param \~japanese aID リソースID
    Character(const int& aID);
    virtual ~Character() = default;
public:
    virtual void draw() const override;
    virtual void update(GameState& aState) override;

    /// @brief \~english  start turn.
    /// @brief \~japanese ターンを開始します。
    virtual void turnStart();
    /// @brief \~english  end turn.
    /// @brief \~japanese ターンを終了します。
    virtual void turnEnd();
    virtual const bool& turn() const;

    /**
     * \~english
     * @brief level up
     * @param aLevel increased value
     * \~japanese
     * @brief レベルアップ
     * @param aLevel 上昇レベル
     */
    void levelUp(const int& aLevel);
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
    void levelUp(GameState& aState, const int& aLevel);

    /**
     * @brief \~english  waiting.
     * @brief \~japanese 待機します。
     */
    virtual void wait();
    /**
     * \~english
     * @brief move position of character.
     * @param aState game state
     * @param aPosition moving target coordinate
     * \~japanese
     * @brief キャラクター座標を移動させます。
     * @param aState ゲーム状態
     * @param aPosition 移動目標
     */
    virtual void move(GameState& aState, const KVector& aPosition);
    /**
     * @brief \~english  resolve overlap with wall.
     * @brief \~japanese 壁との重なりを解消します。
     */
    void resolveOverlap(const GameState& aState);
    /**
     * \~english
     * @brief  check Item at feet.
     * @return Item at feet
     * \~japanese
     * @brief  足元のアイテムを確認します。
     * @return 足元のアイテム
     */
    Item* checkItem(GameState& aState) const;

    /**
     * \~english
     * @brief rotate object so that it points in the specified direction.
     * @param aDirection specified direction
     * \~japanese
     * @brief 指定方向を向くように回転させます。
     * @param aDirection 指定方向
     */
    void lookAt(const KVector& aDirection);

    /**
     * \~english
     * @brief attacking.
     * @param aState game state
     * \~japanese
     * @brief 攻撃を行います。
     * @param aState ゲーム状態
     */
    virtual void attack(GameState& aState);
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
     * @brief use Item.
     * @param aState game state
     * @param aItem  Item to use
     * \~japanese
     * @brief アイテムを使用します。
     * @param aState ゲーム状態
     * @param aItem  使用アイテム
     */
    virtual void use(GameState& aState, Item& aItem);
    /**
     * \~english
     * @brief equip Item.
     * @param aState game state
     * @param aItem  Item to equip
     * \~japanese
     * @brief アイテムを装備します。
     * @param aState ゲーム状態
     * @param aItem  装備アイテム
     */
    virtual void equip(GameState& aState, Item& aItem);
    /**
     * \~english
     * @brief take off equipment.
     * @param aState   state of game
     * @param aItem    equipment of take off
     * @param aMessage whether output message
     * \~japanese
     * @brief 装備を外します。
     * @param aState   ゲーム状態
     * @param aItem    外す装備
     * @param aMessage メッセージを出力するか
     */
    bool takeOff(GameState& aState, Item& aItem, const bool& aMessage = true);
    /**
     * \~english
     * @brief throw Item.
     * @param aState game state
     * @param aItem  Item to throw
     * \~japanese
     * @brief アイテムを投擲します。
     * @param aState ゲーム状態
     * @param aItem  投擲アイテム
     */
    void throwing(GameState& aState, Item& aItem);
    /**
     * \~english
     * @brief put Item.
     * @param aState game state
     * @param aItem  Item to put
     * \~japanese
     * @brief アイテムを設置します。
     * @param aState ゲーム状態
     * @param aItem  設置アイテム
     */
    void putting(GameState& aState, Item& aItem);

    /**
     * \~english
     * @brief setting new position of character.
     * @param aState    state of game
     * @param aPosition new position
     * \~japanese
     * @brief 新しいキャラクター座標を設定します。
     * @param aState    ゲーム状態
     * @param aPosition 新しい座標
     */
    void setPosition(const GameState& aState, const KVector& aPosition);

    /**
     * @brief \~english  synchronize position.
     * @brief \~japanese 位置を同期します。
     */
    virtual void syncPosition() = 0;

    const KVector& position() const;
    const KVector& direction() const;
    const float& size() const;

    const Item * const * weapon() const;
    const int& weaponIndex() const;

    const Item * shield() const;
    const Item * headEquipment() const;
    const Item * bodyEquipment() const;
    const Item * footEquipment() const;
};

#endif /* CHARACTER_H */

