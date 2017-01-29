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
    /**
     * @brief \~english  position coordinate
     * @brief \~japanese 位置座標
     */
    KVector mPosition;
    /**
     * @brief \~english  drawing vertex
     * @brief \~japanese 描画頂点
     */
    Vector<KVector> mVertex;
    /**
     * @brief \~english  drawing pattern
     * @brief \~japanese 描画模様
     */
    KTexture mTexture;

    /**
     * @brief \~english  whether active
     * @brief \~japanese アクティブ状態か
     */
    bool mActive;

    /**
     * \~english
     * @brief rotate drawing vertex.
     * @param aQuater rotation information
     * \~japanese
     * @brief 描画頂点を回転させます。
     * @param aQuater 回転情報
     */
    void rotate(const KQuaternion& aQuater);
public:
    /**
     * \~english
     * @brief generate stairs at specified position
     * @param aPosition specified position
     * \~
     * @brief 指定位置に階段を生成します。
     * @param aPosition 指定座標
     */
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
    void update(GameState& aState) override;

    /**
     * \~english
     * @brief  determine whether usable the staircase.
     * @param  aPosition determination coordinates
     * @return whether usable
     * \~japanese
     * @brief  階段を使用できるかを判定します。
     * @param  aPosition 判定座標
     * @return 使用できるか
     */
    bool judge(const KVector& aPosition);
    /**
     * @brief \~english  make the stairs unusable.
     * @brief \~japanese 階段を使えなくします。
     */
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
    /**
     * \~english
     * @brief  get whether active.
     * @return whether avtive
     * \~japanese
     * @brief  アクティブ状態を取得します。
     * @return アクティブか
     */
    const bool& isActive() const;
};

#endif /* STAIR_H */

