/**
 * @file   SpecialFunction.cpp
 * @brief  Special
 * @author Maeda Takumi
 */
#include "Special.h"

#include "GameState.h"
#include "Item.h"
#include "Effect.h"

void Special::miss(GameState& aState) {
    aState.mBulletin.write(Message("何も起こらない!", 0xffff0000));
}

void Special::damage(GameState& aState) {
    int damage;
    { // ダメージ計算
        int defence(0);
        if (mOCharacter->shield()) defence += mOCharacter->shield()->param().mPower;
        if (mOCharacter->headEquipment()) defence += mOCharacter->headEquipment()->param().mPower;
        if (mOCharacter->bodyEquipment()) defence += mOCharacter->bodyEquipment()->param().mPower;
        if (mOCharacter->footEquipment()) defence += mOCharacter->footEquipment()->param().mPower;
        damage = Math::max(mValue - defence, 0.0f);
    }

    mOCharacter->mCharacterParameter.mHP = Math::max(0, (int) (mOCharacter->mCharacterParameter.mHP - damage));
    if (damage) {
        color txtColor(&(aState.mPlayer) == mOCharacter ? 0xffff0000 : 0xffffffff);
        aState.mBulletin.write(Message(mSCharacter->mCharacterParameter.mName + "は" + mOCharacter->mCharacterParameter.mName + "に" + toString(damage) + "ダメージを与えた。", txtColor));
    } else {
        aState.mBulletin.write(mOCharacter->mCharacterParameter.mName + "にダメージはない。");
    }

    if (!mOCharacter->mCharacterParameter.mHP) {
        Special kill(SPECIAL_KILL, mSCharacter, mOCharacter);
        if (sSpecials.back() != kill) { // 最後尾と被りなし(2回殺さない)
            add(kill);
        }
    }
}

void Special::damage_ignore(GameState& aState) {
    int damage(mValue);
    mOCharacter->mCharacterParameter.mHP = Math::max(0, mOCharacter->mCharacterParameter.mHP - damage);
    if (mSCharacter != mOCharacter) { // 対象と発動者が異なるとき
        color txtColor(&(aState.mPlayer) == mOCharacter ? 0xffff0000 : 0xffffffff);
        aState.mBulletin.write(Message(mSCharacter->mCharacterParameter.mName + "は" + mOCharacter->mCharacterParameter.mName + "に" + toString(damage) + "ダメージを与えた。", txtColor));
    }

    if (!mOCharacter->mCharacterParameter.mHP) {
        Special kill(SPECIAL_KILL, mSCharacter, mOCharacter);
        if (sSpecials.back() != kill) { // 最後尾と被りなし(2回殺さない)
            add(kill);
        }
    }
}

void Special::damage_stamina(GameState& aState) {
    mOCharacter->mCharacterParameter.mStamina = Math::max(0, mOCharacter->mCharacterParameter.mStamina - (int) mValue);
}

void Special::heal(GameState& aState) {
    int healing(mValue);
    if (mOCharacter) {
        CharacterParameter & param(mOCharacter->mCharacterParameter);
        param.mHP = Math::min(param.mHP + healing, param.mMHP);
        if (mSCharacter != mOCharacter) aState.mBulletin.write(mSCharacter->mCharacterParameter.mName + "は" + param.mName + "のHPを" + toString(healing) + "回復させた。");
    } else {
        CharacterParameter & param(mSCharacter->mCharacterParameter);
        param.mHP = Math::min(param.mHP + healing, param.mMHP);
        aState.mBulletin.write(param.mName + "のHPは" + toString(healing) + "回復した。");
    }
}

void Special::heal_stamina(GameState& aState) {
    int healing(mValue);
    if (mOCharacter) {
        CharacterParameter & param(mOCharacter->mCharacterParameter);
        param.mStamina = Math::min((int) (param.mStamina + healing), param.mMaxStamina);
        if (mSCharacter != mOCharacter) aState.mBulletin.write(mSCharacter->mCharacterParameter.mName + "は" + param.mName + "のスタミナを" + toString(healing) + "回復させた。");
    } else {
        CharacterParameter & param(mSCharacter->mCharacterParameter);
        param.mStamina = Math::min((int) (param.mStamina + healing), param.mMaxStamina);
        aState.mBulletin.write(param.mName + "のスタミナは" + toString(healing) + "回復した。");
    }
}

void Special::grow(GameState& aState) {
    CharacterParameter & param(mSCharacter->mCharacterParameter);
    int exp(mValue); // 整数型にキャストして誤差を防ぐ

    param.mExperience += exp;
    aState.mBulletin.write(param.mName + "は" + toString(exp) + "経験値を得た。");

    int level(param.mLevel - 1), grow(0);
    for (; param.mExperience >= param.mRequireExperience[level] && level < 99; ++level, ++grow);
    if (grow) add(Special(SPECIAL_LEVELUP, grow, mSCharacter));
}

void Special::levelup(GameState& aState) {
    mSCharacter->levelUp(aState, mValue);
}

void Special::explosion(GameState& aState) {
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
}

void Special::kill(GameState& aState) {
    bool& dead(mOCharacter->mCharacterParameter.mDead);
    if (!dead) {
        dead = true;
        mOCharacter->mWhoKilleMe = mSCharacter;
        aState.mBulletin.write(Message(mSCharacter->mCharacterParameter.mName + "は" + mOCharacter->mCharacterParameter.mName + "を倒した。", 0xffff0000));

        // 経験値の分配
        // 経験値(基本経験値 × レベル)
        int exp(mOCharacter->mCharacterParameter.mExperience * mOCharacter->mCharacterParameter.mLevel);
        Special grow(SPECIAL_GROW, exp, mSCharacter);
        if (sSpecials.back() == grow) {
            sSpecials.back().mValue += exp;
        } else add(grow);
    }
}

