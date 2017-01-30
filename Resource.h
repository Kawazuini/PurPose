/**
 * @file Resource.h
 * @brief リソース管理ヘッダ
 */

/*
 * リソース使用方法
 * 
 * プロジェクト → プロパティ → リンカー → 追加の依存性 → 「Resource.o」
 * リンカー → ライブラリ → オプションの追加 → その他のオプション → 「Resource.o」(-無)
 * 
 * *.rcファイル → プロパティ → カスタム・ビルド・ステップ
 * → コマンド行 → windres *.rc *.o
 * → 出力 → *.o
 */
#ifndef RESOURCE_H
#define RESOURCE_H

#define IDI_HERO 2

#define IDI_CHARSET      1022
#define IDI_CHARSET_BIG  1023
#define IDI_CHARSET_MINI 1024

static const int ID_ENEMY(100);
static const int ID_ENEMY_SLIME(ID_ENEMY + 1);

static const int ID_HERO(300);

static const int ID_ITEM(500);
static const int ID_ITEM_POTION(ID_ITEM + 1);

#endif /* RESOURCE_H */
