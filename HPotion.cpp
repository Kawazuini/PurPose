/**
 * @file HPotion.cpp
 * @brief HPotion
 */
#include "HPotion.h"

const String HPotion::NAME("Potion");

HPotion::HPotion() {
    mName = NAME;
    mCost = 10;
}

HPotion::~HPotion() {
}
