/**
 * @file   GameState.cpp
 * @brief  GameState
 * @author Maeda Takumi
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Map.h"

class Bulletin;
class Hero;
class Mapping;
class Stage;

/**
 * @brief  \~english  state of game
 * @brief  \~japanese ゲームの状態
 * @author \~ Maeda Takumi
 */
class GameState : private KNonCopy {
public:
    /**
     * @brief \~english  player Character
     * @brief \~japanese プレイヤーキャラクター
     */
    const Hero& mPlayer;
    /**
     * @brief \~english  map information
     * @brief \~japanese マップ情報
     */
    const Map& mMap;
    /**
     * @brief \~english  map drawing system
     * @brief \~japanese マップ描画システム
     */
    const Mapping& mMapping;
    /**
     * @brief \~english  map entity
     * @brief \~japanese マップ実体
     */
    const Stage& mStage;
    /**
     * @brief \~english  message system
     * @brief \~japanese メッセージシステム
     */
    Bulletin& mBulletin;

    GameState(
            const Hero& aPlayer,
            const Map& aMap,
            const Mapping& aMapping,
            const Stage& aStege,
            Bulletin& aBulletin
            );
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
};

#endif /* GAMESTATE_H */

