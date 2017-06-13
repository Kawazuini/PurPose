/**
 * @file   Command.h
 * @brief  Command
 * @author Maeda Takumi
 */
#ifndef COMMAND_H
#define COMMAND_H

#include "GameManager.h"

/**
 * @brief  \~english  Command
 * \~japanese
 * @brief  選択肢
 * @note   一番最後の選択肢はキャンセル用にしておく
 * @author \~ Maeda Takumi
 */
class Command : private KNonCopy {
public:
    /**
     * @brief \~english  command processing function
     * @brief \~japanese コマンド処理関数
     */
    using CommandFunction = void (GameManager::*)();
protected:
    /**
     * @brief \~english  Command execution target
     * @brief \~japanese コマンド実行対象
     */
    GameManager& mGameManager;
    /**
     * @brief \~english  Command title
     * @brief \~japanese 選択肢タイトル
     */
    String mTitle;
    /**
     * @brief \~english  Command text
     * @brief \~japanese 選択肢テキスト
     */
    List<String> mCommandText;
    /**
     * @brief \~english  processing each Command
     * @brief \~japanese コマンド毎の処理内容
     */
    Vector<CommandFunction> mCommand;
    /**
     * @brief \~english  state of choice
     * @brief \~japanese 選択状態
     */
    int mChoice;
    /**
     * @brief \~english  drawing area
     * @brief \~japanese 描画領域
     */
    KRect mDrawArea;

    /**
     * \~english
     * @param aGameManager target of command
     * @param aTitle       command title
     * @param aText        command text
     * \~japanese
     * @param aGameManager コマンド対象
     * @param aTitle       コマンドタイトル
     * @param aText        コマンドテキスト
     */
    Command(
            GameManager& aGameManager,
            const String& aTitle,
            const List<String>& aText
            );
public:
    /**
     * \~english
     * @param aGameManager target of command
     * @param aTitle       command title
     * @param aText        command text
     * @param aCommand     command function
     * \~japanese
     * @param aGameManager コマンド対象
     * @param aTitle       コマンドタイトル
     * @param aText        コマンドテキスト
     * @param aCommand     コマンド関数
     */
    Command(
            GameManager& aGameManager,
            const String& aTitle,
            const List<String>& aText,
            const Vector<CommandFunction>& aCommand
            );
    virtual ~Command() = default;

    /**
     * @brief \~english  drawing processing
     * @brief \~japanese 描画処理
     */
    virtual void draw(Device& aDevice);

    /**
     * \~english
     * @brief change selected Command.
     * @param aAmount change amount
     * \~japanese
     * @brief 選択肢を変更します。
     * @param aAmount 選択変更量
     */
    virtual void changeCommand(const int& aAmount);

    /**
     * @brief \~english  do command.
     * @brief \~japanese コマンドを実行します。
     */
    virtual void choose();
    /**
     * @brief \~english  cancel to command.
     * @brief \~japanese コマンドをキャンセルします。
     */
    virtual void cancel();

    /**
     * \~english
     * @brief  get command title.
     * @return command title
     * \~japanese
     * @brief  コマンドタイトルを取得します。
     * @return コマンドタイトル
     */
    const String& title() const;
    /**
     * \~english
     * @brief  get command text.
     * @return command text
     * \~japanese
     * @brief  コマンドテキストを取得します。
     * @return コマンドテキスト
     */
    const List<String>& commandText() const;
    /**
     * \~english
     * @brief  get state of choice.
     * @return state of choice
     * \~japanese
     * @brief  選択状態を取得します。
     * @return 選択状態
     */
    const int& choice() const;
    /**
     * \~english
     * @brief  get drawing area.
     * @return drawing area
     * \~japanese
     * @brief  描画領域を取得します。
     * @return 描画領域
     */
    const KRect& drawArea() const;
};

#endif /* COMMAND_H */

