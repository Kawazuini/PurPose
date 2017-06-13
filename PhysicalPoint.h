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
class PhysicalPoint final : public Object {
private:
    /* ダミー座標 */ KVector mDummy;
    /* 座標       */ KVector& mPosition;
    /* 1F前の座標 */ KVector mPrePosition;

    /* 力   */ KVector mForce;
    /* 速度 */ KVector mVelocity;

    /* 壁に当たっているか */ bool mOnWall;
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

    /**
     * \~english
     * @brief generate points with mass.
     * @param aMass mass
     * \~japanese
     * @brief 質量を持った点を生成します。
     * @param aMass 質量
     */
    PhysicalPoint(const float& aMass);
    /**
     * \~english
     * @brief give a mass to the position vector.
     * @param aPoint position vector
     * @param aMass  mass
     * \~japanese
     * @brief 位置ベクトルに質量を付与します。
     * @param aPoint 位置ベクトル
     * @param aMass  質量
     */
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
    void resolveConflicts(const GameState& aState);

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

    /**
     * \~english
     * @brief  get whether hit on wall.
     * @return whether hit on wall
     * \~japanese
     * @brief  壁に衝突しているかを取得します。
     * @return 壁に衝突しているか
     */
    const bool& isOnWall() const;
};

#endif /* PHYSICALPOINT_H */

