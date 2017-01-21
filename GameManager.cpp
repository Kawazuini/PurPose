/**
 * @file   GameManager.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Command.h"
#include "Enemy.h"
#include "Item.h"
#include "Special.h"
#include "Stair.h"

GameManager::GameManager() :
mFumble(0),
mWait(false),
mAttack(false),
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
    while (!mGameState.mEnemies.empty()) {
        mGameState.mEnemies.front()->mCharacterParameter.mDead = true;
        mGameState.mEnemies.front()->update(mGameState);
    }
}

void GameManager::reset() {
    mSpawnPeriod = 30;

    mScene = START;
    mGameState.mPlayer.reset();

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
                if (mWait) {
                    mGameState.mPlayer.wait();
                    mWait = false;
                }
                if (mAttack) {
                    mGameState.mPlayer.attack(mGameState);
                    mAttack = false;
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

                if (mGameState.mPlayer.mCharacterParameter.mDead) mScene = GAME_OVER;

                Special::invocation(mGameState);
            }
            break;
        }
        case GAME_OVER:
            mGameState.mBulletin.write("ゲームオーバー!!");
            mGameState.mBulletin.flush();
            reset();
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

void GameManager::input(const InputType& aInputType, const float& aValue) {
    static const KVector MOVE_W(0.00, 0.00, -1.0);
    static const KVector MOVE_A(-1.0, 0.00, 0.00);
    static const KVector MOVE_S(0.00, 0.00, 1.00);
    static const KVector MOVE_D(1.00, 0.00, 0.00);

    if (!mCommandWait) {
        switch (aInputType) {
            case GO_FRONT: mMove += MOVE_W;
                break;
            case GO_LEFT: mMove += MOVE_A;
                break;
            case GO_BACK: mMove += MOVE_S;
                break;
            case GO_RIGHT: mMove += MOVE_D;
                break;
            case WAIT: mWait = true;
                break;
            case SELECT: mFumble = -aValue; // 逆転
                break;
            case DECISION: mAttack = true;
                break;
            case CANCEL:
            {
                makeItemCommand();
                break;
            }
            case FACE_UP: mAngle.y = -aValue;
                break;
            case FACE_DOWN: mAngle.y = aValue;
                break;
            case FACE_LEFT: mAngle.x = aValue;
                break;
            case FACE_RIGHT: mAngle.x = -aValue;
                break;
        }
    } else {
        switch (aInputType) {
            case GO_FRONT: mCommandManager.changeCommand(-1);
                break;
            case GO_BACK: mCommandManager.changeCommand(1);
                break;
            case SELECT: mCommandManager.changeCommand(-aValue);
                break;
            case DECISION:
                mCommandManager.choose();
                mCommandManager.back();
                mDevice.refresh(mGameState);
                mCommandWait = false;
                break;
            case CANCEL:
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
            for (Enemy* i : mGameState.mEnemies) {
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
            for (Enemy* i : mGameState.mEnemies) if (i->turn()) return false;
            return true;
        }
    }
}

void GameManager::spawnEnemy() {
    if (mGameState.mEnemies.size() < 10) {
        Enemy* tmp = new Enemy(random(8) + 1, mGameState);
        tmp->setPosition(mGameState, mGameState.respawn());
    }
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
                item->mItemParameter.mName + "をどうしますか?",
                commandMessage,
                commands,
                KVector(500, 200)
                ));
        mCommandWait = true;
    }
}

