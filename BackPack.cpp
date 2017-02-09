/**
 * @file   BackPack.cpp
 * @brief  BackPack
 * @author Maeda Takumi
 */
#include "BackPack.h"

#include "Item.h"

BackPack::BackPack() :
mCursor(0) {
}

BackPack::~BackPack() {
    for (Stack<Item*>* i : mBackPack) {
        while (!i->empty()) {
            delete i->top();
            i->pop();
        }
        delete i;
    }
}

bool BackPack::add(Item * const aItem) {
    String name(aItem->param().mName);
    for (Stack<Item*>* i : mBackPack) {
        // すでにバッグに入っている
        if (i->top()->param().mName == name) {
            i->push(aItem);
            return true;
        }
    }
    // 新規アイテム登録
    Stack<Item*>* tmp = new Stack<Item*>();
    tmp->push(aItem);
    mBackPack.push_back(tmp);
    return true;
}

void BackPack::selectChange(const int& aAmount) {
    mCursor += aAmount;
    if (mCursor > (int) (mBackPack.size() - 1)) mCursor = 0;
    else if (mCursor < 0) mCursor = mBackPack.size() - 1;
}

Item* BackPack::takeOut() {
    if (!mBackPack.empty()) {
        Stack<Item*>* cursor = mBackPack[mCursor];
        if (!cursor->empty()) {
            Item* item = cursor->top();
            cursor->pop();
            if (cursor->empty()) { // アイテム使い切り
                mBackPack.erase(mBackPack.begin() + mCursor);
                // カーソルが末尾
                if (!(mBackPack.size() - mCursor))
                    mCursor = Math::max(0, mCursor - 1);
            }
            return item;
        }
        return NULL;
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

Item* BackPack::lookFor(const int& ID) {
    int count(0);
    for (Stack<Item*>* i : mBackPack) {
        if (i->top()->param().mID == ID) {
            if (!i->empty()) {
                Item * item(i->top());
                i->pop();
                if (i->empty()) { // アイテム使い切り
                    mBackPack.erase(mBackPack.begin() + count);
                    // カーソルが末尾
                    if (!(mBackPack.size() - mCursor))
                        mCursor = Math::max(0, mCursor - 1);
                }
                return item;
            }
        }
        count++;
    }
    return NULL;
}

void BackPack::draw(KGLUI& aGLUI, const KRect& aRect) const {
    static const int SIZE(CHARSET_MINI.mSize * 2);
    static const color BASE(0x7700cc00);

    aGLUI.mScreen.clearRect(aRect);
    aGLUI.mScreen.drawClearRect(aRect, BASE);

    KRect listArea(aRect);
    listArea.width /= 2;

    aGLUI.mScreen.drawClearRect(KRect(listArea.x + 2, listArea.y + 2, listArea.width - 4, listArea.height - 4), BASE);
    aGLUI.mScreen.drawRect(KRect(listArea.x + 5, listArea.y + 5 + mCursor * SIZE, listArea.width - 8, SIZE), BASE);

    int line(0);
    for (Stack<Item*>* i : mBackPack) {
        String equipSign(i->top()->mEquipped ? "E " : "  ");
        aGLUI.mScreen.drawText(// アイテム名
                CHARSET_MINI,
                equipSign + i->top()->param().mName,
                KVector(listArea.x + 5, listArea.y + line * SIZE + 5),
                0xffffffff
                );
        String number(toString(i->size()));
        aGLUI.mScreen.drawText(// アイテム個数
                CHARSET_MINI,
                number,
                KVector(listArea.right() - CHARSET_MINI.getWidth(number) - 5, listArea.y + line * SIZE + 5),
                0xffffffff
                );
        ++line;
    }

    KRect introArea(aRect);
    introArea.width /= 2;
    introArea.x += introArea.width;

    aGLUI.mScreen.drawClearRect(KRect(introArea.x + 2, introArea.y + 2, introArea.width - 4, introArea.height - 4), BASE);

    const Item * selectedItem(lookAt());
    if (selectedItem) {
        line = 0;
        aGLUI.mScreen.drawText(// アイテム名
                CHARSET_MINI,
                selectedItem->param().mName,
                KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                0xffffffff
                );
        if (selectedItem->param().mUsable) {
            String text("使うと");
            Special special(selectedItem->param().mSpecial);
            switch (special.type()) {
                case HEAL: text += "HPが" + toString((int) special.value()) + "回復します。";
                    break;
            }
            aGLUI.mScreen.drawText(// 特殊効果
                    CHARSET_MINI,
                    text,
                    KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                    0xffffffff
                    );
        }

        line++; // スペース

        aGLUI.mScreen.drawText(// 大きさ
                CHARSET_MINI,
                "Size    : " + toString(selectedItem->param().mSize),
                KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                0xffffffff
                );
        aGLUI.mScreen.drawText(// 重量
                CHARSET_MINI,
                "Weight  : " + toString(selectedItem->param().mWeight),
                KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                0xffffffff
                );
        if (selectedItem->param().mEquippable) {
            ItemType type(selectedItem->param().mItemType);
            if (type == EQUIPMENT_SWORD || type == EQUIPMENT_BOW || type == EQUIPMENT_GUN) { // 武器
                aGLUI.mScreen.drawText(// 攻撃力
                        CHARSET_MINI,
                        "Attack  : " + toString(selectedItem->param().mPower),
                        KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                        0xffffffff
                        );
            } else {
                aGLUI.mScreen.drawText(// 防御力
                        CHARSET_MINI,
                        "Defence : " + toString(selectedItem->param().mPower),
                        KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                        0xffffffff
                        );
            }
            aGLUI.mScreen.drawText(// 有効射程
                    CHARSET_MINI,
                    "Range   : " + toString(selectedItem->param().mEffectiveRange),
                    KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                    0xffffffff
                    );
            aGLUI.mScreen.drawText(// 有効角
                    CHARSET_MINI,
                    "Angle   : " + toString(selectedItem->param().mEffectiveAngle),
                    KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                    0xffffffff
                    );
            if (type == EQUIPMENT_BOW || type == EQUIPMENT_GUN) {
                aGLUI.mScreen.drawText(// 装填数
                        CHARSET_MINI,
                        "Magzine : " + toString(selectedItem->param().mStack),
                        KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                        0xffffffff
                        );
            }
        }
        aGLUI.mScreen.drawText(// コスト
                CHARSET_MINI,
                "Cost    : " + toString(selectedItem->param().mCost) + "Turn",
                KVector(introArea.x + 5, introArea.y + line++ * SIZE + 5),
                0xffffffff
                );
    }
}

