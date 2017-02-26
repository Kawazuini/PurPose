/**
 * @file   Effect.h
 * @brief  Effect
 * @author Maeda Takumi
 */
#ifndef EFFECT_H
#define EFFECT_H

#include "Object.h"

class Effect : public KDrawer, public Object {
public:

    /**
     * @brief \~englsih  effect type
     * @brief \~japanese エフェクト種別
     */
    enum EffectType {
        /** 銃撃 */ EFFECT_GUNSHOT,
        /** 爆発 */ EFFECT_EXPLOSION,
    };
private:
    /* エフェクトの種類       */ EffectType mType;
    /* エフェクト値(大きさ等) */ int mValue;
    /* エフェクト発生位置     */ KVector mPosition;
    /* フレームカウント       */ int mFrameCount;
    /* エフェクトテクスチャ   */ KTexture mEffect;
public:
    Effect(
            const EffectType& aType,
            const int& aValue,
            const KVector& aPosition = KVector()
            );
    virtual ~Effect() = default;

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
     * @param aState ゲーム状態
     */
    void update(GameState& aState) override;
};

#endif /* EFFECT_H */

