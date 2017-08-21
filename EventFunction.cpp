/**
 * @file   EventFunction.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Command.h"
#include "CommandManager.h"

void GameManager::stairEvent() {
    mCommandManager.push(*(new Command(*this, "つぎのフロアに移動しますか?",{"はい", "いいえ"}, Vector<Command::CommandFunction>{newFloor, stairCancel})));
    mCommandWait = true;
}

