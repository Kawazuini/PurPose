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
     * @brief \~english  
     * @brief \~japanese 描画更新有無
     */
    bool mUpdated;
public:
    BackPack();
    virtual ~BackPack();

    /**
     * \~english
     * @brief  add items to the backpack.
     * @param  aItem added Item
     * @return whether Item could be added
     * \~japanese
     * @brief  バックパックにアイテムを追加しますか。
     * @param  aItem 追加アイテム
     * @return アイテムを追加できたか
     */
    bool add(Item * const aItem);

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
     * @brief  take out selected Item.
     * @return selected Item
     * \~japanese
     * @brief  選択アイテムを取り出します。
     * @return 選択アイテム
     */
    Item* takeOut();
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
    const Item * const lookAt() const;

    /**
     * \~english
     * @brief  look for reference Item by id.
     * @return result Item's reference
     * \~japanese
     * @brief  IDでアイテムを探します。
     * @return 検索結果のアイテム
     */
    Item* lookFor(const int& ID);

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
};

#endif /* BACKPACK_H */

