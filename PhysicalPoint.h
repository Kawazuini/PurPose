/**
 * @file   PhysicalPoint.cpp
 * @brief  PhysicalPoint
 * @author Maeda Takumi
 */
#ifndef PHYSICALPOINT_H
#define PHYSICALPOINT_H

#include "Object.h"

/**
 * @brief  \~english  point with physical behavior
 * @brief  \~japanese 物理的挙動を持った点(質点)
 * @author \~ Maeda Takumi
 */
class PhysicalPoint : public Object {
public:
    /**
     * @brief \~english  dummy coordinates
     * @brief \~japanese ダミー座標
     */
    KVector mDummy;
    /**
     * @brief \~english  coordinate
     * @brief \~japanese 座標
     */
    KVector& mPosition;
    /**
     * @brief \~english  coordinate before 1F
     * @brief \~japanese 1F前の座標
     */
    KVector mPrePosition;

    /**
     * @brief \~english  force
     * @brief \~japanese 力
     */
    KVector mForce;
    /**
     * @brief \~english  velocity
     * @brief \~japanese 速度
     */
    KVector mVelocity;

    /**
     * @brief \~english  whether hit on wall
     * @brief \~japanese 壁に当たっているか
     */
    bool mOnWall;
public:
    /**
     * @brief \~english  mass
     * @brief \~japanese 質量
     */
    float mMass;
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


    PhysicalPoint(const float& aMass);
    PhysicalPoint(KVector& aPoint, const float& aMass);
    virtual ~PhysicalPoint() = default;

    /**
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態
     */
    void update(GameState& aState) override;
    /**
     * @brief \~english  resolve conflict.
     * @brief \~japanese 衝突を解決します。
     */
    void resolveConflicts();

    /**
     * @brief 力を掛ける
     * @param aForce 力
     */
    void applyForce(const KVector& aForce);

    /**
     * \~english
     * @brief  get coordinate.
     * @return coordinate
     * \~japanese
     * @brief  座標を取得します。
     * @return 座標
     */
    const KVector& position() const;

    /**
     * \~english
     * @brief move specified coordinate.
     * @param aPosition specified coordinate
     * \~japanese
     * @brief 指定座標に移動します。
     * @param aPosition 指定座標
     */
    void translate(const KVector& aPosition);
    /**
     * \~english
     * @brief set new coordinate.
     * @param aPosition new coordinate
     * \~japanese
     * @brief 新しく座標を設定します。
     * @param aPosition 新しい座標
     */
    void setPosition(const KVector& aPosition);

    const bool& isOnWall() const;
};

#endif /* PHYSICALPOINT_H */

