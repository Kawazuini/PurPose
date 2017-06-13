/**
 * @file   NumberSelector.cpp
 * @brief  NumberSelector
 * @author Maeda Takumi
 */
#include "NumberSelector.h"

const List<String> NumberSelector::COUNT_TEXT({"999"});

NumberSelector::NumberSelector(
        GameManager& aGameManager,
        const String& aTitle,
        const int& aMax,
        const int& aMin,
        const NumberSelectorFunction& aSelect
        ) :
Command(aGameManager, aTitle, COUNT_TEXT),
mMax(aMax),
mMin(aMin),
mSelect(aSelect) {
    mChoice = mMin;
    println(0);
}

void NumberSelector::draw(Device& aDevice) {
    static const int SIZE(CHARSET_SMALL.mSize * 2);
    static const color BASE(0x7700cc00);

    KTexture & screen(aDevice.screen());

    screen.clearRect(mDrawArea);
    // 二重枠描画
    screen.drawClearRect(mDrawArea, BASE);
    screen.drawClearRect(KRect(mDrawArea.x + 2, mDrawArea.y + 2, mDrawArea.width - 4, mDrawArea.height - 4), BASE);

    // セレクトナンバー描画
    KVector txt(mDrawArea.x + 5, mDrawArea.y + 5);
    screen.drawText(CHARSET_SMALL, mTitle, txt, 0xffffffff);
    String number("x" + toString(mChoice));
    int center(mDrawArea.centerX() - CHARSET_SMALL.getWidth(number) / 2);
    screen.drawText(CHARSET_SMALL, number, KVector(center, txt.y + SIZE), 0xffffffff); // センタリング
}

void NumberSelector::changeCommand(const int& aAmount) {
    mChoice += aAmount;
    if (mChoice > mMax) mChoice = mMin;
    else if (mChoice < mMin) mChoice = mMax;
}

void NumberSelector::choose() {
    (mGameManager.*mSelect)(mChoice);
}

