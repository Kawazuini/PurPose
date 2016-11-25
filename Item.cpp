/**
 * @file Item.cpp
 * @brief Item
 */
#include "Item.h"

Item::Item() {
}

Item::~Item() {
}

String Item::name() const {
    return mName;
}

int Item::cost() const {
    return mCost;
}
