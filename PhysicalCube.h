/**
 * @file   PhysicalCube.h
 * @brief  PhesicalCube
 * @author Maeda Takumi
 */
#ifndef PHYSICALCUBE_H
#define PHYSICALCUBE_H

#include "Object.h"

class Character;

/**
 * @brief  \~english  cube with physical behavior
 * @brief  \~japanese 物理的挙動を持った立方体
 * @author \~ Maeda Takumi
 */
class PhysicalCube : public KDrawCube, public Object {
protected:
    /**
     * @brief \~english  diagonal point on surface
     * @brief \~japanese 面上の対角点
     */
    static const int DIAGONAL_POINT_ON_SURFACE[8][3];

    /**
     * @brief \~english  mass
     * @brief \~japanese 質量
     */
    float mMass;
    /**
     * @brief \~english  Center coordinate before 1F
     * @brief \~japanese 1F前の中心座標
     */
    KVector mPrePosition;
    /**
     * @brief \~english  collision vertex number
     * @brief \~japanese 衝突頂点番号
     */
    int mHitIndex;
    /**
     * @brief \~english  collision polygon
     * @brief \~japanese 衝突ポリゴン
     */
    KPolygon mHitPolygon;

    /**
     * @brief \~english  external force
     * @brief \~japanese 外力
     */
    KVector mForce;
    /**
     * @brief \~english  velocity
     * @brief \~japanese 速度
     */
    KVector mVelocity;
    /**
     * @brief \~english  rotation information
     * @brief \~japanese 回転情報
     */
    KQuaternion mRotation;

    /**
     * @brief \~english  whether moved
     * @brief \~japanese 動いているか
     */
    bool mMove;
    /**
     * @brief \~english  collision Character for each frame
     * @brief \~japanese フレームごとの衝突キャラクター
     */
    Vector<Character*> mHitCharacter;
public:
    /**
     * @brief \~english  whether receive gravity
     * @brief \~japanese 重力を受けるか
     */
    bool mGravity;
    /**
     * @brief \~english  whether collision determination is performed
     * @brief \~japanese 衝突判定を行うか
     */
    bool mCollider;
    /**
     * @brief \~english  whther rotate
     * @brief \~japanese 回転を行うか
     */
    bool mRotatable;
    /**
     * @brief \~english  whther reflect on wall
     * @brief \~japanese 壁との反射を行うか
     */
    bool mReflect;

    /**
     * \~english
     * @brief generate cube.
     * @param aScale    scale
     * @param aMass     mass
     * @param aPosition generating coordinate
     * \~japanese
     * @brief 立方体を生成します。
     * @param aScale    大きさ
     * @param aMass     質量
     * @param aPosition 生成座標
     */
    PhysicalCube(
            const float& aScale,
            const float& aMass,
            const KVector& aPosition = KVector()
            );
    virtual ~PhysicalCube() = default;

    /**
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief   更新処理
     * @param   aState ゲーム状態の情報
     * @details 適当な物理演算を行います。<br>
     * 反射係数や摩擦係数などの物理情報は将来的にはGameStateに含まれる予定です。<br>
     * 物理演算が気に入らない場合はmRotateableをfalseにすると改善されるかもしれません。
     */
    void update(GameState& aState) override;

    /**
     * @brief \~english  resolve conflict.
     * @brief \~japanese 衝突を解決します。
     */
    void resolveConflict(const GameState& aState);
    /**
     * @brief \~english  rotational movement.
     * @brief \~japanese 回転運動を行います。
     */
    void gyro(const GameState& aState);

    /**
     * \~english
     * @brief apply force
     * @param aForce force
     * \~japanese
     * @brief 力を掛ける
     * @param aForce 力
     */
    void applyForce(const KVector& aForce);

    /**
     * \~english
     * @brief set new coordinate.
     * @param aPosition new coordinate
     * \~japanese
     * @brief 新しく座標を設定します。
     * @param aPosition 新しい座標
     */
    void setPosition(const KVector& aPosition);

    /**
     * \~english
     * @brief  get whether move
     * @return whether move
     * \~japanese
     * @brief  動いているかを取得します。
     * @return 動いているか
     */
    const bool& isMove() const;
    /**
     * \~english
     * @brief  get whether hit wall
     * @return whether hit wall
     * \~japanese
     * @brief  壁に衝突しているかを取得します。
     * @return 壁に衝突しているか
     */
    bool isHitWall() const;
    /**
     * \~english
     * @brief  get conflicting Characters in order.
     * @return conflicting Character
     * \~japanese
     * @brief  衝突したキャラクターを順番に取得します。。
     * @return 衝突キャラクター
     */
    const Vector<Character*>& hitCharacter() const;

    /**
     * \~english
     * @brief  get speed
     * @return speed
     * \~japanese
     * @brief  速さを取得します。
     * @return 速さ
     */
    float speed() const;
    /**
     * \~english
     * @brief  get impulse.
     * @return impulse
     * \~japanese
     * @brief  力積を取得します。
     * @return 力積
     */
    float impulse() const;
};

#endif /* PHYSICALCUBE_H */

