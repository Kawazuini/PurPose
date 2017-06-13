/**
 * @file   Money.cpp
 * @brief  Money
 * @author Maeda Takumi
 */
#include "Money.h"

#include "GameState.h"
#include "Map.h"

const int Money::TEX_SIZE(32);

Money::Money(
        GameManager& aManager,
        const EventFunction& aFunction,
        const KVector& aPosition
        ) :
Event(aManager, aFunction),
mPosition(aPosition + KVector(0, 1, 0)),
mImage(IDI_MONEY),
mTexture(TEX_SIZE, false),
mHaribote(mPosition, 1.0f, mTexture) {
    mTexture.drawImage(mImage, KRect(TEX_SIZE, TEX_SIZE), KVector());
    mTexture.reflect();
}

void Money::update(GameState& aState) {
    Event::update(aState);

    // 拾ったときにイベント消去
    if (condition(aState)) {
        aState.removeMoney(*this);
        delete this;
    }
}

bool Money::condition(const GameState& aState) const {
    return (mPosition - aState.mPlayer.position()).lengthSquared() < MAP_SCALE;
}

