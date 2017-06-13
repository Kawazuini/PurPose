/**
 * @file   Object.cpp
 * @brief  Object
 * @author Maeda Takumi
 */
#include "Object.h"

int Object::sIDDistributor(0);
List<Object*> Object::sObjects;

Object::Object() :
mID(++sIDDistributor),
mUpdated(false) {
    add();
}

Object::~Object() {
    remove();
}

void const Object::UPDATE(GameState& aState) {
    List<Object*> tmp(sObjects);
    int size(sObjects.size()), currentSize;
    while (!tmp.empty()) {
        tmp.front()->mUpdated = true; // 自殺考慮で事前に書き換える
        tmp.front()->update(aState);
        if (size != (currentSize = sObjects.size())) { // リストの増減が起きた
            // 最新状態に上書きし、更新位置を調整する
            size = currentSize;
            tmp = sObjects;
            while (!tmp.empty() && tmp.front()->mUpdated) tmp.pop_front();
        } else tmp.pop_front();
    }
    // 更新状態を戻す
    for (Object* i : sObjects) i->mUpdated = false;
}

void Object::add() {
    remove(); // 2重追加防止
    sObjects.push_back(this);
}

void Object::remove() {
    for (auto i = sObjects.begin(), i_e(sObjects.end()); i != i_e; ++i) {
        if (*i == this) {
            sObjects.erase(i);
            return;
        }
    }
}

