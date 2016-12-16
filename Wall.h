/**
 * @file Wall.h
 * @brief Wall
 */
#ifndef WALL_H
#define WALL_H

#include "main.h"

/** @brief 壁 */
class Wall : public KDrawer {
private:
    static const int WALL_HEIGHT;

    static Vector<KPolygon*> sWalls;
    /** @brief ポリゴン   */ KPolygon* mPolygon;
    /** @brief 描画頂点数 */ int mVertexSize;
    /** @brief 描画頂点   */ KVector* mVertex;
public:
    Wall(const float& aScale, const KRect& aWall);
    Wall(const Wall& orig);
    virtual ~Wall();

    /** @brief 描画処理 */ void draw() const override;

    /**
     * @brief 衝突判定リストの取得
     * @return 衝突判定リスト
     */
    static const Vector<KPolygon*>& wallList();
};

#endif /* WALL_H */
