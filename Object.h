/**
 * @file   Object.h
 * @brief  Object
 * @author Maeda Takumi
 */
#ifndef OBJECT_H
#define OBJECT_H

#include "GameState.h"
#include "Parameter.h"

/**
 * @brief  \~english  base of all Object
 * @brief  \~japanese 全てのオブジェクトの基底
 * @author \~ Maeda Takumi
 */
class Object : private KNonCopy {
private:
    /**
     * @brief \~english  list of Object
     * @brief \~japanese Objectリスト
     */
    static List<Object*> sObjects;
    /**
     * @brief \~english  whether updated
     * @brief \~japanese 更新有無
     */
    bool mUpdated;
protected:
    Object();
    virtual ~Object();
public:
    /**
     * @brief \~english  Parameter
     * @brief \~japanese パラメータ
     */
    Parameter mParameter;

    /**
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態の情報
     */
    virtual void update(const GameState& aState) {
    };
    /**
     * @brief \~english  bulk update in list.
     * @brief \~japanese リスト内一括更新。
     */
    static void const UPDATE(const GameState& aState);
    /**
     * @brief \~english  add myself to list.
     * @brief \~japanese リストに自分を追加します。
     */
    void add();
    /**
     * @brief \~english  remove myself form list.
     * @brief \~japanese リストから自分を消します。
     */
    void remove();
};

#endif /* OBJECT_H */

