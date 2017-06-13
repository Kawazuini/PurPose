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

CommandManager::~CommandManager() {
    for (Command* i : mCommands) delete i;
}

void CommandManager::update() {
    for (Command* i : mCommands) i->draw(mDevice);
}

void CommandManager::changeCommand(const int& aAmount) {
    if (!mCommands.empty()) {
        mCommands.back()->changeCommand(aAmount);
    }
}

void CommandManager::choose() {
    if (!mCommands.empty()) {
        mCommands.back()->choose();
    }
}

void CommandManager::cancel() {
    if (!mCommands.empty()) {
        mCommands.back()->cancel();
        mCommands.pop_back();
    }
}

void CommandManager::push(Command& aCommand) {
    mCommands.push_front(&aCommand);
}

void CommandManager::pop() {
    if (!mCommands.empty()) {
        mCommands.pop_back();
    }
}

int CommandManager::size() {
    return mCommands.size();
}

