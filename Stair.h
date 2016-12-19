/**
 * @file   Stair.h
 * @brief  Stair
 * @author Maeda Takumi
 */
#ifndef STAIR_H
#define STAIR_H

#include "main.h"

/**
 * @brief  \~english  rogue's stair
 * @brief  \~japanese 階段
 * @author \~ Maeda Takumi
 */
class Stair : public KDrawer, public KUpdater {
private:
    KVector mPosition;
    Vector<KVector> mVertex;

    KTexture* mTexture;
public:
    Stair(const KVector& aPosition);
    virtual ~Stair();

    /***/
    void rotate(const KQuaternion& aQuater);
    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    void update() override;
    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;

    /**
     * \~english
     * @brief  get position coordinate.
     * @return position coordinate
     * \~japanese
     * @brief  位置座標を取得します。
     * @return 位置座標
     */
    KVector position() const;
};

#endif /* STAIR_H */

