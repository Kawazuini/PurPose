/**
 * @file   ScoreManager.cpp
 * @brief  ScoreManager
 * @author Maeda Takumi
 */
#include "ScoreManager.h"

#include "Device.h"

const String ScoreManager::RANK_FILE_NAME("Ranking.rank");

ScoreManager::ScoreManager() :
mFile(RANK_FILE_NAME) {
    for (String i : mFile.read(false)) {
        Vector<String> scoreInfo(split(i, "/"));
        Score sc{
            toInt(scoreInfo[0]),
            scoreInfo[1],
            scoreInfo[2]
        };
        mRanking.push_back(sc);
    }
}

void ScoreManager::draw(KGLUI& aUI, const int& aRank) const {
    static const int SIZE(CHARSET.mSize * 2);

    int rank(aRank - 1);
    for (int i = 0, i_e(Math::min((int) (mRanking.size()), 8)); i < i_e; ++i) {
        // ~8位まで描画
        aUI.screen().drawText(
                CHARSET,
                toString(i + 1) + ".   " +
                toString(mRanking[i].mScore) + "pt : " +
                mRanking[i].mName + "は" + mRanking[i].mBrief,
                KVector(2, 19) * Device::UI_SIZE + KVector(0, SIZE) * i,
                rank == i ? 0xffff0000 : 0xffffffff
                );
    }
}

int ScoreManager::newScore(const GameState& aState, const bool& aClear) {
    Score sc{
        calcScore(aState),
        aState.mPlayer.mCharacterParameter.mName,
        ""
    };
    if (aClear) sc.mBrief = "B" + toString(aState.mFloorNumber) + "Fのすべてをクリアした。";
    else sc.mBrief = "B" + toString(aState.mFloorNumber) + "Fで倒れた。";

    mRanking.push_back(sc);

    // スコア順に並び替える
    std::sort(mRanking.begin(), mRanking.end(),
            [](const Score& x, const Score & y) -> bool {
                return x.mScore > y.mScore;
            }
    );

    Vector<String> ranking;
    int count(0), rank(0);
    for (Score i : mRanking) {
        ranking.push_back(toString(i.mScore) + "/" + i.mName + "/" + i.mBrief);
        if (i.mScore == sc.mScore && i.mName == sc.mName && i.mBrief == sc.mBrief) rank = count + 1;
        if (30 < ++count) break; // 30位までしかランクを残さない
    }
    mFile.write(ranking);
    return rank;
}

int ScoreManager::calcScore(const GameState& aState) {
    return aState.mFloorNumber * 1000 + aState.mPlayer.backPack().weight() * 100 + aState.mPlayer.mCharacterParameter.mLevel;
}

