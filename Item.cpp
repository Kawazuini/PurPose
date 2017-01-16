/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

#include "Cube.h"
#include "Character.h"

List<Item*> Item::sItems;

const float Item::ITEM_SCALE = 1.0f;

Item::Item() : Item(KVector()) {
    hide();
}

Item::Item(const KVector& aPosition) :
mEntity(ITEM_SCALE, aPosition),
mUsable(false),
mEquippable(false),
mThrowable(true),
mPickable(true),
mName(""),
mWeight(0.0f) {
    add();
    mEntity.Object::remove();
}

Item::~Item() {
    remove();
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

void Item::embody() {
    add();
    mEntity.add();
    mPickable = true;
}

void Item::hide() {
    remove();
    mEntity.remove();
    mPickable = false;
}

void Item::use(Character& aChar) {
    delete this;
}

void Item::throwing(Character& aChar) {
    embody();
    mEntity.translate(aChar.position() + aChar.direction() * aChar.size());
    mEntity.applyForce(aChar.direction() * aChar.mParameter.mStrength * 100);
}

const bool& Item::usable() const {
    return mUsable;
}

const bool& Item::equippable() const {
    return mEquippable;
}

const bool& Item::throwable() const {
    return mThrowable;
}

const bool& Item::pickable() const {
    return mPickable;
}

const String& Item::name() const {
    return mName;
}

const KVector& Item::position() const {
    return mEntity.position();
}

