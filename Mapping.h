/**
 * @file   Mapping.h
 * @brief  Mapping
 * @author Maeda Takumi
 */
#ifndef MAPPING_H
#define MAPPING_H

#include "Map.h"

class Character;

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
        /** floor  color */ color mFloor;
        /** grid   color */ color mGrid;
    } mColors;

    /**
     * @brief \~english  array of Map information
     * @brief \~japanese マップ情報配列
     */
    Map mMap;

    /**
     * @brief \~english  mapping information array
     * @brief \~japanese マッピング情報
     */
    bool mMapping[MAP_MAX_WIDTH][MAP_MAX_HEIGHT][5];
public:
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
            const Character& aPlayer,
            const KRect& aRect,
            const int& aSize) const;

    /**
     * @brief \~english  mapping the room.
     * @brief \~japanese 部屋をマッピングします。
     */
    void room(const KVector& aPlayer);
    // void room(const int& x, const int& y);
};

#endif /* MAPPING_H */

