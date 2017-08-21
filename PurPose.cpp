/**
 * @file   PurPose.cpp
 * @brief  PurPose
 * @author Maeda Takumi
 */
#include "PurPose.h"

#include "InputManager.h"

PurPose::PurPose(KWindow& aWindow) :
KApplication(aWindow),
mSelect(0),
mInput(
mFace.y,
mFace.x,
*(mKeyboard.mKeyboard + KKeyboard::KEY_ID_W),
*(mKeyboard.mKeyboard + KKeyboard::KEY_ID_S),
*(mKeyboard.mKeyboard + KKeyboard::KEY_ID_A),
*(mKeyboard.mKeyboard + KKeyboard::KEY_ID_D),
*(mKeyboard.mKeyboard + KKeyboard::KEY_ID_Q),
mMouse.mRight,
mMouse.mLeft,
*(mKeyboard.mKeyboard + KKeyboard::KEY_ID_R),
*(mKeyboard.mKeyboard + KKeyboard::KEY_ID_TAB),
*(mKeyboard.mKeyboard + KKeyboard::KEY_ID_L),
mSelect,
mMouse.mLeft,
mMouse.mRight
),
mGameManager(mCamera, mFrontUI, mInput) {
}

void PurPose::draw() const {
    KDrawer::DRAW();
    mGameManager.draw();
}

void PurPose::update() {
    KUpdater::UPDATE();
    if (mWindow.isActive()) {
        mMouse.hide();
        keyProcess();
        mouseProcess();
        mGameManager.update();
    } else mMouse.show();
}

void PurPose::reset() {
    mGameManager.reset();
}

void PurPose::keyProcess() {
    static const KSwitch * key(mKeyboard.mKeyboard);
    static const KSwitch & SHIFT(*(key + KKeyboard::KEY_ID_SHIFT));
    static const KSwitch & F(*(key + KKeyboard::KEY_ID_F));
    static const KSwitch & P(*(key + KKeyboard::KEY_ID_P));

    static KSwitch & ESC(*(mKeyboard.mKeyboard + KKeyboard::KEY_ID_ESCAPE));
    if (ESC.isTouch()) {
        mMouse.show();
        stop(ESC);
    } else if (!ESC.offFrame()) {
        mMouse.hide();
    }

    if (SHIFT.onFrame() && F.isTouch()) mWindow.changeFullScreen();
    if (SHIFT.onFrame() && P.isTouch()) {
        Orchestra & orche(mGameManager.mGameState.mBGM);
        if (orche.volume()) orche.changeVolume(-1.0);
        else orche.changeVolume(1.0);
    }
}

void PurPose::mouseProcess() {
    // マウス感度
    static const float FACE_COEFFICIENT(Math::PI / 180 / 10);

    mSelect = -mMouse.wheel(); // ホイール反転

    KVector center(mWindow.windowArea().center());
    mFace = mMouse.position() - center;
    mMouse.setPos(center);
    if (!mFace.isZero()) mFace *= FACE_COEFFICIENT;
}

