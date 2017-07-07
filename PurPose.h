/**
 * @file   PurPose.h
 * @brief  PurPose
 * @author Maeda Takumi
 */
#ifndef PurPose_H
#define PurPose_H

#include "main.h"

#include "GameManager.h"

/**
 * @brief  \~english  game class
 * @brief  \~japanese ゲームクラス
 * @author \~ Maeda Takumi
 */
class PurPose final : public KApplication {
private:
    /* 振り向き入力 */ KVector mFace;
    /* 選択入力     */ int mSelect;
    /* 入力管理     */ const InputManager mInput;
    /* ゲーム管理   */ GameManager mGameManager;
public:
    /**
     * @param aWindow
     * \~english  drawing target
     * \~japanese 描画対象
     */
    PurPose(KWindow& aWindow);
    ~PurPose() = default;

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
     * @brief \~english  reset all geme state.
     * @brief \~japanese ゲーム状態をリセットします。
     */
    void reset();

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
};

#endif /* TERUTERUCHAN_H */

