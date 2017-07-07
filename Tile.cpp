/**
 * @file   Tile.cpp
 * @brief  Tile
 * @author Maeda Takumi
 */
#include "Tile.h"

#include "GameState.h"

Vector<Tile*> Tile::sDrawList;

Tile::Tile(const Vector<KVector>& aVertex, const int& sepX, const int& sepY) :
mPolygon(aVertex),
mPosition(mPolygon.mVertex[0]),
mNormal(mPolygon.mNormal),
mDistance(0.0f) {
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

    sDrawList.push_back(this);
    KDrawer::remove();
}

Tile::~Tile() {
    for (auto i = sDrawList.begin(), i_e = sDrawList.end(); i != i_e; ++i) {
        if (*i == this) {
            sDrawList.erase(i);
            break;
        }
    }
}

void Tile::draw() const {
    if (mNormal.x != 0) {
        CthulhuXShading->ON();
    } else if (mNormal.y != 0) {
        CthulhuYShading->ON();
    } else if (mNormal.z != 0) {
        CthulhuZShading->ON();
    }

    glNormal3f(DEPLOY_VEC(mPolygon.mNormal));
    for (auto i = mPolyList.begin(), i_e = mPolyList.end(); i != i_e; ++i) {
        glBegin(GL_POLYGON);
        glVertex3f(DEPLOY_VEC(i->mVertex[0]));
        glVertex3f(DEPLOY_VEC(i->mVertex[1]));
        glVertex3f(DEPLOY_VEC(i->mVertex[2]));
        glVertex3f(DEPLOY_VEC(i->mVertex[3]));
        glEnd();
    }
}

void Tile::TILE_DRAW(const GameState& aState) {
    static KVector prePosition; // 1F前のカメラ位置
    
    const KCamera& camera(aState.mCamera.camera());
    const KVector & cameraPosition(camera.position());

    if (prePosition != cameraPosition) {
        prePosition = cameraPosition;
        for (Tile* i : sDrawList) { // カメラとの距離の計算
            i->mDistance = (i->mPosition - cameraPosition).dot(i->mNormal);
        }
        // カメラから近い順に並べる(遠景の描画をデプスバッファにより省く)
        std::sort(sDrawList.begin(), sDrawList.end(),
                [](const Tile* x, const Tile * y) -> bool {
                    return x->mDistance < y->mDistance;
                }
        );
    }

    for (Tile* i : sDrawList) {
        if (camera.isInCamera(i->mNormal) && camera.isInCamera(i->mPolygon.mVertex)) {
            i->draw();
        }
    }
}

