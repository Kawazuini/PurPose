/**
 * @file TelePotion.cpp
 * @brief TelePotion
 */
#include "TelePotion.h"

const String TelePotion::NAME("テレポーション");

TelePotion::TelePotion() {
    mName = NAME;
    mUseCost = 10;
}

TelePotion::~TelePotion() {
}
