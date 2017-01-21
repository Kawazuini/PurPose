/**
 * @file   Enemy.cpp
 * @brief  Enemy
 * @author Maeda Takumi
 */
#include "Enemy.h"
#include "GameState.h"
#include "Special.h"


const int Enemy::TEX_SIZE = 64;

Enemy::Enemy(const int& aID, GameState& aState) :
Character(aID, aState),
mSphere(mBody.mPosition, mCharacterParameter.mSize, 10, 10),
mTexture(TEX_SIZE) {
    Vector<String> param(split(loadString(mCharacterParameter.mID), ","));

    aState.mEnemies.push_back(this);

    mBody.mRadius = mCharacterParameter.mSize;

    mDirection = KVector(0, 0, -1);

    mTexture.drawRect(
            KRect(TEX_SIZE, TEX_SIZE),
            toColor(param[mCharacterParameter.mParameterIndex++])
            );
    mTexture.drawText(
            CHARSET_BIG,
            param[mCharacterParameter.mParameterIndex],
            KVector(TEX_SIZE / 4),
            toColor(param[mCharacterParameter.mParameterIndex + 1])
            );
    mTexture.reflect();

    mSphere.mTexture = &mTexture;
}

void Enemy::die(GameState& aState) {
    Character::die(aState);
    for (auto i = aState.mEnemies.begin(), i_e = aState.mEnemies.end(); i != i_e; ++i) {
        if (*i == this) {
            aState.mEnemies.erase(i);
            return;
        }
    }
}

void Enemy::update(GameState& aState) {
    if (mTurn) lookAt((aState.mPlayer.position() - mBody.mPosition));
    Character::update(aState);
}

void Enemy::attack(GameState& aState) {
    if ((aState.mPlayer.position() - mBody.mPosition).length()
            <= (aState.mPlayer.size() + mBody.mRadius + mCharacterParameter.mAttackRange)) {
        Special::Damage(*this, aState.mPlayer, 1);
    }
    turnEnd();
}

void Enemy::syncPosition() {
    mSphere.tlanslate(mBody.mPosition);
}

void Enemy::lookAt(const KVector& aDirection) {
    static const KVector AXIS(0, 1, 0);
    // 2段階回転
    KQuaternion rotate(mDirection.extractVertical(AXIS).roundAngle(aDirection.extractVertical(AXIS)));
    mSphere.rotate(rotate);
    mDirection = mDirection.rotate(rotate);
    rotate = mDirection.roundAngle(aDirection);
    mSphere.rotate(rotate);
    mDirection = mDirection.rotate(rotate);
}

