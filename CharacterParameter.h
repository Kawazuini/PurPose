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

    enum CharacterIndex {
        CHARACTER_INDEX_NAME,
        CHARACTER_INDEX_SIZE,
        CHARACTER_INDEX_AI,
        CHARACTER_INDEX_LEVEL,
        CHARACTER_INDEX_EXP,
        CHARACTER_INDEX_REQUIREDEXP,
        CHARACTER_INDEX_MHP,
        CHARACTER_INDEX_AGI,
        CHARACTER_INDEX_ATTACKREACH,
        CHARACTER_INDEX_STR,
        CHARACTER_INDEX_ATTACK_COST,
    };
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
     * @brief \~japanese 体力
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

    /**
     * @brief \~english  attack cost
     * @brief \~japanese 攻撃にかかるコスト
     */
    int mAttackCost;

    /**
     * \~english
     * @brief generate parameters from resource ID.
     * @param aID resource ID
     * \~japanese
     * @brief リソースIDからパラメータを生成します。
     * @param aID リソースID
     */
    CharacterParameter(const int& aID);
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

