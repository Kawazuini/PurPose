/**
 * @file   Merchant.cpp
 * @brief  Merchant
 * @author Maeda Takumi
 */
#include "Merchant.h"

#include "GameState.h"
#include "Map.h"

Merchant::Merchant(
        GameManager& aManager,
        const EventFunction& aFunction
        ) :
Character(ID_INDEX_MERCHANT),
Event(aManager, aFunction) {
}

void Merchant::update(GameState& aState) {
    Character::update(aState);
    Event::update(aState);
}

bool Merchant::condition(const GameState& aState) const {
    static const float SCALE_SQUARE(MAP_SCALE * MAP_SCALE);

    return (mPosition - aState.mPlayer.position()).lengthSquared() < SCALE_SQUARE;
}

