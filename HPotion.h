/**
 * @file   HPotion.h
 * @brief  HPotion
 * @author Maeda Takumi
 */
#ifndef HPOTION_H
#define HPOTION_H

#include "Item.h"

class HPotion : public Item {
private:
    static const String NAME;
public:
    HPotion();
    HPotion(const HPotion& orig) = default;
    virtual ~HPotion() = default;

    virtual void use(Character& aChar);
};

#endif /* HPOTION_H */

