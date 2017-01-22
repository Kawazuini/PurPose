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

    MapGenerator::RANDOM_MAP(mGameState.mMap);
    mGameState.mStage.set(mGameState.mMap);
    mGameState.mMapping.set(mGameState.mMap);

    mGameState.mPlayer.newFloar(mGameState);

    List<Item*> item(mGameState.mItems);
    for (Item* i : item) {
        mGameState.removeItem(*i);
        delete i;
    }
    for (int i = 0; i < 10; ++i) {
        mGameState.addItem(*(new HPotion(mGameState.respawn())));
    }

    List<Enemy*> enemy(mGameState.mEnemies);
    for (Enemy* i : enemy) {
        mGameState.removeEnemy(*i);
        delete i;
    }

    turnStart(PLAYER);
}

void GameManager::stairCancel() {
    mGameState.mStage.stair().stop();
}

void GameManager::useItem() {
    mGameState.mPlayer.useItem(mGameState);
}

void GameManager::equipItem() {
    mGameState.mPlayer.equipItem(mGameState);
}

void GameManager::throwItem() {
    mGameState.mPlayer.throwItem(mGameState);
}

