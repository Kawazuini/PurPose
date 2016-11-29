/**
 * @file Enemy.h
 * @brief Enemy
 */
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

class Enemy : public Character {
private:
    static const int TEX_SIZE;
protected:
    KTexture* mTexture;

    KDrawSphere* mSphere;
public:
    Enemy(const String& aType, const color& aColor);
    virtual ~Enemy();

    void move(const KVector& aMovement) override;

    void setPosition(const KVector& aPosition) override;

    /** @brief 描画処理 */ void draw() override;
    /** @brief 更新処理 */ virtual void update(const KVector& aPlayer);
};

#endif /* ENEMY_H */
