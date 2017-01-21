/**
 * @file   HPotion.h
 * @brief  HPotion
 * @author Maeda Takumi
 */
#ifndef HPOTION_H
#define HPOTION_H

#include "Potion.h"

class HPotion : public Potion {
private:
    static const String NAME;
public:
    HPotion();
    HPotion(const KVector& aPosition);
    virtual ~HPotion() = default;

    virtual void use(Character& aChar);
};

#endif /* HPOTION_H */

