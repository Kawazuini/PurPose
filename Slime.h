/**
 * @file   Slime.h
 * @brief  Slime
 * @author Maeda Takumi
 */
#ifndef SLIME_H
#define SLIME_H

#include "main.h"

#include "Enemy.h"

class Slime : public Enemy {
public:
    Slime();
    virtual ~Slime();

    virtual void update(const KVector& aPlayer) override;
    
    virtual void damage(const int& aDamage) override;
};

#endif /* SLIME_H */

