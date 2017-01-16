/**
 * @file   Cube.h
 * @brief  Cube
 * @author Maeda Takumi
 */
#ifndef CUBE_H
#define CUBE_H

#include "Object.h"

/**
 * @brief  \~english  regular hexahedron
 * @brief  \~japanese 正六面体
 * @author Maeda Takumi
 */
class Cube : public KDrawer, public Object {
protected:
    /** @brief 重心頂点番号 */ static const int CENTROID;
    /** @brief 描画頂点番号 */ static const int DRAW_VERTEX_INDEX[6][4];

    /**
     * @brief \~english
     * @brief \~japanese 面上の対角点
     */
    static const int SURFACE_DIAGONAL_POINT[8][3];
    /** @brief 頂点を含む面構成頂点番号(描画頂点番号を参照) */
    static const int APEX_PLANE[8][3];

    /** @brief 質量 */ float mMass;
    /** @brief 頂点 */ KVector mVertex[9];
    /**
     * @brief \~english  Center coordinate before 1F
     * @brief \~japanese 1F前の中心座標
     */
    KVector mPrePosition;
    /** @brief 法線 */ KVector mNormal[6];
    /** @brief 重心から頂点への距離 */ float mRadius;
    /** @brief 衝突頂点番号         */ int mHitIndex;

    /** @brief 外力 */ KVector mForce;
    /** @brief 速度 */ KVector mVelocity;
    /** @brief 回転情報             */ KQuaternion mRotation;


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
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態の情報
     * 適当な物理演算を行います。<br>
     * 反射係数や摩擦係数などの物理情報は将来的にはGameStateに含まれる予定です。<br>
     * 物理演算が気に入らない場合はmRotateableをfalseにすると改善されるかもしれません。
     */
    void update(const GameState& aState) override;


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
    const KVector& position() const;
    /**
     * \~english
     * @brief  get distance of each vertex from the centroid coordinate
     * @return distance of each vertex from the centroid coordinate
     * \~japanese
     * @brief  重心からの各頂点の距離を取得します
     * @return 重心からの各頂点の距離
     */
    const float& radius() const;
};

#endif /* CUBE_H */
