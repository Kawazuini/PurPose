/**
 * @file   LevelUp.cpp
 * @brief  LevelUp
 * @author Maeda Takumi
 */
#ifndef LEVELUP_H
#define LEVELUP_H

#include "Special.h"

/**
 * @brief  \~english  Special effective of level up
 * @brief  \~japanese レベルアップ効果
 * @author \~ Maeda Takumi
 */
class LevelUp : public Special {
    friend class SpecialManager;
private:
    /**
     * @brief \~english  level increase value
     * @brief \~japanese レベル上昇値
     */
    int mLevel;

    LevelUp& operator+=(const LevelUp& aLevelUp);
    LevelUp operator+(const LevelUp& aLevelUp) const;

    /**
     * @brief \~english  effect invocation.
     * @brief \~japanese 効果の発動。
     */
    virtual void special() override;
public:
    LevelUp(const int& aLevel, Object * const aSubject);
    virtual ~LevelUp() = default;
};

#endif /* LEVELUP_H */

