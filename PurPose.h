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
    /// @param \~english  aWindow drawing target
    /// @param \~japanese aWindow 描画対象
    PurPose(KWindow& aWindow);
    ~PurPose() = default;

    void draw() const override;
    void update() override;

    /// @brief \~english  reset all geme state.
    /// @brief \~japanese ゲーム状態をリセットします。
    void reset();

    /// @brief \~english  key processing
    /// @brief \~japanese キー処理
    void keyProcess();
    /// @brief \~english  mouse processing
    /// @brief \~japanese マウス処理
    void mouseProcess();
};

#endif /* TERUTERUCHAN_H */

