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
    Slime(GameState& aState);
private:
    virtual ~Slime() = default;
public:
    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    virtual void update(GameState& aState) override;
};

#endif /* SLIME_H */

