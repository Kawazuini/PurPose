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
    Potion(const int& aID, const KVector& aPosition);
    virtual ~Potion() = default;

    virtual void use(Character& aChar);
};

#endif /* POTION_H */

