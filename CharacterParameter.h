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
class CharacterParameter {
private:
    // 配列初期化インデックス
    static const int PARAMETER_INDEX_NAME;
    static const int PARAMETER_INDEX_SIZE;
    static const int PARAMETER_INDEX_AI;
    static const int PARAMETER_INDEX_LEVEL;
    static const int PARAMETER_INDEX_EXP;
    static const int PARAMETER_INDEX_REQUIREDEXP;
    static const int PARAMETER_INDEX_MHP;
    static const int PARAMETER_INDEX_AGI;
    static const int PARAMETER_INDEX_ATTACKREACH;
    static const int PARAMETER_INDEX_STR;
public:
    /**
     * @brief \~english  parameter table(able to manage additional information)
     * @brief \~japanese パラメータテーブル(追加情報を管理できます。)
     */
    Vector<String> mParameterTable;

    /**
     * @brief \~english  whether dead
     * @brief \~japanese 死んでいるか
     */
    bool mDead;

    int mID; ///< ID
    /**
     * @brief \~english  name of Character
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
     * @brief \~japanese 取得経験値合計
     */
    int mExperience;
    /**
     * @brief \~english  required experience value for level up
     * @brief \~japanese レベルアップに必要な経験値
     */
    int mRequireExperience;

    /**
     * @brief \~english  Max Hit Points
     * @brief \~japanese 最大体力
     */
    int mMHP;
    /**
     * @brief \~english  Hit Points
     * @briev \~japanese 体力
     */
    int mHP;

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
     * @brief \~english  strength
     * @brief \~japanese 力
     */
    int mSTR;

    CharacterParameter();
    CharacterParameter(const int& aID);
    CharacterParameter(const int& aID, const Vector<String>& aParameter);

    virtual ~CharacterParameter() = default;

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
