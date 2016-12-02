/**
 * @file   Device.cpp
 * @brief  Device
 * @author Maeda Takumi
 */
#include "Device.h"

#include "BackPack.h"
#include "Hero.h"
#include "Map.h"

Bulletin Device::sBulletin;

Device::Device(const KCamera& aCamera, const Hero& aUser) : mUI(aCamera) {
    mUser = &aUser;
}

void Device::draw() {
    Map::MapPlayer player(mUser->mEyeCamera->mPosition, mUser->mEyeCamera->mDirection);
    mUser->sMap->draw(mUI, player, KRect(200, 200), 5);

    mUser->mBackPack.draw(mUI, KRect(KGLUI::WIDTH - 252, 0, 250, KGLUI::HEIGHT - 2));

    sBulletin.draw(mUI, CHARSET_MINI, KRect(10, KGLUI::HEIGHT - 200, 500, 200));

    mUI.draw();
}

