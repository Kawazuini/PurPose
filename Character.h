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

class Equipment;
class GameState;
class Item;
class Weapon;

/**
 * @brief  \~english  Base of Character
 * @brief  \~japanese キャラクター基底
 * @author \~ Maeda Takumi
 */
class Character : public Object {
protected:
    /**
     * @brief \~english  whether my turn
     * @brief \~japanese 自分のターンか
     */
    bool mTurn;

    /**
     * @brief \~english  position and size manager
     * @brief \~japanese 位置と大きさの管理
     */
    KSphere mBody;
    /**
     * @brief \~english  coordinate before 1F
     * @brief \~japanese 1F前の座標
     */
    KVector mPrePosition;
    /**
     * @brief \~english  direction of Character
     * @brief \~japanese キャラクター方向
     */
    KVector mDirection;

    /**
     * @brief \~english  Equipment of Weapon
     * @brief \~japanese 武器装備
     */
    Equipment* mWeapon;
    Equipment* mShield;
    Equipment* mEquip1;
    Equipment* mEquip2;
public:
    CharacterParameter mCharacterParameter;
protected:
    Character();
    Character(const int& aID);
    virtual ~Character() = default;
public:
    /**
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態の情報
     */
    virtual void update(GameState& aState) override;

    /**
     * @brief \~english  start turn.
     * @brief \~japanese ターンを開始します。
     */
    virtual void turnStart();
    /**
     * @brief \~english  end turn.
     * @brief \~japanese ターンを終了します。
     */
    virtual void turnEnd();
    /**
     * \~english
     * @brief  get whether my turn.
     * @return whether my turn
     * \~japanese
     * @brief  自分のターンかを取得します。
     * @return 自分のターンか
     */
    virtual bool turn() const;

    /**
     * @brief \~english  waiting.
     * @brief \~japanese 待機します。
     */
    virtual void wait();
    /**
     * \~english
     * @brief  move position of character.
     * @param  aPosition moving target coordinate
     * \~japanese
     * @brief  キャラクター座標を移動させます。
     * @param  aPosition 移動目標
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
     * @brief attacking.
     * @param aState game state
     * \~japanese
     * @brief 攻撃を行います。
     * @param aState ゲーム状態
     */
    virtual void attack(GameState& aState) {
    };

    /**
     * \~english
     * @brief use Item.
     * @param aItem Item to use
     * \~japanese
     * @brief アイテムを使用します。
     * @param aItem 使用アイテム
     */
    virtual void use(GameState& aState, Item& aItem);
    /**
     * \~english
     * @brief equip Item.
     * @param aItem Item to equip
     * \~japanese
     * @brief アイテムを装備します。
     * @param aItem 装備アイテム
     */
    virtual void equip(GameState& aState, Item& aItem);
    /**
     * \~english
     * @brief throw Item.
     * @param aItem Item to throw
     * \~japanese
     * @brief アイテムを投擲します。
     * @param aItem 投擲アイテム
     */
    virtual void throwing(GameState& aState, Item& aItem);

    /**
     * \^english
     * @brief equip weapon.
     * @param equipment of weapon
     * \^japanese
     * @brief 武器を装備します。
     * @param 装備武器
     */
    virtual void equipWeapon(Weapon& aWeapon);

    /**
     * \~english
     * @brief setting new position of character.
     * @param aPosition new position
     * \~japanese
     * @brief 新しいキャラクター座標を設定します。
     * @param aPosition 新しい座標
     */
    virtual void setPosition(const GameState& aState, const KVector& aPosition);

    /**
     * @brief \~english  synchronize position.
     * @brief \~japanese 位置を同期します。
     */
    virtual void syncPosition() {
    };

    /**
     * \~english
     * @brief  get position and size
     * @return position and size
     * \~japanese
     * @brief  位置と大きさを取得します。
     * @return 位置と大きさ
     */
    virtual const KSphere& body() const;
    /**
     * \~english
     * @brief  get positon of character.
     * @return position of character
     * \~japanese
     * @brief  キャラクター座標を取得します。
     * @return キャラクター座標
     */
    virtual KVector position() const;
    /**
     * \~english
     * @brief  get direction of character.
     * @return direction of character
     * \~japanese
     * @brief  キャラクター方向を取得します。
     * @return キャラクター方向
     */
    virtual KVector direction() const;
    /**
     * \~english
     * @brief  get whether dead.
     * @return whether dead
     * \~japanese
     * @brief  死んでいるかを取得します。
     * @return 死んでいるか
     */
    bool dead() const;
    /**
     * \~english
     * @brief  get size of character.
     * @return size of character
     * \~japanese
     * @brief  キャラクターサイズを取得します。
     * @return キャラクターサイズ
     */
    virtual float size() const;
};

#endif /* CHARACTER_H */

