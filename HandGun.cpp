/**
 * @file   HandGun.cpp
 * @brief  HandGun
 * @author Maeda Takumi
 */
#include "HandGun.h"

const String HandGun::NAME("HandGun");

HandGun::HandGun() {
    mItemParameter.mName = NAME;
    mWeight = 2.0f;
}

HandGun::~HandGun() {
}

