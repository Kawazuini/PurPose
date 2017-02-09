/**
 * @file   Special.cpp
 * @brief  Special
 * @author Maeda Takumi
 */
#include "Special.h"

#include "GameState.h"
#include "Item.h"

List<Special> Special::sSpecials;

Special::Special(
        const SpecialType& aType,
        const double aValue,
        Character * const aSubject,
        Character * const aObject
        ) :
mType(aType),
mValue(aValue),
mSubject(aSubject),
mObject(aObject) {
}

Special::Special(
        const Special& aSpecial,
        Character * const aSubject,
        Character * const aObject
        ) :
Special(aSpecial.mType, aSpecial.mValue, aSubject, aObject) {
}

void Special::special(GameState& aState) {
    CharacterParameter * S(mSubject ? &(mSubject->mCharacterParameter) : NULL);
    CharacterParameter * O(mObject ? &(mObject->mCharacterParameter) : NULL);

    switch (mType) {
        case MISS:
        {
            aState.mBulletin.write("何も起こらない!");
            break;
        }
        case DAMAGE:
        {
            int damage;
            { // ダメージ計算
                int defence(0);
                if (mObject->shield()) {
                    defence += mObject->shield()->param().mPower;
                }
                if (mObject->headEquipment()) {
                    defence += mObject->headEquipment()->param().mPower;
                }
                if (mObject->bodyEquipment()) {
                    defence += mObject->bodyEquipment()->param().mPower;
                }
                if (mObject->footEquipment()) {
                    defence += mObject->footEquipment()->param().mPower;
                }
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
                if (sSpecials.back().mType == GROW) {
                    sSpecials.back().mValue += O->mExperience;
                } else add(Special(GROW, O->mExperience, mSubject));
            }
            break;
        }
        case GROW:
        {
            S->mExperience += mValue;
            aState.mBulletin.write(S->mName + "は" + toString((int) mValue) + "経験値を得た。");

            // レベルアップ(必要経験値 = 2 * (level + 1) * (level + 4))
            int level(S->mLevel);
            for (; S->mRequireExperience <= S->mExperience; ++level, S->mRequireExperience += 2 * (level + 1) * (level + 4)) {
                if (sSpecials.back().mType == LEVELUP) {
                    sSpecials.back().mValue += 1.0f;
                } else add(Special(LEVELUP, 1.0f, mSubject));
            }
            break;
        }
        case HEAL:
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
        case LEVELUP:
        {
            mSubject->levelUp(aState, mValue);
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

