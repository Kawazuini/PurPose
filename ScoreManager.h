/**
 * @file   ScoreManager.h
 * @brief  ScoreManager
 * @author Maeda Takumi
 */
#ifndef SCOREMANAGER_H
#define SCOREMANAGER_H

#include "GameState.h"

/**
 * @brief  \~english  management of game score
 * @brief  \~japanese ゲームスコア管理
 * @author \~ Maeda Takumi
 */
class ScoreManager final {
private:
    /* ランキングファイル名 */ static const String RANK_FILE_NAME;
    /* ランキングファイル  */ KFile mFile;

    /* 得点情報 */
    struct Score {
        /* 得点 */ int mScore;
        /* 名前 */ String mName;
        /* 詳細 */ String mBrief;
    };

    /* スコアランキング */ Vector<Score> mRanking;
public:
    ScoreManager();
    ~ScoreManager() = default;

    /**
     * \~english
     * @brief draw score.
     * @param aUI   drawing target
     * @param aRank rank information
     * \~japanese
     * @brief 得点を描画します。
     * @param aUI   描画対象
     * @param aRank 順位情報
     */
    void draw(KGLUI& aUI,const int& aRank) const;

    /**
     * \~english
     * @brief  add new score
     * @param  aState game state
     * @param  aClear clear flag
     * @return score rank
     * \~japanese
     * @brief  新しいスコアを追加します。
     * @param  aState ゲーム状態
     * @param  aClear クリアフラグ
     * @return 順位
     */
    int newScore(const GameState& aState, const bool& aClear = false);

    /**
     * \~english
     * @brief  calc score
     * @param  aState game state
     * @return score
     * \~japanese
     * @brief  スコアを計算します。
     * @param  aState ゲーム状態
     * @return スコア
     */
    static int calcScore(const GameState& aState);
};

#endif /* SCOREMANAGER_H */

