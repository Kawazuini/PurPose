/**
 * @file   Device.cpp
 * @brief  Device
 * @author Maeda Takumi
 */
#include "Device.h"

#include "BackPack.h"
#include "Command.h"
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

Device::Device() :
mMappingUpdatePeriod(25) {
    KDrawer::remove();
}

void Device::draw() const {
    mUI.draw();
}

void Device::update(const GameState& aState) {
    static int frameCount = 0;
    if (frameCount++ > 0xfffffff) frameCount = 0;
    if (frameCount % mMappingUpdatePeriod == 0)
        aState.mMapping.draw(mUI, aState.mPlayer, MAP_AREA, 5);

    aState.mPlayer.backPack().draw(mUI, BACKPACK_AREA);

    aState.mBulletin.draw(mUI, CHARSET_MINI, BULLETIN_AREA);

    static int preHP = 0;
    if (preHP != aState.mPlayer.mParameter.mHP) { // draw HP
        preHP = aState.mPlayer.mParameter.mHP;
        drawHP(aState.mPlayer);
    }
}

void Device::refresh(const GameState& aState) {
    mUI.screen().clearRect(KRect(KGLUI::WIDTH, KGLUI::HEIGHT));

    aState.mMapping.draw(mUI, aState.mPlayer, MAP_AREA, 5);
    aState.mPlayer.backPack().draw(mUI, BACKPACK_AREA);
    aState.mBulletin.forcedDraw(mUI, CHARSET_MINI, BULLETIN_AREA);
    drawHP(aState.mPlayer);
}

void Device::drawHP(const Hero& aPlayer) {
    float perHP = (float) aPlayer.mParameter.mHP / aPlayer.mParameter.mMaxHP; // 残HPの割合
    KRect hp(HPBAR_AREA.x + 1, HPBAR_AREA.y + 1, HPBAR_AREA.width * perHP - 2, HPBAR_AREA.height - 2);

    mUI.screen().drawRect(HPBAR_AREA, HPBAR_COLOR); // バーを描画
    // HPバーの色が徐々に変化
    if (perHP > 0.5) {
        float alpha = 2 * perHP - 1.0;
        mUI.screen().drawRect(hp, ((int) (255 * alpha) << 24) + MAXHP_COLOR);
        mUI.screen().drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + MIDHP_COLOR);
    } else {
        float alpha = 2 * perHP;
        mUI.screen().drawRect(hp, ((int) (255 * alpha) << 24) + MIDHP_COLOR);
        mUI.screen().drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + MINHP_COLOR);
    }
}

void Device::drawCommand(const Command& aChoice) {
    static const color BASE = 0xff00ff00;

    KRect area(aChoice.drawArea());
    area.width += 10;
    area.height += 10;

    mUI.screen().clearRect(area);
    mUI.screen().drawClearRect(area, BASE);
    mUI.screen().drawClearRect(KRect(area.x + 2, area.y + 2, area.width - 4, area.height - 4), BASE);
    mUI.screen().drawRect(KRect(area.x + 5, area.y + 5 + (aChoice.choice() + 1) * 16, area.width - 8, 16), BASE);

    mUI.screen().drawText(CHARSET_MINI, aChoice.title(), KVector(area.x + 5, area.y + 5), 0);
    int count = 1;
    for (String i : aChoice.commandText()) {
        mUI.screen().drawText(CHARSET_MINI, i, KVector(area.x + 5, area.y + count * 16 + 5), 0);
        ++count;
    }
}

