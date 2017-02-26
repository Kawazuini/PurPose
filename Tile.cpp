/**
 * @file   Tile.cpp
 * @brief  Tile
 * @author Maeda Takumi
 */
#include "Tile.h"

Tile::Tile(const Vector<KVector>& aVertex, const int& sepX, const int& sepY) :
mPolygon(aVertex) {

    KVector width((aVertex[3] - aVertex[0]) / sepX);
    KVector height((aVertex[1] - aVertex[0]) / sepY);

    for (int i = 0; i < sepX; ++i) {
        for (int j = 0; j < sepY; ++j) {
            Vector<KVector> list{
                aVertex[0] + width * (i + 0) + height * (j + 0),
                aVertex[0] + width * (i + 0) + height * (j + 1),
                aVertex[0] + width * (i + 1) + height * (j + 1),
                aVertex[0] + width * (i + 1) + height * (j + 0),
            };
            mPolyList.push_back(KPolygon(list));
        }
    }
}

void Tile::draw() const {
    if (KCamera::isInCamera(mPolygon.mNormal)) {
        CthulhuShading->ON();

        glNormal3f(DEPLOYMENT(mPolygon.mNormal));

        for (auto i = mPolyList.begin(), i_e = mPolyList.end(); i != i_e; ++i) {
            glBegin(GL_POLYGON);
            glVertex3f(DEPLOYMENT(i->mVertex[0]));
            glVertex3f(DEPLOYMENT(i->mVertex[1]));
            glVertex3f(DEPLOYMENT(i->mVertex[2]));
            glVertex3f(DEPLOYMENT(i->mVertex[3]));
            glEnd();
        }
        PhongShading->ON();
    }
}

