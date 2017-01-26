/**
 * @file   WaterBalloon.h
 * @brief  WaterBalloon
 * @author Maeda Takumi
 */
#ifndef WATERBALLOON_H
#define WATERBALLOON_H

#include "Object.h"
#include "PhysicalPoint.h"

/**
 * @brief  \~english  physical water balloon
 * @brief  \~japanese 物理的水風船
 * @author \~ Maeda Tkumi
 */
class WaterBalloon : public KDrawSphere, public Object {
private:
    /**
     * @brief \~english  
     * @brief \~japanese 頂点毎の質点
     */
    Vector<Vector<PhysicalPoint*>> mPoints;

    /**
     * @brief \~english  ideal volume
     * @brief \~japanese 理想体積
     */
    float mVolume;

    /**
     * @brief \~english  elasticity
     * @brief \~japanese 柔軟性
     */
    float mElasticity;

    bool mFluctuation;
    float mFrame;
public:
    WaterBalloon(
            const KVector& aPosition,
            const float& aRadius,
            const int& aStack,
            const int& aSlice
            );
    virtual ~WaterBalloon();

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
     * \~english
     * @brief  calculate volume.
     * @return volume
     * \~japanese
     * @brief  体積を計算します。
     * @return 体積
     * @detail 割と適当な概算(実装の返却地補正とか)ですが、半径によらず正確な体積が求められる気がします。
     */
    float calcVolume() const;

    /**
     * \~english
     * @brief translate center coordinate into argument.
     * @param aVec new center coordinate
     * \~japanese
     * @brief 中心座標を指定座標に遷移させます。
     * @param 設定する中心座標
     */
    void translate(const KVector& aPosition) override;
};

#endif /* WATERBALLOON_H */

