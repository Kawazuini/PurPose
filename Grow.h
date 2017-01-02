/**
 * @file   Grow.h
 * @brief  Grow
 * @author Maeda Takumi
 */
#ifndef GROW_H
#define GROW_H

#include "Special.h"

/**
 * @brief  \~english  Special effective of Grow
 * @brief  \~japanese 成長効果
 * @author \~ Maeda Takumi
 */
class Grow : public Special {
    friend class SpecialManager;
private:
    /**
     * @brief \~english  experience point
     * @brief \~japanese 経験値
     */
    int mEXP;

    Grow& operator+=(const Grow& aGrow);
    Grow operator+(const Grow& aGrow) const;

    /**
     * @brief \~english  effect invocation.
     * @brief \~japanese 効果の発動。
     */
    virtual void special() override;
public:
    Grow(const int& aEXP, Object * const aSubject);
    Grow(const Grow& orig) = default;
    virtual ~Grow() = default;
};

#endif /* GROW_H */

