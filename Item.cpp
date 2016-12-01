/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

String Item::name() const {
    return mName;
}

int Item::cost() const {
    return mCost;
}
