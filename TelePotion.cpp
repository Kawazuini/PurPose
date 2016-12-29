/**
 * @file TelePotion.cpp
 * @brief TelePotion
 */
#include "TelePotion.h"

const String TelePotion::NAME("テレポーション");

TelePotion::TelePotion() : Potion() {
    mName = NAME;
}

TelePotion::TelePotion(const KVector& aPosition) : Potion(aPosition) {
    mName = NAME;
}

TelePotion::~TelePotion() {
}
