/**
 * @file   Enemy.h
 * @brief  Enemy
 * @author Maeda Takumi
 */
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "WaterBalloon.h"

/**
 * @brief  \~english  enemy character
 * @brief  \~japanese 敵キャラクター
 * @author \~ Maeda Takumi
 */
class Enemy : public Character {
private:
    static const int PARAMETER_INDEX_COLOR;
    static const int PARAMETER_INDEX_CHAR;
    static const int PARAMETER_INDEX_CHARCOLOR;

    /**
     * @brief \~english  texture size
     * @brief \~japanese テクスチャサイズ
     */
    static const int TEX_SIZE;
protected:
    /**
     * @brief \~english  characteristic
     * @brief \~japanese 見た目の特徴
     */
    KTexture mTexture;
    /**
     * @brief \~english  Enemy shape
     * @brief \~japanese 敵の外形
     */
    //WaterBalloon mBalloon;
     KDrawSphere mBalloon;
public:
    /**
     * \~english
     * @brief generate Character from resource ID.
     * @param aID resource ID
     * \~japanese
     * @brief リソースIDからキャラクターを生成します。
     * @param aID リソースID
     */
    Enemy(const int& aID);
    virtual ~Enemy() = default;

    /**
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態の情報
     */
    void update(GameState& aState) override;

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

