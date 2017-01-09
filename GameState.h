/**
 * @file   GameState.cpp
 * @brief  GameState
 * @author Maeda Takumi
 */
#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "Map.h"

class Hero;
class Mapping;
class Stage;

class GameState : private KNonCopy {
public:
    /**
     * @brief \~english  reference of player
     * @brief \~japanese プレイヤー参照
     */
    const Hero& mPlayer;
    const Map& mMap;
    const Mapping& mMapping;
    const Stage& mStage;

    GameState(
            const Hero& aPlayer,
            const Map& aMap,
            const Mapping& aMapping,
            const Stage& aStege
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

