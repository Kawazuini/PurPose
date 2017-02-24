/**
 * @file   Effect.cpp
 * @brief  Effect
 * @author Maeda Takumi
 */
#include "Effect.h"
#include "GameState.h"

Effect::Effect(
        const EffectType& aType,
        const int& aValue,
        const KVector& aPosition
        ) :
mType(aType),
mValue(aValue),
mPosition(aPosition),
mFrameCount(0),
mEffect(NULL) {
    switch (mType) {
        case EFFECT_EXPLOSION:
        {
            mEffect = new KTexture(64);
            mEffect->drawRect(KRect(64, 64), 0x77a22042); // 真紅
            mEffect->reflect();
            break;
        }
    }
}

Effect::~Effect() {
    if (mEffect) delete mEffect;
}

void Effect::draw() const {
    switch (mType) {
        case EFFECT_EXPLOSION:
        {
            KDrawSphere ds(
                    mPosition,
                    mFrameCount,
                    10, 10
                    );
            ds.mTexture = mEffect;
            ds.draw();
            break;
        }
    }
}

void Effect::update(GameState& aState) {
    ++mFrameCount;
    float dist((aState.mPlayer.position() - mPosition).length()); // エフェクトとの距離

    switch (mType) {
        case EFFECT_GUNSHOT:
        {
            KMidi::Note note{
                KMidi::A4, mValue, Math::max(127, (int) (127 - dist))
            };
            aState.mBGM.playSE(KMidi::Gunshot, note);
            delete this;
            break;
        }
        case EFFECT_EXPLOSION:
        {
            if (mFrameCount == 1) {
                KMidi::Note note{
                    KMidi::C3, mValue * 10, (int) (Math::max(0.0f, Math::min(1.0f, 1.0f - dist / 10 / mValue)) * 127)
                };
                aState.mBGM.playSE(KMidi::Timpani, note);
            }
            if (mFrameCount > mValue / 10) delete this;
            break;
        }
    }
}

