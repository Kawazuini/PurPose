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

class PurPose : public KApplication {
private:
    /**
     * @brief \~english  scene of play
     * @brief \~japanese プレイシーン
     */
    static const int SCENE_GAME_PLAY;
    /**
     * @brief \~english  scene of game over
     * @brief \~japanese ゲームオーバーシーン
     */
    static const int SCENE_GAME_OVER;
    /**
     * @brief \~english  scene of start
     * @brief \~japanese スタートシーン
     */
    static const int SCENE_START;
    /**
     * @brief \~english  scene of ending
     * @brief \~japanese エンディングシーン
     */
    static const int SCENE_ENDING;

    int mScene;

    /** @brief プレイヤーターン */ static const int PLAYER_TURN;
    /** @brief 敵ターン         */ static const int ENEMY_TURN;

    int mTurn;

    Hero* mPlayer;
    Map* mMap;

    bool mMenu;

public:
    PurPose(KWindow* aWindow);
    virtual ~PurPose();

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

    /** @brief 描画処理 */ void draw() override;

    void turnStart(const int& aTurn);
    bool checkTurnEnd();
};

#endif /* TERUTERUCHAN_H */
