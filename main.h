/**
 * @file   main.h
 * @brief  Project Headder
 * @author Maeda Takumi
 */

/*
 * Kawazuini.h使用方法(NetBeansの場合)
 * c++コンパイラ -> インクルードディレクトリ -> Kawazuini
 * c++コンパイラ -> c++標準                  -> c++11
 * c++コンパイラ -> 追加のオプション         -> -mwindows
 * 
 * リンカー -> ライブラリ -> プロジェクトの追加(Kawazuini)
 * リンカー -> ライブラリ -> オプションの追加 -> 静的バインド
 *                                            -> その他のオプション
 * -> -lgdi32, -lgdiplus, -lOle32, -lmsimg32, -lwinmm -lOpenGL32 -lGLU32
 */

#ifndef MAIN_H
#define MAIN_H

#include "Kawazuini.h"

#include "Resource.h"

/** @brief 秒間更新数   */ static const int FPS(50);

/** @brief 単位(s : 秒) */
static inline long double operator "" _s(long double aTime) {
    return aTime * FPS;
};

/** @brief 文字セット画像(小) */ static const KImage IMG_CHARSET_SMALL(IDI_CHARSET_SMALL);
/** @brief 文字セット画像(中) */ static const KImage IMG_CHARSET_MEDIUM(IDI_CHARSET_MEDIUM);
/** @brief 文字セット画像(大) */ static const KImage IMG_CHARSET_LARGE(IDI_CHARSET_LARGE);
/** @brief アイテム画像       */ static const KImage IMG_ITEM(IDI_ITEM);

/** @brief 文字セット(小) */ static const KCharset CHARSET_SMALL(IMG_CHARSET_SMALL, 8);
/** @brief 文字セット(中) */ static const KCharset CHARSET(IMG_CHARSET_MEDIUM, 16);
/** @brief 文字セット(大) */ static const KCharset CHARSET_LARGE(IMG_CHARSET_LARGE, 32);

/**
 * @brief \~english  drawing with phong shading and noise for x normal
 * @brief \~japanese フォンシェーディングと法線がx軸と平行の時のノイズでの描画
 */
extern KShader* CthulhuXShading;
/**
 * @brief \~english  drawing with phong shading and noise for x normal
 * @brief \~japanese フォンシェーディングと法線がy軸と平行の時のノイズでの描画
 */
extern KShader* CthulhuYShading;
/**
 * @brief \~english  drawing with phong shading and noise for x normal
 * @brief \~japanese フォンシェーディングと法線がz軸と平行の時のノイズでの描画
 */
extern KShader* CthulhuZShading;

extern String PlayerName;

#endif /* MAIN_H */

