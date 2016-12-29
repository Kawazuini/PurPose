/**
 * @file HPotion.cpp
 * @brief HPotion
 */
#include "HPotion.h"
#include "Character.h"

const String HPotion::NAME("Potion");

HPotion::HPotion() : Potion() {
    mName = NAME;
    mWeight = 0.01f;
}

HPotion::HPotion(const KVector& aPosition) : Potion(aPosition) {
    mName = NAME;
    mWeight = 0.01f;
}

void HPotion::use(Character& aChar) {
    aChar.recover(5);
    Item::use(aChar);
}

