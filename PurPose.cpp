/**
 * @file   PurPose.cpp
 * @brief  PurPose
 * @author Maeda Takumi
 */
#include "PurPose.h"

#include "Bulletin.h"
#include "Device.h"
#include "Slime.h"
#include "Map.h"
#include "Hero.h"

const int PurPose::SCENE_GAME_PLAY = 0;
const int PurPose::SCENE_GAME_OVER = -1;
const int PurPose::SCENE_START = 1;
const int PurPose::SCENE_ENDING = 2;

const int PurPose::PLAYER_TURN = 0;
const int PurPose::ENEMY_TURN = 1;

PurPose::PurPose(KWindow* aWindow) : KApplication(aWindow) {
    KOpenGL _(KOpenGL::GLConfig{true, true, true, true});

    mScene = SCENE_START;

    mMenu = false;
    mMap = new Map(Map::RANDOM_MAP(), 16);
    mMap->define();

    Character::setMap(mMap);

    mPlayer = new Hero();
    new Slime();
    new Slime();
    new Slime();

    turnStart(PLAYER_TURN);
}

PurPose::~PurPose() {
}

void PurPose::update() {
    switch (mScene) {
        case SCENE_GAME_PLAY:
        {
            if (checkTurnEnd()) {
                switch (mTurn) {
                    case PLAYER_TURN:
                        turnStart(ENEMY_TURN);
                        break;
                    case ENEMY_TURN:
                        turnStart(PLAYER_TURN);
                        break;
                }
            }
            keyProcess();
            mouseProcess();

            List<Enemy*> enemies = Enemy::sEnemies;
            for (Enemy* i : enemies) {
                i->update(mPlayer->position());
            }

            if (mPlayer->dead()) mScene = SCENE_GAME_OVER;

            KUpdater::UPDATE();
            KApplication::update();
            break;
        }
        case SCENE_GAME_OVER:
            Device::sBulletin.write("ゲームオーバー!!");
            break;
        case SCENE_START:
            Device::sBulletin.write("ゲームスタート!!");
            mScene = SCENE_GAME_PLAY;
            break;
        case SCENE_ENDING:
            break;
    }
}

void PurPose::keyProcess() {
    static const KSwitch* key = mKeyboard.mKeyboard;
    static const KSwitch* W = key + KKeyboard::K_W;
    static const KSwitch* A = key + KKeyboard::K_A;
    static const KSwitch* S = key + KKeyboard::K_S;
    static const KSwitch* D = key + KKeyboard::K_D;
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
        mMenu = true;
        mMouse.show();
        stop(const_cast<KSwitch*> (ESCAPE));
    } else if (!ESCAPE->offFrame()) {
        mMouse.hide();
    }
    if (O->isTouch()) mWindow->toFullScreen();
}

void PurPose::mouseProcess() {
    if (mMouse.wheel() > 0) mPlayer->fumble(-1);
    if (mMouse.wheel() < 0) mPlayer->fumble(1);

    if (mMouse.mLeft.isTouch()) mPlayer->attack();
    if (mMouse.mRight.isTouch()) mPlayer->useItem();

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
    mPlayer->draw();
}

void PurPose::turnStart(const int& aTurn) {
    mTurn = aTurn;
    switch (mTurn) {
        case PLAYER_TURN: return mPlayer->turnStart();
        case ENEMY_TURN:
        {
            List<Enemy*> enemies = Enemy::sEnemies;
            for (Enemy* i : enemies) {
                i->turnStart();
            }
            return;
        }
    }
}

bool PurPose::checkTurnEnd() {
    switch (mTurn) {
        case PLAYER_TURN: return !mPlayer->turn();
        case ENEMY_TURN:
        {
            List<Enemy*> enemies = Enemy::sEnemies;
            for (Enemy* i : enemies) if (i->turn()) return false;
            return true;
        }
    }
}

