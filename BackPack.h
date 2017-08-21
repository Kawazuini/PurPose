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
class BackPack final : public KDrawer, private KUpdater {
private:
    /* リスト描画最大列数   */ static const int MAX_DRAW_LINE;

    static const KRect DRAWAREA_BACKPACK;
    static const KRect DRAWAREA_ITEM;
    static const KRect DRAWAREA_CONTENT;
    static const color COLOR_BASE;
    static const color COLOR_TEXT;

    KGLUI mUI;
    bool mChange;

    /* アイテム袋           */ Vector<List<Item*>*> mBackPack;
    /* アイテム選択カーソル */ int mCursor;
    /* 総重量               */ float mWeight;

    /* 描画開始位置         */ int mDrawBegin;
    /* 描画終了位置         */ int mDrawEnd;

    /* 小数以下の桁合わせ(描画で使用) */
    static inline String digit(float aValue) {
        StringStream digit;
        digit << std::fixed << std::setprecision(3) << std::setw(6) << aValue;
        return digit.str();
    };
public:
    BackPack(const KCamera& aCamera);
    ~BackPack();

    void draw() const override;
    void update() override;

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
     * @param  aID selection ID (When it is 0, it returns the number of selected items)
     * @return selected Item's stack number
     * \~japanese
     * @brief  選択アイテムの保持数を取得します。
     * @param  aID 選択ID(0の時は選択中のアイテムの個数を返します)
     * @return 選択アイテムの保持数
     */
    int lookCount(const int& aID = 0) const;
    /**
     * \~english
     * @brief  add items to the backpack.
     * @param  aItem added Item
     * \~japanese
     * @brief  バックパックにアイテムを追加します。
     * @param  aItem 追加アイテム
     */
    void add(Item& aItem);
    /**
     * \~english
     * @brief  take out selected Item.
     * @param  aCount number of item
     * @param  aID ID for search
     * @return selected Item
     * \~japanese
     * @brief  選択アイテムを取り出します。
     * @param  aCount アイテムの個数
     * @param  aID 検索用ID
     * @return 選択アイテム
     */
    Item* takeOut(const int& aCount = 1, const int& aID = 0);

    /// @brief \~english  sort items by ID.
    /// @brief \~japanese アイテムをIDでソートします。
    void sort();

    /// @brief \~english  clear all item.
    /// @brief \~japanese アイテムを全消去します。
    void clear();

    const float& weight() const;
};

#endif /* BACKPACK_H */

