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
    mTurnCount = 0;

    MapGenerator::RANDOM_MAP(mGameState.mMap);
    mGameState.clearWall();
    mGameState.mStage.reset();
    mGameState.mStage.generate(mGameState);
    mGameState.mMapping.set(mGameState.mMap);

    mGameState.mPlayer.newFloor(mGameState);
    ++mGameState.mFloorNumber;

    // 敵のスポーンテーブルの作成
    Vector<String> table(split(loadString(ID_INDEX_SPAWN + mGameState.mFloorNumber), ","));
    mEnemySpawnTable.clear();
    int sumPercent(0);
    for (int i = 0, i_e(SPAWN_ENEMY_KIND_MAX * 2); i < i_e; ++i) {
        if (table[i * 2] == "") break;
        sumPercent += toInt(table[i * 2 + 1]);
        mEnemySpawnTable.push_back(SpawnData{ID_INDEX_CHARACTER + toInt(table[i * 2]), sumPercent});
    }

    // アイテムスポーンテーブルの作成
    table = split(loadString(ID_INDEX_ITEMSPAWN + toInt(table[SPAWN_ENEMY_KIND_MAX * 2])), ",");
    mItemSpawnTable.clear();
    sumPercent = 0;
    for (int i = 0, i_e(table.size()); i < i_e; ++i) {
        sumPercent += toInt(table[i]);
        mItemSpawnTable.push_back(SpawnData{ID_INDEX_ITEM + i + 1, sumPercent});
    }

    mGameState.clearEnemy();
    mGameState.clearItem();

    // アイテムの配置
    if (!mItemSpawnTable.empty()) {
        for (int i = 0; i < SPAWN_ITEM_MAX; ++i) {
            int ItemID;
            Item* item;
            ItemType type;
            int rand(random(mItemSpawnTable.back().mSpawnPercent));
            for (SpawnData j : mItemSpawnTable) {
                if (rand < j.mSpawnPercent) {
                    ItemID = j.mSpawnID;
                    break;
                }
            }
            mGameState.addItem(*(item = new Item(ItemID, mGameState.respawn())));
            type = item->param().mItemType;
            if (type == ITEM_ARROW || type == ITEM_AMMO) { // 銃弾と矢は複数配置
                for (int i = 0, i_e(random(7) + 3); i < i_e; ++i) {
                    item->mMagazine.push_back(new Item(ItemID));
                }
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

