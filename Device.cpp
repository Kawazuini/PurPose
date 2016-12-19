/**
 * @file   Device.cpp
 * @brief  Device
 * @author Maeda Takumi
 */
#include "Device.h"

#include "BackPack.h"
#include "Hero.h"
#include "Mapping.h"

const int Device::UI_SIZE = KGLUI::WIDTH / 64; // BLOCK(64 × 36)
const KRect Device::MAP_AREA(KVector(1, 2) * UI_SIZE, KVector(15, 16) * UI_SIZE);
const KRect Device::BACKPACK_AREA(KVector(47, 1) * UI_SIZE, KVector(63, 35) * UI_SIZE);
const KRect Device::BULLETIN_AREA(KVector(1, 24) * UI_SIZE, KVector(45, 35) * UI_SIZE);
const KRect Device::HPBAR_AREA(KVector(1, 1) * UI_SIZE, KVector(45, 2) * UI_SIZE);
const color Device::HPBAR_COLOR = 0xff5a544b; // 海松茶
const color Device::MAXHP_COLOR = 0x003eb370; // 緑(透過値は描画時に決定)
const color Device::MIDHP_COLOR = 0x00ffd900; // 黄(透過値は描画時に決定)
const color Device::MINHP_COLOR = 0x00e60033; // 赤(透過値は描画時に決定)

Bulletin Device::sBulletin;

Device::Device(const KCamera& aCamera, const Hero& aUser) : mUI(aCamera) {
    mUser = &aUser;
}

void Device::draw() {
    Mapping::MappingPlayer player(mUser->mEyeCamera.mPosition, mUser->mEyeCamera.mDirection);
    mUser->sMapDrawer->draw(mUI, player, MAP_AREA, 5);

    mUser->mBackPack.draw(mUI, BACKPACK_AREA);

    sBulletin.draw(mUI, CHARSET_MINI, BULLETIN_AREA);

    {
        mUI.mScreen->drawRect(HPBAR_AREA, HPBAR_COLOR); // バーを描画

        float perHP = (float) mUser->mHP / mUser->mMaxHP; // 残HPの割合
        KRect hp(HPBAR_AREA.x + 1, HPBAR_AREA.y + 1, HPBAR_AREA.width * perHP - 2, HPBAR_AREA.height - 2);

        // HPバーの色が徐々に変化
        if (perHP > 0.5) {
            float alpha = 2 * perHP - 1.0;
            mUI.mScreen->drawRect(hp, ((int) (255 * alpha) << 24) + MAXHP_COLOR);
            mUI.mScreen->drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + MIDHP_COLOR);
        } else {
            float alpha = 2 * perHP;
            mUI.mScreen->drawRect(hp, ((int) (255 * alpha) << 24) + MIDHP_COLOR);
            mUI.mScreen->drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + MINHP_COLOR);
        }
    }

    mUI.draw();
}

