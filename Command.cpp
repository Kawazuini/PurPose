/**
 * @file   Command.cpp
 * @brief  Command
 * @author Maeda Takumi
 */
#include "Command.h"

Command::Command(
        GameManager& aGameManager,
        const String& aTitle,
        const List<String>& aText,
        const Vector<GameManager::CommandFunc>& aCommand,
        const KVector& aPosition
        ) :
mGameManager(aGameManager),
mTitle(aTitle),
mCommandText(aText),
mCommand(aCommand),
mChoice(0) {
    int width = CHARSET_MINI.getWidth(mTitle);
    for (String i : aText) {
        width = Math::max(width, CHARSET_MINI.getWidth(i));
    }
    mDrawArea = KRect(
            aPosition.x, aPosition.y, width,
            (aText.size() + 1) * CHARSET_MINI.mSize * 2
            );
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

