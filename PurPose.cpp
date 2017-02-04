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
mGameManager(InputManager(
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
    KOpenGL _(KOpenGL::GLConfig{true, true, true, true});
    reset();
}

void PurPose::reset() {
    mGameManager.reset();
}

void PurPose::draw() {
    mGameManager.draw();
}

void PurPose::update() {
    static bool pActive(false);
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
    KApplication::update();
}

void PurPose::keyProcess() {
    static const KSwitch * key(mKeyboard.mKeyboard);
    static const KSwitch & SHIFT(*(key + KKeyboard::KEY_ID_SHIFT));
    static const KSwitch & F(*(key + KKeyboard::KEY_ID_F));
    static const KSwitch & ESCAPE(*(key + KKeyboard::KEY_ID_ESCAPE));

    if (ESCAPE.isTouch()) {
        mMouse.show();
        stop(const_cast<KSwitch*> (&ESCAPE));
    } else if (!ESCAPE.offFrame()) {
        mMouse.hide();
    }

    if (SHIFT.offFrame() && F.isTouch()) mWindow.toFullScreen();
}

void PurPose::mouseProcess() {
    mSelect = -mMouse.wheel();

    KVector center(mWindow.windowArea().center());
    mFace = mMouse.pos() - center;
    mMouse.setPos(center);
    if (!mFace.isZero()) {
        mFace = mFace / 1800 * Math::PI;
    }
}

