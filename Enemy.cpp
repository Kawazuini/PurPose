/**
 * @file   Enemy.cpp
 * @brief  Enemy
 * @author Maeda Takumi
 */
#include "Enemy.h"

#include "GameState.h"
#include "Special.h"

const int Enemy::PARAMETER_INDEX_COLOR(10);
const int Enemy::PARAMETER_INDEX_CHAR(11);
const int Enemy::PARAMETER_INDEX_CHARCOLOR(12);

const int Enemy::TEX_SIZE = 64;

Enemy::Enemy(const int& aID) :
Character(aID),
mSphere(mBody.mPosition, mCharacterParameter.mSize, 10, 10),
mTexture(TEX_SIZE) {
    mBody.mRadius = mCharacterParameter.mSize;

    mDirection = KVector(0, 0, -1);

    mTexture.drawRect(
            KRect(TEX_SIZE, TEX_SIZE),
            toColor(mCharacterParameter.mParameterTable[PARAMETER_INDEX_COLOR])
            );
    mTexture.drawText(
            CHARSET_BIG,
            mCharacterParameter.mParameterTable[PARAMETER_INDEX_CHAR],
            KVector(TEX_SIZE / 4),
            toColor(mCharacterParameter.mParameterTable[PARAMETER_INDEX_CHARCOLOR])
            );
    mTexture.reflect();

    mSphere.mTexture = &mTexture;
}

void Enemy::update(GameState& aState) {
    if (mTurn) lookAt((aState.mPlayer.position() - mBody.mPosition));
    Character::update(aState);
}

void Enemy::attack(GameState& aState) {
    if (
            KSphere(mBody.mPosition, mBody.mRadius + mCharacterParameter.mAttackRange)
            * aState.mPlayer.body()
            ) {
        Special::add(Special(DAMAGE, mCharacterParameter.mSTR, this, &aState.mPlayer));
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

