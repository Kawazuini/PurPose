/**
 * @file Wall.cpp
 * @brief Wall
 */
#include "Wall.h"
#include "Map.h"

const int Wall::WALL_HEIGHT = 1;

Array<KPolygon*> Wall::sWalls;

Wall::Wall(const Map& aMap, const KRect& aWall) {
    static const float W_U = (float) WALL_HEIGHT / 2;
    static const float W_D = -W_U;

    static const int U = 1;
    static const int D = 2;
    static const int L = 4;
    static const int R = 8;
    int type;

    float scale = aMap.scale();
    const KVector X = KVector(scale, 0, 0);
    const KVector Y = KVector(0, scale, 0);
    const KVector Z = KVector(0, 0, scale);

    // 衝突判定の生成
    Array<KVector> vertex;
    if (aWall.height == -1) { // ↑
        type = U;
        vertex.push_back(KVector(aWall.x, W_D, aWall.y));
        vertex.push_back(KVector(aWall.x, W_U, aWall.y));
        vertex.push_back(KVector(aWall.right(), W_U, aWall.y));
        vertex.push_back(KVector(aWall.right(), W_D, aWall.y));
        for (auto i = vertex.begin(), i_e = vertex.end(); i != i_e; ++i) *i = *i * scale;
    } else if (aWall.height == 0) { // ↓
        type = D;
        vertex.push_back(KVector(aWall.x, W_D, aWall.y));
        vertex.push_back(KVector(aWall.right(), W_D, aWall.y));
        vertex.push_back(KVector(aWall.right(), W_U, aWall.y));
        vertex.push_back(KVector(aWall.x, W_U, aWall.y));
        for (auto i = vertex.begin(), i_e = vertex.end(); i != i_e; ++i) *i = (*i + KVector(0, 0, 1)) * scale;
    } else if (aWall.width == -1) { // ←
        type = L;
        vertex.push_back(KVector(aWall.x, W_D, aWall.y));
        vertex.push_back(KVector(aWall.x, W_D, aWall.bottom()));
        vertex.push_back(KVector(aWall.x, W_U, aWall.bottom()));
        vertex.push_back(KVector(aWall.x, W_U, aWall.y));
        for (auto i = vertex.begin(), i_e = vertex.end(); i != i_e; ++i) *i = *i * scale;
    } else if (aWall.width == 0) { // →
        type = R;
        vertex.push_back(KVector(aWall.x, W_D, aWall.y));
        vertex.push_back(KVector(aWall.x, W_U, aWall.y));
        vertex.push_back(KVector(aWall.x, W_U, aWall.bottom()));
        vertex.push_back(KVector(aWall.x, W_D, aWall.bottom()));
        for (auto i = vertex.begin(), i_e = vertex.end(); i != i_e; ++i) *i = (*i + KVector(1, 0, 0)) * scale;
    }
    sWalls.push_back(mPolygon = new KPolygon(vertex));

    // 描画頂点の決定
    KVector origin = mPolygon->mVertex[0];
    if (type & (U | D)) {
        mVertexSize = aWall.width;
        mVertex = new KVector[mVertexSize * 4];
        KVector* ver = mVertex;
        KVector shift = type == U ? Y : X;
        KVector subShift = type == U ? X : Y;
        for (int i = 0; i < aWall.width; ++i, ver += 4) {
            *(ver + 0) = origin;
            *(ver + 1) = origin + shift;
            *(ver + 2) = origin + shift + subShift;
            *(ver + 3) = origin + subShift;
            origin += X;
        }
    } else if (type & (L | R)) {
        mVertexSize = aWall.height;
        mVertex = new KVector[mVertexSize * 4];
        KVector* ver = mVertex;
        KVector shift = type == L ? Z : Y;
        KVector subShift = type == L ? Y : Z;
        for (int i = 0; i < aWall.height; ++i, ver += 4) {
            *(ver + 0) = origin;
            *(ver + 1) = origin + shift;
            *(ver + 2) = origin + shift + subShift;
            *(ver + 3) = origin + subShift;
            origin += Z;
        }
    }
}

Wall::Wall(const Wall& orig) {
    delete[] mVertex;
}

Wall::~Wall() {
}

void Wall::draw() const {
    glNormal3f(DEPLOYMENT(mPolygon->mNormal));

    KVector* vertex = mVertex;
    for (int i = 0; i < mVertexSize; ++i, vertex += 4) { // 四角形
        glBegin(GL_TRIANGLE_FAN);
        glVertex3f(DEPLOYMENT(*(vertex + 0)));
        glVertex3f(DEPLOYMENT(*(vertex + 1)));
        glVertex3f(DEPLOYMENT(*(vertex + 2)));
        glVertex3f(DEPLOYMENT(*(vertex + 3)));
        glEnd();
    }
}

const Array<KPolygon*>& Wall::wallList() {
    return sWalls;
}
