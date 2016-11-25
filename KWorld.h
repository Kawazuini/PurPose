/**
 * @file KWorld.h
 * @brief KWorld
 */
#ifndef KWORLD_H
#define KWORLD_H

#include "KGame.h"

/** @brief 世界定数 */
class KWorld {
public:
    /** @brief 標準秒間更新数 */ static const int FRAME_PER_SECOND;
    /** @brief 標準重力加速度 */ static const KVector ACCELE_GRAVITY;

    /** @brief 秒間更新数 */ static int sFramePerSecond;
    /** @brief 重力加速度 */ static KVector sAcceleGravity;
private:
    KWorld() = default;
    virtual ~KWorld() = default;
};

#endif /* KWORLD_H */
