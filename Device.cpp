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
#include "Item.h"

const int Device::UI_SIZE(KGLUI::WIDTH / 64); // BLOCK(64 × 36)
const KRect Device::AREA_BULLETIN(KVector(1, 2) * UI_SIZE, KVector(31, 35) * UI_SIZE);
const KRect Device::AREA_MAP(KVector(49, 1) * UI_SIZE, KVector(63, 15) * UI_SIZE);
const KRect Device::AREA_BACKPACK(KVector(1, 2) * UI_SIZE, KVector(48, 35) * UI_SIZE);
const KRect Device::AREA_STATUS(KVector(4, 1) * UI_SIZE, KVector(45, 2) * UI_SIZE);
const KRect Device::AREA_FLOOR(KVector(1, 0) * UI_SIZE, KVector(3, 2) * UI_SIZE);
const KRect Device::AREA_BULLET(KVector(59, 31) * UI_SIZE, KVector(63, 35) * UI_SIZE);
const color Device::COLOR_STATUS_BAR(0xff5a544b); // 海松茶
const color Device::COLOR_HP_MAX(0x003eb370); // 緑(透過値は描画時に決定)
const color Device::COLOR_HP_MID(0x00ffd900); // 黄(透過値は描画時に決定)
const color Device::COLOR_HP_MIN(0x00e60033); // 赤(透過値は描画時に決定)
const color Device::COLOR_STAMINA(0xffe6b422); // 黄金色

Device::Device(const KCamera& aCamera) :
mUI(aCamera),
mMappingUpdatePeriod(25) {
    KDrawer::remove();
}

void Device::draw() const {
    mUI.draw();
}

void Device::update(GameState& aState) {
    aState.mBulletin.draw(mUI, CHARSET_MINI, AREA_BULLETIN);

    static int frameCount = 0;
    if (frameCount++ > 0xfffffff) frameCount = 0;
    if (frameCount % mMappingUpdatePeriod == 0) drawMap(aState.mMapping, aState.mPlayer);

    drawPlayerStatus(aState.mPlayer);
    drawFloor(aState);
    drawBullet(aState.mPlayer);
}

void Device::refresh(GameState& aState) {
    mUI.mScreen.clearRect(KRect(KGLUI::WIDTH, KGLUI::HEIGHT));

    aState.mBulletin.forcedDraw(mUI, CHARSET_MINI, AREA_BULLETIN);
    drawMap(aState.mMapping, aState.mPlayer);
    drawPlayerStatus(aState.mPlayer);
    drawFloor(aState);
    drawBullet(aState.mPlayer);
}

void Device::drawMap(const Mapping& aMapping, const Hero& aPlayer) {
    aMapping.draw(mUI, aPlayer, AREA_MAP, 5);
}

void Device::drawPlayerStatus(const Hero& aPlayer) {
    static const int HALF_HEIGHT(AREA_STATUS.height / 2);

    KRect bar(AREA_STATUS.x, AREA_STATUS.y, AREA_STATUS.width, HALF_HEIGHT);
    mUI.mScreen.drawRect(bar, COLOR_STATUS_BAR); // HPバーを描画

    float perHP((float) aPlayer.mCharacterParameter.mHP / aPlayer.mCharacterParameter.mMHP); // 残HPの割合
    KRect hp(bar.x + 1, bar.y + 1, bar.width * perHP - 2, bar.height - 2);

    // HPバーの色が徐々に変化
    if (perHP > 0.5) {
        float alpha(2 * perHP - 1.0);
        mUI.mScreen.drawRect(hp, ((int) (255 * alpha) << 24) + COLOR_HP_MAX);
        mUI.mScreen.drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + COLOR_HP_MID);
    } else {
        float alpha(2 * perHP);
        mUI.mScreen.drawRect(hp, ((int) (255 * alpha) << 24) + COLOR_HP_MID);
        mUI.mScreen.drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + COLOR_HP_MIN);
    }

    bar.y = bar.bottom();
    mUI.mScreen.drawRect(bar, COLOR_STATUS_BAR); // スタミナバーを描画
    float pStamina((float) aPlayer.mStamina / aPlayer.mMAXStamina); // 残スタミナの割合
    KRect st(bar.x + 1, bar.y + 1, bar.width * pStamina - 2, bar.height - 2);
    mUI.mScreen.drawRect(st, COLOR_STAMINA);
}

void Device::drawBackPack(const BackPack& aBackPack) {
    aBackPack.draw(mUI, AREA_BACKPACK);
}

void Device::drawMessageLog(Bulletin& aBulletin) {
    aBulletin.drawLog(mUI, CHARSET_MINI, AREA_BULLETIN);
}

void Device::drawCommand(const Command& aCommand) {
    static const int SIZE(CHARSET_MINI.mSize * 2);
    static const int HALF_WIDTH(KGLUI::WIDTH / 2);
    static const int HALF_HEIGHT(KGLUI::HEIGHT / 2);
    static const color BASE(0x7700cc00);

    KRect area(aCommand.drawArea());
    area.width += 10;
    area.height += 10;
    area.x = HALF_WIDTH - area.width / 2;
    area.y = HALF_HEIGHT - area.height / 2;

    mUI.mScreen.clearRect(area);
    mUI.mScreen.drawClearRect(area, BASE);
    mUI.mScreen.drawClearRect(KRect(area.x + 2, area.y + 2, area.width - 4, area.height - 4), BASE);
    mUI.mScreen.drawRect(KRect(area.x + 5, area.y + 5 + (aCommand.choice() + 1) * 16, area.width - 8, SIZE), BASE);

    mUI.mScreen.drawText(CHARSET_MINI, aCommand.title(), KVector(area.x + 5, area.y + 5), 0xffffffff);
    int count(1);
    for (String i : aCommand.commandText()) {
        mUI.mScreen.drawText(CHARSET_MINI, i, KVector(area.x + 5, area.y + count * SIZE + 5), 0xffffffff);
        ++count;
    }
}

void Device::drawFloor(const GameState& aState) {
    static const int SIZE(CHARSET.mSize * 2);

    mUI.mScreen.clearRect(AREA_FLOOR);
    String floor(toString(aState.mFloorNumber) + "F");
    mUI.mScreen.drawText(
            CHARSET,
            floor,
            KVector(AREA_FLOOR.right() - CHARSET.getWidth(floor), AREA_FLOOR.bottom() - SIZE),
            0xff00ff00
            );
}

void Device::drawBullet(const Hero& aPlayer) {
    static const int SIZE(CHARSET.mSize * 2);

    const Item * const weapon(aPlayer.weapon());
    if (weapon) {
        if (weapon->mEquipped) {
            ItemType type(weapon->param().mItemType);
            if (type == WEAPON_GUN || type == WEAPON_BOW) {
                mUI.mScreen.clearRect(AREA_BULLET);
                mUI.mScreen.drawText(
                        CHARSET,
                        toString(weapon->mMagazine.size()),
                        AREA_BULLET.start(),
                        0xffffffff
                        );
                mUI.mScreen.drawHLine(AREA_BULLET.left(), AREA_BULLET.right(), AREA_BULLET.centerY(), 0xffffffff);
                String stack(toString(weapon->param().mStack));
                mUI.mScreen.drawText(
                        CHARSET,
                        stack,
                        KVector(AREA_BULLET.right() - CHARSET.getWidth(stack), AREA_BULLET.bottom() - SIZE),
                        0xffffffff
                        );
            }
        }
    }
}

KGLUI& Device::UI() {
    return mUI;
}

