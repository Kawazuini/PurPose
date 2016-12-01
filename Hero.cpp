/**
 * @file   Hero.cpp
 * @brief  Hero
 * @author Maeda Takumi
 */
#include "Hero.h"

#include "PurPose.h"

#include "Map.h"
#include "Wall.h"

#include "HPotion.h"
#include "TelePotion.h"

Hero::Hero() {
    KDrawer::erase(); // 独自描画

    mName = "aaa";

    mSpeed = 1;
    mSize = 1;
    mEyeCamera = new KFPSCamera();
    mDevice = new KGLUI(*mEyeCamera);

    mActionPoint = 0;

    mAgility = 12;

    mMoveCost = 1;

    mCircleTexture = new KTexture(64);
    mCircleTexture->drawText(CHARSET_BIG, "!", KVector(16), 0xffffff);
    mCircleTexture->update();

    setPosition(mPosition);

    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new HPotion());
    mBackPack.add(new TelePotion());
    mBackPack.add(new TelePotion());
}

Hero::~Hero() {
}

void Hero::draw() {
    drawCircle();

    mBackPack.draw(*mDevice, KRect(KGLUI::WIDTH - 252, 0, 250, KGLUI::HEIGHT - 2));
    PurPose::mMessage.draw(*mDevice, CHARSET_MINI, KRect(10, KGLUI::HEIGHT - 200, 500, 200));
    mDevice->draw();
}

void Hero::update() {
    Character::update();

    light.mPosition = mEyeCamera->mPosition;
    light.mDirection = mEyeCamera->mDirection;
    light.at();

    // マップ更新
    Map::MapPlayer player(mEyeCamera->mPosition, mEyeCamera->mDirection);
    sMap->draw(*mDevice, player, KRect(200, 200), 5);
}

void Hero::move(const KVector& aMovement) {
    if (isMovable()) {
        mPosition += mEyeCamera->convertDirection(aMovement).normalization() * mSpeed;
        resolveOverlap();
        mEyeCamera->mPosition = mPosition;
        mEyeCamera->set();
    }
}

void Hero::attack() {
    static int d = 0;
    if (isAttackable()) {
        PurPose::mMessage.push(mName + "のこうげき!!" + toString(d++));
    }
}

void Hero::swivel(const float& aAngleV, const float& aAngleH) {
    mEyeCamera->rotate(aAngleV, aAngleH);
}

void Hero::fumble(const int& aMoment) {
    mBackPack.selectChange(aMoment);
}

void Hero::setPosition(const KVector& aPosition) {
    Character::setPosition(aPosition);

    mEyeCamera->mPosition = mPosition;
}

void Hero::drawCircle() const {
    static const int QUALITY = 30;
    static const float BAND_WIDTH = 0.125;

    if (mTurn) {
        KVector position = mEyeCamera->mPosition;

        float ap = mActionPoint * mSpeed;


        mCircleTexture->bindON();
        glBegin(GL_QUAD_STRIP);
        for (int i = QUALITY; i >= 0; --i) {
            float theta = (float) i / QUALITY * Math::PI * 2;
            KVector v1(sin(theta) * ap, -BAND_WIDTH, cos(theta) * ap);
            KVector v2(sin(theta) * ap, BAND_WIDTH, cos(theta) * ap);
            glNormal3f(DEPLOYMENT(v1));
            glTexCoord2f(i, 0);
            glVertex3f(DEPLOYMENT(position - v1));
            glNormal3f(DEPLOYMENT(v2));
            glTexCoord2f(i, 1);
            glVertex3f(DEPLOYMENT(position - v2));
        }
        glEnd();
        mCircleTexture->bindOFF();
    }
}











