/**
 * @file   main.h
 * @brief  プロジェクトヘッダ(Project Headder)
 * @author Maeda Takumi
 */

/*
 * Kawazuii.h使用方法
 * c++コンパイラ → インクルードディレクトリ → Kawazuini
 * リンカー → ライブラリ → プロジェクトの追加(Kawazuini)
 * 
 * c++コンパイラ → 追加のオプション → "-mwindows"
 * c++コンパイラ → c++標準 → c++11
 * 
 * リンカー → ライブラリ → オプションの追加 → 静的バインド
 * その他のオプション→ -lgdi32, -lgdiplus, -lOle32, -lmsimg32, -lwinmm -lOpenGL32 -lGLU32
 */

#ifndef MAIN_H
#define MAIN_H

#include "Kawazuini.h"

#include "Resource.h"

/** @brief 秒間更新数          */ static const int FPS = 50;

/** @brief 単位(s : 秒) */
static inline long double operator "" _s(long double aTime) {
    return aTime * FPS;
};

/** @brief 文字セット画像     */ static const KImage IMG_CHARSET(IDI_CHARSET);
/** @brief 文字セット画像(大) */ static const KImage IMG_CHARSET_BIG(IDI_CHARSET_BIG);
/** @brief 文字セット画像(小) */ static const KImage IMG_CHARSET_MINI(IDI_CHARSET_MINI);

/** @brief 敵画像 */ static const KImage IMG_ENEMY(ID_ENEENE);

/** @brief 文字セット     */ static const KCharset CHARSET(IMG_CHARSET, 16);
/** @brief 文字セット(大) */ static const KCharset CHARSET_BIG(IMG_CHARSET_BIG, 32);
/** @brief 文字セット(小) */ static const KCharset CHARSET_MINI(IMG_CHARSET_MINI, 8);

extern KShader* NoneShading;
extern KShader* PhongShading;
extern KShader* CthulhuXShading;
extern KShader* CthulhuYShading;
extern KShader* CthulhuZShading;

#endif /* MAIN_H */
