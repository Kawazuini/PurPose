/**
 * @file   GameManager.h
 * @brief  GameManager
 * @author Maeda Takumi
 */
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "CommandManager.h"
#include "Device.h"
#include "GameState.h"
#include "InputManager.h"
#include "ItemType.h"
#include "ScoreManager.h"

/**
 * @brief  \~english  game management system
 * @brief  \~japanese ゲーム管理システム
 * @author \~ Maeda Takumi
 */
class GameManager final : public KDrawer, public KUpdater {
    friend class PurPose;
private:
    /* 1F毎の最大敵生成数       */ static const int SPAWN_ENEMY_MAX;
    /* 1F毎の最大アイテム生成数 */ static const int SPAWN_ITEM_MAX;
    /* 1F毎の最大お金生成数     */ static const int SPAWN_MONEY_MAX;

    KCamera& mCamera;
    /* ゲーム状態           */ GameState mGameState;
    /* UI                   */ Device mDevice;
    /* コマンド管理システム */ CommandManager mCommandManager;
    /* スコア管理システム   */ ScoreManager mScoreManager;

    /* 生成情報 */
    struct SpawnData {
        /* レベル   */ int mLevel;
        /* ID       */ int mSpawnID;
        /* 生成確率 */ int mSpawnPercent;
    };
    /* 敵生成テーブル       */ Vector<SpawnData> mEnemySpawnTable;
    /* アイテム生成テーブル */ Vector<SpawnData> mItemSpawnTable;

    /* ゲームシーン */
    enum Scene {
        /* 開始           */ SCENE_START,
        /* プレイ         */ SCENE_PLAY,
        /* ゲームオーバー */ SCENE_OVER,
        /* エンディング   */ SCENE_ENDING,
    } mScene;

    /* ターン */
    enum Turn {
        /* プレイヤーのターン */ PLAYER,
        /* 敵のターン         */ ENEMY,
    } mTurn;

    /* 描画処理関数   */ using DrawFunction = void (GameManager::*)() const;
    /* 描画処理関数群 */ DrawFunction mDrawFunc[4];
    /* ----- 描画関数 ----- */
    void draw_start() const;
    void draw_play() const;
    void draw_over() const;
    void draw_ending() const;

    /* 更新処理関数   */ using UpdateFunction = void (GameManager::*)();
    /* 更新処理関数群 */ UpdateFunction mUpdateFunc[4];
    /* ----- 更新関数 ----- */
    void update_start();
    void drawTitle(const color& aColor);
    void update_play();
    void update_over();
    void update_ending();

    /* フレームカウント */ int mFrameCount;
    /* キーフラグ       */ bool mKeyFrag;
    /* ランキング(リザルト時に使用) */
    int mRanking;

    /* ターンカウント */ int mTurnCount;
    /* 敵発生周期     */ int mSpawnPeriod;

    /* アイテム画面状態     */ bool mInventory;
    /* コマンドウェイト状態 */ bool mCommandWait;
public:
    /** @brief InputManager */
    InputManager mInputManager;

    /**
     * @param aWindow       window for drawing
     * @param aInputManager input manager
     */
    GameManager(
            KCamera& aCamera,
            KGLUI& aUI,
            const InputManager& aInputManager
            );
    virtual ~GameManager();

    /**
     * @brief \~english  reset all geme state.
     * @brief \~japanese ゲーム状態を初期化します。
     */
    void reset();

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;
    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    void update() override;

    /**
     * \~english
     * @brief start new Turn.
     * @param aTurn new Turn
     * \~japanese
     * @brief 新しくターンを開始します。
     * @param aTurn 新しいターン
     */
    void turnStart(const Turn& aTurn);
    /**
     * \~english
     * @brief  check current turn is over.
     * @return whether Turn over
     * \~japanese
     * @brief  現在のターンが終了しているかを確認します。
     * @return ターンが終了しているか
     */
    bool checkTurnEnd() const;

    /**
     * @brief \~english  spawn new Enemy.
     * @brief \~japanese 敵を発生させます。
     */
    void spawnEnemy();

    /**
     * @brief \~english  make Item command.
     * @brief \~japanese アイテムコマンドを作成します。
     */
    void makeItemCommand();

    /**
     * @breif  get device.
     * @return device
     */
    const Device& device() const;

    /* ------------------------- in CommandFnction.cpp ------------------------- */

    /**
     * @brief \~english  do nothing.
     * @brief \~japanese なにもしません。
     */
    void cancel() {
    };

    /**
     * @brief \~english  generate new Stage.
     * @brief \~japanese 新しいフロアを生成します。
     */
    void newFloor();
    /**
     * @brief \~english  cancel stair processing.
     * @brief \~japanese 階段の処理をキャンセルします。
     */
    void stairCancel();

    /**
     * @brief \~english  player use Item.
     * @brief \~japanese アイテムを使用。
     */
    void useItem();
    /**
     * @brief \~english  player equip Item.
     * @brief \~japanese アイテムを装備。
     */
    void equipItem();
    /**
     * @brief \~english  player take off Item.
     * @brief \~japanese アイテムを装備から外す。
     */
    void takeoffItem();
    /**
     * @brief \~english  player throw Item.
     * @brief \~japanese アイテムを投擲。
     */
    void throwItem();
    /**
     * @brief \~english  player put Item.
     * @brief \~japanese アイテムを設置。
     */
    void putItem();
    /**
     * @brief \~english  player put Items.
     * @brief \~japanese アイテムを複数設置。
     */
    void putItems(const int& aNumber);

    /* ------------------------- in EventFnction.cpp ------------------------- */
    /**
     * @brief \~english  event process for stair
     * @brief \~japanese 階段のイベント処理
     */
    void stairEvent();
    /**
     * @brief \~english  event process for get money
     * @brief \~japanese お金取得イベント
     */
    void getMoneyEvent();
};

#endif /* GAMEMANAGER_H */

