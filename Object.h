/**
 * @file   Object.h
 * @brief  Object
 * @author Maeda Takumi
 */
#ifndef OBJECT_H
#define OBJECT_H

#include "main.h"

class GameState;

/**
 * @brief  \~english  base of all Object
 * @brief  \~japanese 全てのオブジェクトの基底
 * @author \~ Maeda Takumi
 */
class Object : private KNonCopy {
private:
    /* ID割り当て変数 */ static int sIDDistributor;
    /* ID             */ const int mID;
    /* Objectリスト   */ static List<Object*> sObjects;
    /* 更新状態       */ bool mUpdated;
protected:
    Object();
    virtual ~Object();
public:

    /**
     * \~english
     * @brief update processing
     * @param aState information of game state
     * \~japanese
     * @brief 更新処理
     * @param aState ゲーム状態
     */
    virtual void update(GameState& aState) = 0;
    /**
     * \~english
     * @brief bulk update in list.
     * @param aState nformation of game state
     * \~japanese
     * @brief リスト内一括更新。
     * @param aState ゲーム状態
     */
    static void const UPDATE(GameState& aState);
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

