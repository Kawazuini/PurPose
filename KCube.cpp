/**
 * @file KCube.cpp
 * @brief KCube
 */
#include "KCube.h"

#include "KWorld.h"

const int KCube::CENTROID = 8;

const int KCube::VERTEX_INDEX[6][4] = {
    {4, 5, 7, 6},
    {6, 2, 0, 4},
    {1, 5, 4, 0},
    {6, 7, 3, 2},
    {5, 1, 3, 7},
    {2, 3, 1, 0},
};

const int KCube::DIAGONAL[8] = {6, 7, 4, 5, 2, 3, 0, 1};

const int KCube::NEXT_INDEX[8][3] = {
    {0, 3, 4},
    {0, 2, 4},
    {1, 3, 6},
    {0, 2, 7},
    {0, 5, 7},
    {1, 4, 6},
    {2, 5, 7},
    {3, 4, 6},
};

const int KCube::APEX_PLANE[8][3] = {
    {0, 1, 2},
    {0, 2, 4},
    {0, 1, 3},
    {0, 3, 4},
    {1, 2, 5},
    {2, 4, 5},
    {1, 3, 5},
    {3, 4, 5},
};

KCube::KCube(const KVector * const aVertex) :
mHitPolygon(Array<KVector>{KVector()}) {
    mMass = 1;

    mVertex[8] = KVector(); // 重心を求める
    for (int i = 0; i < 8; ++i) mVertex[CENTROID] += (mVertex[i] = aVertex[i]);
    mVertex[CENTROID] /= 8;

    mRadius = (mVertex[0] - mVertex[CENTROID]).length();
    mHitIndex = CENTROID;
}

KCube::KCube(const KVector& aCentroid, const float& aSideLength)
: mHitPolygon(Array<KVector>{KVector()}) {
    mMass = 1;

    float planeLength = aSideLength / 2; // 重心から面までの距離
    mVertex[0] = KVector(-planeLength, -planeLength, -planeLength);
    mVertex[1] = KVector(+planeLength, -planeLength, -planeLength);
    mVertex[2] = KVector(-planeLength, +planeLength, -planeLength);
    mVertex[3] = KVector(+planeLength, +planeLength, -planeLength);
    mVertex[4] = KVector(-planeLength, -planeLength, +planeLength);
    mVertex[5] = KVector(+planeLength, -planeLength, +planeLength);
    mVertex[6] = KVector(-planeLength, +planeLength, +planeLength);
    mVertex[7] = KVector(+planeLength, +planeLength, +planeLength);
    mVertex[8] = KVector();
    translate(aCentroid);

    mRadius = (mVertex[0] - mVertex[CENTROID]).length();
    mHitIndex = CENTROID;

    mGravity = mCollider = mRotatable = true;
}

void KCube::translate(const KVector& aVec) {
    for (int i = 0; i < 9; ++i) mVertex[i] += aVec;
}

void KCube::rotate(KVector aOrigin, const KQuaternion& aQuater) {
    // 頂点座標の回転
    for (int i = 0; i < 9; ++i) {
        mVertex[i] -= aOrigin;
        mVertex[i] = mVertex[i].rotate(aQuater);
        mVertex[i] += aOrigin;
    }
}

void KCube::applyForce(const KVector& aForce) {
    mForce += aForce;
}

void KCube::accele(const KVector& aAccele) {
    mVelocity += aAccele;
}

void KCube::draw() const {
    for (int i = 0; i < 6; ++i) { // 六個の面
        KVector p1 = mVertex[VERTEX_INDEX[i][1]] - mVertex[VERTEX_INDEX[i][0]];
        KVector p2 = mVertex[VERTEX_INDEX[i][2]] - mVertex[VERTEX_INDEX[i][1]];
        KVector p3 = p1.cross(p2);

        glBegin(GL_POLYGON);
        glNormal3d(DEPLOYMENT(p1.cross(p2)));
        for (int j = 0; j < 4; ++j) { // 四角形
            glVertex3d(DEPLOYMENT(mVertex[VERTEX_INDEX[i][j]]));
        }
        glEnd();
    }
}

