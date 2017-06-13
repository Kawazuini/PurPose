/**
 * @file   CommandManager.h
 * @brief  CommandManager
 * @author Maeda Takumi
 */
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "main.h"

class Command;
class Device;

/**
 * @brief  \~english  management system of choice
 * @brief  \~japanese 選択肢管理システム
 * @author \~ Maeda Takumi
 */
class CommandManager final : public KUpdater {
private:
    /* 選択肢   */ List<Command*> mCommands;
    /* 描画対象 */ Device& mDevice;
public:
    /**
     * \~english  @param aDevice drawing target
     * \~japanese @param aDevice 描画対象
     */
    CommandManager(Device& aDevice);
    virtual ~CommandManager();

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    void update() override;

    /**
     * \~english
     * @brief change choice of command.
     * @param aAmount change amount
     * \~japanese
     * @brief コマンドの選択状況を変更します。
     * @param aAmount 変更量
     */
    void changeCommand(const int& aAmount);
    /**
     * @brief \~english  do choice.
     * @brief \~japanese 選択肢を実行します。
     */
    void choose();
    /**
     * @brief \~english  cancel to command.
     * @brief \~japanese コマンドをキャンセルします。
     */
    void cancel();

    /**
     * \~english
     * @brief add command.
     * @param aCommand addition command
     * \~japanese
     * @brief コマンドを追加します。
     * @param aCommand 追加するコマンド
     */
    void push(Command& aCommand);
    /**
     * @brief \~english  back to command.
     * @brief \~japanese コマンドを戻します。
     */
    void pop();
    
    /**
     * \~english
     * @brief  get number of commands.
     * @return number of commands
     * \~japanese
     * @brief  コマンド数を取得します。
     * @return コマンド数
     */
    int size();
};

#endif /* COMMANDMANAGER_H */

