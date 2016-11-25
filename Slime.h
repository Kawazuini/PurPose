/**
 * @file Slime.h
 * @brief Slime
 */
#ifndef SLIME_H
#define SLIME_H

#include "main.h"

#include "Enemy.h"

class Slime : public Enemy {
private:
    float mSpeed;
public:
    Slime();
    virtual ~Slime();

    virtual void update(const KVector& aPlayer) override;
};

#endif /* SLIME_H */

