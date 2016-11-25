/**
 * @file main.h
 * @brief ヘッダーファイル
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
#include "KawazuGame.h"

#include "Resource.h"

/** @brief 背景色(白)          */ static const int BACK_COLOR = 0xff00ffff;
/** @brief 秒間更新数          */ static const int FPS = 50;

/** @brief 単位(s : 秒) */
static inline long double operator "" _s(long double aTime) {
    return aTime * FPS;
};

/** @brief 単位(kg : キログラム) */
static inline long double operator "" _kg(long double aWeight) {
    return aWeight / 10;
};

/** @brief 重力加速度 : 9.8(m/s^2) */ static const float GRAVITY = 9.8 / (1.0_s * 1.0_s);
/** @brief 空気抵抗係数(無次元数)  */ static const float AIR_RESISTANCE = 0.05;
/** @brief 水中抵抗係数(無次元数)  */ static const float WATER_RESISTANCE = 0.5;
/** @brief 音速                    */ static const float SONIC = 5;

/** @brief 主人公画像     */ static const KImage IMG_HERO(IDI_HERO);

/** @brief 文字セット画像     */ static const KImage IMG_CHARSET(IDI_CHARSET);
/** @brief 文字セット画像(大) */ static const KImage IMG_CHARSET_BIG(IDI_CHARSET_BIG);
/** @brief 文字セット画像(小) */ static const KImage IMG_CHARSET_MINI(IDI_CHARSET_MINI);

/** @brief 文字セット     */ static const KCharset CHARSET(IMG_CHARSET, 16);
/** @brief 文字セット(大) */ static const KCharset CHARSET_BIG(IMG_CHARSET_BIG, 32);
/** @brief 文字セット(小) */ static const KCharset CHARSET_MINI(IMG_CHARSET_MINI, 8);

#endif /* MAIN_H */
