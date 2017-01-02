/**
 * @file   Special.cpp
 * @brief  Special
 * @author Maeda Takumi
 */
#include "Special.h"

int Special::sIDDistributor = 0;

Special::Special(Object * const aSubject, Object * const aObject)
: mID(++sIDDistributor) {
    mSubject = aSubject;
    mObject = aObject;
}

