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
#include "Composer.h"

void GameManager::newFloor() {
    CthulhuShading->ON();
    glUniform1i(glGetUniformLocation(CthulhuShading->program(), "uRandom"), random(500) + 250);

    mTurnCount = 0;

    MapGenerator::RANDOM_MAP(mGameState.mMap);
    mGameState.clearWall();
    mGameState.mStage.reset();
    mGameState.mStage.generate(mGameState);
    mGameState.mMapping.set(mGameState.mMap);

    mGameState.mPlayer.newFloor(mGameState);
    ++mGameState.mFloorNumber;

    // スポーンテーブルの作成
    Vector<String> table(split(loadString(ID_SPAWNTABLE + mGameState.mFloorNumber), ","));

    // 敵のスポーン
    mEnemySpawnTable.clear();
    int sumPercent(0);
    for (int i = 0, i_e(SPAWN_ENEMY_KIND_MAX * 2); i < i_e; ++i) {
        if (table[i * 2] == "") break;
        sumPercent += toInt(table[i * 2 + 1]);
        mEnemySpawnTable.push_back(EnemySpawnData{toInt(table[i * 2]), sumPercent});
    }

    // アイテムスポーン
    mItemSpawnTable.clear();
    sumPercent = 0;
    for (int i = 0; i < SPAWN_ITEM_KIND_MAX; ++i) {
        if (table[i + SPAWN_ENEMY_KIND_MAX * 2] != "") {
            sumPercent += toInt(table[i + SPAWN_ENEMY_KIND_MAX * 2]);
            mItemSpawnTable.push_back(ItemSpawnData{static_cast<ItemType> (i), sumPercent});
        }
    }

    mGameState.clearEnemy();
    mGameState.clearItem();

    // アイテムの配置
    if (!mItemSpawnTable.empty()) {
        for (int i = 0; i < SPAWN_ITEM_MAX; ++i) {
            int rand(random(mItemSpawnTable.back().mSpawnPercent));
            ItemType IT;
            for (ItemSpawnData i : mItemSpawnTable) {
                if (rand < i.mSpawnPercent) {
                    IT = i.mSpawnType;
                    break;
                }
            }
            int kind(random(ITEM_KINDS[IT]) + IT * 100 + ID_ITEM);
            if (IT == ITEM_ARROW || IT == ITEM_BULLET) {
                // 銃弾と矢は複数配置
                mGameState.addItem(*(new Item(kind, mGameState.respawn(), random(7) + 3)));
            } else {
                mGameState.addItem(*(new Item(kind, mGameState.respawn())));
            }
        }
    }

    mGameState.mBGM.stop();
    mGameState.mBGM.setScore(Composer::compose());
    mGameState.mBGM.play();

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

