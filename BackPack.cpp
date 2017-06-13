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
    int end(Math::max(0, (int) (mBackPack.size() - 1)));
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
        return mBackPack[mCursor]->front();
    } else return NULL;
}

const Item * BackPack::lookAt() const {
    if (!mBackPack.empty()) {
        return mBackPack[mCursor]->front();
    } else return NULL;
}

int BackPack::lookCount(const int& aID) const {
    if (!mBackPack.empty()) {
        if (!aID) return mBackPack[mCursor]->size(); // ID指定なし
        for (List<Item*>* i : mBackPack) {
            if (i->back()->param().mID == aID) {
                return i->size();
            }
        }
    }
    return 0;
}

void BackPack::add(Item& aItem) {
    String name(aItem.param().mName);
    List<Item*>* target(NULL);
    for (List<Item*>* i : mBackPack) {
        if (i->back()->param().mName == name) { // すでにバッグに入っている
            target = i;
            break;
        }
    }
    if (!target) { // 新規アイテム登録
        mBackPack.push_back(target = new List<Item*>());
    }
    target->push_back(&aItem);
    mWeight += aItem.param().mWeight;
}

Item* BackPack::takeOut(const int& aCount, const int& aID) {
    Item * item(NULL);
    if (!mBackPack.empty()) {
        int index(0);
        bool search(false);
        if (!aID) { // ID指定なし
            index = mCursor;
            search = true;
        } else {
            // アイテム検索
            for (List<Item*>* i : mBackPack) {
                if (i->back()->param().mID == aID) {
                    search = true;
                    break;
                }
                index++;
            }
        }
        if (search) { // 検索成功
            List<Item*>* target(mBackPack[index]);

            // 個数分詰め込む
            for (int i = 0; i < aCount; ++i) {
                if (!target->empty()) {
                    if (i == 0) {
                        item = target->back();
                    } else {
                        item->mMagazine.push_back(target->back());
                    }
                    target->pop_back();
                    mWeight -= item->param().mWeight;
                } else {
                    break;
                }
            }

            if (target->empty()) { // アイテム使い切り
                mBackPack.erase(mBackPack.begin() + index);
                // カーソルが末尾ならずらす
                if (!(mBackPack.size() - mCursor)) mCursor = Math::max(0, mCursor - 1);
            }
        }
    }
    return item;
}

void BackPack::sort() {
    // IDが若い順に並べる
    std::sort(mBackPack.begin(), mBackPack.end(),
            [](const List<Item*>* x, const List<Item*>* y) -> bool {
                return x->front()->param().mID < y->front()->param().mID;
            }
    );
}

void BackPack::clear() {
    mCursor = 0;
    for (List<Item*>* i : mBackPack) {
        while (!i->empty()) {
            delete i->back();
            i->pop_back();
        }
        delete i;
    }
    mBackPack.clear();
    mWeight = 0.0f;
}

