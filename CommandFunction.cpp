/**
 * @file   CommandFunction.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Enemy.h"
#include "Item.h"
#include "MapGenerator.h"
#include "Stair.h"

void GameManager::newFloar() {
    mTurnCount = 0;

    MapGenerator::RANDOM_MAP(mGameState.mMap);
    mGameState.mStage.set(mGameState.mMap);
    mGameState.mMapping.set(mGameState.mMap);

    mGameState.mPlayer.newFloar(mGameState);

    mGameState.clearEnemy();

    mGameState.clearItem();
    for (int i = 0; i < 10; ++i) {
        mGameState.addItem(*(new Item(501, mGameState.respawn())));
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

void GameManager::takeoffItem() {
    mGameState.mPlayer.takeoffItem(mGameState);
}

void GameManager::throwItem() {
    mGameState.mPlayer.throwItem(mGameState);
}

void GameManager::putItem() {
    mGameState.mPlayer.putItem(mGameState);
}

