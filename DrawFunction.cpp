/**
 * @file   DrawFunction.cpp
 * @brief  GameManager
 * @author Maeda Takumi
 */
#include "GameManager.h"

#include "Tile.h"
#include "Item.h"

void GameManager::draw_start() const {
    Tile::TILE_DRAW(mGameState);
}

void GameManager::draw_play() const {
    KDrawer::DRAW();
    Tile::TILE_DRAW(mGameState);
    Haribote::HARIBOTE_DRAW(mGameState);

    KShading::ColorShading->ON();
    if (mInventory) mGameState.mPlayer.backPack().draw();
    else mGameState.mBulletin.draw();
    mGameState.mMapping.draw();
}

void GameManager::draw_over() const {
    Tile::TILE_DRAW(mGameState);
}

void GameManager::draw_ending() const {
    Tile::TILE_DRAW(mGameState);
}

