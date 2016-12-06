/**
 * @file   Weapon.cpp
 * @brief  Weapon
 * @author Maeda Takumi
 */
#include "Weapon.h"

#include "Character.h"

Weapon::Weapon() {
}

void Weapon::equip(Character& aChar) {
    aChar.equipWeapon(*this);
}

