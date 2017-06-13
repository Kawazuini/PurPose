/**
 * @file   Enemy.h
 * @brief  Enemy
 * @author Maeda Takumi
 */
#ifndef ENEMY_H
#define ENEMY_H

#include "Character.h"
#include "Haribote.h"

/**
 * @brief  \~english  Character of Enemy
 * @brief  \~japanese 敵キャラクター
 * @author \~ Maeda Takumi
 */
class Enemy final : public Character {
private:

    /* 画像向き */
    enum Direction {
        DIRECTION_FRONT,
        DIRECTION_BACK,
        DIRECTION_LEFT,
        DIRECTION_RIGHT,
    } mImageDirection;

    /* テクスチャサイズ */ static const int TEX_SIZE;
    /* テクスチャ画像   */ KImage mImage;
    /* テクスチャ       */ KTexture mTexture;
    /* ハリボテ         */ Haribote mHaribote;

    /* ダメージ表示フレーム数 */ int mDamageFrame;
    /* 前フレームHP           */ int mPreHP;
public:
    /**
     * \~english
     * @param aID    resource ID
     * @param aLevel initial level
     * \~japanese
     * @param aID    リソースID
     * @param aLevel 初期レベル
     */
    Enemy(const int& aID, const int& aLevel);
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
};

#endif /* ENEMY_H */

