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

/**
 * @brief  \~english  game management system
 * @brief  \~japanese ゲーム管理システム
 * @author \~ Maeda Takumi
 */
class GameManager : public KDrawer, public KUpdater {
private:
    static const List<String> COMMAND_TEXT_YES_NO;

    static const int SPAWN_ENEMY_MAX;
    static const int SPAWN_ENEMY_KIND_MAX;
    static const int SPAWN_ITEM_MAX;
    static const int SPAWN_ITEM_KIND_MAX;
    static const Vector<int> ITEM_KINDS;

    struct EnemySpawnData {
        int mSpawnID;
        int mSpawnPercent;
    };
    Vector<EnemySpawnData> mEnemySpawnTable;

    struct ItemSpawnData {
        ItemType mSpawnType;
        int mSpawnPercent;
    };
    Vector<ItemSpawnData> mItemSpawnTable;

    /**
     * @brief \~english  state of game
     * @brief \~japanese ゲーム状態
     */
    GameState mGameState;

    /**
     * @brief \~english  whether open inventory
     * @brief \~japanese アイテム画面を開いているか
     */
    bool mInventory;

    Device mDevice; ///< UI

    /**
     * @brief \~english  drawing processing function
     * @brief \~japanese 描画処理関数
     */
    using DrawFunction = void (GameManager::*)() const;
    /**
     * @brief \~english  update processing function
     * @brief \~japanese 更新処理関数
     */
    using UpdateFunction = void (GameManager::*)();

    /**
     * @brief \~english  game scene
     * @brief \~japanese ゲームシーン
     */
    enum Scene {
        SCENE_START,
        SCENE_PLAY,
        SCENE_OVER,
        SCENE_ENDING,
    } mScene;

    DrawFunction mDrawFunc[4];
    UpdateFunction mUpdateFunc[4];

    void draw_start() const;
    void draw_play() const;
    void draw_over() const;
    void draw_ending() const;
    void update_start();
    void drawTitle(const color& aColor);
    void update_play();
    void update_over();
    void update_ending();

    /**
     * @brief \~english  turn sysytem
     * @brief \~japanese ターンシステム
     */
    enum Turn {
        PLAYER,
        ENEMY,
    } mTurn;
    /**
     * @brief \~english  turn count
     * @brief \~japanese ターンカウント
     */
    int mTurnCount;

    /**
     * @brief \~english  period of spawning enemy
     * @brief \~japanese 敵発生周期
     */
    int mSpawnPeriod;

    /**
     * @brief \~english  whether waiting for command
     * @brief \~japanese コマンドウェイト状態
     */
    bool mCommandWait;
    /**
     * @brief \~english  command management system
     * @brief \~japanese コマンド管理システム
     */
    CommandManager mCommandManager;
public:
    /**
     * @brief \~english  command processing function
     * @brief \~japanese コマンド処理関数
     */
    using CommandFunction = void (GameManager::*)();

    InputManager mInputManager;

    GameManager(const InputManager& aInputManager);
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
};

#endif /* GAMEMANAGER_H */

