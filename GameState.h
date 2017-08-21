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
#include "Orchestra.h"

class Enemy;

/**
 * @brief  \~english  state of game
 * @brief  \~japanese ゲームの状態
 * @author \~ Maeda Takumi
 */
class GameState final : private KNonCopy {
private:
    /* キャラクターリスト */ List<Character*> mCharacters;
    /* 敵リスト           */ List<Enemy*> mEnemies;
    /* アイテムリスト     */ List<Item*> mItems;
    /* 壁の衝突判定リスト */ List<KPolygon*> mWalls;
public:
    /// @brief \~english  gravitational acceleration : 9.80665(m/s^2)
    /// @brief \~japanese 重力加速度 : 9.80665(m/s^2)
    static const float GRAVITATIONAL_ACCELERATION;
    /// @brief \~english  default air resistance
    /// @brief \~japanese デフォルトの空気抵抗係数(適当)
    static const float AIR_RESISTANCE;
    /// @brief \~english  gravity
    /// @brief \~japanese 重力
    KVector mGravity;
    /// @brief \~english  air resistance
    /// @brief \~japanese 空気抵抗係数
    float mAirResistance;
    /// @brief \~english  whether during physical calculation
    /// @brief \~japanese 物理演算中か
    bool mPhysical;

    /// @brief \~english  player Character
    /// @brief \~japanese プレイヤーキャラクター
    Hero mPlayer;

    /// @brief \~english  eye camera
    /// @brief \~japanese 目線カメラ
    KFPSCamera mCamera;
    /// @brief \~english  hand light
    /// @brief \~japanese ハンドライト
    KHandLight mHandLight;

    /// @brief \~english  floor number
    /// @brief \~japanese 階層数
    int mFloorNumber;

    /// @brief \~english  message system
    /// @brief \~japanese メッセージシステム
    Bulletin mBulletin;

    /// @brief \~english  map information
    /// @brief \~japanese マップ情報
    Map mMap;
    /// @brief \~english  map drawing system
    /// @brief \~japanese マップ描画システム
    Mapping mMapping;
    /// @brief \~english  map entity
    /// @brief \~japanese マップ実体
    Stage mStage;

    Orchestra mBGM; ///< Back Ground Music

    GameState(KCamera& aCamera);
    ~GameState() = default;

    const List<Character*>& charList() const;
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
     * @brief 敵をリストから消去します。
     * @param aEnemy 消去する敵
     */
    void removeEnemy(Enemy& aEnemy);
    /**
     * @brief \~english  empty the Enemy list.
     * @brief \~japanese 敵リストを空にします。
     */
    void clearEnemy();

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
     * @brief アイテムをリストから消去します。
     * @param aItem 消去するアイテム
     */
    void removeItem(Item& aItem);
    /**
     * @brief \~english  empty the Item list.
     * @brief \~japanese アイテムリストを空にします。
     */
    void clearItem();

    const List<KPolygon*>& wallList() const;
    /**
     * \~english
     * @brief add wall to list.
     * @param aWall addition wall
     * \~japanese
     * @brief 壁をリストに追加します。
     * @param aWall 追加する壁
     */
    void addWall(KPolygon& aWall);
    /**
     * \~english
     * @brief remove wall from list.
     * @param aWall removal wall
     * \~japanese
     * @brief 壁をリストから消去します。
     * @param aWall 消去する壁
     */
    void removeWall(KPolygon& aWall);
    /**
     * @brief \~english  empty the wall list.
     * @brief \~japanese 壁リストを空にします。
     */
    void clearWall();

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

