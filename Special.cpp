/**
 * @file   Special.cpp
 * @brief  Special
 * @author Maeda Takumi
 */
#include "Special.h"

#include "GameState.h"
#include "Item.h"
#include "Effect.h"

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
    CharacterParameter * S(mSCharacter ? &(mSCharacter->mCharacterParameter) : NULL);
    CharacterParameter * O(mOCharacter ? &(mOCharacter->mCharacterParameter) : NULL);

    switch (mType) {
        case SPECIAL_MISS:
        {
            aState.mBulletin.write("何も起こらない!");
            break;
        }
        case SPECIAL_DAMAGE:
        {
            int damage;
            { // ダメージ計算
                int defence(0);
                if (mOCharacter->shield()) defence += mOCharacter->shield()->param().mPower;
                if (mOCharacter->headEquipment()) defence += mOCharacter->headEquipment()->param().mPower;
                if (mOCharacter->bodyEquipment()) defence += mOCharacter->bodyEquipment()->param().mPower;
                if (mOCharacter->footEquipment()) defence += mOCharacter->footEquipment()->param().mPower;
                damage = Math::max(mValue - defence, 0.0f);
            }

            O->mHP = Math::max(0, (int) (O->mHP - damage));
            if (damage) {
                aState.mBulletin.write(S->mName + "は" + O->mName + "に" + toString(damage) + "ダメージを与えた。");
            } else {
                aState.mBulletin.write(O->mName + "にダメージはない。");
            }

            if (!O->mHP) {
                Special kill(SPECIAL_KILL, mSCharacter, mOCharacter);
                if (sSpecials.back() != kill) { // 最後尾と被りなし(2回殺さない)
                    add(kill);
                }
            }
            break;
        }
        case SPECIAL_GROW:
        {
            S->mExperience += mValue;
            aState.mBulletin.write(S->mName + "は" + toString((int) mValue) + "経験値を得た。");

            // レベルアップ(必要経験値 = 2 * (level + 1) * (level + 4))
            int level(S->mLevel);
            for (; S->mRequireExperience <= S->mExperience; ++level, S->mRequireExperience += 2 * (level + 1) * (level + 4)) {
                if (sSpecials.back().mType == SPECIAL_LEVELUP) {
                    sSpecials.back().mValue += 1.0f;
                } else add(Special(SPECIAL_LEVELUP, 1.0f, mSCharacter));
            }
            break;
        }
        case SPECIAL_HEAL:
        {
            if (O) {
                O->mHP = Math::min((int) (O->mHP + mValue), O->mMHP);
                aState.mBulletin.write(S->mName + "は" + O->mName + "のHPを" + toString((int) mValue) + "かいふくさせた。");
                break;
            } else {
                S->mHP = Math::min((int) (S->mHP + mValue), S->mMHP);
                aState.mBulletin.write(S->mName + "のHPは" + toString((int) mValue) + "回復した。");
                break;
            }
        }
        case SPECIAL_LEVELUP:
        {
            mSCharacter->levelUp(aState, mValue);
            break;
        }
        case SPECIAL_EXPLOSION:
        {
            KVector hypocenter; // 爆心地
            if (mOCharacter) hypocenter = mOCharacter->position();
            if (mOItem) hypocenter = mOItem->mEntity.position();

            float effectRange(mValue / 10); // 威力100で10m
            for (Character* i : aState.charList()) {
                float dist((i->position() - hypocenter).length()); // 爆心地からの距離
                if (dist < effectRange) {
                    add(Special(SPECIAL_DAMAGE, (1.0f - dist / effectRange) * mValue, mSCharacter, i));
                }
            }

            // エフェクト
            new Effect(Effect::EFFECT_EXPLOSION, mValue, hypocenter);

            break;
        }
        case SPECIAL_KILL:
        {
            aState.mBulletin.write(Message(S->mName + "は" + O->mName + "を倒した。", 0xffff0000));
            O->mDead = true;
            if (sSpecials.back().mType == SPECIAL_GROW) {
                sSpecials.back().mValue += O->mExperience;
            } else add(Special(SPECIAL_GROW, O->mExperience, mSCharacter));
            break;
        }
    }
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

const SpecialType& Special::type() const {
    return mType;
}

const float& Special::value() const {
    return mValue;
}

