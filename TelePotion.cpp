/**
 * @file TelePotion.cpp
 * @brief TelePotion
 */
#include "TelePotion.h"

const String TelePotion::NAME("テレポーション");

TelePotion::TelePotion() :
Potion() {
    mItemParameter.mName = NAME;
}

TelePotion::TelePotion(const KVector& aPosition) : Potion(aPosition) {
    mItemParameter.mName = NAME;
}

