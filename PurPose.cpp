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
mGameManager(
mCamera,
mFrontUI,
InputManager(
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
)) {
}

void PurPose::reset() {
    mGameManager.reset();
}

void PurPose::draw() const {
    KDrawer::DRAW();
    mGameManager.draw();
}

void PurPose::update() {
    static bool pActive(false);
    KUpdater::UPDATE();
    if (mWindow.isActive()) {
        if (!pActive) {
            mMouse.hide();
            pActive = true;
        }
        keyProcess();
        mouseProcess();

        mGameManager.update();
        KUpdater::UPDATE();
    } else {
        mMouse.show();
        pActive = false;
    }
}

void PurPose::keyProcess() {
    static const KSwitch * key(mKeyboard.mKeyboard);
    static const KSwitch & SHIFT(*(key + KKeyboard::KEY_ID_SHIFT));
    static const KSwitch & F(*(key + KKeyboard::KEY_ID_F));

    if ((mKeyboard.mKeyboard + KKeyboard::KEY_ID_ESCAPE)->isTouch()) {
        mMouse.show();
        stop(*(mKeyboard.mKeyboard + KKeyboard::KEY_ID_ESCAPE));
    } else if (!(mKeyboard.mKeyboard + KKeyboard::KEY_ID_ESCAPE)->offFrame()) {
        mMouse.hide();
    }

    if (SHIFT.offFrame() && F.isTouch()) mWindow.changeFullScreen();
}

void PurPose::mouseProcess() {
    // マウス感度
    static const float FACE_COEFFICIENT(Math::PI / 180 / 10);

    mSelect = -mMouse.wheel(); // ホイール反転

    KVector center(mWindow.windowArea().center());
    mFace = mMouse.pos() - center;
    mMouse.setPos(center);
    if (!mFace.isZero()) mFace *= FACE_COEFFICIENT;
}

