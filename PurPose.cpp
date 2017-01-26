/**
 * @file   PurPose.cpp
 * @brief  PurPose
 * @author Maeda Takumi
 */
#include "PurPose.h"

#include "WaterBalloon.h"

PurPose::PurPose(KWindow& aWindow) : KApplication(aWindow) {
    KOpenGL _(KOpenGL::GLConfig{true, true, true, true});
    reset();
}

void PurPose::reset() {
    mGM.reset();
}

void PurPose::draw() {
    mGM.draw();
}

void PurPose::update() {
    keyProcess();
    mouseProcess();

    mGM.update();
    KUpdater::UPDATE();

    KApplication::update();
}

void PurPose::keyProcess() {
    static const KSwitch * key(mKeyboard.mKeyboard);
    static const KSwitch & Q(*(key + KKeyboard::K_Q));
    static const KSwitch & W(*(key + KKeyboard::K_W));
    static const KSwitch & A(*(key + KKeyboard::K_A));
    static const KSwitch & S(*(key + KKeyboard::K_S));
    static const KSwitch & D(*(key + KKeyboard::K_D));
    // system
    static const KSwitch & O(*(key + KKeyboard::K_O));
    static const KSwitch & ESCAPE(*(key + KKeyboard::K_ESCAPE));

    if (W.isTouch() || W.onFrame() > 10) mGM.input(GameManager::GO_FRONT);
    if (A.isTouch() || A.onFrame() > 10) mGM.input(GameManager::GO_LEFT);
    if (S.isTouch() || S.onFrame() > 10) mGM.input(GameManager::GO_BACK);
    if (D.isTouch() || D.onFrame() > 10) mGM.input(GameManager::GO_RIGHT);
    if (Q.isTouch() || Q.onFrame() > 50) mGM.input(GameManager::WAIT);

    // system
    if (ESCAPE.isTouch()) {
        mMouse.show();
        stop(const_cast<KSwitch*> (&ESCAPE));
    } else if (!ESCAPE.offFrame()) {
        mMouse.hide();
    }

    if (O.isTouch()) mWindow.toFullScreen();
}

void PurPose::mouseProcess() {
    if (mMouse.wheel()) mGM.input(GameManager::SELECT, mMouse.wheel());

    if (mMouse.mLeft.isTouch()) mGM.input(GameManager::DECISION);
    if (mMouse.mRight.isTouch()) mGM.input(GameManager::CANCEL);

    KVector center = mWindow.windowArea().center();
    KVector angle = mMouse.pos() - center;
    mMouse.setPos(center);

    if (!angle.isZero()) {
        angle /= 10;
        angle = angle / 180 * Math::PI;
        if (angle.y) {
            mGM.input(angle.y > 0 ? GameManager::FACE_UP : GameManager::FACE_DOWN, Math::abs(angle.y));
        }
        if (angle.x) {
            mGM.input(angle.x > 0 ? GameManager::FACE_LEFT : GameManager::FACE_RIGHT, Math::abs(angle.x));
        }
    }
}

