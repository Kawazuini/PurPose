/**
 * @file Dice.cpp
 * @brief Dice
 */
#include "Dice.h"

Dice::Dice(const KVector * const aMaterialPoints, const KVector& aVec)
: KCube(aMaterialPoints), mTexture(NULL) {
    KVector rand(float(random(10)) - 5, float(random(10)) - 5, float(random(10)) - 5);
    float moment = float(random(90)) / 180 * Math::PI;

    mRotation = KQuaternion(rand, moment);

    mVelocity = KVector(0, 10, 0);
    translate(mVelocity);
}

Dice::Dice(const KVector& aCentroid, const float& aSideLength, const KTexture& aTexture)
: KCube(aCentroid, aSideLength), mTexture(&aTexture) {
    KVector rand(float(random(10)) - 5, float(random(10)) - 5, float(random(10)) - 5);
    float moment = float(random(90)) / 180 * Math::PI;

    mRotation = KQuaternion(rand, moment);
}

void Dice::draw() const {
    mTexture->bindON();
    static int tex[4][2] = {0, 0, 1, 0, 1, 1, 0, 1};
    for (int i = 0; i < 6; ++i) { // 六個の面
        KVector p1 = mVertex[VERTEX_INDEX[i][1]] - mVertex[VERTEX_INDEX[i][0]];
        KVector p2 = mVertex[VERTEX_INDEX[i][2]] - mVertex[VERTEX_INDEX[i][1]];
        KVector p3 = p1.cross(p2);

        glBegin(GL_POLYGON);
        glNormal3d(DEPLOYMENT(p1.cross(p2)));
        for (int j = 0; j < 4; ++j) { // 四角形
            glTexCoord2f(tex[j][0], tex[j][1]);
            glVertex3d(DEPLOYMENT(mVertex[VERTEX_INDEX[i][j]]));
        }
        glEnd();
    }
    mTexture->bindOFF();
}

void Dice::update() {
    KCube::update();
}
