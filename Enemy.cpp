/**
 * @file Enemy.cpp
 * @brief Enemy
 */
#include "Enemy.h"

const int Enemy::TEX_SIZE = 64;

Enemy::Enemy(const String& aType, const color& aColor) :
mSphere(KVector(), 1),
mDirection(0, 0, 1) {
    //KImage img(TEX_SIZE, TEX_SIZE);
    //img.changeColor(0x00000000, aColor);
    //img.drawImage(IMG_CHARSET_BIG, CHARSET_BIG.charPosition(aType), KVector(TEX_SIZE / 4));

    mTexture = new KTexture(TEX_SIZE);

    setPosition(mPosition);
}

Enemy::~Enemy() {
}

bool Enemy::move(const KVector& aMovement) {
    if (Character::move(aMovement)) mSphere.mPosition += aMovement;
}

void Enemy::setPosition(const KVector& aPosition) {
    Character::setPosition(aPosition);

    mSphere.mPosition = mPosition;
}

void Enemy::draw() {
    mTexture->bindON();
   // mSphere.draw();
    mTexture->bindOFF();
}

void Enemy::update(const KVector& aPlayer) {
    Character::update();

    if (mTurn) {
        // 移動方向の決定
        if (aPlayer != mSphere.mPosition) {
            KVector eyeDir = (aPlayer - mSphere.mPosition).normalization();
           // KQuaternion rotate = mDirection.roundAngle(eyeDir);
           // mSphere.rotate(rotate);
           // mDirection = mDirection.rotate(rotate);
        }
    }
}

