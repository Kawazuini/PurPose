/**
 * @file Map.h
 * @brief Map
 */
#ifndef MAP_H
#define MAP_H

#include "main.h"

class KImage;
class Wall;

/** @brief 情報であり実体でもある */
class Map : private KNonCopy {
private:
    static const KVector X; ///< x軸の単位ベクトル
    static const KVector Y; ///< y軸の単位ベクトル
    static const KVector Z; ///< z軸の単位ベクトル

    /** @brief 方向 */
    typedef enum {
        UP = 0,
        DOWN = 1,
        LEFT = 2,
        RIGHT = 3,
    } Direction;

    /** @brief マップの構成要素 */
    typedef enum {
        /** @brief 道       */ LOAD = 1,
        /** @brief 壁       */ WALL = LOAD * 2,
        /** @brief 部屋     */ ROOM = WALL * 2,
        /** @brief スタート */ START = ROOM * 2 | ROOM,

        /** @brief どれでもない(処理用) */ OTHER = ROOM * 4,
    } MapChip;

    /** @brief 情報(配列管理) */
    template <class Type> class Info : private KNonCopy {
    public:
        /** @brief 横幅       */ const int mWidth;
        /** @brief 縦幅       */ const int mHeight;
        /** @brief 奥行       */ const int mDepth;
        /** @brief 大きさ     */ const int mSize;
        /** @brief 移動(横軸) */ const int mIndexX;
        /** @brief 移動(縦軸) */ const int mIndexY;
        /** @brief 移動(奥行) */ const int mIndexZ;
        /** @breif マップ情報 */ Type * const mInfo;

        Info(const int& x, const int& y = 1, const int& z = 1) :
        mWidth(x), mHeight(y), mDepth(z), mSize(x * y * z),
        mIndexX(y * z), mIndexY(z), mIndexZ(1),
        mInfo(new Type[mSize]) {
        };

        virtual ~Info() {
            delete[] mInfo;
        };

        /** @brief 全要素を引き数値で埋める */
        void init(const Type& aInit) {
            Type* tmp = mInfo;
            for (int i = 0; i < mSize; ++i, ++tmp) *tmp = aInit;
        };
    };

    typedef Info<MapChip> MapInfo; ///< マップ情報

    /* ファイル変換情報 */
    static const int M_START = 0;
    static const int M_ROOM = 1;
    static const int M_WALL = 2;
public:
    /** @brief RADAM_MAPの最大横幅 */ static const int MAX_WIDTH;
    /** @brief RADAM_MAPの最大縦幅 */ static const int MAX_HEIGHT;
    /** @brief RADAM_MAPの最小横幅 */ static const int MIN_WIDTH;
    /** @brief RADAM_MAPの最小縦幅 */ static const int MIN_HEIGHT;

    /** @brief ミニマップ描画色 */
    typedef struct {
        /** @brief プレイヤー描画色 */ color mPlayer;
        /** @brief 壁描画色         */ color mWall;
        /** @brief 床描画色         */ color mFloar;
        /** @brief 枠描画色         */ color mGrid;
    } MiniMapColors;
    /** @brief マップ描画色   */ MiniMapColors mColors;

    /** @briey プレイヤー描画情報 */
    class MapPlayer {
    public:
        /** @brief プレイヤー座標 */ KVector mPosition;
        /** @brief プレイヤー方向 */ KVector mDirection;

        /**
         * @brief プレイヤー描画情報
         * @param aPosition  プレイヤー座標
         * @param aDirection プレイヤー方向
         */
        MapPlayer(const KVector& aPosition, const KVector& aDirection) {
            mPosition = KVector(aPosition.x, aPosition.z);
            mDirection = KVector(aDirection.x, aDirection.z);
        };
        virtual ~MapPlayer() = default;
    };

    /** @brief 1マスのサイズ  */ const float mScale;

    /** @brief 文字列からマップ生成 */ static MapInfo& STRING_MAP(const List<String>& aMap);
    /** @brief ランダムマップ生成   */ static MapInfo& RANDOM_MAP();
    /** @brief 壁伸ばし法で壁を生成 */ static bool wallGrow(MapInfo * const aMap, MapInfo& aPole, KVector& aPoint, bool aExcep[4]);
    /** @brief 部屋の作成           */ static void makeRoom(MapInfo * const aInfo);
    /** @brief 小道の除去           */ static void clean(MapInfo * const aInfo);
protected:

    /** @brief マップ情報配列     */ MapInfo* mMap;
    /** @brief マップ踏破情報配列 */ Info<bool>* mMapping;

    /** @brief スタート位置   */ KVector* mStart;
    /** @brief 壁生成情報     */ List<KRect> mWallInfo;

    List<Wall*> mWalls;

    KRect warpzone; // 

    /** @brief 隣り合ったブロックを繋げる */ void createWall();
public:
    Map(MapInfo& aMap, const int& aChipSize);
    virtual ~Map();

    /** @brief マップの実体化 */ void define();

    /**
     * @brief ミニマップの描画
     * @param aGLUI   描画を行うインターフェース
     * @param aPlayer プレイヤー描画情報
     * @param aRect   描画領域
     * @param aSize   一マスの描画サイズ
     */
    void draw(
            KGLUI& aGLUI,
            const MapPlayer& aPlayer,
            const KRect& aRect,
            const int& aSize);
    /**
     * @brief プレイヤーの描画
     * @param aGLUI   描画を行うインターフェース
     * @param aPlayer プレイヤー描画情報
     * @param aSize   一マスの描画サイズ
     */
    void drawAllow(KGLUI& aGLUI, const MapPlayer& aPlayer, const int& aSize);
    /**
     * @breif 描画の際に使用(部屋を広げる)
     * @param x 対象のx座標
     * @param y 対象のy座標
     */
    void room(const int& x, const int& y);

    /** @return スタート位置       */ KVector start() const;
    /**
     * @brief リスポーン座標を返す
     * @return リスポーン可能座標
     */
    KVector respawn() const;

    /** @return ワープ位置       */ KRect warp() const;

    /**
     * @brief 倍率の取得
     * @return 倍率
     */
    float scale() const;
};

#endif /* MAP_H */
