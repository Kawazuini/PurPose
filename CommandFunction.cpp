/**
 * @file   CommandFunction.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Composer.h"
#include "Enemy.h"
#include "Item.h"
#include "MapGenerator.h"
#include "NumberSelector.h"
#include "Stair.h"

#include "Event.h"
#include "Money.h"

void GameManager::newFloor() {
    mTurnCount = 0;

    MapGenerator::RANDOM_MAP(mGameState.mMap);
    mGameState.clearWall();
    mGameState.mStage.reset();
    mGameState.mStage.generate(mGameState, *this, GameManager::stairEvent);
    mGameState.mStage.stair().enable();

    mGameState.mMapping.set(mGameState.mMap);

    mGameState.mPlayer.newFloor(mGameState);
    ++mGameState.mFloorNumber;

    // スポーンインデックス
    Vector<String> tableIndex(split(loadString(ID_INDEX_SPAWN + mGameState.mFloorNumber), ","));

    // ゲームクリア
    if (tableIndex[0] == "CLEAR") {
        mScene = SCENE_ENDING;
        return;
    }

    // 敵のスポーンテーブルの作成
    Vector<String> table(split(loadString(ID_INDEX_ENEMYSPAWN + toInt(tableIndex[0])), ","));
    mEnemySpawnTable.clear();
    int sumPercent(0);
    for (int i = 0, i_e(table.size() / 2); i < i_e; ++i) {
        sumPercent += toInt(table[i * 2 + 1]);
        mEnemySpawnTable.push_back(SpawnData{toInt(table[i * 2]), ID_INDEX_ENEMY + i, sumPercent});
    }

    // アイテムスポーンテーブルの作成
    table = split(loadString(ID_INDEX_ITEMSPAWN + toInt(tableIndex[1])), ",");
    mItemSpawnTable.clear();
    sumPercent = 0;
    for (int i = 0, i_e(table.size()); i < i_e; ++i) {
        sumPercent += toInt(table[i]);
        mItemSpawnTable.push_back(SpawnData{0, ID_INDEX_ITEM + i + 1, sumPercent});
    }

    mGameState.clearEnemy();
    mGameState.clearItem();
    mGameState.clearMoney();

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

    for (int i = 0, i_e(random(SPAWN_MONEY_MAX)); i < i_e; ++i) {
        Money * money(new Money(*this, getMoneyEvent, mGameState.respawn()));
        money->enable();
        mGameState.addMoney(*money);
    }

    mGameState.mBGM.stop();
    mGameState.mBGM.setScore(Composer::compose());
    mGameState.mBGM.play();

    turnStart(PLAYER);
}

void GameManager::stairCancel() {
    mGameState.mStage.stair().disable();
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
    // 複数所持の場合は置く数を選択
    int count(mGameState.mPlayer.backPack().lookCount());
    if (count > 1) {
        mCommandManager.push(*(new NumberSelector(*this, "いくつ置きますか?", count, 1, putItems)));
    } else {
        mGameState.mPlayer.putItem(mGameState);
    }
}

void GameManager::putItems(const int& aNumber) {
    mGameState.mPlayer.putItem(mGameState, aNumber);
}

