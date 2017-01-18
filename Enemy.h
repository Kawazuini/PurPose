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
     * @brief \~english  Enemy Character List
     * @brief \~japanese 敵キャラクターリスト
     */
    static List<Enemy*> sEnemies;
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
    Enemy(const String& aType, const float& aSize, const color& aColor);
    virtual ~Enemy();

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;

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
     * \~english
     * @brief  get reference of Enemy Character List
     * @return reference of Enemy Character  List
     * \~japanese
     * @brief  敵キャラクターリストの参照を取得します。
     * @return 敵キャラクターリストの参照
     */
    static const List<Enemy*>& enemyList();

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

