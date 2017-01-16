/**
 * @file   Cube.cpp
 * @brief  Cube
 * @author Maeda Takumi
 */
#include "Cube.h"

#include "Tile.h"

const int Cube::CENTROID = 8;

const int Cube::DRAW_VERTEX_INDEX[6][4] = {
    {5, 1, 3, 7},
    {0, 4, 6, 2},
    {3, 2, 6, 7},
    {0, 1, 5, 4},
    {4, 5, 7, 6},
    {1, 0, 2, 3},
};

const int Cube::SURFACE_DIAGONAL_POINT[8][3] = {
    {3, 5, 6},
    {2, 4, 7},
    {1, 4, 7},
    {0, 5, 6},
    {1, 2, 7},
    {0, 3, 6},
    {0, 3, 5},
    {1, 2, 4},
};

const int Cube::APEX_PLANE[8][3] = {
    {1, 3, 5},
    {0, 3, 5},
    {1, 2, 5},
    {0, 2, 5},
    {1, 3, 4},
    {0, 3, 4},
    {1, 2, 4},
    {0, 2, 4},
};

Cube::Cube(const float& aScale, const KVector& aPosition) :
mMass(1),
mVertex({
    KVector(0, 0, 0) * aScale,
    KVector(1, 0, 0) * aScale,
    KVector(0, 1, 0) * aScale,
    KVector(1, 1, 0) * aScale,
    KVector(0, 0, 1) * aScale,
    KVector(1, 0, 1) * aScale,
    KVector(0, 1, 1) * aScale,
    KVector(1, 1, 1) * aScale,
    KVector(1, 1, 1) * aScale / 2
}),
mPrePosition(aPosition),
mNormal({
    KVector(1.00f, 0.00f, 0.00f),
    KVector(-1.0f, 0.00f, 0.00f),
    KVector(0.00f, 1.00f, 0.00f),
    KVector(0.00f, -1.0f, 0.00f),
    KVector(0.00f, 0.00f, 1.00f),
    KVector(0.00f, 0.00f, -1.0f)
}),
mRadius((mVertex[0] - mVertex[CENTROID]).length()),
mHitIndex(CENTROID),
mGravity(true),
mCollider(true),
mRotatable(true) {
    translate(aPosition);
    rotate(mVertex[CENTROID], KQuaternion(KVector(0, 1, 0), Math::PI / 4));
    rotate(mVertex[CENTROID], KQuaternion(KVector(1, 0, 0), Math::PI / 4));
    mRotation = KQuaternion(KVector(0, 1, 0), Math::PI / 30);
}

void Cube::add() {
    KDrawer::add();
    Object::add();
}

void Cube::remove() {
    KDrawer::remove();
    Object::remove();
}

void Cube::draw() const {
    for (int i = 0; i < 6; ++i) { // 六個の面
        glBegin(GL_POLYGON);
        glNormal3f(DEPLOYMENT(mNormal[i]));
        for (int j = 0; j < 4; ++j) { // 四角形
            glVertex3f(DEPLOYMENT(mVertex[DRAW_VERTEX_INDEX[i][j]]));
        }
        glEnd();
    }
}

