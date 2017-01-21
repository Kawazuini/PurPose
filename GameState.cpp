/**
 * @file   GameState.cpp
 * @brief  GameState
 * @author Maeda Takumi
 */
#include "GameState.h"

const float GameState::GRAVITATIONAL_ACCELERATION = 9.80665 / (1.0_s * 1.0_s);
const float GameState::AIR_RESISTANCE = 0.005;

GameState::GameState() :
mGravity(0, -GRAVITATIONAL_ACCELERATION, 0),
mAirResistance(AIR_RESISTANCE),
mPlayer(mCharacters) {
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

MapChip GameState::getMap(const KVector& aPosition) const {
    KVector pos(aPosition / MAP_SCALE);
    if (pos.x < 0 || MAP_MAX_WIDTH < pos.x || pos.z < 0 || MAP_MAX_HEIGHT < pos.z) return OTHER;
    return mMap[(int) pos.x][(int) pos.z];
}

