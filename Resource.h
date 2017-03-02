/**
 * @file   Resource.h
 * @brief  \~english  resource management header
 * @brief  \~japanese リソース管理ヘッダ
 * @author \~ Maeda Takumi
 */

/*
 * リソース使用方法(NetBeans)
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
#define IDI_ENEENE       101
#define IDI_ENEMY        100

// Config.rc
#define ID_CONFIG_MAP_SCALE             51
#define ID_CONFIG_MAP_CEILING_HEIGHT    52
#define ID_CONFIG_MAP_FLOOR_HEIGHT      53
#define ID_CONFIG_ENEMY_SPAWN_MAX       54
#define ID_CONFIG_ENEMY_SPAWN_KIND_MAX  55
#define ID_CONFIG_ITEM_SPAWN_MAX        56

// Index.rc
#define ID_INDEX_CHARACTER 100
#define ID_INDEX_ITEM      200
#define ID_INDEX_SPECIAL   300
#define ID_INDEX_SPAWN     400
#define ID_INDEX_ITEMSPAWN 500
#define ID_INDEX_HERO      ID_INDEX_CHARACTER + 1

#endif /* RESOURCE_H */

