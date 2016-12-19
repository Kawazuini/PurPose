/**
 * @file   PurPose.cpp
 * @brief  PurPose
 * @author Maeda Takumi
 */
#include "PurPose.h"

#include "Bulletin.h"
#include "Device.h"
#include "Slime.h"
#include "MapGenerator.h"
#include "Mapping.h"
#include "Hero.h"
#include "Stair.h"

PurPose::PurPose(KWindow* aWindow) : KApplication(aWindow) {
    KOpenGL _(KOpenGL::GLConfig{true, true, true, true});

    mStage = NULL;
    mPlayer = NULL;

    reset();
}

PurPose::~PurPose() {
    delete mStage;
    delete mPlayer;
    List<Enemy*> list = Enemy::sEnemies;
    for (Enemy* i : list) delete i;
}

void PurPose::reset() {
    mTurnCount = 0;

    mScene = START;

    Map data;
    MapGenerator::RANDOM_MAP(data);
    if (mStage) delete mStage;
    mStage = new Stage(data, 16);
    mMapping.set(data);

    Character::setStage(mStage);
    Character::setMap(&mMapping);

    if (mPlayer) delete mPlayer;
    mPlayer = new Hero();
    mPlayer->newFloar();

    List<Enemy*> list = Enemy::sEnemies;
    for (Enemy* i : list) delete i;

    mSpawnPeriod = 30;
}

void PurPose::update() {
    switch (mScene) {
        case GAME_PLAY:
        {
            if (checkTurnOver()) {
                switch (mTurn) {
                    case PLAYER:
                        turnStart(ENEMY);
                        break;
                    case ENEMY:
                        turnStart(PLAYER);
                        break;
                }
            }
            keyProcess();
            mouseProcess();

            List<Enemy*> enemies = Enemy::sEnemies;
            for (Enemy* i : enemies) {
                i->update(mPlayer->position());
            }


            KUpdater::UPDATE();
            KApplication::update();

            if (mPlayer->dead()) mScene = GAME_OVER;
            if (mPlayer->isClear()) newFloar();

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
        case ENDING:
            break;
    }
}

void PurPose::keyProcess() {
    static const KSwitch* key = mKeyboard.mKeyboard;
    static const KSwitch* W = key + KKeyboard::K_W;
    static const KSwitch* A = key + KKeyboard::K_A;
    static const KSwitch* S = key + KKeyboard::K_S;
    static const KSwitch* D = key + KKeyboard::K_D;
    static const KSwitch* debug = key + KKeyboard::K_0;
    // system
    static const KSwitch* O = key + KKeyboard::K_O;
    static const KSwitch* ESCAPE = key + KKeyboard::K_ESCAPE;

    KVector move = KVector();
    if (W->isTouch() || W->onFrame() > 10) move.z = -1;
    if (A->isTouch() || A->onFrame() > 10) move.x = -1;
    if (S->isTouch() || S->onFrame() > 10) move.z = 1;
    if (D->isTouch() || D->onFrame() > 10) move.x = 1;
    if (!move.isZero()) mPlayer->move(move);

    // system
    if (ESCAPE->isTouch()) {
        mMouse.show();
        stop(const_cast<KSwitch*> (ESCAPE));
    } else if (!ESCAPE->offFrame()) {
        mMouse.hide();
    }
    if (O->isTouch()) mWindow->toFullScreen();

    if (debug->isTouch()) newFloar();
}

void PurPose::mouseProcess() {
    if (mMouse.wheel() > 0) mPlayer->fumble(-1);
    if (mMouse.wheel() < 0) mPlayer->fumble(1);

    if (mMouse.mLeft.isTouch()) mPlayer->attack();
    if (mMouse.mRight.isTouch()) mPlayer->useItem();
    if (mMouse.mMiddle.isTouch()) mPlayer->equipItem();

    KVector center = mWindow->windowArea().center();
    KVector angle = mMouse.pos() - center;
    mMouse.setPos(center);

    if (!angle.isZero()) {
        angle /= 10;
        angle = angle / 180 * Math::PI;
        angle.y = -angle.y; // 上下反転
        mPlayer->swivel(angle.y, angle.x);
    }
}

void PurPose::draw() {
    KDrawer::DRAW();
    if (mPlayer) mPlayer->draw();
}

void PurPose::turnStart(const Turn& aTurn) {
    mTurn = aTurn;
    switch (mTurn) {
        case PLAYER:
        {
            ++mTurnCount;
            if (!(mTurnCount % mSpawnPeriod)) spawnEnemy();
            return mPlayer->turnStart();
        }
        case ENEMY:
        {
            List<Enemy*> enemies = Enemy::sEnemies;
            for (Enemy* i : enemies) {
                i->turnStart();
            }
            return;
        }
    }
}

bool PurPose::checkTurnOver() {
    switch (mTurn) {
        case PLAYER: return !mPlayer->turn();
        case ENEMY:
        {
            List<Enemy*> enemies = Enemy::sEnemies;
            for (Enemy* i : enemies) if (i->turn()) return false;
            return true;
        }
    }
}

void PurPose::newFloar() {
    Map data;
    MapGenerator::RANDOM_MAP(data);
    if (mStage) delete mStage;
    mStage = new Stage(data, 16);
    mMapping.set(data);

    Character::setStage(mStage);
    Character::setMap(&mMapping);

    mPlayer->newFloar();

    List<Enemy*> list = Enemy::sEnemies;
    for (Enemy* i : list) delete i;

    turnStart(PLAYER);
}

void PurPose::spawnEnemy() {
    if (Enemy::sEnemies.size() < 10)
        new Slime();
    println(Enemy::sEnemies.size());
}

