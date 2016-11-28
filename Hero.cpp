/**
 * @file Hero.cpp
 * @brief Hero
 */
#include "Hero.h"

#include "Map.h"
#include "Wall.h"

#include "HPotion.h"
#include "TelePotion.h"

Hero::Hero() {
    KDrawer::remove();

    mSpeed = 1;
    mSize = 1;
    mEyeCamera = new KFPSCamera();
    mDevice = new KGLUI(*mEyeCamera);

    mActionPoint = 0;

    mAgility = 12;

    mMoveCost = 1;

    // KImage img(64, 64);
    // img.drawImage(IMG_CHARSET_BIG, CHARSET_BIG.charPosition("|"), KVector(16));

    mCircleTexture = new KTexture(64);

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

bool Hero::move(const KVector& aMovement) {
    KVector moving = mEyeCamera->convertDirection(aMovement).normalization() * mSpeed;
    if (Character::move(moving)) {
        mEyeCamera->mPosition = mPosition;
        mEyeCamera->set();
        return true;
    }
    return false;
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











