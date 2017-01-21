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
    KTexture mTexture;
    /**
     * @brief \~english  
     * @brief \~japanese 
     */
    KDrawSphere mSphere;
public:
    Enemy(
            const int& aID,
            GameState& aState,
            const String& aType,
            const float& aSize,
            const color& aColor
            );
protected:
    virtual ~Enemy() = default;

    /**
     * \~english
     * @brief 
     * @param aState information of game state
     * \~japanese
     * @brief 死にます。
     * @param aState ゲーム状態
     */
    void die(GameState& aState) override;
public:
    /**
     * \~english
     * @brief attacking.
     * @param aState game state
     * \~japanese
     * @brief   攻撃を行います。
     * @param   aState ゲーム状態
     * @details 敵(aState内のPlayer)と接触しているときに攻撃を行います。
     */
    void attack(GameState& aState) override;

    /**
     * @brief \~english  synchronize position.
     * @brief \~japanese 位置を同期します。
     */
    virtual void syncPosition();

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

