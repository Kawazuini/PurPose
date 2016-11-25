/**
 * @file Dice.h
 * @brief Dice
 */
#ifndef DICE_H
#define DICE_H

#include "main.h"

class Dice : public KCube {
private:
    const KTexture * const mTexture;
public:
    Dice(const KVector * const aMaterialPoints, const KVector& aVec);
    Dice(const KVector& aCentroid, const float& aSideLength, const KTexture& aTexture);
    virtual ~Dice() = default;

    /** @brief 描画処理 */
    virtual void draw() override;
    /** @brief 更新処理 */
    virtual void update() override;
};

#endif /* DICE_H */
