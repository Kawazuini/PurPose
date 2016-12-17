/**
 * @file   Mapping.cpp
 * @brief  Mapping
 * @author Maeda Takumi
 */
#ifndef MAPPING_H
#define MAPPING_H

#include "Map.h"

/**
 * @brief  \~english  Map drawing system
 * @brief  \~japanese マップ描画システム
 * @author Maeda Takumi
 */
class Mapping : private KNonCopy {
private:

    /**
     * @brief \~english  map drawing color
     * @brief \~japanese マップ描画色
     */
    struct MapColors {
        /** player color */ color mPlayer;
        /** wall   color */ color mWall;
        /** floar  color */ color mFloar;
        /** grid   color */ color mGrid;
    } mColors;

    /**
     * @brief \~english  array of Map information
     * @brief \~japanese マップ情報配列
     */
    Map mMap;
    /**
     * @brief \~english  scale of entity from information
     * @brief \~japanese 情報に対する実体の倍率
     */
    const float mScale;

    /**
     * @brief \~english  mapping information array
     * @brief \~japanese マッピング情報
     */
    bool mMapping[MAP_MAX_WIDTH][MAP_MAX_HEIGHT][5];

    /**
     * @brief \~english  mapping the room.
     * @brief \~japanese 部屋をマッピングします。
     */
    void room(const int& x, const int& y);
public:

    /**
     * @brief \~english  player drawing information
     * @brief \~japanese プレイヤー描画情報
     */
    struct MappingPlayer {
        /**
         * @brief \~english  player coodinate
         * @brief \~japanese プレイヤー座標
         */
        KVector mPosition;
        /**
         * @brief \~english  player direction
         * @brief \~japanese プレイヤー方向
         */
        KVector mDirection;

        MappingPlayer(const KVector& aPosition, const KVector& aDirection) {
            mPosition = KVector(aPosition.x, aPosition.z);
            mDirection = KVector(aDirection.x, aDirection.z);
        };
        MappingPlayer(const MappingPlayer& orig) = delete;
        virtual ~MappingPlayer() = default;
    };

    Mapping();
    virtual ~Mapping() = default;

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
     * @brief draw map.
     * @param aGLUI   drawing ui
     * @param aPlayer player drawing information
     * @param aRect   drawing area
     * @param aSize   square size
     * \~japanese
     * @brief マップを描画します。
     * @param aGLUI   描画を行うインターフェース
     * @param aPlayer プレイヤー描画情報
     * @param aRect   描画領域
     * @param aSize   一マスの描画サイズ
     */
    void draw(
            KGLUI& aGLUI,
            const MappingPlayer& aPlayer,
            const KRect& aRect,
            const int& aSize);
};

#endif /* MAPPING_H */

