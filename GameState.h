/**
 * @file   GameState.cpp
 * @brief  GameState
 * @author Maeda Takumi
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Bulletin.h"
#include "Hero.h"
#include "Mapping.h"
#include "Stage.h"

class Enemy;

/**
 * @brief  \~english  state of game
 * @brief  \~japanese ゲームの状態
 * @author \~ Maeda Takumi
 */
class GameState : private KNonCopy {
private:
    /**
     * @brief \~english  list of Character
     * @brief \~japanese キャラクターリスト
     */
    List<Character*> mCharacters;
    /**
     * @brief \~english  list of Enemy
     * @brief \~japanese 敵リスト
     */
    List<Enemy*> mEnemies;
    /**
     * @brief \~english  list of Item
     * @brief \~japanese アイテムリスト
     */
    List<Item*> mItems;
public:
    /**
     * @brief \~english  gravitational acceleration : 9.80665(m/s^2)
     * @brief \~japanese 重力加速度 : 9.80665(m/s^2)
     */
    static const float GRAVITATIONAL_ACCELERATION;
    /**
     * @brief \~english  default air resistance
     * @brief \~japanese デフォルトの空気抵抗係数(適当)
     */
    static const float AIR_RESISTANCE;
    /**
     * @brief \~english  gravity
     * @brief \~japanese 重力
     */
    KVector mGravity;
    /**
     * @brief \~english  air resistance
     * @brief \~japanese 空気抵抗係数
     */
    float mAirResistance;
    /**
     * @brief \~english  whether during physical calculation
     * @brief \~japanese 物理演算中か
     */
    bool mPhysical;

    /**
     * @brief \~english  message system
     * @brief \~japanese メッセージシステム
     */
    Bulletin mBulletin;

    /**
     * @brief \~english  player Character
     * @brief \~japanese プレイヤーキャラクター
     */
    Hero mPlayer;

    /**
     * @brief \~english  floor number
     * @brief \~japanese 階層数
     */
    int mFloorNumber;

    /**
     * @brief \~english  map information
     * @brief \~japanese マップ情報
     */
    Map mMap;
    /**
     * @brief \~english  map drawing system
     * @brief \~japanese マップ描画システム
     */
    Mapping mMapping;
    /**
     * @brief \~english  map entity
     * @brief \~japanese マップ実体
     */
    Stage mStage;

    GameState();
    virtual ~GameState() = default;

    /**
     * \~english
     * @brief  get list of Character.
     * @return list of Character
     * \~japanese
     * @brief  キャラクターリストを取得します。
     * @return キャラクターリスト
     */
    const List<Character*>& charList() const;
    /**
     * \~english
     * @brief  get list of Enemy.
     * @return list of Enemy
     * \~japanese
     * @brief  敵リストを取得します。
     * @return 敵リスト
     */
    const List<Enemy*>& enemyList() const;
    /**
     * \~english
     * @brief add Enemy to list.
     * @param aEnemy addition Enemy
     * \~japanese
     * @brief 敵をリストに追加します。
     * @param aEnemy 追加する敵
     */
    void addEnemy(Enemy& aEnemy);
    /**
     * \~english
     * @brief remove Enemy from list.
     * @param aEnemy removal Enemy
     * \~japanese
     * @brief 敵をリストに追加します。
     * @param aEnemy 追加する敵
     */
    void removeEnemy(Enemy& aEnemy);
    /**
     * @brief \~english  empty the Enemy list.
     * @brief \~japanese 敵リストを空にします。
     */
    void clearEnemy();
    /**
     * \~english
     * @brief  get list of Item.
     * @return list of Item
     * \~japanese
     * @brief  アイテムリストを取得します。
     * @return アイテムリスト
     */
    const List<Item*>& itemList() const;
    /**
     * \~english
     * @brief add Item to list.
     * @param aItem addition Item
     * \~japanese
     * @brief アイテムをリストに追加します。
     * @param aItem 追加するアイテム
     */
    void addItem(Item& aItem);
    /**
     * \~english
     * @brief remove Item from list.
     * @param aItem removal Item
     * \~japanese
     * @brief アイテムをリストに追加します。
     * @param aItem 追加するアイテム
     */
    void removeItem(Item& aItem);
    /**
     * @brief \~english  empty the Item list.
     * @brief \~japanese アイテムリストを空にします。
     */
    void clearItem();

    /**
     * \~english
     * @brief  get respawnable coordinate.
     * @return respawnable coordinate
     * \~japanese
     * @brief  リスポーン可能座標を取得します。
     * @return リスポーン可能座標
     */
    KVector respawn() const;
    /**
     * \~english
     * @brief  get the map element of the specified coordinates.
     * @param  aPosition specified cooddinate
     * @return map component
     * \~japanese
     * @brief  指定座標のマップ要素を取得します。
     * @param  aPosition 取得したい座標
     * @return マップ構成要素
     */
    MapChip getMap(const KVector& aPosition) const;
};

#endif /* GAMESTATE_H */

