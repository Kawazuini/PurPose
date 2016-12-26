/**
 * @file   Enemy.cpp
 * @brief  Enemy
 * @author Maeda Takumi
 */
#include "Enemy.h"

List<Enemy*> Enemy::sEnemies;

const int Enemy::TEX_SIZE = 64;

Enemy::Enemy(const String& aType, const float& aSize, const color& aColor) :
mSphere(new KDrawSphere(mBody.mPosition, aSize, 10, 10)) {
    add();

    mBody.mRadius = aSize;

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

void Enemy::syncPosition() {
    mSphere->tlanslate(mBody.mPosition);
}

void Enemy::draw() const {
    mSphere->draw();
}

void Enemy::update(const KVector& aPlayer) {
    Character::update();
}

void Enemy::lookAt(const KVector& aDirection) {
    KVector AXIS(0, 1, 0);
    // 2段階回転
    KQuaternion rotate = mDirection.extractVertical(AXIS).roundAngle(aDirection.extractVertical(AXIS));
    mSphere->rotate(rotate);
    mDirection = mDirection.rotate(rotate);
    rotate = mDirection.roundAngle(aDirection);
    mSphere->rotate(rotate);
    mDirection = mDirection.rotate(rotate);
}

