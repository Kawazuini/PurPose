/**
 * @file   Object.h
 * @brief  Object
 * @author Maeda Takumi
 */
#ifndef OBJECT_H
#define OBJECT_H

#include "Parameter.h"

/**
 * @brief  \~english  base of all Object
 * @brief  \~japanese 全てのオブジェクトの基底
 * @author \~ Maeda Takumi
 */
class Object {
public:
    /**
     * @brief \~english  Parameter
     * @brief \~japanese パラメータ
     */
    Parameter mParameter;
    Object();
    Object(const Object& orig);
    virtual ~Object();
};

#endif /* OBJECT_H */

