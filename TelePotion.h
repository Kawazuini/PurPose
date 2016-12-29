/**
 * @file TelePotion.h
 * @brief TelePotion
 */
#ifndef TELEPOTION_H
#define TELEPOTION_H

#include "Potion.h"

class TelePotion : public Potion {
private:
    static const String NAME;
public:
    TelePotion();
    TelePotion(const KVector& aPosition);
    TelePotion(const TelePotion& orig) = delete;
    virtual ~TelePotion();
};

#endif /* TELEPOTION_H */
