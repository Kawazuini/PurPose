/**
 * @file HPotion.h
 * @brief HPotion
 */
#ifndef HPOTION_H
#define HPOTION_H

#include "Item.h"

class HPotion : public Item {
private:
    static const String NAME;
public:
    HPotion();
    HPotion(const HPotion& orig) = delete;
    virtual ~HPotion();
};

#endif /* HPOTION_H */
