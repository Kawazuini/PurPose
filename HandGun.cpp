/**
 * @file   HandGun.cpp
 * @brief  HandGun
 * @author Maeda Takumi
 */
#include "HandGun.h"

const String HandGun::NAME("HandGun");

HandGun::HandGun() {
    mParameter.mName = NAME;
    mWeight = 2.0f;
}

HandGun::~HandGun() {
}

