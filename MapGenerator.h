/**
 * @file   MapGenerator.h
 * @brief  MapGenerator
 * @author Maeda Takumi
 */
#ifndef MAPGENERATOR_H
#define MAPGENERATOR_H

#include "Map.h"

/**
 * @brief \~english  Map generating
 * @brief \~japanese マップ生成
 * @author \~ Maeda Takumi
 */
class MapGenerator {
private:

    typedef struct {
        int mWidth;
        int mHeight;
        Map mMap;
    } MapDocument;

    MapGenerator() = default;
    MapGenerator(const MapGenerator& orig) = delete;
    virtual ~MapGenerator() = default;

    /** @brief 壁伸ばし法で壁を生成 */ static bool wallGrow(MapDocument& aMap, MapDocument& aPole, KVector& aPoint, bool aExcep[4]);
    /** @brief 部屋の作成           */ static void makeRoom(MapDocument& aInfo);
    /** @brief 小道の除去           */ static void clean(MapDocument& aInfo);
public:

    /**
     * @brief \~english  file convert information
     * @brief \~japanese ファイル変換情報
     */
    typedef enum {
        _START = 0,
        _ROOM = 1,
        _WALL = 2,
    } FILE_TO_MAP;

    /**
     * @brief \~english  RANDOM_MAP's max width
     * @brief \~japanese RANDOM_MAPの最大横幅
     */
    static const int RANDOM_MAX_WIDTH;
    /**
     * @brief \~english  RANDOM_MAP's max height
     * @brief \~japanese RANDOM_MAPの最大縦幅
     */
    static const int RANDOM_MAX_HEIGHT;
    /**
     * @brief \~english  RANDOM_MAP's min width
     * @brief \~japanese RANDOM_MAPの最小横幅
     */
    static const int RANDOM_MIN_WIDTH;
    /**
     * @brief \~english  RANDOM_MAP's min height
     * @brief \~japanese RANDOM_MAPの最小縦幅
     */
    static const int RANDOM_MIN_HEIGHT;

    /**
     * \~english
     * @brief generate Map with Strings.
     * @param aDist storage array
     * @param aMap  map generation information
     * \~japanese
     * @brief 文字列からのマップ生成。
     * @param aDist 格納配列
     * @param aMap  マップ生成情報
     */
    static void STRING_MAP(Map& aDist, const Vector<String>& aMap);
    /**
     * \~english
     * @brief generate Map with random.
     * @param aDist storage array
     * \~japanese
     * @brief 乱数でマップを生成します。
     * @param aDist 格納配列
     */
    static void RANDOM_MAP(Map& aDist);
};

#endif /* MAPGENERATOR_H */

