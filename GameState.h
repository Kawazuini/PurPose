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
     * @brief \~english  message system
     * @brief \~japanese メッセージシステム
     */
    Bulletin mBulletin;

    /**
     * @brief \~english  List of Character
     * @brief \~japanese キャラクターリスト
     */
    List<Character*> mCharacters;
    /**
     * @brief \~english  player Character
     * @brief \~japanese プレイヤーキャラクター
     */
    Hero mPlayer;
    /**
     * @brief \~english  Enemy Character List
     * @brief \~japanese 敵キャラクターリスト
     */
    List<Enemy*> mEnemies;

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
     * @return map compoment
     * \~japanese
     * @brief  指定座標のマップ要素を取得します。
     * @param  aPosition 取得したい座標
     * @return マップ構成要素
     */
    MapChip getMap(const KVector& aPosition) const;
};

#endif /* GAMESTATE_H */

