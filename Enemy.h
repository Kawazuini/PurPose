/**
 * @file   Enemy.h
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
    /**
     * @brief \~english  texture size
     * @brief \~japanese テクスチャサイズ
     */
    static const int TEX_SIZE;
protected:
    /**
     * @brief \~english  
     * @brief \~japanese 
     */
    KTexture* mTexture;

    /**
     * @brief \~english  
     * @brief \~japanese 
     */
    KDrawSphere* mSphere;
public:
    Enemy(const String& aType, const float& aSize, const color& aColor);
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
    void remove();

    /**
     * @brief \~english  synchronize position.
     * @brief \~japanese 位置を同期します。
     */
    virtual void syncPosition();

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;
    /** @brief 更新処理 */ virtual void update(const KVector& aPlayer);

    /**
     * \~english
     * @brief rotate drawing object so that it points in the specified direction.
     * @param aDirection specified direction
     * \~japanese
     * @brief 指定方向を向くように描画オブジェクトを回転させます。
     * @param aDirection 指定方向
     */
    void lookAt(const KVector& aDirection);
};

#endif /* ENEMY_H */

