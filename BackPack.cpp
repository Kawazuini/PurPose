/**
 * @file   BackPack.cpp
 * @brief  BackPack
 * @author Maeda Takumi
 */
#include "BackPack.h"

#include "Item.h"

const int BackPack::MAX_DRAW_LINE(31);

BackPack::BackPack() :
mCursor(0),
mDrawBegin(0),
mDrawEnd(MAX_DRAW_LINE) {
}

BackPack::~BackPack() {
    clear();
}

void BackPack::selectChange(const int& aAmount) {
    mCursor += aAmount;
    int end(mBackPack.size() - 1);
    if (mCursor > end) mCursor = 0;
    else if (mCursor < 0) mCursor = end;

    if (mCursor < mDrawBegin) {
        mDrawBegin = mCursor;
        mDrawEnd = mDrawBegin + MAX_DRAW_LINE;
    }
    if (mDrawEnd <= mCursor) {
        mDrawEnd = mCursor + 1;
        mDrawBegin = mDrawEnd - MAX_DRAW_LINE;
    }
}

Item* BackPack::lookAt() {
    if (!mBackPack.empty()) {
        return mBackPack[mCursor]->top();
    } else return NULL;
}

const Item * BackPack::lookAt() const {
    if (!mBackPack.empty()) {
        return mBackPack[mCursor]->top();
    } else return NULL;
}

int BackPack::lookCount(const int& aID) const {
    if (!mBackPack.empty()) {
        if (!aID) return mBackPack[mCursor]->size(); // ID指定なし
        for (Stack<Item*>* i : mBackPack) {
            if (i->top()->param().mID == aID) {
                return i->size();
            }
        }
    }
    return 0;
}

void BackPack::add(Item& aItem) {
    String name(aItem.param().mName);
    Stack<Item*>* target(NULL);
    for (Stack<Item*>* i : mBackPack) {
        if (i->top()->param().mName == name) { // すでにバッグに入っている
            target = i;
            break;
        }
    }
    if (!target) { // 新規アイテム登録
        mBackPack.push_back(target = new Stack<Item*>());
    }
    target->push(&aItem);
    mWeight += aItem.param().mWeight;
}

Item* BackPack::takeOut(const int& aID) {
    Item * item(NULL);
    if (!mBackPack.empty()) {
        int count(0);
        Stack<Item*>* target;
        bool search(false);
        if (!aID) { // ID指定なし
            count = mCursor;
            search = true;
        } else {
            for (Stack<Item*>* i : mBackPack) {
                if (i->top()->param().mID == aID) {
                    search = true;
                    break;
                }
                count++;
            }
        }
        if (search) {
            target = mBackPack[count];
            if (!target->empty()) {
                item = target->top();
                target->pop();
                mWeight -= item->param().mWeight;
            }
            if (target->empty()) { // アイテム使い切り
                mBackPack.erase(mBackPack.begin() + count);
                // カーソルが末尾ならずらす
                if (!(mBackPack.size() - mCursor)) mCursor = Math::max(0, mCursor - 1);
            }
        }
    }
    return item;
}

void BackPack::clear() {
    for (Stack<Item*>* i : mBackPack) {
        while (!i->empty()) {
            delete i->top();
            i->pop();
        }
        delete i;
    }
    mBackPack.clear();
}

