/**
 * @file   Effect.h
 * @brief  Effect
 * @author Maeda Takumi
 */
#ifndef EFFECT_H
#define EFFECT_H

#include "Object.h"

/**
 * @brief  \~english  Effect of sound & visial
 * @brief  \~japanese 効果音・ビジュアル効果
 * @author \~ Maeda Takumi
 */
class Effect final : public KDrawer, public Object {
public:

    /**
     * \~english  @brief effect type
     * \~japanese @brief エフェクト種別
     */
    enum EffectType {
        /** \~japanese 銃撃 */ EFFECT_GUNSHOT,
        /** \~japanese 爆発 */ EFFECT_EXPLOSION,
    };
private:
    /* エフェクトの種類       */ EffectType mType;
    /* エフェクト値(大きさ等) */ int mValue;
    /* エフェクト発生位置     */ KVector mPosition;
    /* フレームカウント       */ int mFrameCount;
public:
    /**
     * \~english
     * @param aType     type of Effect
     * @param aValue    Effect Value
     * @param aPosition Effect position
     * \~japanese
     * @param aType     効果種別
     * @param aValue    効果値
     * @param aPosition 効果位置
     */
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

