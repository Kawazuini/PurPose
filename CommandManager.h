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

    Device& mDevice;
public:
    CommandManager(Device& aDevice);
    virtual ~CommandManager() = default;

    /**
     * @brief \~english  update processing
     * @brief \~japanese 更新処理
     */
    void update() override;

    void changeCommand(const int& aAmount);
    void choose();
    void cancel();

    void add(const Command& aChoice);
    void back();
};

#endif /* COMMANDMANAGER_H */

