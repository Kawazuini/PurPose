/**
 * @file   Enemy.cpp
 * @brief  Enemy
 * @author Maeda Takumi
 */
#include "Enemy.h"
#include "GameState.h"
#include "Special.h"


const int Enemy::TEX_SIZE = 64;

Enemy::Enemy(
        GameState& aState,
        const String& aType,
        const float& aSize,
        const color& aColor
        ) :
Character(aState),
mSphere(mBody.mPosition, aSize, 10, 10),
mTexture(TEX_SIZE) {
    aState.mEnemies.push_back(this);

    mBody.mRadius = aSize;

    mDirection = KVector(0, 0, -1);

    mTexture.drawRect(KRect(TEX_SIZE, TEX_SIZE), aColor);
    mTexture.drawText(CHARSET_BIG, aType, KVector(TEX_SIZE / 4), 0xffffffff);
    mTexture.reflect();

    mSphere.mTexture = &mTexture;

    setPosition(aState, mBody.mPosition);
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

void Enemy::attack(GameState& aState) {
    if ((aState.mPlayer.position() - mBody.mPosition).length()
            <= (aState.mPlayer.size() + mBody.mRadius + mParameter.mAttackRange)) {
        Special::Damage(*this, aState.mPlayer, 1);
    }
    turnEnd();
}

void Enemy::syncPosition() {
    mSphere.tlanslate(mBody.mPosition);
}

void Enemy::lookAt(const KVector& aDirection) {
    KVector AXIS(0, 1, 0);
    // 2段階回転
    KQuaternion rotate = mDirection.extractVertical(AXIS).roundAngle(aDirection.extractVertical(AXIS));
    mSphere.rotate(rotate);
    mDirection = mDirection.rotate(rotate);
    rotate = mDirection.roundAngle(aDirection);
    mSphere.rotate(rotate);
    mDirection = mDirection.rotate(rotate);
}

