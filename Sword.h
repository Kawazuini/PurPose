/**
 * @file   Sword.h
 * @brief  Sword
 * @author Maeda Takumi
 */
#ifndef SWORD_H
#define SWORD_H

#include "Weapon.h"

class Sword : public Weapon {
public:
    Sword();
    Sword(const Sword& orig) = default;
    virtual ~Sword() = default;
};

#endif /* SWORD_H */

