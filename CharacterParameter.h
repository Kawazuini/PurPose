/**
 * @file   CharacterParameter.h
 * @brief  CharacterParameter
 * @author Maeda Takumi
 */
#ifndef CHARACTERPARAMETER_H
#define CHARACTERPARAMETER_H

#include "AI.h"

/**
 * @brief  \~english  Parameter of Character
 * @brief  \~japanese キャラクターパラメータ
 * @author \~ Maeda Takumi
 */
class CharacterParameter final {
private:

    /* リソース内インデックス */
    enum CharacterIndex {
        CHARACTER_INDEX_NAME,
        CHARACTER_INDEX_SIZE,
        CHARACTER_INDEX_AI,
        CHARACTER_INDEX_EXP,
        CHARACTER_INDEX_GROW,
        CHARACTER_INDEX_MHP,
        CHARACTER_INDEX_STR,
        CHARACTER_INDEX_PER,
        CHARACTER_INDEX_AGI,
        CHARACTER_INDEX_ATTACKREACH,
        CHARACTER_INDEX_ATTACK_COST,
        CHARACTER_INDEX_INCREASE_MHP,
        CHARACTER_INDEX_INCREASE_STR,
        CHARACTER_INDEX_TEXTURE,
    };
public:
    /**
     * @brief \~english  parameter table
     * @brief \~japanese パラメータテーブル
     */
    Vector<String> mParameterTable;

    /**
     * @brief \~english  whether dead
     * @brief \~japanese 死んでいるか
     */
    bool mDead;

    int mID; ///< ID
    /**
     * @brief \~english  Character name
     * @brief \~japanese キャラクター名
     */
    String mName;
    /**
     * @brief \~english  Character size
     * @brief \~japanese キャラクターサイズ
     */
    float mSize;

    AI mAI; ///< AI

    /**
     * @brief \~english  level
     * @brief \~japanese レベル
     */
    int mLevel;
    /**
     * @brief \~english  sum of experience value acquired
     * @brief \~japanese 合計取得経験値
     */
    int mExperience;
    /**
     * @brief \~english  required experience value for level up
     * @brief \~japanese レベルアップに必要な経験値
     */
    Vector<int> mRequireExperience;

    /**
     * @brief \~english  Max Hit Points
     * @brief \~japanese 最大体力
     */
    int mMHP;
    /**
     * @brief \~english  Hit Points
     * @brief \~japanese 体力
     */
    int mHP;

    /**
     * @brief \~english  max value of stamina
     * @brief \~japanese スタミナの最大値
     */
    int mMaxStamina;
    /**
     * @brief \~english  stamina
     * @brief \~japanese スタミナ
     */
    int mStamina;

    /**
     * @brief \~english  strength
     * @brief \~japanese 力
     */
    int mSTR;
    /**
     * @brief \~english  perception
     * @brief \~japanese 知覚
     */
    int mPER;
    /**
     * @brief \~english  moving speed
     * @brief \~japanese 移動速度
     */
    float mAGI;

    /**
     * @brief \~english  Attack range
     * @brief \~japanese 攻撃範囲
     */
    float mAttackRange;


    /**
     * @brief \~english  attack cost
     * @brief \~japanese 攻撃にかかるコスト
     */
    int mAttackCost;

    /**
     * @brief \~english  increase value of MHP when level up
     * @brief \~japanese レベルアップ時のHPの上昇値
     */
    int mIncreaseMHP;
    /**
     * @brief \~english  increase value of STR when level up
     * @brief \~japanese レベルアップ時の力の上昇値
     */
    int mIncreaseSTR;

    /**
     * @brief \~english  texture number
     * @brief \~japanese テクスチャ番号
     */
    int mTextureNumber;

    /**
     * \~english  @param aID resource ID
     * \~japanese @param aID リソースID
     */
    CharacterParameter(const int& aID);
    ~CharacterParameter() = default;

    /**
     * \~english
     * @brief  compute throw power.
     * @return throw power
     * \~japanese
     * @brief  投擲力を計算します。
     * @return 投擲力
     */
    float throwPower() const;
};

#endif /* CHARACTERPARAMETER_H */

