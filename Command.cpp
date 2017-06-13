/**
 * @file   Command.cpp
 * @brief  Command
 * @author Maeda Takumi
 */
#include "Command.h"

Command::Command(
        GameManager& aGameManager,
        const String& aTitle,
        const List<String>& aText
        ) :
Command(
aGameManager,
aTitle,
aText,
Vector<CommandFunction>()
) {
}

Command::Command(
        GameManager& aGameManager,
        const String& aTitle,
        const List<String>& aText,
        const Vector<CommandFunction>& aCommand
        ) :
mGameManager(aGameManager),
mTitle(aTitle),
mCommandText(aText),
mCommand(aCommand),
mChoice(0) {
    int width(CHARSET_SMALL.getWidth(mTitle));
    for (String i : aText) {
        width = Math::max(width, CHARSET_SMALL.getWidth(i));
    }
    mDrawArea = KRect(width, (aText.size() + 1) * CHARSET_SMALL.mSize * 2);
    // 表示枠分を余計に確保
    mDrawArea.width += 10;
    mDrawArea.height += 10;
    // センタリング表示
    KVector uiCenter(mGameManager.device().UI().area().center());
    mDrawArea.x = uiCenter.x - mDrawArea.width / 2;
    mDrawArea.y = uiCenter.y - mDrawArea.height / 2;
}

void Command::draw(Device& aDevice) {
    static const int SIZE(CHARSET_SMALL.mSize * 2);
    static const color BASE(0x7700cc00);

    KTexture& screen(aDevice.screen());

    screen.clearRect(mDrawArea);
    // 二重枠描画
    screen.drawClearRect(mDrawArea, BASE);
    screen.drawClearRect(KRect(mDrawArea.x + 2, mDrawArea.y + 2, mDrawArea.width - 4, mDrawArea.height - 4), BASE);

    // カーソル・コマンド描画
    KVector txt(mDrawArea.x + 5, mDrawArea.y + 5);
    KVector cursor(txt + KVector(0, mChoice + 1) * SIZE);
    screen.drawRect(KRect(cursor, cursor + KVector(mDrawArea.width - 8, SIZE)), BASE);
    screen.drawText(CHARSET_SMALL, mTitle, txt, 0xffffffff);
    int count(1);
    for (String i : mCommandText) {
        screen.drawText(CHARSET_SMALL, i, txt + KVector(0, count * SIZE), 0xffffffff);
        ++count;
    }
}

void Command::changeCommand(const int& aAmount) {
    mChoice += aAmount;
    if (mChoice > (int) (mCommandText.size() - 1)) mChoice = 0;
    else if (mChoice < 0) mChoice = mCommandText.size() - 1;
}

void Command::choose() {
    (mGameManager.*mCommand[mChoice])();
}

void Command::cancel() {
    (mGameManager.*mCommand.back())();
}

const String& Command::title() const {
    return mTitle;
}

const List<String>& Command::commandText() const {
    return mCommandText;
}

const int& Command::choice() const {
    return mChoice;
}

const KRect& Command::drawArea() const {
    return mDrawArea;
}

