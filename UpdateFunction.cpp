/**
 * @file   UpdateFunction.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Command.h"
#include "Enemy.h"
#include "Special.h"
#include "Stair.h"

void GameManager::update_start() {
    static const int PULSE(192); // 枠が満ちる周期

    const KRect & area(mDevice.UI().area());

    // にゅにゅっと差分
    float xDiff((float) area.width / PULSE), yDiff((float) area.height / PULSE);

    static const color WHITE(0xffffffff);

    KTexture & screen(mDevice.screen());

    if (mFrameCount <= PULSE * 2) mFrameCount++;
    if (mFrameCount <= PULSE * 2) screen.clearRect(area);

    if (mFrameCount <= PULSE) { // にゅにゅっと伸ばす
        for (int i = 1; i < 64; ++i) { // 上下ににゅにゅっと
            if (i % 2) screen.drawVLine(0, mFrameCount * yDiff, Device::UI_SIZE * i, WHITE);
            else screen.drawVLine(area.height, area.height - mFrameCount * yDiff, Device::UI_SIZE * i, WHITE);
        }
        for (int i = 1; i < 40; ++i) { // 左右ににゅにゅっと
            if (i % 2) screen.drawHLine(0, mFrameCount * xDiff, Device::UI_SIZE * i, WHITE);
            else screen.drawHLine(area.width, area.width - mFrameCount * xDiff, Device::UI_SIZE * i, WHITE);
        }
    } else if (mFrameCount <= PULSE * 2) { // にゅにゅっと縮める
        int fc(mFrameCount - PULSE);
        for (int i = 1; i < 64; ++i) { // 上下ににゅにゅっと
            if (i % 2) screen.drawVLine(fc * yDiff, area.height, Device::UI_SIZE * i, WHITE);
            else screen.drawVLine(area.height - fc * yDiff, 0, Device::UI_SIZE * i, WHITE);
        }
        for (int i = 1; i < 40; ++i) { // 左右ににゅにゅっと
            if (i % 2) screen.drawHLine(fc * xDiff + 1, area.width, Device::UI_SIZE * i, WHITE);
            else screen.drawHLine(area.width - fc * xDiff, 0, Device::UI_SIZE * i, WHITE);
        }

        // だんだん濃くなる
        color drawColor((int) ((double) fc / PULSE * 255) << 24 | 0x00ffffff);
        drawTitle(drawColor);

        static const String TXT_START("---左クリックでSTART---");
        static const int WIDTH_START(CHARSET.getWidth(TXT_START) / 2);
        static const String TXT_RELEASE("~~~ESCでマウスのロックを解除~~~");
        static const int WIDTH_RELEASE(CHARSET_SMALL.getWidth(TXT_RELEASE) / 2);
        screen.drawText(CHARSET, TXT_START, KVector(area.centerX() - WIDTH_START, area.centerY() + CHARSET.mSize * 2), drawColor);
        screen.drawText(CHARSET_SMALL, TXT_RELEASE, KVector(area.centerX() - WIDTH_RELEASE, area.centerY() + CHARSET.mSize * 5), drawColor);
    }

    // ゲーム開始
    if (!mInputManager.isAnyKeyPressed()) {
        mKeyFrag = true;
    } else if (mKeyFrag) {
        mFrameCount = 0;
        mKeyFrag = false;
        screen.clearRect(area);
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
        mGameState.mBulletin.write("R                : リロード/アイテム画面でのソート");
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
    KTexture & screen(mDevice.screen());
    // P
    screen.drawRect(KRect(KVector(2, 1) * Device::UI_SIZE, KVector(3, 9) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(3, 1) * Device::UI_SIZE, KVector(7, 2) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(3, 5) * Device::UI_SIZE, KVector(7, 6) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(7, 2) * Device::UI_SIZE, KVector(8, 5) * Device::UI_SIZE), aColor);
    // U
    screen.drawRect(KRect(KVector(11, 2) * Device::UI_SIZE, KVector(12, 8) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(16, 2) * Device::UI_SIZE, KVector(17, 8) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(12, 8) * Device::UI_SIZE, KVector(16, 9) * Device::UI_SIZE), aColor);
    // R
    screen.drawRect(KRect(KVector(20, 1) * Device::UI_SIZE, KVector(21, 9) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(21, 1) * Device::UI_SIZE, KVector(25, 2) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(21, 5) * Device::UI_SIZE, KVector(25, 6) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(25, 2) * Device::UI_SIZE, KVector(26, 5) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(23, 6) * Device::UI_SIZE, KVector(24, 7) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(24, 7) * Device::UI_SIZE, KVector(25, 8) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(25, 8) * Device::UI_SIZE, KVector(26, 9) * Device::UI_SIZE), aColor);
    // P
    screen.drawRect(KRect(KVector(29, 1) * Device::UI_SIZE, KVector(30, 9) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(30, 1) * Device::UI_SIZE, KVector(34, 2) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(30, 5) * Device::UI_SIZE, KVector(34, 6) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(34, 2) * Device::UI_SIZE, KVector(35, 5) * Device::UI_SIZE), aColor);
    // O
    screen.drawRect(KRect(KVector(39, 1) * Device::UI_SIZE, KVector(43, 2) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(39, 8) * Device::UI_SIZE, KVector(43, 9) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(38, 2) * Device::UI_SIZE, KVector(39, 8) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(43, 2) * Device::UI_SIZE, KVector(44, 8) * Device::UI_SIZE), aColor);
    // S
    screen.drawRect(KRect(KVector(48, 1) * Device::UI_SIZE, KVector(52, 2) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(48, 8) * Device::UI_SIZE, KVector(52, 9) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(47, 2) * Device::UI_SIZE, KVector(48, 4) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(52, 2) * Device::UI_SIZE, KVector(53, 3) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(48, 4) * Device::UI_SIZE, KVector(50, 5) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(50, 5) * Device::UI_SIZE, KVector(52, 6) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(52, 6) * Device::UI_SIZE, KVector(53, 8) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(47, 7) * Device::UI_SIZE, KVector(48, 8) * Device::UI_SIZE), aColor);
    // E
    screen.drawRect(KRect(KVector(56, 2) * Device::UI_SIZE, KVector(57, 9) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(57, 2) * Device::UI_SIZE, KVector(62, 3) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(57, 5) * Device::UI_SIZE, KVector(62, 6) * Device::UI_SIZE), aColor);
    screen.drawRect(KRect(KVector(57, 8) * Device::UI_SIZE, KVector(62, 9) * Device::UI_SIZE), aColor);
}

void GameManager::update_play() {
    static const KVector MOVE_W(0.00f, 0.00f, -1.0f);
    static const KVector MOVE_A(-1.0f, 0.00f, 0.00f);
    static const KVector MOVE_S(0.00f, 0.00f, 1.00f);
    static const KVector MOVE_D(1.00f, 0.00f, 0.00f);

    // 視点移動
    if (mInputManager.mFaceUD || mInputManager.mFaceLR) mGameState.mCamera.rotate(-mInputManager.mFaceUD, mInputManager.mFaceLR);

    if (mInputManager.mInventory.isTouch()) {
        mInventory = !mInventory; // アイテム画面の切り替え

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
            mCommandManager.pop();
            mDevice.refresh(mGameState);
            mCommandWait = mCommandManager.size();
        }
        return;
    }

    mGameState.mBulletin.mDraw = !mInventory;

    if (mInventory) { // インベントリ状態
        mDevice.drawBackPack(mGameState.mPlayer.backPack());
        // ターン終了でインベントリを閉じる
        if (!mGameState.mPlayer.turn()) {
            mInventory = false;
            mDevice.refresh(mGameState);
        }
        // アイテムの選択・アイテムコマンドの生成・アイテムのソート
        mGameState.mPlayer.fumble(mInputManager.mSelect);
        if (mInputManager.mDecision.isTouch()) makeItemCommand();
        if (mInputManager.mReload.isTouch()) mGameState.mPlayer.sortItem();
        return;
    }


    // ログ表示
    if (mInputManager.mLogView.onFrame()) {
        mGameState.mBulletin.mDrawLog = true;
    } else if (mInputManager.mLogView.offFrame() == 0) {
        mDevice.refresh(mGameState);
    }

    // ターンチェンジ(物理演算が行われていないとき)
    if (!mGameState.mPhysical && checkTurnEnd()) {
        switch (mTurn) {
            case PLAYER: turnStart(ENEMY);
                break;
            case ENEMY: turnStart(PLAYER);
                break;
        }
    }

    { // プレイヤー更新
        // 移動・待機
        KVector move;
        if (mInputManager.mGoFront.isTouch() || mInputManager.mGoFront.onFrame() > 10) move += MOVE_W;
        if (mInputManager.mGoBack.isTouch() || mInputManager.mGoBack.onFrame() > 10) move += MOVE_S;
        if (mInputManager.mGoLeft.isTouch() || mInputManager.mGoLeft.onFrame() > 10) move += MOVE_A;
        if (mInputManager.mGoRight.isTouch() || mInputManager.mGoRight.onFrame() > 10) move += MOVE_D;
        if (!move.isZero()) mGameState.mPlayer.move(mGameState, mGameState.mCamera.convertDirection(move));
        if (mInputManager.mWait.isTouch() || mInputManager.mWait.onFrame() > 50) mGameState.mPlayer.wait();
        // 武器装備の変更
        mGameState.mPlayer.weaponFumble(mInputManager.mSelect);
        // 武器構え・攻撃・リロード
        if (mInputManager.mHold.onFrame()) {
            mGameState.mPlayer.arm();
            mCamera.zoom(0.5f);
        } else {
            mGameState.mPlayer.disarm();
            mCamera.zoom(1.0f);
        }
        if (mInputManager.mAttack.isTouch()) mGameState.mPlayer.attack(mGameState);
        if (mInputManager.mReload.isTouch()) mGameState.mPlayer.reload(mGameState);
    }

    // イベントの再有効化(イベントが無効で発生条件を満たしていないとき)
    if (!mGameState.mStage.stair().isActive() && !mGameState.mStage.stair().condition(mGameState)) {
        mGameState.mStage.stair().enable();
    }

    // オブジェクト更新
    mGameState.mPhysical = false;
    Object::UPDATE(mGameState);
    Special::invocation(mGameState);

    // 敵の死
    List<Enemy*> enemies(mGameState.enemyList()); // リスト保護
    for (Enemy* i : enemies) {
        if (i->mCharacterParameter.mDead) {
            mGameState.removeEnemy(*i);
            delete i;
        }
    }

    // ゲームオーバー
    if (mGameState.mPlayer.mCharacterParameter.mDead) mScene = SCENE_OVER;
}

void GameManager::update_over() {
    static const color TXT_COLOR(0x77d003a);

    static const String OVER_TEXT("!!GAME OVER!!");
    static const KVector TEXT_WIDTH(CHARSET.getWidth(OVER_TEXT));

    if (mFrameCount == 0) mRanking = mScoreManager.newScore(mGameState); // 初期フレームで記録

    // 死因
    String name(mGameState.mPlayer.mCharacterParameter.mName + "は");
    KVector nameWidth(CHARSET.getWidth(name) / 2);
    String cause(
            "B" + toString(mGameState.mFloorNumber) + "Fで" +
            mGameState.mPlayer.mWhoKilleMe->mCharacterParameter.mName + "に" +
            "倒された!!"
            );
    KVector causeWidth(CHARSET.getWidth(cause) / 2);
    // スコア
    String score("Score : " + toString(ScoreManager::calcScore(mGameState)));
    KVector scoreWidth(CHARSET_LARGE.getWidth(score) / 2);

    KTexture & screen(mDevice.screen());
    screen.drawText(CHARSET_LARGE, OVER_TEXT, KVector(32, 1) * Device::UI_SIZE - TEXT_WIDTH, TXT_COLOR);
    screen.drawText(CHARSET, name, KVector(32, 6) * Device::UI_SIZE - nameWidth, TXT_COLOR);
    screen.drawText(CHARSET, cause, KVector(32, 8) * Device::UI_SIZE - causeWidth, TXT_COLOR);
    screen.drawText(CHARSET_LARGE, score, KVector(32, 11) * Device::UI_SIZE - scoreWidth, TXT_COLOR);
    mScoreManager.draw(mDevice.UI(), mRanking);

    if (mFrameCount < 1.0_s) ++mFrameCount;

    if (!mInputManager.isAnyKeyPressed() && mFrameCount > 0.5_s) {
        mKeyFrag = true;
    } else if (mKeyFrag) {
        reset();
        mFrameCount = 0;
        mKeyFrag = false;
    }
}

void GameManager::update_ending() {
    static const color TXT_COLOR(0x77d003a);

    static const String GAME_TEXT("!!GAME CLEAR!!");
    static const KVector TEXT_WIDTH(CHARSET.getWidth(GAME_TEXT));

    if (mFrameCount == 0) mRanking = mScoreManager.newScore(mGameState, true); // 初期フレームで記録

    String score("Score : " + toString(ScoreManager::calcScore(mGameState)));
    KVector scoreWidth(CHARSET_LARGE.getWidth(score) / 2);

    KTexture & screen(mDevice.screen());
    screen.drawText(CHARSET_LARGE, GAME_TEXT, KVector(32, 6) * Device::UI_SIZE - TEXT_WIDTH, TXT_COLOR);
    screen.drawText(CHARSET_LARGE, score, KVector(32, 11) * Device::UI_SIZE - scoreWidth, TXT_COLOR);
    mScoreManager.draw(mDevice.UI(), mRanking);

    if (mFrameCount < 1.0_s) ++mFrameCount;

    if (!mInputManager.isAnyKeyPressed() && mFrameCount > 0.5_s) {
        mKeyFrag = true;
    } else if (mKeyFrag) {
        reset();
        mFrameCount = 0;
        mKeyFrag = false;
    }
}

