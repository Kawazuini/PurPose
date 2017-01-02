/**
 * @file   SpecialManager.cpp
 * @brief  SpecialManager
 * @author Maeda Takumi
 */
#include "SpecialManager.h"

#include "Grow.h"
#include "LevelUp.h"
#include "Special.h"

List<Special*> SpecialManager::sSpecials;

void SpecialManager::update() {
    while (!sSpecials.empty()) {
        Special* sp = sSpecials.front();
        sSpecials.pop_front();
        sp->special();
        delete sp;
    }
}

void SpecialManager::add(Special * const aSpecial) {
    static const TypeID GROW = typeid (Grow);
    static const TypeID LVUP = typeid (LevelUp);

    if (!sSpecials.empty()) {
        if (typeid (*aSpecial) == GROW && typeid (*(sSpecials.back())) == GROW) {
            if (aSpecial->mSubject == sSpecials.back()->mSubject) {
                *(dynamic_cast<Grow*> (sSpecials.back())) += *(dynamic_cast<Grow*> (aSpecial));
                return;
            }
        }
        if (typeid (*aSpecial) == LVUP && typeid (*(sSpecials.back())) == LVUP) {
            if (aSpecial->mSubject == sSpecials.back()->mSubject) {
                *(dynamic_cast<LevelUp*> (sSpecials.back())) += *(dynamic_cast<LevelUp*> (aSpecial));
                return;
            }
        }
    }
    sSpecials.push_back(aSpecial);
}

void SpecialManager::cutin(Special * const aSpecial) {
    sSpecials.push_front(aSpecial);
}

