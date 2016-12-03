/**
 * @file   Character.h
 * @brief  Character
 * @author Maeda Takumi
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include "main.h"

class Map;

/**
 * @brief  \~english  Base of Character
 * @brief  \~japanese キャラクター基底
 * @author Maeda Takumi
 */
class Character : public KDrawer, public KUpdater {
protected:
    /**
     * @brief \~english  list of Character
     * @brief \~japanese キャラクターリスト
     */
    static List<Character*> sCharacters;
    /**
     * @brief \~english  shared map information
     * @brief \~japanese 共有マップ情報
     */
    static Map* sMap;

    /**
     * @brief \~english  whether my turn
     * @brief \~japanese 自分のターンか
     */
    bool mTurn;

    /**
     * @brief \~english  position of character
     * @brief \~japanese キャラクター座標
     */
    KVector mPosition;
    /**
     * @brief \~english  direction of character
     * @brief \~japanese キャラクター方向
     */
    KVector mDirection;

    /**
     * @brief \~english  name of character
     * @brief \~japanese キャラクター名
     */
    String mName;
    /**
     * @brief \~english  size of character
     * @brief \~japanese キャラクターサイズ
     */
    float mSize;

    /**
     * @brief \~english  max of hit points
     * @brief \~japanese 最大HP
     */
    int mMaxHP;
    /**
     * @brief \~english  hit points
     * @briev \~japanese HP
     */
    int mHP;

    /**
     * @brief \~english  actionable point
     * @brief \~japanese 行動可能数
     */
    int mActionPoint;
    /**
     * @brief \~english  recovered actionable point per turn
     * @brief \~japanese 俊敏性(ActionPoint回複数)
     */
    int mAgility;
    /**
     * @brief \~english  cost of moving
     * @brief \~japanese 移動コスト
     */
    int mMoveCost;
    /**
     * @brief \~english  cost of attack
     * @brief \~japanese 攻撃コスト
     */
    int mAttackCost;
public:
    Character();
    virtual ~Character();

    /**
     * @brief \~english  add myself to list.
     * @brief \~japanese リストに自分を追加。
     */
    void add();
    /**
     * @brief \~english  erase myself form list.
     * @brief \~japanese リストから自分を消す。
     */
    void erase();

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
    /** @brief ターン終了 */
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
     * @brief  get whether movabble.
     * @return whether movable
     * \~japanese
     * @brief  移動可能かを取得します。
     * @return 移動可能かどうか
     */
    bool isMovable();

    /**
     * \~english
     * @brief  move position of character.
     * @param  aDirection moving direction
     * \~japanese
     * @brief  キャラクター座標を移動させます。
     * @param  aDirection 移動方向
     */
    virtual void move(const KVector& aDirection) {
    };

    /**
     * \~english
     * @brief  get whether attackable.
     * @return whether attackable
     * \~japanese
     * @brief  攻撃可能かを取得します。
     * @return 攻撃可能かどうか
     */
    virtual bool isAttackable();

    /**
     * @brief \~english  attacking
     * @brief \~japanese 攻撃を行います
     */
    virtual void attack() {
    };

    /**
     * \~english
     * @brief receive damage.
     * @param aDamage amount of damage
     * \~japanese
     * @brief ダメージを受けます。
     * @param aDamage ダメージ量
     */
    virtual void damage(const int& aDamage);

    /**
     * @brief \~english  resolve overlap with wall.
     * @brief \~japanese 壁との重なりを解消します。
     */
    void resolveOverlap();

    /**
     * \~english
     * @brief setting new shared map.
     * @param aMap new shared map
     * \~japanese
     * @brief 新しい共有マップを設定します。
     * @param aMap 新しい共有マップ
     */
    static void setMap(Map * const aMap);
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
     * @brief  get size of character.
     * @return size of character
     * \~japanese
     * @brief  キャラクターサイズを取得します。
     * @return キャラクターサイズ
     */
    virtual float size() const;
};

#endif /* CHARACTER_H */

