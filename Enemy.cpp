/**
 * @file   Enemy.cpp
 * @brief  Enemy
 * @author Maeda Takumi
 */
#include "Enemy.h"

List<Enemy*> Enemy::sEnemies;

const int Enemy::TEX_SIZE = 64;

Enemy::Enemy(const String& aType, const color& aColor) :
mSphere(new KDrawSphere(mBody.mPosition, 1, 10, 10)) {
    add();

    mDirection = KVector(0, 0, -1);
    mTexture = new KTexture(TEX_SIZE);
    mTexture->drawRect(KRect(TEX_SIZE, TEX_SIZE), aColor);
    mTexture->drawText(CHARSET_BIG, aType, KVector(TEX_SIZE / 4), 0xffffffff);

    mSphere->mTexture = mTexture;

    mTexture->reflect();

    setPosition(mBody.mPosition);
}

Enemy::~Enemy() {
    erase();
    delete mTexture;
}

void Enemy::add() {
    sEnemies.push_back(this);
}

void Enemy::erase() {
    for (auto i = sEnemies.begin(), i_e = sEnemies.end(); i != i_e; ++i) {
        if (*i == this) {
            sEnemies.erase(i);
            return;
        }
    }
}

void Enemy::move(const KVector& aMovement) {
    if (mTurn) {
        mBody.mPosition += aMovement.normalization();
        resolveOverlap();
        mSphere->tlanslate(mBody.mPosition);
        turnEnd();
    }
}

void Enemy::setPosition(const KVector& aPosition) {
    Character::setPosition(aPosition);

    mSphere->tlanslate(mBody.mPosition);
}

void Enemy::draw() const {
    mSphere->draw();
}

void Enemy::update(const KVector& aPlayer) {
    if (mTurn) {
        // 移動方向の決定
        if (aPlayer != mBody.mPosition) {
            KVector eyeDir = (aPlayer - mBody.mPosition).normalization();
            KQuaternion rotate = mDirection.roundAngle(eyeDir);
            mSphere->rotate(rotate);
            mDirection = mDirection.rotate(rotate);
        }
    }

    Character::update();
}

