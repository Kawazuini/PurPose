/**
 * @file   DrawFunction.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Tile.h"

void GameManager::draw_start() const {
    KDrawer::DRAW();
    mDevice.draw();
}

void GameManager::draw_play() const {
    KDrawer::DRAW();
    Tile::TILE_DRAW(mGameState);
    Character::CHARACTER_DRAW(mGameState);
    NoneShading->ON();
    mDevice.draw();
    mGameState.mMapping.draw();
    PhongShading->ON();
}

void GameManager::draw_over() const {
}

void GameManager::draw_ending() const {
}

