/**
 * @file   GameState.cpp
 * @brief  GameState
 * @author Maeda Takumi
 */
#include "GameState.h"

#include "Hero.h"
#include "Mapping.h"
#include "Stage.h"

GameState::GameState(
        const Hero& aPlayer,
        const Map& aMap,
        const Mapping& aMapping,
        const Stage& aStege
        ) :
mPlayer(aPlayer),
mMap(aMap),
mMapping(aMapping),
mStage(aStege) {
}

KVector GameState::respawn() const {
    Vector<KVector> result;
    for (int i = 0; i < MAP_MAX_WIDTH; ++i) {
        for (int j = 0; j < MAP_MAX_HEIGHT; ++j) {
            if (mMap[i][j] == ROOM) result.push_back(KVector(i * MAP_SCALE, 0, j * MAP_SCALE));
        }
    }
    if (result.empty()) return KVector();
    return result[random(result.size())] + MAP_OFFSET;
}