void KCube::update() {
    static float e = 0.5; // 衝突が起きた面の反発係数
    static float q = 0.5; // 摩擦係数

    KVector G = KWorld::sAcceleGravity; // 重力加速度
    int F = KWorld::sFramePerSecond; // 秒間更新数

    { // 回転を含まない物理運動
        if (mGravity) applyForce(G * mMass); // 重力を受ける
        // 速度に変換 -> 座標移動
        accele((mForce / mMass) / F);
        translate(mVelocity / F);
    }

    if (mRotatable) { // 回転運動
        if (mHitIndex != CENTROID) { // 地面に衝突している
            KSegment segment(mVertex[CENTROID], mVertex[CENTROID] + G.normalization() * (mRadius + 1)); // 重心から重力を垂らす
            KVector gravityPoint = KVector(); // 面と重力線の交点
            for (int i = 0; i < 3; ++i) {
                KPolygon polygon({
                    mVertex[VERTEX_INDEX[APEX_PLANE[mHitIndex][i]][0]],
                    mVertex[VERTEX_INDEX[APEX_PLANE[mHitIndex][i]][1]],
                    mVertex[VERTEX_INDEX[APEX_PLANE[mHitIndex][i]][2]],
                    mVertex[VERTEX_INDEX[APEX_PLANE[mHitIndex][i]][3]]
                }); // 衝突点を含む面の作成
                if (polygon * segment) {
                    gravityPoint = polygon.hitPoint(segment);
                    break;
                }
            }
            if (!(gravityPoint.isZero())) { // 地面に沿うように倒れる
                KVector normal = mHitPolygon.mNormal;
                KVector fallLine = gravityPoint - mVertex[mHitIndex]; // 回転原点から重力作用点までのベクトル
                KVector fallAxis = fallLine.cross(normal); // 回転軸
                float fallMoment = ((G * mMass).extractVertical(fallLine)).length() / (mRadius * F * F); // 回転量
                float angle = fallLine.angle(KVector(fallLine.extractVertical(normal))); // 地面との角度
                if (Math::approximately(mRotation.t, 1.0f)) { // 回転が弱い場合地面に沿う
                    rotate(mVertex[mHitIndex], KQuaternion(fallAxis, angle));
                } else {
                    rotate(mVertex[mHitIndex], mRotation);
                }
                mRotation = mRotation * KQuaternion(fallAxis, fallMoment);
                mVelocity = mVelocity.rotate(mRotation);
            }
            float attenuate = q * G.length() / (mRadius * F * F); // 摩擦による減衰角度
            KVector axis = KVector(mRotation).normalization();
            mRotation = mRotation * KQuaternion(-axis, attenuate);
        } else { // 空中回転
            rotate(mVertex[CENTROID], mRotation);
        }
    }
    // mRotation = mRotation.slerp(KQuaternion(1, 0, 0, 0), 0.011);

    if (mCollider) { // 地面との衝突判定
        KPolygon grand(Array<KVector>{
            KVector(10000, 0, 10000),
            KVector(10000, 0, -10000),
            KVector(-10000, 0, -10000),
            KVector(-10000, 0, 10000),
        });

        /*
                KPolygon grand(List<KVector>{
                    KVector(100, 10, 100),
                    KVector(100, 10, -100),
                    KVector(-100, -10, 100),
                    KVector(-100, -10, -100)
                });
         */

        KVector point = grand.mVertex[0];
        KVector normal = grand.mNormal;

        KVector outward[8]; // 中心座標からの各頂点へのベクトル
        for (int i = 0; i < 8; ++i) outward[i] = mVertex[i] - mVertex[CENTROID];

        float s = (mVertex[CENTROID] - point).dot(normal); // 重心から面までの距離
        float r = 0; // 重心から頂点までの距離を法線に射影
        for (int i = 0; i < 8; ++i) {
            float d = outward[i].dot(-normal); // 正負を反転させる(地面に向かうのが正)
            if (r < d) {
                r = d;
                mHitIndex = i;
                mHitPolygon = grand;
            }
        }
        if (s < r) { // 面にめり込んでいる
            // 面に沿うように修正
            translate(normal * (r - s));

            // 衝突が起きた場合速度ベクトルを反射させる
            if (Math::PI / 2 < mVelocity.angle(normal)) { // 入射角が鋭角の時のみ反射
                float a = (-mVelocity).dot(normal);
                mVelocity = mVelocity + (normal * 2 * a);
                mVelocity *= e;
            }
        } else mHitIndex = CENTROID;
    }

    // std::cout << " x : " << mVertex[8].x << " y : " << mVertex[8].y << " z : " << mVertex[8].z << std::endl;
    // std::cout << " x : " << mVelocity.x << " y : " << mVelocity.y << " z : " << mVelocity.z << std::endl;
    // std::cout << "t" << mRotation.t << " x : " << mRotation.x << " y : " << mRotation.y << " z : " << mRotation.z << std::endl;

    mForce = KVector(); // 力は慣性により保存されない
}
