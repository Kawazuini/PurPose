/**
 * @file   PurPose.cpp
 * @brief  PurPose
 * @author Maeda Takumi
 */
#include "PurPose.h"

PurPose::PurPose(KWindow* aWindow) : KApplication(aWindow) {
    KOpenGL _(KOpenGL::GLConfig{true, true, true, true});

    reset();
}

PurPose::~PurPose() {
}

void PurPose::reset() {
    mGM.reset();
}

void PurPose::update() {
    keyProcess();
    mouseProcess();

    mGM.update();
    KUpdater::UPDATE();

    KApplication::update();
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

    if (W->isTouch() || W->onFrame() > 10) mGM.input(GameManager::W);
    if (A->isTouch() || A->onFrame() > 10) mGM.input(GameManager::A);
    if (S->isTouch() || S->onFrame() > 10) mGM.input(GameManager::S);
    if (D->isTouch() || D->onFrame() > 10) mGM.input(GameManager::D);

    // system
    if (ESCAPE->isTouch()) {
        mMouse.show();
        stop(const_cast<KSwitch*> (ESCAPE));
    } else if (!ESCAPE->offFrame()) {
        mMouse.hide();
    }
    if (O->isTouch()) mWindow->toFullScreen();

    // if (debug->isTouch()) newFloar();
}

void PurPose::mouseProcess() {
    if (mMouse.wheel()) mGM.input(GameManager::WHEEL, mMouse.wheel());

    if (mMouse.mLeft.isTouch()) mGM.input(GameManager::LEFT);
    if (mMouse.mRight.isTouch()) mGM.input(GameManager::RIGHT);
    if (mMouse.mMiddle.isTouch()) mGM.input(GameManager::MIDDLE);

    KVector center = mWindow->windowArea().center();
    KVector angle = mMouse.pos() - center;
    mMouse.setPos(center);

    if (!angle.isZero()) {
        angle /= 10;
        angle = angle / 180 * Math::PI;
        angle.y = -angle.y; // 上下反転
        mGM.input(GameManager::POSITION_X, angle.x);
        mGM.input(GameManager::POSITION_Y, angle.y);
    }
}

void PurPose::draw() {
    mGM.draw();
}

