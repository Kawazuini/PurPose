/**
 * @file KWorld.cpp
 * @brief KWorld
 */
#include "KWorld.h"

const int KWorld::FRAME_PER_SECOND = 50;
const KVector KWorld::ACCELE_GRAVITY(0, -9.80665, 0);

int KWorld::sFramePerSecond = FRAME_PER_SECOND;
KVector KWorld::sAcceleGravity(ACCELE_GRAVITY);
