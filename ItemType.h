/**
 * @file   ItemType.h
 * @brief  ItemType
 * @author Maeda Takumi
 */
#ifndef ITEMTYPE_H
#define ITEMTYPE_H

/**
 * @brief  \~english  type of Item
 * @brief  \~japanese アイテム種別
 * @author \~ Maeda Takumi
 */
enum ItemType {
    ITEM_POTION,
    EQUIPMENT_WEAPON,
    EQUIPMENT_SHIELD,
    EQUIPMENT_HEAD,
    EQUIPMENT_BODY,
    EQUIPMENT_FOOT,
};

static inline ItemType toItemType(const String& aType) {
    if (aType == "Potion") return EQUIPMENT_WEAPON;
    else if (aType == "Weapon") return EQUIPMENT_WEAPON;
    else if (aType == "Shield") return EQUIPMENT_SHIELD;
    else if (aType == "HeadEquipment") return EQUIPMENT_HEAD;
    else if (aType == "BodyEquipment") return EQUIPMENT_BODY;
    else if (aType == "FootEquipment") return EQUIPMENT_FOOT;
}

#endif /* ITEMTYPE_H */

