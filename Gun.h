/**
 * @file   Gun.h
 * @brief  Gun
 * @author Maeda Takumi
 */
#ifndef GUN_H
#define GUN_H

#include "Weapon.h"

class Gun : public Weapon {
public:
    Gun();
    virtual ~Gun();

    virtual void attack();
};

#endif /* GUN_H */

