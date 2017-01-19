/**
 * @file TelePotion.cpp
 * @brief TelePotion
 */
#include "TelePotion.h"

const String TelePotion::NAME("テレポーション");

TelePotion::TelePotion() : Potion() {
    mParameter.mName = NAME;
}

TelePotion::TelePotion(const KVector& aPosition) : Potion(aPosition) {
    mParameter.mName = NAME;
}

TelePotion::~TelePotion() {
}
