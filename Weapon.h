/**
 * @file   Weapon.h
 * @brief  Weapon
 * @author Maeda Takumi
 */
#ifndef WEAPON_H
#define WEAPON_H

#include "Equipment.h"

/**
 * @brief  \~english  Base of all Weapons
 * @brief  \~japanese 武器基底
 * @author \~ Maeda Takumi
 */
class Weapon : public Equipment {
public:
    Weapon();
    Weapon(const Weapon& orig) = default;
    virtual ~Weapon() = default;

    /**
     * \~english
     * @brief equip Weapon.
     * @param aChar Character of equipping
     * \~japanese
     * @brief 武器を装備します。
     * @param aChar 装備キャラクター
     */
    virtual void equip(Character& aChar) override;
};

#endif /* WEAPON_H */

