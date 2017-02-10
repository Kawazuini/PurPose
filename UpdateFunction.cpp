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
    static const KRect ALL(KGLUI::WIDTH, KGLUI::HEIGHT);
    static const int PULSE(192); // 枠が満ちる周期
    static const double XDIFF((double) KGLUI::WIDTH / PULSE);
    static const double YDIFF((double) KGLUI::HEIGHT / PULSE);

    static int frameCount(0);

    if (frameCount <= PULSE * 2) frameCount++;
    if (frameCount <= PULSE * 2) mDevice.UI().mScreen.clearRect(ALL);

    if (frameCount <= PULSE) {
        for (int i = 1; i < 64; ++i) {
            if (i % 2) mDevice.UI().mScreen.drawVLine(0, frameCount * YDIFF, Device::UI_SIZE * i, 0xffffffff);
            else mDevice.UI().mScreen.drawVLine(KGLUI::HEIGHT, KGLUI::HEIGHT - frameCount * YDIFF, Device::UI_SIZE * i, 0xffffffff);
        }
        for (int i = 1; i < 36; ++i) {
            if (i % 2) mDevice.UI().mScreen.drawHLine(0, frameCount * XDIFF, Device::UI_SIZE * i, 0xffffffff);
            else mDevice.UI().mScreen.drawHLine(KGLUI::WIDTH, KGLUI::WIDTH - frameCount * XDIFF, Device::UI_SIZE * i, 0xffffffff);
        }
    } else if (frameCount <= PULSE * 2) {
        int fc(frameCount - PULSE);
        for (int i = 1; i < 64; ++i) {
            if (i % 2) mDevice.UI().mScreen.drawVLine(fc * YDIFF, KGLUI::HEIGHT, Device::UI_SIZE * i, 0xffffffff);
            else mDevice.UI().mScreen.drawVLine(KGLUI::HEIGHT - fc * YDIFF, 0, Device::UI_SIZE * i, 0xffffffff);
        }
        for (int i = 1; i < 36; ++i) {
            if (i % 2) mDevice.UI().mScreen.drawHLine(fc * XDIFF + 1, KGLUI::WIDTH, Device::UI_SIZE * i, 0xffffffff);
            else mDevice.UI().mScreen.drawHLine(KGLUI::WIDTH - fc * XDIFF, 0, Device::UI_SIZE * i, 0xffffffff);
        }
        color drawColor((int) ((double) fc / PULSE * 255) << 24 | 0xffffff);
        drawTitle(drawColor);

        String txt("---左クリックでSTART---");
        mDevice.UI().mScreen.drawText(
                CHARSET,
                txt,
                KVector(
                KGLUI::WIDTH / 2 - CHARSET.getWidth(txt) / 2,
                KGLUI::HEIGHT / 2 + CHARSET.mSize * 2
                ),
                drawColor
                );
        txt = "~~~ESCでマウスのロックを解除~~~";
        mDevice.UI().mScreen.drawText(
                CHARSET_MINI,
                txt,
                KVector(
                KGLUI::WIDTH / 2 - CHARSET_MINI.getWidth(txt) / 2,
                KGLUI::HEIGHT / 2 + CHARSET.mSize * 5
                ),
                drawColor
                );
    }

    if (mInputManager.mDecision.isTouch()) {
        frameCount = 0;
        mDevice.UI().mScreen.clearRect(ALL);
        mGameState.mBulletin.write(" ");
        mGameState.mBulletin.write(" ");
        mGameState.mBulletin.write("ゲームスタート!!");
        mGameState.mBulletin.write(" ");
        mGameState.mBulletin.write("操作説明");
        mGameState.mBulletin.write("W : 前進  S : 後退  A : 左へ  D : 右へ");
        mGameState.mBulletin.write("TAB              : アイテム選択画面");
        mGameState.mBulletin.write("マウス移動       : 視点移動");
        mGameState.mBulletin.write("ホイール回転     : 項目選択");
        mGameState.mBulletin.write("左クリック       : 決定/攻撃");
        mGameState.mBulletin.write("右クリック       : キャンセル/武器を構える");
        mGameState.mBulletin.write("R                : リロード");
        mGameState.mBulletin.write("L                : ログの確認");
        mGameState.mBulletin.write("Shift + F        : フルスクリーン/フルスクリーン解除");
        mGameState.mBulletin.write("ESC              : ゲーム中断/再開");
        mGameState.mBulletin.write("");
        mGameState.mBulletin.write("");
        mGameState.mBulletin.write("");
        mGameState.mBulletin.write(Message("読み切れない?", 0xffff0000));
        mGameState.mBulletin.write(Message("Lでログを確認してみよう!", 0xffff0000));
        mGameState.mBulletin.flush();
        mScene = SCENE_PLAY;
        turnStart(PLAYER);
    }
}

