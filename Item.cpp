/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

void Item::use(Character& aChar){
    delete this;
}

String Item::name() const {
    return mName;
}

int Item::cost() const {
    return mCost;
}
