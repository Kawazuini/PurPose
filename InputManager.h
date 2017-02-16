/**
 * @file   InputManager.h
 * @brief  InputManager
 * @author Maeda Takumi
 */
#ifndef INPUTMANAGER_H
#define INPUTMANAGER_H

#include "main.h"

/**
 * @brief  \~english  input management system
 * @brief  \~japanese 入力管理システム
 * @author \~ Maeda Takumi
 */
class InputManager {
public:
    float& mFaceUD;
    float& mFaceLR;

    KSwitch& mGoFront;
    KSwitch& mGoBack;
    KSwitch& mGoLeft;
    KSwitch& mGoRight;
    KSwitch& mWait;
    KSwitch& mHold;
    KSwitch& mAttack;
    KSwitch& mReload;

    KSwitch& mInventory;
    KSwitch& mLogView;
    int& mSelect;
    KSwitch& mDecision;
    KSwitch& mCancel;

    InputManager(
            float& aFaceUD,
            float& aFaceLR,
            KSwitch& aGoFront,
            KSwitch& aGoBack,
            KSwitch& aGoLeft,
            KSwitch& aGoRight,
            KSwitch& aWait,
            KSwitch& aHold,
            KSwitch& aAttack,
            KSwitch& aReload,
            KSwitch& aInventory,
            KSwitch& aLogView,
            int& aSelect,
            KSwitch& aDecision,
            KSwitch& aCancel
            ) :
    mFaceUD(aFaceUD),
    mFaceLR(aFaceLR),
    mGoFront(aGoFront),
    mGoBack(aGoBack),
    mGoLeft(aGoLeft),
    mGoRight(aGoRight),
    mWait(aWait),
    mHold(aHold),
    mAttack(aAttack),
    mReload(aReload),
    mInventory(aInventory),
    mLogView(aLogView),
    mSelect(aSelect),
    mDecision(aDecision),
    mCancel(aCancel) {
    };
    virtual ~InputManager() = default;

    bool isAnyKeyPressed() const {
        return mGoFront .onFrame() ||
                mGoBack .onFrame() ||
                mGoLeft .onFrame() ||
                mGoRight .onFrame() ||
                mWait .onFrame() ||
                mHold .onFrame() ||
                mAttack .onFrame() ||
                mReload .onFrame() ||
                mInventory.onFrame() ||
                mLogView .onFrame() ||
                mDecision .onFrame() ||
                mCancel .onFrame();
    };
};

#endif /* INPUTMANAGER_H */

