/**
 * @file   Object.cpp
 * @brief  Object
 * @author Maeda Takumi
 */
#include "Object.h"

List<Object*> Object::sObjects;

Object::Object() :
mUpdated(false) {
    add();
}

Object::~Object() {
    remove();
}

void const Object::UPDATE(GameState& aState) {
    // listの増減で今までのiteratorが崩壊する!!!!!
    int pSize = sObjects.size();
    for (auto i = sObjects.begin(), i_e = sObjects.end(); i != i_e;) {
        (*i)->mUpdated = true;
        (*i)->update(aState);
        if (pSize != sObjects.size()) { // 削除 or 追加が行われた。
            pSize = sObjects.size();
            i = sObjects.begin();
            i_e = sObjects.end();
            for (; i != i_e; ++i) {
                if (!(*i)->mUpdated) { // 続きを探す。
                    break;
                }
            }
            continue;
        }
        ++i;
    }

    // 更新有無をもとに戻す。
    for (Object* i : sObjects) i->mUpdated = false;
}

void Object::add() {
    sObjects.push_back(this);
}

void Object::remove() {
    for (auto i = sObjects.begin(), i_e = sObjects.end(); i != i_e; ++i) {
        if (*i == this) {
            sObjects.erase(i);
            return;
        }
    }
}

