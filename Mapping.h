/**
 * @file   Mapping.h
 * @brief  Mapping
 * @author Maeda Takumi
 */
#ifndef MAPPING_H
#define MAPPING_H

#include "Map.h"
#include "Object.h"

class Character;

/**
 * @brief  \~english  Map drawing system
 * @brief  \~japanese マップ描画システム
 * @author Maeda Takumi
 */
class Mapping : public KDrawer, public Object {
private:
    /* テクスチャサイズ */ static const int TEX_SIZE;

    /* マップ描画色 */
    struct MapColors {
        /* player color */ color mPlayer;
        /* wall   color */ color mWall;
        /* floor  color */ color mFloor;
        /* grid   color */ color mGrid;
    } mColors;
    /* マップ情報     */ Map mMap;
    /* マッピング情報 */ bool mMapping[MAP_MAX_WIDTH][MAP_MAX_HEIGHT][5];

    /* UI対象カメラ     */ const KCamera& mCamera;
    /* 描画キャンバス   */ KTexture mCanvas;
    /* マップ描画角度   */ float mAngle;
    /* マップ描画サイズ */ int mScale;

    /* 部屋のマッピング */ void room(const KVector& aPlayer);
public:
    Mapping(const KCamera& aCamera);
    virtual ~Mapping() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    void draw() const override;
    /**
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態
     */
    void update(GameState& aState) override;

    /**
     * \~english
     * @brief set the map info
     * @param aMap map info
     * \~japanese
     * @brief マップ情報を設定します。
     * @param aMap マップ情報
     */
    void set(const Map& aMap);
    /**
     * @brief \~english  reset mapping information.
     * @brief \~japanese マッピング情報をリセットします。
     */
    void reset();

    /**
     * \~english
     * @brief change map scale.
     * @param aAmount change amount
     * \~japanese
     * @brief マップスケールを変更します。
     * @param aAmount 変更量
     */
    void zoom(const int& aAmount);
    /**
     * \~english
     * @brief draw map.
     * @param aState     state of game
     * @param aRect      drawing area
     * @param aSize      square size
     * @param aCentering whether centering
     * \~japanese
     * @brief マップを描画します。
     * @param aPlayer    描画中心
     * @param aRect      描画領域
     * @param aSize      一マスの描画サイズ
     * @param aCentering 中央寄せするか
     */
    void draw(
            const GameState& aState,
            const KRect& aRect,
            const int& aSize,
            const bool& aCentering
            );
};

#endif /* MAPPING_H */

