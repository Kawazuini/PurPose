/**
 * @file   CommandManager.h
 * @brief  CommandManager
 * @author Maeda Takumi
 */
#ifndef COMMANDMANAGER_H
#define COMMANDMANAGER_H

#include "Device.h"

class Command;

/**
 * @brief  \~english  management system of choice
 * @brief  \~japanese 選択肢管理システム
 * @author \~ Maeda Takumi
 */
class CommandManager : public KUpdater {
private:
    /**
     * @brief \~english  choices
     * @brief \~japanese 選択肢
     */
    List<Command> mCommands;

    /**
     * @brief \~english  drawing target
     * @brief \~japanese 描画対象
     */
    Device& mDevice;
public:
    /**
     * \~english
     * @brief generate command managed system.
     * @param aDevice drawing target
     * \~japanese
     * @brief コマンド管理システムを生成します。
     * @param aDevice 描画対象
     */
    CommandManager(Device& aDevice);
    virtual ~CommandManager() = default;

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
     * @brief コマンドの選択内容を変更します。
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
    void add(const Command& aCommand);
    /**
     * @brief \~english  back to command.
     * @brief \~japanese コマンドを戻します。
     */
    void back();
};

#endif /* COMMANDMANAGER_H */

