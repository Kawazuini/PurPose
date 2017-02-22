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
        const double aValue,
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
                aState.mBulletin.write(O->mName + "は倒れた。");
                O->mDead = true;
                if (sSpecials.back().mType == SPECIAL_GROW) {
                    sSpecials.back().mValue += O->mExperience;
                } else add(Special(SPECIAL_GROW, O->mExperience, mSCharacter));
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

