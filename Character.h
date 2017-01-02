/**
 * @file   Character.h
 * @brief  Character
 * @author Maeda Takumi
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include "main.h"

#include "Object.h"
#include "Rank.h"

class Equipment;
class Item;
class Mapping;
class Weapon;
class Stage;

/**
 * @brief  \~english  Base of Character
 * @brief  \~japanese キャラクター基底
 * @author \~ Maeda Takumi
 */
class Character : public KDrawer, public KUpdater, public Object {
protected:
    /**
     * @brief \~english  List of Character
     * @brief \~japanese キャラクターリスト
     */
    static List<Character*> sCharacters;
    /**
     * @brief \~english  shared Stage
     * @brief \~japanese 共有マップ
     * @note  壁破壊・階段認知など
     */
    static Stage* sStage;
    /**
     * @brief \~english  shared drawing Stage
     * @brief \~japanese 共有描画マップ
     * @note  隠蔽・初期化など
     */
    static Mapping* sMapDrawer;

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
    Character();
    virtual ~Character();

    /**
     * @brief \~english  add myself to List.
     * @brief \~japanese リストに自分を追加。
     */
    void add();
    /**
     * @brief \~english  erase myself form List.
     * @brief \~japanese リストから自分を消す。
     */
    void remove();

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    virtual void update() override;

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
     * \~english
     * @brief  move position of character.
     * @param  aDirection moving direction
     * \~japanese
     * @brief  キャラクター座標を移動させます。
     * @param  aDirection 移動方向
     */
    virtual void move(const KVector& aDirection);
    /**
     * @brief \~english  resolve overlap with wall.
     * @brief \~japanese 壁との重なりを解消します。
     */
    void resolveOverlap();
    /**
     * \~english
     * @brief  check Item at feet.
     * @return Item at feet
     * \~japanese
     * @brief  足元のアイテムを確認します。
     * @return 足元のアイテム
     */
    Item* checkItem() const;

    /**
     * @brief \~english  attacking
     * @brief \~japanese 攻撃を行います
     */
    virtual void attack() {
    };

    /**
     * \~english
     * @brief receive damage.
     * @param aChar   Character that took damage
     * @param aDamage amount of damage
     * \~japanese
     * @brief ダメージを受けます。
     * @param aChar   与ダメージキャラクター
     * @param aDamage ダメージ量
     * @note  引数のキャラクターでカウンターや経験値取得など
     */
    virtual void damage(Character& aChar, const int& aDamage);
    /**
     * \~english
     * @brief recover damage.
     * @param aRecover amount of recover
     * \~japanese
     * @brief ダメージを回復します。
     * @param aRecover 回復量
     */
    virtual void recover(const int& aRecover);

    /**
     * @brief \~english  die.
     * @brief \~japanese 死にます。
     */
    virtual void die();

    /**
     * \~english
     * @brief use Item.
     * @param aItem Item to use
     * \~japanese
     * @brief アイテムを使用します。
     * @param aItem 使用アイテム
     */
    virtual void use(Item& aItem);
    /**
     * \~english
     * @brief equip Item.
     * @param aItem Item to equip
     * \~japanese
     * @brief アイテムを装備します。
     * @param aItem 装備アイテム
     */
    virtual void equip(Item& aItem);

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
     * @brief setting new shared map.
     * @param aStage new shared map
     * \~japanese
     * @brief 新しい共有マップを設定します。
     * @param aStage 新しい共有マップ
     */
    static void setStage(Stage * const aStage);
    /**
     * \~english
     * @brief setting new shared drawing map.
     * @param aMap new shared drawing map
     * \~japanese
     * @brief 新しい共有描画マップを設定します。
     * @param aMap 新しい共有描画マップ
     */
    static void setMap(Mapping * const aMap);
    /**
     * \~english
     * @brief setting new position of character.
     * @param aPosition new position
     * \~japanese
     * @brief 新しいキャラクター座標を設定します。
     * @param aPosition 新しい座標
     */
    virtual void setPosition(const KVector& aPosition);

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
    virtual KSphere body() const;
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
     * @brief  get name of character.
     * @return name of character
     * \~japanese
     * @brief  キャラクター名を取得します。
     * @return キャラクター名
     */
    virtual String name() const;
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

