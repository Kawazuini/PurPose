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

#define ID_CONFIG_MAP_SCALE             51
#define ID_CONFIG_MAP_CEILING_HEIGHT    52
#define ID_CONFIG_MAP_FLOOR_HEIGHT      53
#define ID_CONFIG_ENEMY_SPAWN_MAX       54
#define ID_CONFIG_ENEMY_SPAWN_KIND_MAX  55
#define ID_CONFIG_ITEM_SPAWN_MAX        56
#define ID_CONFIG_ITEM_SPAWN_KIND_MAX   57
#define ID_CONFIG_ITEM_POTION_KIND      58
#define ID_CONFIG_ITEM_ARROW_KIND       59
#define ID_CONFIG_ITEM_BULLET_KIND      60
#define ID_CONFIG_WEAPON_SWORD_KIND     61
#define ID_CONFIG_WEAPON_BOW_KIND       62
#define ID_CONFIG_WEAPON_GUN_KIND       63
#define ID_CONFIG_EQUIPMENT_SHIELD_KIND 64
#define ID_CONFIG_EQUIPMENT_HEAD_KIND   65
#define ID_CONFIG_EQUIPMENT_BODY_KIND   66
#define ID_CONFIG_EQUIPMENT_FOOT_KIND   67

#define ID_ENEMY  100
#define ID_ENEENE 101

static const int ID_HERO(300);

#define ID_ITEM              500
#define ID_ITEM_POTION       500
#define ID_ITEM_ARROW        600
#define ID_ITEM_BULLET       700
#define ID_WEAPON_SWORD      800
#define ID_WEAPON_BOW        900
#define ID_WEAPON_GUN       1000
#define ID_EQUIPMENT_SHIELD 1100
#define ID_EQUIPMENT_HEAD   1200
#define ID_EQUIPMENT_BODY   1300
#define ID_EQUIPMENT_FOOT   1400

#define ID_SPAWNTABLE 10000

#endif /* RESOURCE_H */

