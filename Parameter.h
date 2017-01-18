/**
 * @file   Parameter.h
 * @brief  Prameter
 * @author Maeda Takumi
 */
#ifndef PARAMETER_H
#define PARAMETER_H

#include "main.h"

/**
 * @brief  \~english  Object's Parameter
 * @brief  \~japanese オブジェクトパラメータ
 * @author \~ Maeda Takumi
 */
class Parameter {
private:
    /**
     * @brief \~english  ID distributor
     * @brief \~japanese ID分配用変数
     */
    static int sIDDistributor;
    /**
     * @brief \~english  ID
     * @brief \~japanese ID
     */
    const int mID;
public:
    /**
     * @brief \~english  name of Character
     * @brief \~japanese キャラクター名
     */
    String mName;

    /**
     * @brief \~english  whether dead
     * @brief \~japanese 死んでいるか
     */
    bool mDead;

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
     * @brief \=english  required experience value for level up
     * @brief \~japanese レベルアップに必要な経験値
     */
    int mRequireExperience;

    /**
     * @brief \~english  max of hit points
     * @brief \~japanese 最大HP
     */
    int mMaxHP;
    /**
     * @brief \~english  hit points
     * @briev \~japanese HP
     */
    int mHP;

    /**
     * @brief \~english  moving speed
     * @brief \~japanese 移動速度
     */
    float mSpeed;
    /**
     * @brief \~english  Attack range
     * @brief \~japanese 攻撃範囲
     */
    float mAttackRange;

    /**
     * @brief \~english  strength
     * @brief \~japanese 力
     */
    int mStrength;
    
    Parameter();
    Parameter(const Parameter& orig);
    virtual ~Parameter() = default;
};

#endif /* PARAMETER_H */

