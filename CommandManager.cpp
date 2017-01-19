/**
 * @file   CommandManager.cpp
 * @brief  CommandManager
 * @author Maeda Takumi
 */
#include "CommandManager.h"

#include "Command.h"
#include "Device.h"

CommandManager::CommandManager(Device& aDevice) :
mDevice(aDevice) {
}

void CommandManager::update() {
    for (Command i : mCommands) {
        mDevice.drawCommand(i);
    }
}

void CommandManager::changeCommand(const int& aAmount) {
    if (!mCommands.empty()) {
        mCommands.back().changeCommand(aAmount);
    }
}

void CommandManager::choose() {
    if (!mCommands.empty()) {
        mCommands.back().choose();
    }
}

void CommandManager::cancel() {
    if (!mCommands.empty()) {
        mCommands.back().cancel();
    }
}

void CommandManager::add(const Command& aChoice) {
    mCommands.push_back(aChoice);
}

void CommandManager::back() {
    if (!mCommands.empty()) {
        mCommands.pop_back();
    }
}
