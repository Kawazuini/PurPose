/**
 * @file   Special.cpp
 * @brief  Special
 * @author Maeda Takumi
 */
#include "Special.h"

const Vector<Special::SpecialFunction> Special::SPECIAL_FUNCTION
{
    miss,
            damage, damage_ignore, damage_stamina,
            heal, heal_stamina,
            grow, levelup,
            explosion,
            kill,
};
List<Special> Special::sSpecials;

Special::Special(
        const SpecialType& aType,
        const float aValue,
        Character* aSubject,
        Character* aObject
        ) :
mType(aType),
mValue(aValue),
mSCharacter(aSubject),
mOCharacter(aObject),
mOItem(NULL) {
}

Special::Special(
        const Special& aSpecial,
        Character* aSubject,
        Character* aObject
        ) :
Special(aSpecial.mType, aSpecial.mValue, aSubject, aObject) {
}

Special::Special(
        const Special& aSpecial,
        Character* aSubject,
        Item* aObject
        ) :
mType(aSpecial.mType),
mValue(aSpecial.mValue),
mSCharacter(aSubject),
mOCharacter(NULL),
mOItem(aObject) {
}

List<Special> Special::Specials(const Vector<String>& aSpecials) {
    List<Special> tmp;
    for (int i = 0, i_e = aSpecials.size(); i < i_e; i += 2) {
        if (aSpecials[i] == "") break;
        Special deb(toSpecialType(aSpecials[i]), toFloat(aSpecials[i + 1]));
        tmp.push_back(Special(toSpecialType(aSpecials[i]), toFloat(aSpecials[i + 1])));
    }
    return tmp;
}

bool Special::operator==(const Special& aSpecial) const {
    return mType == aSpecial.mType &&
            mValue == aSpecial.mValue &&
            mSCharacter == aSpecial.mSCharacter &&
            mOCharacter == aSpecial.mOCharacter &&
            mOItem == aSpecial.mOItem;
}

bool Special::operator!=(const Special& aSpecial) const {
    return !(*this == aSpecial);
}

void Special::special(GameState& aState) {
    (this->*SPECIAL_FUNCTION[mType])(aState);
}

void Special::add(const Special& aSpecial) {
    sSpecials.push_back(aSpecial);
}

void Special::cutin(const Special& aSpecial) {
    sSpecials.push_front(aSpecial);
}

void Special::invocation(GameState& aState) {
    while (!sSpecials.empty()) {
        Special sp(sSpecials.front());
        sSpecials.pop_front();
        sp.special(aState);
    }
}

void Special::clear() {
    sSpecials.clear();
}

const SpecialType& Special::type() const {
    return mType;
}

const float& Special::value() const {
    return mValue;
}

