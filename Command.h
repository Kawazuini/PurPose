/**
 * @file   Command.h
 * @brief  Command
 * @author Maeda Takumi
 */
#ifndef COMMAND_H
#define COMMAND_H

#include "main.h"
#include "GameManager.h"

class GameManager;

/**
 * @brief  \~english  Command
 * \~japanese
 * @brief  選択肢
 * @note   一番最後の選択肢はキャンセル用にしておく
 * @author \~ Maeda Takumi
 */
class Command {
private:
    /**
     * @brief \~english  
     * @brief \~japanese コマンド実行対象
     */
    GameManager& mGameManager;
    /**
     * @brief \~english  command title
     * @brief \~japanese 選択肢タイトル
     */
    String mTitle;
    /**
     * @brief \~english  command text
     * @brief \~japanese 選択肢テキスト
     */
    List<String> mCommandText;
    /**
     * @brief \~english  
     * @brief \~japanese コマンド毎の処理内容
     */
    Vector<GameManager::CommandFunc> mCommand;

    /**
     * @brief \~english  state of choose
     * @brief \~japanese 選択状態
     */
    int mChoice;

    /**
     * @brief \~english  drawing area of UI
     * @brief \~japanese UI描画領域
     */
    KRect mDrawArea;
public:
    Command(
            GameManager& aGameManager,
            const String& aTitle,
            const List<String>& aText,
            const Vector<GameManager::CommandFunc>& aCommand,
            const KVector& aPosition
            );
    virtual ~Command() = default;

    /**
     * \~english
     * @brief change selected Command.
     * @param aAmount change amount
     * \~japanese
     * @brief 選択肢を変更します。
     * @param aAmount 選択変更量
     */
    void changeCommand(const int& aAmount);
    
    void choose();
    void cancel();

    const String& title() const;
    const List<String>& commandText() const;
    const int& choice() const;
    const KRect& drawArea() const;
};

#endif /* COMMAND_H */

