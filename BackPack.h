/**
 * @file   BackPack.h
 * @brief  BackPack
 * @author Maeda Takumi
 */
#ifndef BACKPACK_H
#define BACKPACK_H

#include "main.h"

class Item;

/**
 * @brief  \~english  Item bag
 * @brief  \~japanese アイテム袋
 * @author \~ Maeda Takumi
 */
class BackPack {
private:
    static const int MAX_DRAW_LINE;

    /**
     * @brief \~english  Item bag
     * @brief \~japanese アイテム袋
     */
    Vector<Stack<Item*>*> mBackPack;
    /**
     * @brief \~english  Item select cursor
     * @brief \~japanese アイテム選択カーソル
     */
    int mCursor;
    /**
     * @brief \~english  sum weight in bag
     * @brief \~japanese 総重量
     */
    float mWeight;

    int mDrawBegin;
    int mDrawEnd;
public:
    BackPack();
    virtual ~BackPack();

    /**
     * \~english
     * @brief change selected Item.
     * @param aAmount change amount
     * \~japanese
     * @brief 選択アイテムを変更します。
     * @param aAmount 選択変更量
     */
    void selectChange(const int& aAmount);

    /**
     * \~english
     * @brief  get reference selected Item.
     * @return selected Item's reference
     * \~japanese
     * @brief  選択アイテムを参照します。
     * @return 選択アイテム
     */
    Item* lookAt();
    /**
     * \~english
     * @brief  get reference selected Item.
     * @return selected Item's reference
     * \~japanese
     * @brief  選択アイテムを参照します。
     * @return 選択アイテム
     */
    const Item * lookAt() const;
    /**
     * \~english
     * @brief  get stack number selected Item.
     * @return selected Item's stack number
     * \~japanese
     * @brief  選択アイテムの保持数を取得します。
     * @return 選択アイテムの保持数
     */
    int lookCount(const int& aID = 0) const;
    /**
     * \~english
     * @brief  add items to the backpack.
     * @param  aItem added Item
     * \~japanese
     * @brief  バックパックにアイテムを追加しますか。
     * @param  aItem 追加アイテム
     */
    void add(Item& aItem);
    /**
     * \~english
     * @brief  take out selected Item.
     * @return selected Item
     * \~japanese
     * @brief  選択アイテムを取り出します。
     * @return 選択アイテム
     */
    Item* takeOut(const int& aID = 0);

    /**
     * @brief \~english  clear all item.
     * @brief \~japanese アイテムを全消去します。
     */
    void clear();

    /**
     * \~english
     * @brief drawing processing
     * @param aGLUI drawing UI
     * @param aRect drawing area
     * \~japanese
     * @brief 描画処理
     * @param aGLUI 描画UI
     * @param aRect 描画領域
     */
    void draw(KGLUI& aGLUI, const KRect& aRect) const;

    /**
     * \~english
     * @brief  get sum weight
     * @return sum weight
     * \~japanese
     * @brief  総重量を取得します。
     * @return 総重量
     */
    const float& weight() const;
};

#endif /* BACKPACK_H */

