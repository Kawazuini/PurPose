/**
 * @file   PurPose.h
 * @brief  PurPose
 * @author Maeda Takumi
 */
#ifndef PurPose_H
#define PurPose_H

#include "main.h"

class Hero;
class Map;

/**
 * @brief \~english  game class
 * @brief \~japanese ゲームクラス
 * @author \~ Maeda Takumi
 */
class PurPose : public KApplication {
private:

    /**
     * @brief \~english  game scene
     * @brief \~japanese ゲームシーン
     */
    typedef enum {
        GAME_PLAY,
        GAME_OVER,
        START,
        ENDING,
    } Scene;
    /**
     * @brief \~english  current Scene
     * @brief \~japanese 現在のシーン
     */
    Scene mScene;

    /**
     * @brief \~english  turn sysytem
     * @brief \~japanese ターンシステム
     */
    typedef enum {
        PLAYER,
        ENEMY,
    } Turn;
    /**
     * @brief \~english  current turn
     * @brief \~japanese 現在のターン
     */
    Turn mTurn;
    /**
     * @brief \~english  turn count
     * @brief \~japanese ターンカウント
     */
    int mTurnCount;

    /**
     * @brief \~english  playable Character
     * @brief \~japanese プレイアブルキャラクター
     */
    Hero* mPlayer;
    /**
     * @brief \~english  current Map
     * @brief \~japanese 現在のマップ
     */
    Map* mMap;

    /**
     * @brief \~english  period of spawning enemy
     * @brief \~japanese 敵発生周期
     */
    int mSpawnPeriod;
public:
    PurPose(KWindow* aWindow);
    virtual ~PurPose();

    /**
     * @brief \~english  reset all geme state.
     * @brief \~japanese ゲーム状態を初期化します。
     */
    void reset();

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    void update() override;
    /**
     * @brief \~english  key processing
     * @brief \~japanese キー処理
     */
    void keyProcess();
    /**
     * @brief \~english  mouse processing
     * @brief \~japanese マウス処理
     */
    void mouseProcess();

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() override;

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
    bool checkTurnOver();

    /**
     * @brief \~english  generate new Map
     * @brief \~japanese 新しいフロアを生成します
     */
    void newFloar();

    /**
     * @brief \~english  spawn new Enemy.
     * @brief \~japanese 敵を発生させます。
     */
    void spawnEnemy();
};

#endif /* TERUTERUCHAN_H */