void GameManager::drawTitle(const color& aColor) {
    // P
    mDevice.UI().mScreen.drawRect(KRect(KVector(2, 1) * Device::UI_SIZE, KVector(3, 9) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(3, 1) * Device::UI_SIZE, KVector(7, 2) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(3, 5) * Device::UI_SIZE, KVector(7, 6) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(7, 2) * Device::UI_SIZE, KVector(8, 5) * Device::UI_SIZE), aColor);
    // U
    mDevice.UI().mScreen.drawRect(KRect(KVector(11, 2) * Device::UI_SIZE, KVector(12, 8) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(16, 2) * Device::UI_SIZE, KVector(17, 8) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(12, 8) * Device::UI_SIZE, KVector(16, 9) * Device::UI_SIZE), aColor);
    // R
    mDevice.UI().mScreen.drawRect(KRect(KVector(20, 1) * Device::UI_SIZE, KVector(21, 9) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(21, 1) * Device::UI_SIZE, KVector(25, 2) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(21, 5) * Device::UI_SIZE, KVector(25, 6) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(25, 2) * Device::UI_SIZE, KVector(26, 5) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(23, 6) * Device::UI_SIZE, KVector(24, 7) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(24, 7) * Device::UI_SIZE, KVector(25, 8) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(25, 8) * Device::UI_SIZE, KVector(26, 9) * Device::UI_SIZE), aColor);
    // P
    mDevice.UI().mScreen.drawRect(KRect(KVector(29, 1) * Device::UI_SIZE, KVector(30, 9) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(30, 1) * Device::UI_SIZE, KVector(34, 2) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(30, 5) * Device::UI_SIZE, KVector(34, 6) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(34, 2) * Device::UI_SIZE, KVector(35, 5) * Device::UI_SIZE), aColor);
    // O
    mDevice.UI().mScreen.drawRect(KRect(KVector(39, 1) * Device::UI_SIZE, KVector(43, 2) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(39, 8) * Device::UI_SIZE, KVector(43, 9) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(38, 2) * Device::UI_SIZE, KVector(39, 8) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(43, 2) * Device::UI_SIZE, KVector(44, 8) * Device::UI_SIZE), aColor);
    // S
    mDevice.UI().mScreen.drawRect(KRect(KVector(48, 1) * Device::UI_SIZE, KVector(52, 2) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(48, 8) * Device::UI_SIZE, KVector(52, 9) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(47, 2) * Device::UI_SIZE, KVector(48, 4) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(52, 2) * Device::UI_SIZE, KVector(53, 3) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(48, 4) * Device::UI_SIZE, KVector(50, 5) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(50, 5) * Device::UI_SIZE, KVector(52, 6) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(52, 6) * Device::UI_SIZE, KVector(53, 8) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(47, 7) * Device::UI_SIZE, KVector(48, 8) * Device::UI_SIZE), aColor);
    // E
    mDevice.UI().mScreen.drawRect(KRect(KVector(56, 2) * Device::UI_SIZE, KVector(57, 9) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(57, 2) * Device::UI_SIZE, KVector(62, 3) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(57, 5) * Device::UI_SIZE, KVector(62, 6) * Device::UI_SIZE), aColor);
    mDevice.UI().mScreen.drawRect(KRect(KVector(57, 8) * Device::UI_SIZE, KVector(62, 9) * Device::UI_SIZE), aColor);
}

void GameManager::update_play() {
    static const KVector MOVE_W(0.00, 0.00, -1.0);
    static const KVector MOVE_A(-1.0, 0.00, 0.00);
    static const KVector MOVE_S(0.00, 0.00, 1.00);
    static const KVector MOVE_D(1.00, 0.00, 0.00);

    // 視点移動
    if (mInputManager.mFaceUD || mInputManager.mFaceLR) mEyeCamera.rotate(-mInputManager.mFaceUD, mInputManager.mFaceLR);
    mHandLight.mPosition = mEyeCamera.mPosition;
    mHandLight.mDirection = mEyeCamera.mDirection;
    mHandLight.at();

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
        mCommandManager.add(Command(*this, "つぎのフロアに移動しますか?", COMMAND_TEXT_YES_NO, Vector<CommandFunction>{newFloar, stairCancel}));
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

