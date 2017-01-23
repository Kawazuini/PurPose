/**
 * @file   Potion.cpp
 * @brief  Potion
 * @author Maeda Takumi
 */
#include "Potion.h"

#include "Special.h"

Potion::Potion(const int& aID, const KVector& aPosition) :
Item(aID, aPosition) {
}

void Potion::use(Character& aChar) {
    Special::add(Special(mItemParameter.mSpecial, &aChar));
    Item::use(aChar);
}

