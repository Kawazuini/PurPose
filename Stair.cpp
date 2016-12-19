/**
 * @file   Stair.cpp
 * @brief  Stair
 * @author Maeda Takumi
 */
#include "Stair.h"

#include "Map.h"

Stair::Stair(const KVector& aPosition) {
    mPosition = aPosition;

    mVertex.push_back(mPosition - KVector(0, MAP_SCALE / 2, 0));
    mVertex.push_back(mPosition - KVector(MAP_SCALE / 3, 0, 0));
    mVertex.push_back(mPosition + KVector(0, MAP_SCALE / 2, 0));
    mVertex.push_back(mPosition + KVector(MAP_SCALE / 3, 0, 0));

    mTexture = new KTexture(64);
    mTexture->drawRect(KRect(64, 64), 0x55ff0000);
    mTexture->drawRect(KRect(48, 48), 0x5500ff00);
    mTexture->drawRect(KRect(32, 32), 0x550000ff);
    mTexture->reflect();
}

Stair::~Stair() {
    delete mTexture;
}

void Stair::rotate(const KQuaternion& aQuater) {
    for (auto i = mVertex.begin(), i_e = mVertex.end(); i != i_e; ++i) {
        *i -= mPosition;
        *i = i->rotate(aQuater);
        *i += mPosition;
    }
}

void Stair::update() {
    static const KQuaternion ROTATION(KVector(0, 1, 0), Math::PI / 120);
    rotate(ROTATION);
}

void Stair::draw() const {
    glDisable(GL_CULL_FACE);
    glDisable(GL_LIGHTING);

    mTexture->bindON();
    glBegin(GL_POLYGON);

    glTexCoord2f(0, 0);
    glVertex3f(DEPLOYMENT(mVertex[0]));
    glTexCoord2f(0, 1);
    glVertex3f(DEPLOYMENT(mVertex[1]));
    glTexCoord2f(1, 1);
    glVertex3f(DEPLOYMENT(mVertex[2]));
    glTexCoord2f(1, 0);
    glVertex3f(DEPLOYMENT(mVertex[3]));
    glEnd();
    mTexture->bindOFF();

    glEnable(GL_LIGHTING);
    glEnable(GL_CULL_FACE);
}

KVector Stair::position() const {
    return mPosition;
}

