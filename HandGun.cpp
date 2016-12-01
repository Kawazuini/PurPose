/**
 * @file   HandGun.cpp
 * @brief  HandGun
 * @author Maeda Takumi
 */
#include "HandGun.h"

const String HandGun::NAME("HandGun");

HandGun::HandGun() {
    mName = NAME;
    mWeight = 2.0f;
    mCost = 10;
}

HandGun::~HandGun() {
}
