/**
 * @file HPotion.cpp
 * @brief HPotion
 */
#include "HPotion.h"
#include "Character.h"

const String HPotion::NAME("Potion");

HPotion::HPotion() {
    mName = NAME;
    mWeight = 0.01f;
    mCost = 1;
}

void HPotion::use(Character& aChar) {
    aChar.recover(5);
    Item::use(aChar);
}

