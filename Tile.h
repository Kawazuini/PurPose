/**
 * @file   Tile.cpp
 * @brief  Tile
 * @author Maeda Takumi
 */
#ifndef TILE_H
#define TILE_H

#include "main.h"

class GameState;

/**
 * @brief  \~english  splitted polygon
 * @brief  \~japanese ポリゴン分割
 * @author \~ Maeda Takumi
 */
class Tile : public KDrawer {
private:
    /* 描画リスト */ static Vector<Tile*> sDrawList;

    /* 衝突判定       */ KPolygon mPolygon;
    /* 描画用ポリゴン */ Vector<KPolygon> mPolyList;

    /* 位置ベクトル   */ KVector mPosition;
    /* 法線ベクトル   */ KVector mNormal;
    /* カメラとの距離 */ float mDistance;
public:
    /**
     * \~english
     * @brief generate drawing split polygon with unchanged conflict judgment.
     * @param aVertex four vertex
     * @param sepX    number of horizontal divisions 
     * @param sepY    number of vertical divisions 
     * \~japanese
     * @brief 衝突判定が一つのままの描画分割されたポリゴンを生成します。
     * @param aVertex 4つの頂点
     * @param sepX    横の分割数
     * @param sepY    縦の分割数
     */
    Tile(const Vector<KVector>& aVertex, const int& sepX, const int& sepY);
    virtual ~Tile();

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;

    static const void TILE_DRAW(const GameState& aState);
};

#endif /* TILE_H */

