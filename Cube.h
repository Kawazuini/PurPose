/**
 * @file   Cube.h
 * @brief  Cube
 * @author Maeda Takumi
 */
#ifndef CUBE_H
#define CUBE_H

#include "main.h"

/**
 * @brief  \~english  regular hexahedron
 * @brief  \~japanese 正六面体
 * @author Maeda Takumi
 */
class Cube : public KUpdater, public KDrawer {
protected:
    /** @brief 重心頂点番号 */ static const int CENTROID;
    /** @brief 描画頂点番号 */ static const int DRAW_VERTEX_INDEX[6][4];
    /** @brief 対角頂点番号 */ static const int DIAGONAL[8];
    /** @brief 隣接頂点番号 */ static const int NEXT_INDEX[8][3];
    /** @brief 頂点を含む面構成頂点番号(描画頂点番号を参照) */
    static const int APEX_PLANE[8][3];

    /** @brief 質量 */ float mMass;
    /** @brief 頂点 */ KVector mVertex[9];
    /** @brief 法線 */ KVector mNormal[6];
    /** @brief 外力 */ KVector mForce;
    /** @brief 速度 */ KVector mVelocity;
    /** @brief 回転情報             */ KQuaternion mRotation;
    /** @brief 重心から頂点への距離 */ float mRadius;
    /** @brief 衝突頂点番号         */ int mHitIndex;

    /** @brief 衝突ポリゴン */ KPolygon mHitPolygon;

    bool mGravity;
    bool mCollider;
    bool mRotatable;
public:
    Cube(const float& aScale, const KVector& aPosition = KVector());
    virtual ~Cube() = default;

    /**
     * @brief \~english  add myself to (drawer & updater) list.
     * @brief \~japanese リストに自分を追加します。
     */
    void add();
    /**
     * @brief \~english  remove myself form (drawer & updater) list.
     * @brief \~japanese リストから自分を消します。
     */
    void remove();
    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    virtual void draw() const override;
    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    virtual void update() override;

    /**
     * @brief 立方体を移動させる
     * @param aVec 移動量
     */
    void translate(const KVector& aVec);
    /**
     * @brief 立方体を回転させる
     * @param aOrigin 回転原点
     * @param aQuater 回転情報
     */
    void rotate(KVector aOrigin, const KQuaternion& aQuater);
    /**
     * @brief 力を掛ける
     * @param aForce 力
     */
    void applyForce(const KVector& aForce);
    /**
     * @brief 加速させる
     * @param aAccele 加速度
     */
    void accele(const KVector& aAccele);

    /**
     * \~english
     * @brief  get centroid coordinate.
     * @return centroid coordinate
     * \~japanese
     * @brief  重心座標を取得します。
     * @return 重心座標
     */
    KVector position() const;
    /**
     * \~english
     * @brief  get distance of each vertex from the centroid coordinate
     * @return distance of each vertex from the centroid coordinate
     * \~japanese
     * @brief  重心からの各頂点の距離を取得します
     * @return 重心からの各頂点の距離
     */
    float radius() const;
};

#endif /* CUBE_H */
