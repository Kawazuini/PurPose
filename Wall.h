/**
 * @file Wall.h
 * @brief Wall
 */
#ifndef WALL_H
#define WALL_H

#include "Map.h"

/** @brief 壁 */
class Wall : public KDrawer {
private:
    static const int WALL_HEIGHT;

    static Array<KPolygon*> sWalls;
    /** @brief ポリゴン   */ KPolygon* mPolygon;
    /** @brief 描画頂点数 */ int mVertexSize;
    /** @brief 描画頂点   */ KVector* mVertex;
public:
    Wall(const Map& aMap, const KRect& aWall);
    Wall(const Wall& orig);
    virtual ~Wall();

    /** @brief 描画処理 */ void draw() override;

    /**
     * @brief 衝突判定リストの取得
     * @return 衝突判定リスト
     */
    static const Array<KPolygon*>& wallList();
};

#endif /* WALL_H */
