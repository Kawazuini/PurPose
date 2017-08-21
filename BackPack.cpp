/**
 * @file   BackPack.cpp
 * @brief  BackPack
 * @author Maeda Takumi
 */
#include "BackPack.h"

#include "Item.h"

const int BackPack::MAX_DRAW_LINE(31);


const KRect BackPack::DRAWAREA_BACKPACK(KVector(1, 2) * 1024 / 64, KVector(48, 35) * 1024 / 64);
const KRect BackPack::DRAWAREA_ITEM(DRAWAREA_BACKPACK.x + 2, DRAWAREA_BACKPACK.y + 2, DRAWAREA_BACKPACK.width / 2 - 4, DRAWAREA_BACKPACK.height - 4);
const KRect BackPack::DRAWAREA_CONTENT(DRAWAREA_BACKPACK.x + DRAWAREA_BACKPACK.width / 2, DRAWAREA_BACKPACK.y, DRAWAREA_BACKPACK.width / 2, DRAWAREA_BACKPACK.height);
const color BackPack::COLOR_BASE(0x7700cc00);
const color BackPack::COLOR_TEXT(0xffffffff);

BackPack::BackPack(const KCamera& aCamera) :
mUI(aCamera),
mChange(true),
mCursor(0),
mDrawBegin(0),
mDrawEnd(MAX_DRAW_LINE) {
    KDrawer::remove();
}

BackPack::~BackPack() {
    clear();
}

void BackPack::draw() const {
    mUI.draw();
}

void BackPack::update() {
    if (mChange) {
        static const int SIZE(CHARSET_SMALL.mSize * 2);
        static const KVector MARGIN(1, 1);

        KTexture & screen(mUI.screen());
        screen.clearRect(DRAWAREA_BACKPACK);
        screen.drawClearRect(DRAWAREA_BACKPACK, COLOR_BASE);

        screen.drawClearRect(DRAWAREA_ITEM, COLOR_BASE);

        // カーソルの描画
        int cursor(Math::min(MAX_DRAW_LINE - 1, mCursor - mDrawBegin));
        KVector cursorBegin(DRAWAREA_ITEM.begin() + KVector(2, 2 + cursor * SIZE));
        KRect cursorRect(cursorBegin, cursorBegin + KVector(DRAWAREA_ITEM.width - 3, SIZE - 4));
        screen.drawRect(cursorRect, COLOR_BASE);

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
                        KVector(DRAWAREA_ITEM.x, DRAWAREA_ITEM.y + i * SIZE) + MARGIN,
                        COLOR_TEXT
                        );
            }

            screen.drawText(// カーソル位置
                    CHARSET_SMALL,
                    toString(mCursor + 1) + "/" + toString(mBackPack.size()),
                    KVector(DRAWAREA_ITEM.x + 3, DRAWAREA_ITEM.bottom() - SIZE) - MARGIN,
                    COLOR_TEXT
                    );
            String weight("総重量 : " + digit(mWeight));
            screen.drawText(// 総重量
                    CHARSET_SMALL,
                    weight,
                    KVector(DRAWAREA_ITEM.right() - CHARSET_SMALL.getWidth(weight), DRAWAREA_ITEM.bottom() - SIZE) - MARGIN,
                    COLOR_TEXT
                    );
        }

        { // アイテム概要の描画
            static const KVector OFFSET(5, 5);

            screen.drawClearRect(KRect(DRAWAREA_CONTENT.x + 2, DRAWAREA_CONTENT.y + 2, DRAWAREA_CONTENT.width - 4, DRAWAREA_CONTENT.height - 4), COLOR_BASE);

            const Item * selectedItem(lookAt());
            if (selectedItem) {
                const ItemParameter & param(selectedItem->param());

                int line(0);
                screen.drawText(// アイテム名
                        CHARSET_SMALL,
                        "[" + param.mName + "]",
                        KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                        COLOR_TEXT
                        );

                line++; //改行
                for (String i : param.mBrief) {
                    screen.drawText(// アイテム概要
                            CHARSET_SMALL, i,
                            KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                            COLOR_TEXT
                            );
                }
                line++; // 改行


                // アイテム使用説明
                if (param.mUsable) {
                    screen.drawText(// 使用コスト
                            CHARSET_SMALL,
                            "使用コスト : " + toString(param.mCost) + "ターン",
                            KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                            COLOR_TEXT
                            );
                    screen.drawText(
                            CHARSET_SMALL,
                            "使用効果",
                            KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                            COLOR_TEXT
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
                                KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                                COLOR_TEXT
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
                                KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                                0xffff7777
                                );
                        if (type == WEAPON_SWORD) {
                            screen.drawText(// 有効射程
                                    CHARSET_SMALL,
                                    "有効射程　 : " + digit(param.mEffectiveRange) + " m",
                                    KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                                    COLOR_TEXT
                                    );
                            screen.drawText(// 有効範囲
                                    CHARSET_SMALL,
                                    "有効範囲　 : " + digit(param.mEffectiveAngle) + "°",
                                    KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                                    COLOR_TEXT
                                    );
                            screen.drawText(// 攻撃コスト
                                    CHARSET_SMALL,
                                    "攻撃コスト : " + toString(param.mCost) + "ターン",
                                    KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                                    COLOR_TEXT
                                    );
                        } else { // 飛び道具
                            screen.drawText(// 装填数
                                    CHARSET_SMALL,
                                    "装填数　　 : " + toString(param.mStack),
                                    KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                                    COLOR_TEXT
                                    );
                            screen.drawText(// リロードコスト
                                    CHARSET_SMALL,
                                    "装填コスト : " + toString(param.mCost) + "ターン",
                                    KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                                    COLOR_TEXT
                                    );
                        }
                    } else { // 防具;

                        screen.drawText(// 防御力
                                CHARSET_SMALL,
                                "防御力　　 : " + toString(param.mPower),
                                KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                                0xff7777ff
                                );
                    }
                }

                line++; // 改行
                screen.drawText(// 大きさ
                        CHARSET_SMALL,
                        "サイズ　　 : " + digit(param.mSize) + " m",
                        KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                        COLOR_TEXT
                        );
                screen.drawText(// 重量
                        CHARSET_SMALL,
                        "重量　　　 : " + digit(param.mWeight) + " kg",
                        KVector(DRAWAREA_CONTENT.x, DRAWAREA_CONTENT.y + line++ * SIZE) + OFFSET,
                        COLOR_TEXT
                        );
            }
        }
        mUI.refrect();

        mChange = false;
    }
}

void BackPack::selectChange(const int& aAmount) {
    mChange = true;

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
    } else return nullptr;
}

const Item * BackPack::lookAt() const {
    if (!mBackPack.empty()) {
        return mBackPack[mCursor]->front();
    } else return nullptr;
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
    mChange = true;

    String name(aItem.param().mName);
    List<Item*>* target(nullptr);
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
    mChange = true;

    Item * item(nullptr);
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
    mChange = true;

    // IDが若い順に並べる
    std::sort(mBackPack.begin(), mBackPack.end(),
            [](const List<Item*>* x, const List<Item*>* y) -> bool {
                return x->front()->param().mID < y->front()->param().mID;
            }
    );
}

void BackPack::clear() {
    mChange = true;

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

const float& BackPack::weight() const {
    return mWeight;
}

