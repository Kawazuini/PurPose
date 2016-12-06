/**
 * @file   Equipment.cpp
 * @brief  Equipment
 * @author Maeda Takumi
 */
#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"

/**
 * @brief  \~english  Base of all Equipments
 * @brief  \~japanese 装備基底
 * @author \~ Maeda Takumi
 */
class Equipment : public Item {
protected:
public:
    Equipment();
    Equipment(const Equipment& orig) = default;
    virtual ~Equipment() = default;
};

#endif /* EQUIPMENT_H */

