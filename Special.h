/**
 * @file   Special.h
 * @brief  Special
 * @author Maeda Takumi
 */
#ifndef SPECIAL_H
#define SPECIAL_H

#include "main.h"

class Object;

/**
 * @brief  \~english  Special effective
 * @brief  \~japanese 特殊効果
 * @author \~ Maeda Takumi
 */
class Special {
    friend class SpecialManager;
private:
    /**
     * @brief \~english  ID distributor
     * @brief \~japanese ID分配用変数
     */
    static int sIDDistributor;
protected:
    const int mID; ///< @brief ID
    /**
     * @brief \~english  Special effect principal object
     * @brief \~japanese 特殊効果主体オブジェクト
     */
    Object* mSubject;
    /**
     * @brief \~english  Special effect target object
     * @brief \~japanese 特殊効果対象オブジェクト
     */
    Object* mObject;

    Special(Object * const aSubject = NULL, Object * const aObject = NULL);
    Special(const Special& orig) = default;
    virtual ~Special() = default;

    /**
     * @brief \~english  effect invocation.
     * @brief \~japanese 効果の発動。
     */
    virtual void special() {
    };
};

#endif /* SPECIAL_H */

