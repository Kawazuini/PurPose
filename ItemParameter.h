/**
 * @file   ItemParameter.h
 * @brief  ItemParameter
 * @author Maeda Takumi
 */
#ifndef ITEMPARAMETER_H
#define ITEMPARAMETER_H

#include "main.h"

/**
 * @brief  \~english  Parameter of Item
 * @brief  \~japanese アイテムパラメータ
 * @author \~ Maeda Takumi
 */
class ItemParameter {
public:
    /**
     * @brief \~english  name of Item
     * @brief \~japanese アイテム名
     */
    String mName;

    ItemParameter() = default;
    virtual ~ItemParameter() = default;
};

#endif /* ITEMPARAMETER_H */

