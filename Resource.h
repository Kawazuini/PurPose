/**
 * @file   Resource.h
 * @brief  \~english  resource management header
 * @brief  \~japanese リソース管理ヘッダ
 * @author \~ Maeda Takumi
 */

/*
 * リソース使用方法(NetBeans)
 * 
 * プロジェクト -> プロパティ -> リンカー -> 追加の依存性 -> 「Resource.o」
 * リンカー -> ライブラリ -> オプションの追加 -> その他のオプション -> 「Resource.o」
 * 
 * *.rcファイル  -> プロパティ -> カスタム・ビルド・ステップ
 * -> コマンド行 -> windres *.rc *.o
 * -> 出力       -> *.o
 */

#ifndef RESOURCE_H
#define RESOURCE_H

// Image.rc
#define IDI_CHARSET_SMALL  1
#define IDI_CHARSET_MEDIUM 2
#define IDI_CHARSET_LARGE  3

#define IDI_MONEY       28
#define IDI_ITEM        29
#define IDI_CHARACTER   30
#define IDI_MERCHANT    31
#define IDI_SLIME       32
#define IDI_SLIME2      33
#define IDI_SLIME3      34
#define IDI_FOX         35
#define IDI_FOX2        36
#define IDI_BIRD        37
#define IDI_BIRD2       38
#define IDI_MOTH        39
#define IDI_MOTH2       40
#define IDI_GOBLIN      41

// Config.rc
#define ID_CONFIG_MAP_SCALE             51
#define ID_CONFIG_MAP_CEILING_HEIGHT    52
#define ID_CONFIG_MAP_FLOOR_HEIGHT      53
#define ID_CONFIG_ENEMY_SPAWN_MAX       54
#define ID_CONFIG_ITEM_SPAWN_MAX        55
#define ID_CONFIG_MONEY_SPAWN_MAX       56

// Index.rc
#define ID_INDEX_CHARACTER  100
#define ID_INDEX_ITEM       200
#define ID_INDEX_SPECIAL    300
#define ID_INDEX_SPAWN      400
#define ID_INDEX_ENEMYSPAWN 500
#define ID_INDEX_ITEMSPAWN  600
#define ID_INDEX_EXP        700
#define ID_INDEX_HERO       ID_INDEX_CHARACTER + 1
#define ID_INDEX_MERCHANT   ID_INDEX_CHARACTER + 2
#define ID_INDEX_ENEMY      ID_INDEX_CHARACTER + 3

#endif /* RESOURCE_H */

