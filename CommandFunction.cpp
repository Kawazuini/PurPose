/**
 * @file   CommandFunction.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Enemy.h"
#include "HPotion.h"
#include "Item.h"
#include "MapGenerator.h"
#include "Stair.h"

void GameManager::newFloar() {
    mTurnCount = 0;

    MapGenerator::RANDOM_MAP(mMap);
    mStage.set(mMap);
    mMapping.set(mMap);

    mPlayer.newFloar(mGameState);

    List<Item*> iList = Item::itemList();
    for (Item* i : iList) delete i;
    for (int i = 0; i < 25; ++i) {
        new HPotion(mGameState.respawn());
    }

    while (!Enemy::sEnemies.empty()) delete (Enemy::sEnemies.front());

    turnStart(PLAYER);
}

void GameManager::stairCancel() {
    mStage.stair().stop();
}

void GameManager::useItem() {
    mPlayer.useItem(mGameState);
}

void GameManager::equipItem() {
    mPlayer.equipItem(mGameState);
}

void GameManager::throwItem() {
    mPlayer.throwItem(mGameState);
}

