/**
 * @file   Event.cpp
 * @breif  Event
 * @author Maeda Takumi
 */
#include "Event.h"

Event::Event(
        GameManager& aManager,
        const EventFunction& aFunction
        ) :
mGameManager(aManager),
mFunction(aFunction),
mActive(false) {
}

void Event::update(GameState& aState) {
    if (mActive && condition(aState)) {
        (mGameManager.*mFunction)();
    }
}

void Event::enable() {
    mActive = true;
}

void Event::disable() {
    mActive = false;
}

const bool& Event::isActive() const {
    return mActive;
}

