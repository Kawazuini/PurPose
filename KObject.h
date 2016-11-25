/**
 * @file KObject.h
 * @brief KObject
 */
#ifndef KOBJECT_H
#define KOBJECT_H

#include "KDrawer.h"
#include "KUpdater.h"

class KObject : public KDrawer, public KUpdater {
protected:
    /** @brief 重力を受ける   */ bool mGravity = false;
    /** @brief 衝突判定を持つ */ bool mCollider = false;
    /** @brief 回転運動をする */ bool mRotatable = false;
public:
    KObject() = default;
    KObject(const KObject& orig) = default;
    virtual ~KObject() = default;
};

#endif /* KOBJECT_H */
