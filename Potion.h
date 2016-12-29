/**
 * @file   Potion.h
 * @brief  Potion
 * @author Maeda Takumi
 */
#ifndef POTION_H
#define POTION_H

#include "Item.h"

/**
 * @brief  \~english  base of Potion
 * @brief  \~japanese 薬物基底
 * @author \~ Maeda Takumi
 */
class Potion : public Item {
public:
    Potion();
    Potion(const KVector& aPosition);
    Potion(const Potion& orig);
    virtual ~Potion() = default;
};

#endif /* POTION_H */

