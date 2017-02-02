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

#define ID_MAP_SCALE          51 
#define ID_MAP_CEILING_HEIGHT 52
#define ID_MAP_FLOAR_HEIGHT   53
#define ID_MAP_MAX_WIDTH      54
#define ID_MAP_MAX_HEIGHT     55

static const int ID_ENEMY(100);
static const int ID_ENEMY_SLIME(ID_ENEMY + 1);

static const int ID_HERO(300);

static const int ID_ITEM(500);
static const int ID_ITEM_POTION(ID_ITEM + 1);

#define IDI_CHARSET      1022
#define IDI_CHARSET_BIG  1023
#define IDI_CHARSET_MINI 1024

#endif /* RESOURCE_H */

