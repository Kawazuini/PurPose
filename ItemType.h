/**
 * @file   ItemType.h
 * @brief  ItemType
 * @author Maeda Takumi
 */
#ifndef ITEMTYPE_H
#define ITEMTYPE_H

/// @brief  \~english  type of Item
/// @brief  \~japanese アイテム種別

enum ItemType {
    ITEM_POTION,
    ITEM_FOOD,
    ITEM_BOMB,
    ITEM_ARROW,
    ITEM_AMMO,
    WEAPON_SWORD,
    WEAPON_BOW,
    WEAPON_GUN,
    EQUIPMENT_SHIELD,
    EQUIPMENT_HEAD,
    EQUIPMENT_BODY,
    EQUIPMENT_FOOT,
};

/**
 * \~english
 * @brief  convert String to ItemType.
 * @param  aType String
 * @return ItemType
 * \~japanese
 * @brief  文字列をアイテム種別に変換します。
 * @param  aType 文字列
 * @return アイテム種別
 */
static inline ItemType toItemType(const String& aType) {
    if (aType == "Potion") return ITEM_POTION;
    else if (aType == "Food") return ITEM_FOOD;
    else if (aType == "Bomb") return ITEM_BOMB;
    else if (aType == "Arrow") return ITEM_ARROW;
    else if (aType == "Ammo") return ITEM_AMMO;
    else if (aType == "Sword") return WEAPON_SWORD;
    else if (aType == "Bow") return WEAPON_BOW;
    else if (aType == "Gun") return WEAPON_GUN;
    else if (aType == "Shield") return EQUIPMENT_SHIELD;
    else if (aType == "HeadEquipment") return EQUIPMENT_HEAD;
    else if (aType == "BodyEquipment") return EQUIPMENT_BODY;
    else if (aType == "FootEquipment") return EQUIPMENT_FOOT;
}

#endif /* ITEMTYPE_H */