void BackPack::draw(KGLUI& aGLUI, const KRect& aRect) const {
    static const int SIZE(CHARSET_SMALL.mSize * 2);
    static const color BASE(0x7700cc00);
    static const color WHITE(0xffffffff);
    static const KVector MARGIN(1, 1);

    KTexture& screen(aGLUI.screen());
    screen.clearRect(aRect);
    screen.drawClearRect(aRect, BASE);

    KRect listArea(aRect.x + 2, aRect.y + 2, aRect.width / 2 - 4, aRect.height - 4);
    screen.drawClearRect(listArea, BASE);

    // カーソルの描画
    int cursor(Math::min(MAX_DRAW_LINE - 1, mCursor - mDrawBegin));
    KRect cursorRect(
            listArea.x + 2,
            listArea.y + 2 + cursor * SIZE,
            listArea.width - 3,
            SIZE - 4
            );
    screen.drawRect(cursorRect, BASE);

    { // アイテムリストの描画
        Vector<List<Item*>*>::const_iterator item(mBackPack.begin() + mDrawBegin), end(mBackPack.end());
        for (int i = 0; i < MAX_DRAW_LINE && item != end; ++i, ++item) {
            const Item * target((*item)->front());
            int size((*item)->size());

            // (E )アイテム名 ([アイテム個数])
            String txt(
                    (target->mEquipped ? "E " : "  ") +
                    target->param().mName +
                    (size > 1 ? " [" + toString((*item)->size()) + "]" : "")
                    );
            screen.drawText(
                    CHARSET_SMALL,
                    txt,
                    KVector(listArea.x, listArea.y + i * SIZE) + MARGIN,
                    WHITE
                    );
        }

        screen.drawText(// カーソル位置
                CHARSET_SMALL,
                toString(mCursor + 1) + "/" + toString(mBackPack.size()),
                KVector(listArea.x + 3, listArea.bottom() - SIZE) - MARGIN,
                WHITE
                );
        String weight("総重量 : " + digit(mWeight));
        screen.drawText(// 総重量
                CHARSET_SMALL,
                weight,
                KVector(listArea.right() - CHARSET_SMALL.getWidth(weight), listArea.bottom() - SIZE) - MARGIN,
                WHITE
                );
    }

    // アイテム概要の描画
    static const KVector OFFSET(5, 5);

    KRect introArea(aRect);
    introArea.width /= 2;
    introArea.x += introArea.width;

    screen.drawClearRect(KRect(introArea.x + 2, introArea.y + 2, introArea.width - 4, introArea.height - 4), BASE);

    const Item * selectedItem(lookAt());
    if (selectedItem) {
        const ItemParameter & param(selectedItem->param());

        int line(0);
        screen.drawText(// アイテム名
                CHARSET_SMALL,
                "[" + param.mName + "]",
                KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                0xffffffff
                );

        line++; //改行
        for (String i : param.mBrief) {
            screen.drawText(// アイテム概要
                    CHARSET_SMALL, i,
                    KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                    0xffffffff
                    );
        }
        line++; // 改行


        // アイテム使用説明
        if (param.mUsable) {
            screen.drawText(// 使用コスト
                    CHARSET_SMALL,
                    "使用コスト : " + toString(param.mCost) + "ターン",
                    KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                    0xffffffff
                    );
            screen.drawText(
                    CHARSET_SMALL,
                    "使用効果",
                    KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                    0xffffffff
                    );

            for (Special i : param.mSpecials) { // 特殊効果
                String text("　　");
                switch (i.type()) {
                    case SPECIAL_HEAL: text += "HPを" + toString((int) (i.value())) + "回復します。";
                        break;
                    case SPECIAL_HEAL_STAMINA: text += "スタミナを" + toString((int) (i.value())) + "回復します。";
                        break;
                }
                screen.drawText(
                        CHARSET_SMALL,
                        text,
                        KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                        0xffffffff
                        );
            }
        }
        // アイテム装備説明
        if (param.mEquippable) {
            ItemType type(param.mItemType);
            if (type == WEAPON_SWORD || type == WEAPON_BOW || type == WEAPON_GUN) { // 武器
                screen.drawText(// 攻撃力
                        CHARSET_SMALL,
                        "攻撃力　　 : " + toString(param.mPower),
                        KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                        0xffff7777
                        );
                if (type == WEAPON_SWORD) {
                    screen.drawText(// 有効射程
                            CHARSET_SMALL,
                            "有効射程　 : " + digit(param.mEffectiveRange) + " m",
                            KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                            0xffffffff
                            );
                    screen.drawText(// 有効範囲
                            CHARSET_SMALL,
                            "有効範囲　 : " + digit(param.mEffectiveAngle) + "°",
                            KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                            0xffffffff
                            );
                    screen.drawText(// 攻撃コスト
                            CHARSET_SMALL,
                            "攻撃コスト : " + toString(param.mCost) + "ターン",
                            KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                            0xffffffff
                            );
                } else { // 飛び道具
                    screen.drawText(// 装填数
                            CHARSET_SMALL,
                            "装填数　　 : " + toString(param.mStack),
                            KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                            0xffffffff
                            );
                    screen.drawText(// リロードコスト
                            CHARSET_SMALL,
                            "装填コスト : " + toString(param.mCost) + "ターン",
                            KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                            0xffffffff
                            );
                }
            } else { // 防具;

                screen.drawText(// 防御力
                        CHARSET_SMALL,
                        "防御力　　 : " + toString(param.mPower),
                        KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                        0xff7777ff
                        );
            }
        }

        line++; // 改行
        screen.drawText(// 大きさ
                CHARSET_SMALL,
                "サイズ　　 : " + digit(param.mSize) + " m",
                KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                0xffffffff
                );
        screen.drawText(// 重量
                CHARSET_SMALL,
                "重量　　　 : " + digit(param.mWeight) + " kg",
                KVector(introArea.x, introArea.y + line++ * SIZE) + OFFSET,
                0xffffffff
                );
    }
}

const float& BackPack::weight() const {
    return mWeight;
}

