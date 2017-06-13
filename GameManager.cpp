/**
 * @file   GameManager.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Command.h"
#include "Enemy.h"
#include "Item.h"
#include "Stair.h"

const int GameManager::SPAWN_ENEMY_MAX(toInt(loadString(ID_CONFIG_ENEMY_SPAWN_MAX)));
const int GameManager::SPAWN_ITEM_MAX(toInt(loadString(ID_CONFIG_ITEM_SPAWN_MAX)));
const int GameManager::SPAWN_MONEY_MAX(toInt(loadString(ID_CONFIG_MONEY_SPAWN_MAX)));

GameManager::GameManager(
        KCamera& aCamera,
        KGLUI& aUI,
        const InputManager& aInputManager
        ) :
mCamera(aCamera),
mGameState(aCamera),
mDevice(aUI),
mCommandManager(mDevice),
mScene(SCENE_START),
mTurn(PLAYER),
mDrawFunc{draw_start, draw_play, draw_over, draw_ending},
mUpdateFunc{update_start, update_play, update_over, update_ending}

,
mFrameCount(0),
mKeyFrag(false),
mRanking(0),
mTurnCount(0),
mSpawnPeriod(0),
mCommandWait(false),
mInventory(false),
mInputManager(aInputManager) {
    KDrawer::remove();
    KUpdater::remove();
}

GameManager::~GameManager() {
    mGameState.clearEnemy();
    mGameState.clearItem();
    mGameState.clearWall();
    mGameState.clearMoney();
}

void GameManager::reset() {
    mSpawnPeriod = 30;

    mScene = SCENE_START;
    mGameState.mPlayer.reset();
    mGameState.mFloorNumber = 0;

    mGameState.mBulletin.clear();

    newFloor();
}

void GameManager::draw() const {
    (this->*mDrawFunc[mScene])();
}

void GameManager::update() {
    (this->*mUpdateFunc[mScene])();
    mDevice.screen().reflect();
}

void GameManager::turnStart(const Turn & aTurn) {
    mTurn = aTurn;
    switch (mTurn) {
        case PLAYER:
            ++mTurnCount;
            if (!(mTurnCount % mSpawnPeriod)) spawnEnemy();
            mGameState.mPlayer.turnStart();
            break;
        case ENEMY:
            for (Enemy* i : mGameState.enemyList()) i->turnStart();
            break;
    }
}

bool GameManager::checkTurnEnd() const {
    switch (mTurn) {
        case PLAYER: return !mGameState.mPlayer.turn();
        case ENEMY:
            for (Enemy* i : mGameState.enemyList()) if (i->turn()) return false;
            return true;
    }
}

void GameManager::spawnEnemy() {
    if (!mEnemySpawnTable.empty()) {
        if (mGameState.enemyList().size() < SPAWN_ENEMY_MAX) {
            Enemy* tmp;
            int rand(random(mEnemySpawnTable.back().mSpawnPercent));
            for (SpawnData i : mEnemySpawnTable) {
                if (rand < i.mSpawnPercent) {
                    mGameState.addEnemy(*(tmp = new Enemy(i.mSpawnID, i.mLevel)));
                    tmp->setPosition(mGameState, mGameState.respawn());
                    break;
                }
            }
        }
    }
}

void GameManager::makeItemCommand() {
    const Item * item(mGameState.mPlayer.backPack().lookAt());
    if (item) {
        List<String> commandMessage;
        Vector<Command::CommandFunction> commands;

        if (item->param().mUsable) {
            commandMessage.push_back("使う");
            commands.push_back(useItem);
        }
        if (item->param().mEquippable && !item->mEquipped) {
            commandMessage.push_back("装備");
            commands.push_back(equipItem);
        }
        if (item->mTakeoffable && item->mEquipped) {
            commandMessage.push_back("外す");
            commands.push_back(takeoffItem);
        }
        commandMessage.push_back("投げる");
        commands.push_back(throwItem);
        commandMessage.push_back("置く");
        commands.push_back(putItem);
        commandMessage.push_back("キャンセル");
        commands.push_back(cancel);

        mCommandManager.push(*(new Command(*this, item->param().mName + "をどうしますか?", commandMessage, commands)));
        mCommandWait = true;
    }
}

const Device& GameManager::device() const {
    return mDevice;
}

