/**
 * @file   HandGun.h
 * @brief  HandGun
 * @author Maeda Takumi
 */
#ifndef HANDGUN_H
#define HANDGUN_H

#include "Gun.h"

class HandGun : public Gun {
private:
    static const String NAME;
public:
    HandGun();
    virtual ~HandGun();
};

#endif /* HANDGUN_H */

