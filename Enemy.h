/**
 * @file   Enemy.cpp
 * @brief  Enemy
 * @author Maeda Takumi
 */
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"

/**
 * @brief  \~english  enemy character
 * @brief  \~japanese 敵キャラクター
 * @author \~ Maeda Takumi
 */
class Enemy : public Character {
public:
    /**
     * @brief \~english  list of enemy character
     * @brief \~japanese 敵キャラクターリスト
     */
    static List<Enemy*> sEnemies;
private:
    static const int TEX_SIZE;
protected:
    KTexture* mTexture;

    KDrawSphere* mSphere;
public:
    Enemy(const String& aType, const color& aColor);
    virtual ~Enemy();

    /**
     * @brief \~english  add myself to list.
     * @brief \~japanese リストに自分を追加。
     */
    void add();
    /**
     * @brief \~english  erase myself form list.
     * @brief \~japanese リストから自分を消す。
     */
    void erase();

    void move(const KVector& aMovement) override;

    void setPosition(const KVector& aPosition) override;

    /** @brief 描画処理 */ void draw() const override;
    /** @brief 更新処理 */ virtual void update(const KVector& aPlayer);
};

#endif /* ENEMY_H */