void BackPack::draw(KGLUI& aGLUI, const KRect& aRect) const {
    static const int SIZE(CHARSET_MINI.mSize * 2);
    static const color BASE(0x7700cc00);
    static const KVector MARGIN(1, 1);

    aGLUI.mScreen.clearRect(aRect);
    aGLUI.mScreen.drawClearRect(aRect, BASE);


    KRect listArea(aRect.x + 2, aRect.y + 2, aRect.width / 2 - 4, aRect.height - 4);
    aGLUI.mScreen.drawClearRect(listArea, BASE);

    // カーソルの描画
    int cursor(Math::min(MAX_DRAW_LINE - 1, mCursor - mDrawBegin));
    KRect cursorRect(
            listArea.x + 2,
            listArea.y + 2 + cursor * SIZE,
            listArea.width - 3,
            SIZE - 4
            );
    aGLUI.mScreen.drawRect(cursorRect, BASE);

    auto item(mBackPack.begin() + mDrawBegin), end(mBackPack.end());
    for (int i = 0; i < MAX_DRAW_LINE && item != end; ++i, ++item) {
        String equipSign((*item)->top()->mEquipped ? "E " : "  ");
        aGLUI.mScreen.drawText(// アイテム名
                CHARSET_MINI,
                equipSign + (*item)->top()->param().mName,
                KVector(listArea.x, listArea.y + i * SIZE) + MARGIN,
                0xffffffff
                );
        String number(toString((*item)->size()));
        aGLUI.mScreen.drawText(// アイテム個数
                CHARSET_MINI,
                number,
                KVector(listArea.right() - CHARSET_MINI.getWidth(number) - 1, listArea.y + i * SIZE + 1),
                0xffffffff
                );
    }
    aGLUI.mScreen.drawText(// カーソル位置
            CHARSET_MINI,
            toString(mCursor + 1) + "/" + toString(mBackPack.size()),
            KVector(listArea.x + 3, listArea.bottom() - SIZE) - MARGIN,
            0xffffffff
            );
    String weight("総重量 : " + toString(mWeight));
    aGLUI.mScreen.drawText(// 総重量
            CHARSET_MINI,
            weight,
            KVector(listArea.right() - CHARSET_MINI.getWidth(weight), listArea.bottom() - SIZE) - MARGIN,
            0xffffffff
            );

    KRect introArea(aRect);
    introArea.width /= 2;
    introArea.x += introArea.width;

    aGLUI.mScreen.drawClearRect(KRect(introArea.x + 2, introArea.y + 2, introArea.width - 4, introArea.height - 4), BASE);

    const Item * selectedItem(lookAt());
    if (selectedItem) {
        int line(0);
        aGLUI.mScreen.drawText(// アイテム名
                CHARSET_MINI,
                selectedItem->param().mName,
                KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                0xffffffff
                );

        line++; // 改行
        aGLUI.mScreen.drawText(// 大きさ
                CHARSET_MINI,
                "サイズ　　 : " + toString(selectedItem->param().mSize) + " m",
                KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                0xffffffff
                );
        aGLUI.mScreen.drawText(// 重量
                CHARSET_MINI,
                "重量　　　 : " + toString(selectedItem->param().mWeight) + " kg",
                KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                0xffffffff
                );

        if (selectedItem->param().mUsable) {
            aGLUI.mScreen.drawText(// 特殊効果
                    CHARSET_MINI,
                    "使用効果　 : ",
                    KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                    0xffffffff
                    );

            String text("　　使うと");
            Special special(selectedItem->param().mSpecial);
            switch (special.type()) {
                case SPECIAL_HEAL: text += "HPが" + toString((int) special.value()) + "回復します。";
                    break;
            }
            aGLUI.mScreen.drawText(// 特殊効果
                    CHARSET_MINI,
                    text,
                    KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                    0xffffffff
                    );
            aGLUI.mScreen.drawText(// 使用コスト
                    CHARSET_MINI,
                    "使用コスト : " + toString(selectedItem->param().mCost) + "ターン",
                    KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                    0xffffffff
                    );
        }

        if (selectedItem->param().mEquippable) {
            ItemType type(selectedItem->param().mItemType);
            if (type == WEAPON_SWORD || type == WEAPON_BOW || type == WEAPON_GUN) { // 武器
                aGLUI.mScreen.drawText(// 攻撃力
                        CHARSET_MINI,
                        "攻撃力　　 : " + toString(selectedItem->param().mPower),
                        KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                        0xffffffff
                        );
                aGLUI.mScreen.drawText(// 有効射程
                        CHARSET_MINI,
                        "有効射程　 : " + toString(selectedItem->param().mEffectiveRange) + " m",
                        KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                        0xffffffff
                        );
                aGLUI.mScreen.drawText(// 有効範囲
                        CHARSET_MINI,
                        "有効範囲　 : " + toString(selectedItem->param().mEffectiveAngle) + "°",
                        KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                        0xffffffff
                        );
                if (type == WEAPON_BOW || type == WEAPON_GUN) {
                    aGLUI.mScreen.drawText(// 装填数
                            CHARSET_MINI,
                            "装填数　　 : " + toString(selectedItem->param().mStack),
                            KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                            0xffffffff
                            );
                }
                aGLUI.mScreen.drawText(// 攻撃コスト
                        CHARSET_MINI,
                        "攻撃コスト : " + toString(selectedItem->param().mCost) + "ターン",
                        KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                        0xffffffff
                        );
            } else {
                aGLUI.mScreen.drawText(// 防御力
                        CHARSET_MINI,
                        "防御力　　 : " + toString(selectedItem->param().mPower),
                        KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                        0xffffffff
                        );
            }
        }
    }
}

const float& BackPack::weight() const {
    return mWeight;
}

