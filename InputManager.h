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

    KSwitch& mInventory;
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
            KSwitch& aInventory,
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
    mInventory(aInventory),
    mSelect(aSelect),
    mDecision(aDecision),
    mCancel(aCancel) {
    };
    virtual ~InputManager() = default;
};

#endif /* INPUTMANAGER_H */

