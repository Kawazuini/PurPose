/**
 * @file   Slime.h
 * @brief  Slime
 * @author Maeda Takumi
 */
#ifndef SLIME_H
#define SLIME_H

#include "Enemy.h"

class Slime : public Enemy {
public:
    Slime();
    virtual ~Slime() = default;

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    virtual void update(const GameState& aState) override;
};

#endif /* SLIME_H */

