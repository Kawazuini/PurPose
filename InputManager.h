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
class InputManager final {
public:
    /**
     * @brief \~english  up-down turn input
     * @brief \~japanese 上下振り向き入力
     */
    float& mFaceUD;
    /**
     * @brief \~english  right-left turn input
     * @brief \~japanese 左右振り向き入力
     */
    float& mFaceLR;

    /**
     * @brief \~english  front input
     * @brief \~japanese 前進入力
     */
    KSwitch& mGoFront;
    /**
     * @brief \~english  back input
     * @brief \~japanese 後退入力
     */
    KSwitch& mGoBack;
    /**
     * @brief \~english  left input
     * @brief \~japanese 左入力
     */
    KSwitch& mGoLeft;
    /**
     * @brief \~english  right input
     * @brief \~japanese 右入力
     */
    KSwitch& mGoRight;
    /**
     * @brief \~english  wait input
     * @brief \~japanese 待機入力
     */
    KSwitch& mWait;
    /**
     * @brief \~english  hold input
     * @brief \~japanese 構え入力
     */
    KSwitch& mHold;
    /**
     * @brief \~english  attack input
     * @brief \~japanese 攻撃入力
     */
    KSwitch& mAttack;
    /**
     * @brief \~english  reload input
     * @brief \~japanese リロード入力
     */
    KSwitch& mReload;

    /**
     * @brief \~english  inventory input
     * @brief \~japanese アイテム画面切り替え入力
     */
    KSwitch& mInventory;
    /**
     * @brief \~english  log switvh input
     * @brief \~japanese ログ切り替え入力
     */
    KSwitch& mLogView;
    /**
     * @brief \~english  select change input
     * @brief \~japanese 選択変更入力
     */
    int& mSelect;
    /**
     * @brief \~english  decision input
     * @brief \~japanese 決定入力
     */
    KSwitch& mDecision;
    /**
     * @brief \~english  cancel input
     * @brief \~japanese キャンセル入力
     */
    KSwitch& mCancel;

    /**
     * \~english
     * @param aFaceUD    up-down turn input
     * @param aFaceLR    right-left turn input
     * @param aGoFront   front input
     * @param aGoBack    back input
     * @param aGoLeft    left input
     * @param aGoRight   right input
     * @param aWait      wait input
     * @param aHold      hold input
     * @param aAttack    attack input
     * @param aReload    reload input
     * @param aInventory inventory input
     * @param aLogView   log switvh input
     * @param aSelect    select change input
     * @param aDecision  decision input
     * @param aCancel    cancel input
     * \~japanese
     * @param aFaceUD    上下振り向き入力
     * @param aFaceLR    左右振り向き入力
     * @param aGoFront   前進入力
     * @param aGoBack    後退入力
     * @param aGoLeft    左入力
     * @param aGoRight   右入力
     * @param aWait      待機入力
     * @param aHold      構え入力
     * @param aAttack    攻撃入力
     * @param aReload    リロード入力
     * @param aInventory アイテム画面切り替え入力
     * @param aLogView   ログ切り替え入力
     * @param aSelect    選択変更入力
     * @param aDecision  決定入力
     * @param aCancel    キャンセル入力
     */
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

    /**
     * \~english
     * @brief  get whether pushed ane key.
     * @return whether pushed any key
     * \~japanese
     * @brief  いずれかのキーが押されているかどうかを取得します。
     * @return いずれかのキーが押されているか
     */
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