void Cube::update(const GameState& aState) {
    static float e = 0.5; // 衝突が起きた面の反発係数
    static float q = 0.5; // 摩擦係数

    KVector G = KVector(0, -9.80665, 0); // 重力加速度
    int F = 50; // 秒間更新数

    { // 回転を含まない物理運動
        if (mGravity) applyForce(G * mMass); // 重力を受ける
        // 速度に変換 -> 座標移動
        accele((mForce / mMass) / F);
        translate(mVertex[CENTROID] + mVelocity / F);
    }

    KVector centroid(mVertex[CENTROID]);
    KVector moveDiff(centroid - mPrePosition); // 移動量
    if (mCollider) { // 衝突判定
        List<KPolygon*> walls = Tile::polyList();
        for (KPolygon* i : walls) {
            KVector normal(i->mNormal);
            KVector veloP(moveDiff.extractParallel(normal));
            if (i->operator*(KSegment(
                    mPrePosition + (normal * mRadius),
                    mPrePosition - (normal * mRadius) + veloP
                    ))) {
                KVector outward[8]; // 中心座標からの各頂点へのベクトル
                for (int j = 0; j < 8; ++j) {
                    outward[j] = mVertex[j] - centroid;
                }

                float r = 0; // 頂点の内で最も面に近い距離
                for (int j = 0; j < 8; ++j) {
                    float d = outward[j].dot(-normal); // 頂点と面との距離
                    if (r < d) {
                        r = d;
                        mHitIndex = j;
                        mHitPolygon = *i;
                    }
                }

                float s = (centroid - i->mVertex[0]).dot(normal); // 重心から面までの距離
                if (s < r) { // 面にめり込んでいる
                    // 面に沿うように修正
                    translate(centroid + normal * (r - s));

                    // 衝突が起きた場合速度ベクトルを反射させる
                    if (Math::PI / 2 < mVelocity.angle(normal)) { // 入射角が鋭角の時のみ反射
                        float a = (-mVelocity).dot(normal); // 反射量
                        mVelocity += (normal * 2 * a);
                        mVelocity *= e;
                    }
                    break;
                } else mHitIndex = CENTROID;
            }
        }
    }

    if (mRotatable) { // 回転運動
        if (mHitIndex != CENTROID) { // 衝突している
            KVector centroid(mVertex[CENTROID]);

            KVector diff((centroid - mPrePosition).extractVertical(mHitPolygon.mNormal)); // 移動差分(慣性)
            KVector friction(-diff.normalization() * (q * mMass * G.length())); // 摩擦
            KVector rotateAxis = diff.cross(mHitPolygon.mNormal); // 回転軸
            float rotateMoment = (diff - friction).length() / (mRadius * F * F); // 回転量
            mRotation *= KQuaternion(rotateAxis, rotateMoment);


            if (Math::approximately(mRotation.t, 1.0f)) { // 回転が弱い場合、衝突面に沿う
                int nearIndex; // 衝突面から最も近い頂点番号
                float nearSquare = 0xfffffff;
                for (int i = 0; i < 3; ++i) {
                    float dist = (mVertex[SURFACE_DIAGONAL_POINT[mHitIndex][i]] - mVertex[mHitIndex]).extractParallel(mHitPolygon.mNormal).lengthSquared();
                    if (dist < nearSquare) {
                        nearIndex = SURFACE_DIAGONAL_POINT[mHitIndex][i];
                        nearSquare = dist;
                    }
                }
                KVector diagonal(mVertex[nearIndex] - mVertex[mHitIndex]);
                KVector hitLine(diagonal.extractVertical(mHitPolygon.mNormal));
                rotate(mVertex[mHitIndex], diagonal.roundAngle(hitLine) / Math::PI);
            }
        }
        mRotation *= -mRotation / F; // 回転減衰
        rotate(mVertex[mHitIndex], mRotation);
    }

    // std::cout << " x : " << mVertex[8].x << " y : " << mVertex[8].y << " z : " << mVertex[8].z << std::endl;
    // std::cout << " x : " << mVelocity.x << " y : " << mVelocity.y << " z : " << mVelocity.z << std::endl;
    // std::cout << "t" << mRotation.t << " x : " << mRotation.x << " y : " << mRotation.y << " z : " << mRotation.z << std::endl;

    mPrePosition = mVertex[CENTROID];
    mForce = KVector(); // 力は慣性により保存されない
}

void Cube::translate(const KVector& aVec) {
    KVector move(aVec - mVertex[CENTROID]);

    for (int i = 0; i < 9; ++i) mVertex[i] += move;
}

void Cube::rotate(KVector aOrigin, const KQuaternion& aQuater) {
    // 頂点座標の回転
    for (int i = 0; i < 9; ++i) {
        mVertex[i] -= aOrigin;
        mVertex[i] = mVertex[i].rotate(aQuater);
        mVertex[i] += aOrigin;
    }
    // 法線の回転
    for (int i = 0; i < 6; ++i) {

        mNormal[i] = mNormal[i].rotate(aQuater);
    }
}

void Cube::applyForce(const KVector& aForce) {

    mForce += aForce;
}

void Cube::accele(const KVector& aAccele) {

    mVelocity += aAccele;
}

const KVector& Cube::position() const {

    return mVertex[CENTROID];
}

const float& Cube::radius() const {
    return mRadius;
}

