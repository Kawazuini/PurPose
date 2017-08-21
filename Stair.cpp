/**
 * @file   Stair.cpp
 * @brief  Stair
 * @author Maeda Takumi
 */
#include "Stair.h"

#include "GameState.h"

Stair::Stair(
        GameManager& aManager,
        const Event::EventFunction& aFuntion,
        const KVector& aPosition
        ) :
Event(aManager, aFuntion),
mPosition(aPosition),
mVertex({
    mPosition - KVector(0, MAP_SCALE / 2, 0),
    mPosition - KVector(MAP_SCALE / 3, 0, 0),
    mPosition + KVector(0, MAP_SCALE / 2, 0),
    mPosition + KVector(MAP_SCALE / 3, 0, 0)
}),
mTexture(64) {
    mTexture.drawRect(KRect(64, 64), 0x55ff0000);
    mTexture.drawRect(KRect(48, 48), 0x5500ff00);
    mTexture.drawRect(KRect(32, 32), 0x550000ff);
    mTexture.reflect();
}

void Stair::draw() const {
    glDisable(GL_CULL_FACE);

    KShading::PhongShading->ON();
    mTexture.bindON();
    glBegin(GL_POLYGON);

    glTexCoord2f(0, 0);
    glVertex(mVertex[0]);
    glTexCoord2f(0, 1);
    glVertex(mVertex[1]);
    glTexCoord2f(1, 1);
    glVertex(mVertex[2]);
    glTexCoord2f(1, 0);
    glVertex(mVertex[3]);
    glEnd();
    mTexture.bindOFF();
    KShading::PhongShading->ON();

    glEnable(GL_CULL_FACE);
}

void Stair::update(GameState& aState) {
    static const KQuaternion ROTATION(KVector(0, 1, 0), Math::PI / 120);

    Event::update(aState);

    rotate(ROTATION);
}

bool Stair::condition(const GameState& aState) const {
    static const float SCALE_SQUARE(MAP_SCALE * MAP_SCALE);

    return (mPosition - aState.mPlayer.position()).lengthSquared() < SCALE_SQUARE;
}

void Stair::rotate(const KQuaternion& aQuater) {
    for (auto i = mVertex.begin(), i_e = mVertex.end(); i != i_e; ++i) {
        *i -= mPosition;
        *i = i->rotate(aQuater);
        *i += mPosition;
    }
}

const KVector& Stair::position() const {
    return mPosition;
}

