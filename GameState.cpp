/**
 * @file   GameState.cpp
 * @brief  GameState
 * @author Maeda Takumi
 */
#include "GameState.h"

#include "Enemy.h"
#include "Item.h"

const float GameState::GRAVITATIONAL_ACCELERATION(9.80665 / (1.0_s * 1.0_s));
const float GameState::AIR_RESISTANCE(0.005);

GameState::GameState() :
mGravity(0, -GRAVITATIONAL_ACCELERATION, 0),
mAirResistance(AIR_RESISTANCE),
mPhysical(false),
mCamera(mPlayer.mPosition, mPlayer.mDirection),
mFloorNumber(0),
mMapping(mCamera) {
    mCharacters.push_back(&mPlayer);
}

const List<Character*>& GameState::charList() const {
    return mCharacters;
}

const List<Enemy*>& GameState::enemyList() const {
    return mEnemies;
}

void GameState::addEnemy(Enemy& aEnemy) {
    removeEnemy(aEnemy); // 2重追加の防止
    mCharacters.push_back(static_cast<Character*> (&aEnemy));
    mEnemies.push_back(&aEnemy);
}

void GameState::removeEnemy(Enemy& aEnemy) {
    for (auto i = mCharacters.begin(), i_e = mCharacters.end(); i != i_e; ++i) {
        if (*i == static_cast<Character*> (&aEnemy)) {
            mCharacters.erase(i);
            break;
        }
    }
    for (auto i = mEnemies.begin(), i_e = mEnemies.end(); i != i_e; ++i) {
        if (*i == &aEnemy) {
            mEnemies.erase(i);
            break;
        }
    }
}

void GameState::clearEnemy() {
    List<Enemy*> enemy(mEnemies);
    for (Enemy* i : enemy) {
        removeEnemy(*i);
        delete i;
    }
}

const List<Item*>& GameState::itemList() const {
    return mItems;
}

void GameState::addItem(Item& aItem) {
    removeItem(aItem); // 2重追加の防止
    mItems.push_back(&aItem);
}

void GameState::removeItem(Item& aItem) {
    for (auto i = mItems.begin(), i_e = mItems.end(); i != i_e; ++i) {
        if (*i == &aItem) {
            mItems.erase(i);
            break;
        }
    }
}

void GameState::clearItem() {
    List<Item*> item(mItems);
    for (Item* i : item) {
        removeItem(*i);
        delete i;
    }
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

