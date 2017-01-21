/**
 * @file   Item.h
 * @brief  Item
 * @author Maeda Takumi
 */
#include "Item.h"

#include "Character.h"
#include "Map.h"
#include "Special.h"

List<Item*> Item::sItems;

const float Item::ITEM_SCALE = 1.0f;

Item::Item() :
Item(KVector(MAP_SCALE, 0, MAP_SCALE)) {
    hide();
}

Item::Item(const KVector& aPosition) :
mEntity(ITEM_SCALE, aPosition),
mUsable(false),
mEquippable(false),
mThrowable(true),
mPickable(true),
mWeight(0.0f),
mOwener(NULL) {
    Item::add();
}

Item::~Item() {
    Item::remove();
}

void Item::update(GameState& aState) {
    if (mEntity.isMove()) {
        const Vector<Character*>& hitChar(mEntity.hitCharacter());
        if (!hitChar.empty()) {
            Special::Damage(*mOwener, *(hitChar[0]), 3);
            delete this;
        }
    }
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
    Item::add();
    mEntity.KDrawer::add();
    mPickable = true;
}

void Item::hide() {
    Item::remove();
    mEntity.KDrawer::remove();
    mPickable = false;
}

void Item::use(Character & aChar) {
    delete this;
}

void Item::throwing(Character & aChar) {
    embody();
    mEntity.setPosition(aChar.position() + aChar.direction() * (aChar.size() + mEntity.radius() + 0.1f));
    mEntity.applyForce(aChar.direction() * aChar.mCharacterParameter.mSTR * 100);
    mOwener = &aChar;
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
    return mPickable && !mEntity.isMove();
}

const KVector & Item::position() const {
    return mEntity.position();
}

