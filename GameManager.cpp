/**
 * @file   GameManager.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Device.h"
#include "HPotion.h"
#include "Item.h"
#include "MapGenerator.h"
#include "Slime.h"
#include "Special.h"
#include "Stair.h"

GameManager::GameManager() :
mGameState(mPlayer, mMap, mMapping, mStage),
mDevice(mGameState),
mFumble(0),
mScene(START),
mTurn(PLAYER),
mTurnCount(0),
mSpawnPeriod(0) {
    KDrawer::remove();
    KUpdater::remove();
    reset();
}

GameManager::~GameManager() {
    while (!Enemy::sEnemies.empty()) delete (Enemy::sEnemies.front());
}

void GameManager::reset() {
    mSpawnPeriod = 30;

    newFloar();
}

void GameManager::draw() const {
    KDrawer::DRAW();
    mDevice.draw();
}

void GameManager::update() {
    switch (mScene) {
        case GAME_PLAY:
        {
            // ターンチェンジ
            if (checkTurnEnd()) {
                switch (mTurn) {
                    case PLAYER: turnStart(ENEMY);
                        break;
                    case ENEMY: turnStart(PLAYER);
                        break;
                }
            }

            Object::UPDATE(mGameState);

            if (!mMove.isZero()) {
                mPlayer.move(mMove);
                mMove = KVector();
            }
            if (mFumble) {
                mPlayer.fumble(mFumble);
                mFumble = 0;
            }
            if (!mAngle.isZero()) {
                mPlayer.swivel(mAngle.y, mAngle.x);
                mAngle = KVector();
            }

            // 階段に到達
            static const float SCALE_SQUARE = MAP_SCALE * MAP_SCALE;
            if ((mGameState.mStage.stair().position() - mPlayer.position()).lengthSquared() < SCALE_SQUARE) {
                newFloar();
            }

            if (mPlayer.dead()) mScene = GAME_OVER;

            Special::invocation();

            break;
        }
        case GAME_OVER:
            Device::sBulletin.write("ゲームオーバー!!");
            break;
        case START:
            Device::sBulletin.write("ゲームスタート!!");
            Device::sBulletin.write("W : ぜんしん  S : こうたい  A : ひだりに  D : みぎに");
            Device::sBulletin.write("ひだりクリック     : こうげき");
            Device::sBulletin.write("ホイールぐりぐり   : アイテムせんたく");
            Device::sBulletin.write("ちゅうおうクリック : アイテムそうび");
            Device::sBulletin.write("みぎクリック       : アイテムしよう");
            mScene = GAME_PLAY;
            turnStart(PLAYER);
            break;
    }
}

void GameManager::input(const InputType& aInputType, const double& aValue) {
    static const KVector MOVE_W(0.00, 0.00, -1.0);
    static const KVector MOVE_A(-1.0, 0.00, 0.00);
    static const KVector MOVE_S(0.00, 0.00, 1.00);
    static const KVector MOVE_D(1.00, 0.00, 0.00);

    switch (aInputType) {
        case W: mMove += MOVE_W;
            break;
        case A: mMove += MOVE_A;
            break;
        case S: mMove += MOVE_S;
            break;
        case D: mMove += MOVE_D;
            break;
        case WHEEL: mFumble = -aValue; // 逆転
            break;
        case LEFT: mPlayer.attack();
            break;
        case RIGHT: mPlayer.useItem();
            break;
        case MIDDLE: mPlayer.equipItem();
            break;
        case POSITION_X: mAngle.x = aValue;
            break;
        case POSITION_Y: mAngle.y = aValue;
            break;
    }
}

const Hero& GameManager::player() const {
    return mPlayer;
}

void GameManager::turnStart(const Turn& aTurn) {
    mTurn = aTurn;
    switch (mTurn) {
        case PLAYER:
        {
            ++mTurnCount;
            if (!(mTurnCount % mSpawnPeriod)) spawnEnemy();
            mPlayer.turnStart();
            return;
        }
        case ENEMY:
        {
            for (Enemy* i : Enemy::sEnemies) {
                i->turnStart();
            }
            return;
        }
    }
}

bool GameManager::checkTurnEnd() {
    switch (mTurn) {
        case PLAYER: return !mPlayer.turn();
        case ENEMY:
        {
            for (Enemy* i : Enemy::sEnemies) if (i->turn()) return false;
            return true;
        }
    }
}

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

void GameManager::spawnEnemy() {
    if (Enemy::sEnemies.size() < 10) {
        Enemy* tmp = new Slime();
        tmp->setPosition(mGameState.respawn());
    }
    println(Enemy::sEnemies.size());
}

