/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

Item::Item() {
    mUsable = true;
    mEquippable = false;
    mName = "";
    mWeight = 0.0f;
    mUseCost = mEquipCost = 0;
}

void Item::use(Character& aChar) {
    delete this;
}

bool Item::usable() const {
    return mUsable;
}

bool Item::equippable() const {
    return mEquippable;
}

String Item::name() const {
    return mName;
}

int Item::useCost() const {
    return mUseCost;
}

int Item::equipCost() const {
    return mEquipCost;
}

