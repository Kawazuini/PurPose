/**
 * @brief  \~english  Damage.h
 * @brief  \~japanese Damage
 * @author Maeda Takumi
 */
#ifndef DAMAGE_H
#define DAMAGE_H

#include "Special.h"

/**
 * @brief  \~english  Special effective of Damage
 * @brief  \~japanese ダメージ効果
 * @author \~ Maeda Takumi
 */
class Damage : public Special {
private:
    /**
     * @brief \~english  amount of damage
     * @brief \~japanese ダメージ量
     */
    int mDamage;

    /**
     * @brief \~english  effect invocation.
     * @brief \~japanese 効果の発動。
     */
    virtual void special() override;
public:
    Damage(const int& aDamage, Object * const aSubject, Object * const aObject);
    Damage(const Damage& orig) = default;
    virtual ~Damage() = default;

};

#endif /* DAMAGE_H */

