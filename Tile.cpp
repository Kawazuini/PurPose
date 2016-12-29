/**
 * @file   Tile.cpp
 * @brief  Tile
 * @author Maeda Takumi
 */
#include "Tile.h"

List<KPolygon*> Tile::sPolygons;

Tile::Tile(const KVector aVertex[4], const int& sepX, const int& sepY) {
    Vector<KVector> poly{
        aVertex[0], aVertex[1],
        aVertex[2], aVertex[3],
    };
    mPolygon = new KPolygon(poly);

    KVector width = (aVertex[3] - aVertex[0]) / sepX;
    KVector height = (aVertex[1] - aVertex[0]) / sepY;

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
    add();
}

Tile::~Tile() {
    remove();
    delete mPolygon;
}

void Tile::add() {
    sPolygons.push_back(mPolygon);
}

void Tile::remove() {
    for (auto i = sPolygons.begin(), i_e = sPolygons.end(); i != i_e; ++i) {
        if (*i == mPolygon) {
            sPolygons.erase(i);
            return;
        }
    }
}

void Tile::draw() const {
    glNormal3f(DEPLOYMENT(mPolygon->mNormal));

    for (auto i = mPolyList.begin(), i_e = mPolyList.end(); i != i_e; ++i) {
        glBegin(GL_POLYGON);
        glVertex3f(DEPLOYMENT(i->mVertex[0]));
        glVertex3f(DEPLOYMENT(i->mVertex[1]));
        glVertex3f(DEPLOYMENT(i->mVertex[2]));
        glVertex3f(DEPLOYMENT(i->mVertex[3]));
        glEnd();
    }
}

const List<KPolygon*>& Tile::polyList() {
    return sPolygons;
}

