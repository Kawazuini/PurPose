/**
 * @file   Resource.h
 * @brief  \~english  resource management header
 * @brief  \~japanese リソース管理ヘッダ
 * @author \~ Maeda Takumi
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

#define IDI_CHARSET      1
#define IDI_CHARSET_BIG  2
#define IDI_CHARSET_MINI 3

#define ID_CONFIG_MAP_SCALE          51
#define ID_CONFIG_MAP_CEILING_HEIGHT 52
#define ID_CONFIG_MAP_FLOOR_HEIGHT   53
#define ID_CONFIG_SPAWN_MAX          54

static const int ID_ENEMY(100);
static const int ID_ENEMY_SLIME(ID_ENEMY + 1);

static const int ID_HERO(300);

static const int ID_ITEM(500);
static const int ID_ITEM_POTION(ID_ITEM + 1);

static const int ID_SPAWNTABLE(1000);

#endif /* RESOURCE_H */

