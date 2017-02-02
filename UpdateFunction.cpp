/**
 * @file   UpdateFunction.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Command.h"
#include "Special.h"
#include "Stair.h"

void GameManager::update_start() {
    mGameState.mBulletin.write(" ");
    mGameState.mBulletin.write(" ");
    mGameState.mBulletin.write("ゲームスタート!!");
    mGameState.mBulletin.write("操作説明");
    mGameState.mBulletin.write(" ");
    mGameState.mBulletin.write("W : ぜんしん  S : こうたい  A : ひだりに  D : みぎに");
    mGameState.mBulletin.write("TAB              : アイテムせんたくがめん");
    mGameState.mBulletin.write("マウスいどう     : してんいどう");
    mGameState.mBulletin.write("ホイールぐりぐり : アイテムせんたく");
    mGameState.mBulletin.write("ひだりクリック   : けってい/こうげき");
    mGameState.mBulletin.write("みぎクリック     : キャンセル/ぶきをかまえる");
    mGameState.mBulletin.write("R                : リロード");
    mGameState.mBulletin.write("L                : ログのかくにん");
    mGameState.mBulletin.write("ESC              : ゲームしゅうりょう");
    mGameState.mBulletin.write("");
    mGameState.mBulletin.write("");
    mGameState.mBulletin.write("");
    mGameState.mBulletin.write(Message("よみきれない?", 0xffff0000));
    mGameState.mBulletin.write(Message("Lでログをかくにんしてみよう!", 0xffff0000));
    mGameState.mBulletin.flush();
    mScene = SCENE_PLAY;
    turnStart(PLAYER);
}

void GameManager::update_play() {
    static const KVector MOVE_W(0.00, 0.00, -1.0);
    static const KVector MOVE_A(-1.0, 0.00, 0.00);
    static const KVector MOVE_S(0.00, 0.00, 1.00);
    static const KVector MOVE_D(1.00, 0.00, 0.00);

    // 視点移動
    if (mInputManager.mFaceUD || mInputManager.mFaceLR) mEyeCamera.rotate(-mInputManager.mFaceUD, mInputManager.mFaceLR);
    light.mPosition = mEyeCamera.mPosition;
    light.mDirection = mEyeCamera.mDirection;
    light.at();

    if (mInputManager.mInventory.isTouch()) {
        // アイテム画面の切り替え
        mInventory = !mInventory;

        // コマンドキャンセル
        if (mCommandWait) {
            mCommandManager.cancel();
            mCommandWait = false;
        }
        mDevice.refresh(mGameState);
    }

    if (mCommandWait) { // コマンド待機状態
        // コマンド選択・実行・キャンセル(同時押しの場合はキャンセルが優先されます)
        mCommandManager.changeCommand(mInputManager.mSelect);
        if (mInputManager.mCancel.isTouch()) {
            mCommandManager.cancel();
            mDevice.refresh(mGameState);
            mCommandWait = false;
        } else if (mInputManager.mDecision.isTouch()) {
            mCommandManager.choose();
            mCommandManager.back();
            mDevice.refresh(mGameState);
            mCommandWait = false;
        }
        return;
    }

    if (mInventory) {
        mDevice.drawBackPack(mGameState.mPlayer.backPack());
        // ターン終了でインベントリを閉じる
        if (!mGameState.mPlayer.turn()) {
            mInventory = false;
            mDevice.refresh(mGameState);
        }
        // アイテムの選択・アイテムコマンドの生成
        mGameState.mPlayer.fumble(mInputManager.mSelect);
        if (mInputManager.mDecision.isTouch()) makeItemCommand();
        return;
    }

    // ログ表示
    if (mInputManager.mLogView.onFrame()) {
        mDevice.drawMessageLog(mGameState.mBulletin);
    } else if (mInputManager.mLogView.offFrame() == 0) {
        mDevice.refresh(mGameState);
    }

    // ターンチェンジ
    if (checkTurnEnd()) {
        switch (mTurn) {
            case PLAYER: turnStart(ENEMY);
                break;
            case ENEMY: turnStart(PLAYER);
                break;
        }
    }

    // 敵の死
    List<Enemy*> deadEnemy;
    for (Enemy* i : mGameState.enemyList()) {
        if (i->mCharacterParameter.mDead) deadEnemy.push_back(i);
    }
    for (Enemy* i : deadEnemy) {
        mGameState.removeEnemy(*i);
        delete i;
    }

    Object::UPDATE(mGameState);

    // 移動・待機
    KVector move;
    if (mInputManager.mGoFront.isTouch() || mInputManager.mGoFront.onFrame() > 10) move += MOVE_W;
    if (mInputManager.mGoBack.isTouch() || mInputManager.mGoBack.onFrame() > 10) move += MOVE_S;
    if (mInputManager.mGoLeft.isTouch() || mInputManager.mGoLeft.onFrame() > 10) move += MOVE_A;
    if (mInputManager.mGoRight.isTouch() || mInputManager.mGoRight.onFrame() > 10) move += MOVE_D;
    if (!move.isZero()) mGameState.mPlayer.move(mGameState, mEyeCamera.convertDirection(move));
    if (mInputManager.mWait.isTouch() || mInputManager.mWait.onFrame() > 50) mGameState.mPlayer.wait();
    // 武器構え・攻撃・リロード
    if (mInputManager.mHold.onFrame()) {
        mGameState.mPlayer.arm();
        mEyeCamera.mAngle = KCamera::DEFAULT_ANGLE / 2;
    } else {
        mGameState.mPlayer.disarm();
        mEyeCamera.mAngle = KCamera::DEFAULT_ANGLE;
    }
    if (mInputManager.mAttack.isTouch()) mGameState.mPlayer.attack(mGameState);
    if (mInputManager.mReload.isTouch()) mGameState.mPlayer.reload(mGameState);

    // 階段に到達
    if (mGameState.mStage.stair().judge(mGameState.mPlayer.position())) {
        mCommandManager.add(Command(*this, "つぎのフロアにいどうしますか?", COMMAND_TEXT_YES_NO, Vector<CommandFunction>{newFloar, stairCancel}, KVector(400, 200)));
        mCommandWait = true;
    }

    mGameState.mMapping.room(mGameState.mPlayer.position());

    Special::invocation(mGameState);

    if (mGameState.mPlayer.mCharacterParameter.mDead) mScene = SCENE_OVER;
}

void GameManager::update_over() {
    mGameState.mBulletin.write("ゲームオーバー!!");
    mGameState.mBulletin.flush();
    reset();
}

void GameManager::update_ending() {
}

