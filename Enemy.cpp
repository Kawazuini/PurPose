/**
 * @file Enemy.cpp
 * @brief Enemy
 */
#include "Enemy.h"

const int Enemy::TEX_SIZE = 64;

Enemy::Enemy(const String& aType, const color& aColor) :
mSphere(new KDrawSphere(mPosition, 1, 10, 10)) {
    mDirection = KVector(0, 0, -1);
    mTexture = new KTexture(TEX_SIZE);
    mTexture->drawRect(KRect(TEX_SIZE, TEX_SIZE), aColor);
    mTexture->drawText(CHARSET_BIG, aType, KVector(TEX_SIZE / 4), 0xffffffff);

    mSphere->mTexture = mTexture;

    mTexture->update();

    setPosition(mPosition);
}

Enemy::~Enemy() {
}

bool Enemy::move(const KVector& aMovement) {
    if (Character::move(aMovement)) {
        mSphere->tlanslate(mPosition);
        return true;
    }
}

void Enemy::setPosition(const KVector& aPosition) {
    Character::setPosition(aPosition);

    mSphere->tlanslate(mPosition);
}

void Enemy::draw() {
    mSphere->draw();
}

void Enemy::update(const KVector& aPlayer) {
    Character::update();

    if (mTurn) {
        // 移動方向の決定
        if (aPlayer != mPosition) {
            KVector eyeDir = (aPlayer - mPosition).normalization();
            KQuaternion rotate = mDirection.roundAngle(eyeDir);
            mSphere->rotate(rotate);
            mDirection = mDirection.rotate(rotate);
        }
    }
}

