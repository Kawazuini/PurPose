/**
 * @file   BackPack.cpp
 * @brief  BackPack
 * @author Maeda Takumi
 */
#ifndef BACKPACK_H
#define BACKPACK_H

#include "Item.h"

/** @brief バックパック */
class BackPack {
private:
    /** @brief バックパック最大容量   */ static const int MAX_CAPACITY = 99;
    /** @brief アイテム毎の最大所持数 */ static const int MAX_PER_CAPACITY = 99;

    int m;
    /** @brief アイテムリスト */ Item* mItemList[MAX_CAPACITY][MAX_PER_CAPACITY];
    /** @brief 選択アイテム   */ int mCursor;
    /** @brief アイテム種数   */ int mStack;
    /** @brief 所持アイテム数 */ int mPerStack[MAX_CAPACITY];
public:
    BackPack();
    BackPack(const BackPack& orig) = delete;
    virtual ~BackPack() = default;

    /**
     * @brief バックパックにアイテムを追加
     * @param aItem 追加アイテム
     */
    void add(Item * const aItem);
    void dump();

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
     * @brief drawing processing
     * @param aGLUI drawing UI
     * \~japanese
     * @brief 描画処理
     * @param aGLUI 描画UI
     */
    void draw(KGLUI& aGLUI, const KRect& aRect) const;
};

#endif /* BACKPACK_H */
