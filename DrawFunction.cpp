/**
 * @file   DrawFunction.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

void GameManager::draw_start() const {
    KDrawer::DRAW();
    mDevice.draw();
}

void GameManager::draw_play() const {
    KDrawer::DRAW();
    mGameState.mPlayer.draw();
    mDevice.draw();
}

void GameManager::draw_over() const {
}

void GameManager::draw_ending() const {
}

