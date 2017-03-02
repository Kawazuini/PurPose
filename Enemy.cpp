/**
 * @file   Enemy.cpp
 * @brief  Enemy
 * @author Maeda Takumi
 */
#include "Enemy.h"

#include "GameState.h"
#include "Special.h"

const int Enemy::TEX_SIZE(1024);

Enemy::Enemy(const int& aID) :
Character(aID),
mTexture(TEX_SIZE) {
    mTexture.drawImage(IMG_ENEMY, KRect(TEX_SIZE, TEX_SIZE), KVector());
    mTexture.reflect();
}

void Enemy::draw() const {
    KVector AXIS(0, 1, 0);
    float HALF_PI(Math::PI / 2);
    float size(mCharacterParameter.mSize / 2);
    KVector hori(mDirection.cross(AXIS).normalization() * size);
    KVector vert(mDirection.rotate(KQuaternion(hori, HALF_PI)) * size);

    KVector lt(mPosition - hori - vert);
    KVector lb(mPosition - hori + vert);
    KVector rt(mPosition + hori - vert);
    KVector rb(mPosition + hori + vert);

    // ハリボテ描画
    mTexture.bindON();
    glNormal3f(DEPLOYMENT(mDirection));
    glBegin(GL_TRIANGLE_FAN);
    glTexCoord2f(1, 0);
    glVertex3f(DEPLOYMENT(lt));
    glTexCoord2f(0, 0);
    glVertex3f(DEPLOYMENT(rt));
    glTexCoord2f(0, 1);
    glVertex3f(DEPLOYMENT(rb));
    glTexCoord2f(1, 1);
    glVertex3f(DEPLOYMENT(lb));
    glEnd();
    mTexture.bindOFF();
}

void Enemy::update(GameState& aState) {
    if (mTurn) lookAt((aState.mPlayer.position() - mPosition));
    Character::update(aState);
}

void Enemy::levelUp(GameState& aState, const int& aLevel) {
    int hpup(pow(2, aLevel)), strup(pow(2, aLevel));
    mCharacterParameter.mLevel += aLevel;
    mCharacterParameter.mMHP *= hpup;
    mCharacterParameter.mSTR *= strup;

    aState.mBulletin.write(Message(mCharacterParameter.mName + "はレベルが" + toString(mCharacterParameter.mLevel) + "に上がった。", 0xffff0000));
}

void Enemy::attack(GameState& aState) {
    Character::attack(aState);
    if (
            KSphere(mPosition, mBody.mRadius + mCharacterParameter.mAttackRange)
            * aState.mPlayer.body()
            ) {
        Special::add(Special(SPECIAL_DAMAGE, mCharacterParameter.mSTR, this, &aState.mPlayer));
    }
    turnEnd();
}

void Enemy::syncPosition() {
}

void Enemy::lookAt(const KVector& aDirection) {
    static const KVector AXIS(0, 1, 0);
    // 2段階回転
    KQuaternion rotate(mDirection.extractVertical(AXIS).roundAngle(aDirection.extractVertical(AXIS)));
    mDirection = mDirection.rotate(rotate);
    rotate = mDirection.roundAngle(aDirection);
    mDirection = mDirection.rotate(rotate);
}

