/**
 * @file TelePotion.h
 * @brief TelePotion
 */
#ifndef TELEPOTION_H
#define TELEPOTION_H

#include "Item.h"

class TelePotion : public Item {
private:
    static const String NAME;
public:
    TelePotion();
    TelePotion(const TelePotion& orig) = delete;
    virtual ~TelePotion();
};

#endif /* TELEPOTION_H */
