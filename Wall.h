/**
 * @file   Wall.h
 * @brief  Wall
 * @atthor Maeda Takumi
 */
#ifndef WALL_H
#define WALL_H

#include "main.h"

/**
 * @brief \~english  appearance of wall and collision determination
 * @brief \~japanese 壁の外観と衝突判定
 * @author \~ Maeda Takumi
 */
class Wall : public KDrawer {
private:
    /**
     * @brief \~english  Wall List
     * @brief \~japanese 壁リスト
     */
    static List<Wall*> sWalls;

    /**
     * @brief \~english  Polygon of collision determination
     * @brief \~japanese 衝突判定ポリゴン
     */
    KPolygon mPolygon;
    /**
     * @brief \~english  vertex count
     * @brief \~japanese 描画頂点数
     */
    int mVertexSize;
    /**
     * @brief \~english  vertex of drawing
     * @brief \~japanese 描画頂点
     */
    KVector* mVertex;
public:
    Wall(const float& aScale, const KRect& aWall);
    virtual ~Wall();

    /**
     * @brief \~english  add myself to List.
     * @brief \~japanese リストに自分を追加。
     */
    void add();
    /**
     * @brief \~english  erase myself form List.
     * @brief \~japanese リストから自分を消す。
     */
    void erase();

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;

    /**
     * \~english
     * @brief  get Wall List
     * @return Wall List
     * \~japanese
     * @brief  壁リストを取得します。
     * @return 壁リスト
     */
    static const List<Wall*>& wallList();

    /**
     * \~english
     * @brief  get collision determination.
     * @return collision determination
     * \~japanese
     * @brief  衝突判定を取得します。
     * @return 衝突判定
     */
    const KPolygon& polygon() const;
};

#endif /* WALL_H */

