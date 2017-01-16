/**
 * @file   Stair.h
 * @brief  Stair
 * @author Maeda Takumi
 */
#ifndef STAIR_H
#define STAIR_H

#include "Object.h"

/**
 * @brief  \~english  rogue's stair
 * @brief  \~japanese 階段
 * @author \~ Maeda Takumi
 */
class Stair : public KDrawer, public Object {
private:
    KVector mPosition;
    Vector<KVector> mVertex;
    KTexture mTexture;

    /**
     * @brief \~english  
     * @brief \~japanese アクティブ状態か
     */
    bool mActive;
public:
    Stair(const KVector& aPosition);
    virtual ~Stair() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;

    /**
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態の情報
     */
    void update(const GameState& aState) override;

    /***/
    bool judge(const KVector& aPosition);

    /***/
    void rotate(const KQuaternion& aQuater);

    void stop();

    /**
     * \~english
     * @brief  get position coordinate.
     * @return position coordinate
     * \~japanese
     * @brief  位置座標を取得します。
     * @return 位置座標
     */
    const KVector& position() const;
    const bool& isActive() const;
};

#endif /* STAIR_H */

