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
const KRect Device::BULLETIN_AREA(KVector(1, 2) * UI_SIZE, KVector(31, 35) * UI_SIZE);
const KRect Device::MAP_AREA(KVector(49, 1) * UI_SIZE, KVector(63, 15) * UI_SIZE);
const KRect Device::BACKPACK_AREA(KVector(47, 1) * UI_SIZE, KVector(63, 35) * UI_SIZE);
const KRect Device::HPBAR_AREA(KVector(1, 1) * UI_SIZE, KVector(45, 2) * UI_SIZE);
const color Device::HPBAR_COLOR = 0xff5a544b; // 海松茶
const color Device::MAXHP_COLOR = 0x003eb370; // 緑(透過値は描画時に決定)
const color Device::MIDHP_COLOR = 0x00ffd900; // 黄(透過値は描画時に決定)
const color Device::MINHP_COLOR = 0x00e60033; // 赤(透過値は描画時に決定)

Device::Device(const KCamera& aCamera) :
mUI(aCamera),
mMappingUpdatePeriod(25) {
    KDrawer::remove();
}

void Device::draw() const {
    mUI.draw();
}

void Device::update(GameState& aState) {
    aState.mBulletin.draw(mUI, CHARSET_MINI, BULLETIN_AREA);

    static int frameCount = 0;
    if (frameCount++ > 0xfffffff) frameCount = 0;
    if (frameCount % mMappingUpdatePeriod == 0) drawMap(aState.mMapping, aState.mPlayer);

    static int preHP = 0;
    if (preHP != aState.mPlayer.mCharacterParameter.mHP) { // draw HP
        preHP = aState.mPlayer.mCharacterParameter.mHP;
        drawHP(aState.mPlayer);
    }
}

void Device::refresh(GameState& aState) {
    mUI.mScreen.clearRect(KRect(KGLUI::WIDTH, KGLUI::HEIGHT));

    aState.mBulletin.forcedDraw(mUI, CHARSET_MINI, BULLETIN_AREA);
    drawMap(aState.mMapping, aState.mPlayer);
    drawHP(aState.mPlayer);
}

void Device::drawMap(const Mapping& aMapping, const Hero& aPlayer) {
    aMapping.draw(mUI, aPlayer, MAP_AREA, 5);
}

void Device::drawHP(const Hero& aPlayer) {
    float perHP((float) aPlayer.mCharacterParameter.mHP / aPlayer.mCharacterParameter.mMHP); // 残HPの割合
    KRect hp(HPBAR_AREA.x + 1, HPBAR_AREA.y + 1, HPBAR_AREA.width * perHP - 2, HPBAR_AREA.height - 2);

    mUI.mScreen.drawRect(HPBAR_AREA, HPBAR_COLOR); // バーを描画
    // HPバーの色が徐々に変化
    if (perHP > 0.5) {
        float alpha(2 * perHP - 1.0);
        mUI.mScreen.drawRect(hp, ((int) (255 * alpha) << 24) + MAXHP_COLOR);
        mUI.mScreen.drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + MIDHP_COLOR);
    } else {
        float alpha(2 * perHP);
        mUI.mScreen.drawRect(hp, ((int) (255 * alpha) << 24) + MIDHP_COLOR);
        mUI.mScreen.drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + MINHP_COLOR);
    }
}

void Device::drawBackPack(const BackPack& aBackPack) {
    aBackPack.draw(mUI, BACKPACK_AREA);
}

void Device::drawMessageLog(Bulletin& aBulletin) {
    aBulletin.drawLog(mUI, CHARSET_MINI, BULLETIN_AREA);
}

void Device::drawCommand(const Command& aCommand) {
    static const color BASE = 0xff00ff00;

    KRect area(aCommand.drawArea());
    area.width += 10;
    area.height += 10;

    mUI.mScreen.clearRect(area);
    mUI.mScreen.drawClearRect(area, BASE);
    mUI.mScreen.drawClearRect(KRect(area.x + 2, area.y + 2, area.width - 4, area.height - 4), BASE);
    mUI.mScreen.drawRect(KRect(area.x + 5, area.y + 5 + (aCommand.choice() + 1) * 16, area.width - 8, 16), BASE);

    mUI.mScreen.drawText(CHARSET_MINI, aCommand.title(), KVector(area.x + 5, area.y + 5), 0);
    int count(1);
    for (String i : aCommand.commandText()) {
        mUI.mScreen.drawText(CHARSET_MINI, i, KVector(area.x + 5, area.y + count * 16 + 5), 0);
        ++count;
    }
}

