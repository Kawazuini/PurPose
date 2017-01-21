/**
 * @file   CharacterParameter.h
 * @brief  CharacterParameter
 * @author Maeda Takumi
 */
#ifndef CHARACTERPARAMETER_H
#define CHARACTERPARAMETER_H

#include "main.h"

/**
 * @brief  \~english  Parameter of Character
 * @brief  \~japanese キャラクターパラメータ
 * @author \~ Maeda Takumi
 */
class CharacterParameter {
public:
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

    CharacterParameter() :
    mDead(false) {
    };

    CharacterParameter(const int& aID) :
    CharacterParameter(aID, split(loadString(aID), _T(","))) {
    };

    CharacterParameter(const int& aID, const Vector<String>& aParameter) :
    mDead(false),
    mID(aID),
    mName(             aParameter[0]),
    mAI(               aParameter[1]),
    mLevel(            toInt(aParameter[2])),
    mExperience(       toInt(aParameter[3])),
    mRequireExperience(toInt(aParameter[4])),
    mMHP(              toInt(aParameter[5])),
    mHP(mMHP),
    mAGI(              toDouble(aParameter[6])),
    mAttackRange(      toDouble(aParameter[7])),
    mSTR(              toInt(aParameter[8])) {
    };

    virtual ~CharacterParameter() = default;
};

#endif /* CHARACTERPARAMETER_H */

