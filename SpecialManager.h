/**
 * @file   SpecialManager.cpp
 * @brief  SpecialManager
 * @author Maeda Takumi
 */
#ifndef SPECIALMANAGER_H
#define SPECIALMANAGER_H

#include "main.h"

class Special;

/**
 * @brief  \~english  Special effective manage system
 * @brief  \~japanese 特別効果管理システム
 * @author \~ Maeda Takumi
 */
class SpecialManager : private KNonCopy {
private:
    /**
     * @brief \~english  List of Special(invocation in order from the top.)
     * @brief \~japanese 特殊効果リスト(先頭から順に発動します。)
     */
    static List<Special*> sSpecials;

    SpecialManager() = default;
    virtual ~SpecialManager() = default;
public:

    static void update();

    static void add(Special * const aSpecial);
    static void cutin(Special * const aSpecial);
    
    static bool empty();
};

#endif /* SPECIALMANAGER_H */

