/**
 * @file   Heal.h
 * @brief  Heal
 * @author Maeda Takumi
 */
#ifndef HEAL_H
#define HEAL_H

#include "Special.h"

/**
 * @brief  \~english  Special effective of Heal
 * @brief  \~japanese 回復効果
 * @author \~ Maeda Takumi
 */
class Heal : public Special {
public:
    Heal(Object * const aSubject = NULL, Object * const aObject = NULL);
    Heal(const Heal& orig) = default;
    virtual ~Heal() = default;
};

#endif /* HEAL_H */

