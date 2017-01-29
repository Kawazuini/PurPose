/**
 * @file   Tile.cpp
 * @brief  Tile
 * @author Maeda Takumi
 */
#ifndef TILE_H
#define TILE_H

#include "main.h"

/**
 * @brief  \~english  splitted polygon
 * @brief  \~japanese ポリゴン分割
 * @author \~ Maeda Takumi
 */
class Tile : public KDrawer {
private:
    /**
     * @brief \~english  List of Polygon for collision determinate
     * @brief \~japanese 衝突判定リスト
     */
    static List<KPolygon*> sPolygons;

    /**
     * @brief \~english  overall collision determination
     * @brief \~japanese 全体の当たり判定
     */
    KPolygon* mPolygon;
    /**
     * @brief \~english  polygon for drawing
     * @brief \~japanese 描画用ポリゴン
     */
    Vector<KPolygon> mPolyList;
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
    Tile(const KVector aVertex[4], const int& sepX, const int& sepY);
    virtual ~Tile();

    /**
     * @brief \~english  add myself to List.
     * @brief \~japanese リストに自分を追加。
     */
    void add();
    /**
     * @brief \~english  erase myself form List.
     * @brief \~japanese リストから自分を消す。
     */
    void remove();

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;
    
    /**
     * \~english
     * @brief  get Polygon for collision determinate List.
     * @return Polygon for collision determinate List
     * \~japanese
     * @brief  衝突判定リストを取得します。
     * @return 衝突判定リスト
     */
    static const List<KPolygon*>& polyList();
};

#endif /* TILE_H */

