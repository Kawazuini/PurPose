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
    void keyProcessing();
    
    /** @brief 描画処理 */ void draw() override;

    void turnStart(const int& aTurn);
    bool checkTurnEnd();
};

#endif /* TERUTERUCHAN_H */
