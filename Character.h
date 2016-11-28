/**
 * @file   Character.h
 * @brief  Character
 * @author Maeda Takumi
 */
#ifndef CHARACTER_H
#define CHARACTER_H

#include "main.h"

class Map;

/**
 * @brief  \~english  Base of Character
 * @brief  \~japanese キャラクター基底
 * @author Maeda Takumi
 */
class Character : public KDrawer, public KUpdater {
protected:
    /** @brief 共有マップ */ static Map* sMap;

    /** @brief 自分のターン */ bool mTurn;

    /** @brief キャラクター座標 */ KVector mPosition;
    /** @brief キャラクター方向 */ KVector mDirection;

    /* 各自設定項目 */
    float mSpeed;

    float mSize;
    
    int mActionPoint;
    int mAgility;
    int mMoveCost;
    int mAtackCost;
public:
    Character();
    virtual ~Character();

    /**
     * @brief 共有マップの設定
     * @param aMap 共有マップ
     */
    static void setMap(Map * const aMap);

    /** @brief 更新処理 */ virtual void update() override;

    /** @brief ターン開始 */ virtual void turnStart();
    /** @brief ターン終了 */ virtual void turnEnd();

    /**
     * @brief 自分のターンを返す
     * @return 自分のターンか
     */
    virtual bool turn() const;

    /**
     * @brief 移動
     * @param aMove 移動量
     * @return 移動できたか
     */
    virtual bool move(const KVector& aMovement);
    
    virtual bool atack();

    /**
     * @brief 座標設定
     * @param aPosition 座標
     */
    virtual void setPosition(const KVector& aPosition);
    /**
     * @brief キャラクター座標を取得
     * @return キャラクター座標
     */
    virtual KVector position() const;
    /**
     * @brief キャラクター方向を取得
     * @return キャラクター方向
     */
    virtual KVector direction() const;
};

#endif /* CHARACTER_H */

