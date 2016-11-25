/**
 * @file BackPack.h
 * @brief BackPack
 */
#ifndef BACKPACK_H
#define BACKPACK_H

#include "Item.h"

/** @brief バックパック */
class BackPack {
private:
    /** @brief バックパック最大容量   */ static const int MAX_CAPACITY = 99;
    /** @brief アイテム毎の最大所持数 */ static const int MAX_PER_CAPACITY = 99;

    /** @brief アイテムリスト */ Item* mItemList[MAX_CAPACITY][MAX_PER_CAPACITY];
    /** @brief 選択アイテム   */ int mCursor;
    /** @brief アイテム種数   */ int mStack;
    /** @brief 所持アイテム数 */ int mPerStack[MAX_CAPACITY];
public:
    BackPack();
    BackPack(const BackPack& orig) = delete;
    virtual ~BackPack();

    bool use();
    /**
     * @brief バックパックにアイテムを追加
     * @param aItem 追加アイテム
     */
    void add(Item * const aItem);
    void dump();
    
    /**
     * @brief 選択アイテムの変更
     * @param aMoment 選択変更量
     */
    void selectChange(const int& aMoment);

    /**
     * @brief 描画処理
     * @param aGLUI 描画UI
     */
    void draw(KGLUI& aGLUI, const KRect& aRect);
};

#endif /* BACKPACK_H */
