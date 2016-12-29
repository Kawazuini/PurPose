/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

#include "Cube.h"

List<Item*> Item::sItems;

const float Item::ITEM_SCALE = 1.0f;

Item::Item() : Item(KVector()) {
    pickUp();
}

Item::Item(const KVector& aPosition) {
    add();
    mEntity = new Cube(ITEM_SCALE, aPosition);
    mPickedUp = mUsable = mEquippable = false;
    mName = "";
    mWeight = 0.0f;
}

Item::~Item() {
    remove();
    delete mEntity;
}

void Item::add() {
    sItems.push_back(this);
}

void Item::remove() {
    for (auto i = sItems.begin(), i_e = sItems.end(); i != i_e; ++i) {
        if (*i == this) {
            sItems.erase(i);
            return;
        }
    }
}

const List<Item*>& Item::itemList() {
    return sItems;
}

void Item::pickUp() {
    remove();
    mEntity->remove();
    mPickedUp = true;
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

KVector Item::position() const {
    return mEntity->position();
}

