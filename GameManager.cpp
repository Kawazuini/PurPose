/**
 * @file   GameManager.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Command.h"
#include "Item.h"
#include "Slime.h"
#include "Special.h"
#include "Stair.h"

GameManager::GameManager() :
mFumble(0),
mScene(START),
mTurn(PLAYER),
mTurnCount(0),
mSpawnPeriod(0),
mCommandWait(false),
mCommandManager(mDevice) {
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
            if (!mCommandWait) {
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
                    mGameState.mPlayer.move(mGameState, mMove);
                    mMove = KVector();
                }
                if (mFumble) {
                    mGameState.mPlayer.fumble(mFumble);
                    mFumble = 0;
                }
                if (!mAngle.isZero()) {
                    mGameState.mPlayer.swivel(mAngle.y, mAngle.x);
                    mAngle = KVector();
                }

                // 階段に到達
                if (mGameState.mStage.stair().judge(mGameState.mPlayer.position())) {
                    mCommandManager.add(Command(
                            *this,
                            "つぎのフロアにいどうしますか?",
                            List<String>{"はい", "いいえ"},
                    Vector<CommandFunc>{
                        newFloar, stairCancel
                    },
                    KVector(400, 200)
                            ));
                    mCommandWait = true;
                }

                mGameState.mMapping.room(mGameState.mPlayer.position());

                if (mGameState.mPlayer.dead()) mScene = GAME_OVER;

                Special::invocation(mGameState);
            }
            break;
        }
        case GAME_OVER:
            mGameState.mBulletin.write("ゲームオーバー!!");
            break;
        case START:
            mGameState.mBulletin.write("ゲームスタート!!");
            mGameState.mBulletin.write("W : ぜんしん  S : こうたい  A : ひだりに  D : みぎに");
            mGameState.mBulletin.write("ホイールぐりぐり  : アイテムせんたく");
            mGameState.mBulletin.write("ひだりクリック    : こうげき");
            mGameState.mBulletin.write("みぎクリック      : アイテムコマンド");
            mGameState.mBulletin.write("コマンドせんたくのときは");
            mGameState.mBulletin.write("ひだりクリック : けってい");
            mGameState.mBulletin.write("みぎクリック   : キャンセル");
            mGameState.mBulletin.write("ESC            : ゲームしゅうりょう");
            mGameState.mBulletin.flush();
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

    if (!mCommandWait) {
        switch (aInputType) {
            case W: mMove += MOVE_W;
                break;
            case A: mMove += MOVE_A;
                break;
            case S: mMove += MOVE_S;
                break;
            case D: mMove += MOVE_D;
                break;
            case Q: mGameState.mPlayer.wait();
                break;
            case WHEEL: mFumble = -aValue; // 逆転
                break;
            case LEFT: mGameState.mPlayer.attack(mGameState);
                break;
            case RIGHT:
            {
                makeItemCommand();
                break;
            }
            case POSITION_X: mAngle.x = aValue;
                break;
            case POSITION_Y: mAngle.y = aValue;
                break;
        }
    } else {
        switch (aInputType) {
            case W: mCommandManager.changeCommand(-1);
                break;
            case S: mCommandManager.changeCommand(1);
                break;
            case WHEEL: mCommandManager.changeCommand(-aValue);
                break;
            case LEFT:
                mCommandManager.choose();
                mCommandManager.back();
                mDevice.refresh(mGameState);
                mCommandWait = false;
                break;
            case RIGHT:
                mGameState.mStage.stair().stop();
                mCommandManager.back();
                mDevice.refresh(mGameState);
                mCommandWait = false;
                break;
        }
    }
}

void GameManager::turnStart(const Turn & aTurn) {
    mTurn = aTurn;
    switch (mTurn) {
        case PLAYER:
        {
            ++mTurnCount;
            if (!(mTurnCount % mSpawnPeriod)) spawnEnemy();
            mGameState.mPlayer.turnStart();
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

bool GameManager::checkTurnEnd() const {
    switch (mTurn) {
        case PLAYER: return !mGameState.mPlayer.turn();
        case ENEMY:
        {
            for (Enemy* i : Enemy::sEnemies) if (i->turn()) return false;
            return true;
        }
    }
}

void GameManager::spawnEnemy() {
    if (Enemy::sEnemies.size() < 10) {
        Enemy* tmp = new Slime();
        tmp->setPosition(mGameState.respawn());
    }
    println(Enemy::sEnemies.size());
}

void GameManager::makeItemCommand() {
    const Item* item = mGameState.mPlayer.backPack().lookAt();
    if (item) {
        List<String> commandMessage;
        Vector<CommandFunc> commands;

        if (item->usable()) {
            commandMessage.push_back("つかう");
            commands.push_back(useItem);
        }
        if (item->equippable()) {
            commandMessage.push_back("そうび");
            commands.push_back(equipItem);
        }
        if (item->throwable()) {
            commandMessage.push_back("なげる");
            commands.push_back(throwItem);
        }
        commandMessage.push_back("キャンセル");
        commands.push_back(cancel);

        mCommandManager.add(Command(
                *this,
                item->name() + "をどうしますか?",
                commandMessage,
                commands,
                KVector(500, 200)
                ));
        mCommandWait = true;
    }
}

