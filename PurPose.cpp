/**
 * @file PurPose.cpp
 * @brief PurPoseクラスの実装
 */
#include "PurPose.h"

#include "Dice.h"

#include "Slime.h"
#include "Map.h"
#include "Hero.h"

const int PurPose::PLAYER_TURN = 0;
const int PurPose::ENEMY_TURN = 1;

Slime* slime;

PurPose::PurPose(KWindow* aWindow) : KApplication(aWindow) {
    KOpenGL _(KOpenGL::GLConfig{true, true, true, true});

    mMenu = false;
    mMap = new Map(Map::RANDOM_MAP(), 16);
    mMap->define();

    Character::setMap(mMap);

    mPlayer = new Hero();
    slime = new Slime();
    slime->setPosition(mPlayer->position() + KVector(0, 0, 2));

    turnStart(PLAYER_TURN);
}

PurPose::~PurPose() {
}

void PurPose::update() {
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

    KSwitch* key = mKeyboard.mKeyboard;
    if ((key + KKeyboard::K_0)->isTouch()) mWindow->toFullScreen();

    KVector move = KVector();
    if ((key + KKeyboard::K_W)->onFrame()) move.z = -1;
    if ((key + KKeyboard::K_S)->onFrame()) move.z = 1;
    if ((key + KKeyboard::K_D)->onFrame()) move.x = 1;
    if ((key + KKeyboard::K_A)->onFrame()) move.x = -1;
    if ((key + KKeyboard::K_Z)->onFrame()) move.y = 1;
    if ((key + KKeyboard::K_X)->onFrame()) move.y = -1;
    if (!move.isZero()) mPlayer->move(move);

    if (mMouse.wheel() > 0) mPlayer->fumble(-1);
    if (mMouse.wheel() < 0) mPlayer->fumble(1);

    KRect wArea = mWindow->windowArea();
    KVector center(wArea.centerX(), wArea.centerY());
    KVector angle = mMouse.pos() - center;
    mMouse.setPos(center);

    if (!angle.isZero()) {
        angle /= 10;
        angle = angle / 180 * Math::PI;

        angle.y = -angle.y; // 上下反転

        mPlayer->swivel(angle.y, angle.x);
    }


    if ((key + KKeyboard::K_ESCAPE)->isTouch()) {
        mMenu = true;
        mMouse.show();
        stop(key + KKeyboard::K_ESCAPE);
    } else if (!((key + KKeyboard::K_ESCAPE)->offFrame())) {
        mMouse.hide();
    }

    slime->update(mPlayer->position());

    KUpdater::UPDATE();
    KApplication::update();
}

void PurPose::draw() {
    KDrawer::DRAW();
    mPlayer->draw();
}

void PurPose::turnStart(const int& aTurn) {
    mTurn = aTurn;
    switch (mTurn) {
        case PLAYER_TURN: return mPlayer->turnStart();
        case ENEMY_TURN: return slime->turnStart();
    }
}

bool PurPose::checkTurnEnd() {
    switch (mTurn) {
        case PLAYER_TURN: return !mPlayer->turn();
        case ENEMY_TURN: return !slime->turn();
    }
}

