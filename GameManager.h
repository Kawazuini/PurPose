/**
 * @file   GameManager.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "CommandManager.h"
#include "Device.h"
#include "GameState.h"

/**
 * @brief  \~english  management system of game
 * @brief  \~japanese ゲーム管理システム
 * @author \~ Maeda Takumi
 */
class GameManager : public KDrawer, public KUpdater {
private:
    KVector mMove;
    double mFumble;
    KVector mAngle;

    GameState mGameState;

    Device mDevice;

    /**
     * @brief \~english  game scene
     * @brief \~japanese ゲームシーン
     */
    enum Scene {
        GAME_PLAY,
        GAME_OVER,
        START,
        ENDING,
    } mScene;

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

    bool mCommandWait;

    CommandManager mCommandManager;
public:
    /**
     * @brief \~english  command processing function
     * @brief \~japanese コマンド処理関数
     */
    using CommandFunc = void (GameManager::*)();

    enum InputType {
        W, A, S, D, Q,
        WHEEL,
        LEFT,
        RIGHT,
        MIDDLE,
        POSITION_X,
        POSITION_Y,
    };

    GameManager();
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

    void input(const InputType& aInputType, const double& aValue = 0.0);

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

    /***/
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
    void newFloar();
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
     * @brief \~english  player throw Item.
     * @brief \~japanese アイテムを投擲。
     */
    void throwItem();
};

#endif /* GAMEMANAGER_H */

