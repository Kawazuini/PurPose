/**
 * @file   Potion.cpp
 * @brief  Potion
 * @author Maeda Takumi
 */
#include "Potion.h"

Potion::Potion() : Item() {
    mUsable = true;
}

Potion::Potion(const KVector& aPosition) : Item(aPosition) {
    mUsable = true;
}

Potion::Potion(const Potion& orig) {
}

