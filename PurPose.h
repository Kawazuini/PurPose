/**
 * @file   PurPose.h
 * @brief  PurPose
 * @author Maeda Takumi
 */
#ifndef PurPose_H
#define PurPose_H

#include "main.h"

#include "GameManager.h"

class Item;

/**
 * @brief  \~english  game class
 * @brief  \~japanese ゲームクラス
 * @author \~ Maeda Takumi
 */
class PurPose : public KApplication {
private:

    /***/
    GameManager mGM;
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
};

#endif /* TERUTERUCHAN_H */

