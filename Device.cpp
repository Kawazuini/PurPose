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

const int Device::UI_SIZE = KGLUI::WIDTH / 64; // BLOCK(64 × 36)
const KRect Device::AREA_BULLETIN(KVector(1, 2) * UI_SIZE, KVector(31, 35) * UI_SIZE);
const KRect Device::AREA_MAP(KVector(49, 1) * UI_SIZE, KVector(63, 15) * UI_SIZE);
const KRect Device::AREA_BACKPACK(KVector(1, 2) * UI_SIZE, KVector(48, 35) * UI_SIZE);
const KRect Device::AREA_HPBAR(KVector(4, 1) * UI_SIZE, KVector(45, 2) * UI_SIZE);
const KRect Device::AREA_FLOAR(KVector(1, 0) * UI_SIZE, KVector(3, 2) * UI_SIZE);
const KRect Device::AREA_BULLET(KVector(59, 31) * UI_SIZE, KVector(63, 35) * UI_SIZE);
const color Device::COLOR_HPBAR = 0xff5a544b; // 海松茶
const color Device::COLOR_MAXHP = 0x003eb370; // 緑(透過値は描画時に決定)
const color Device::COLOR_MIDHP = 0x00ffd900; // 黄(透過値は描画時に決定)
const color Device::COLOR_MINHP = 0x00e60033; // 赤(透過値は描画時に決定)

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

    static int preHP = 0;
    if (preHP != aState.mPlayer.mCharacterParameter.mHP) { // draw HP
        preHP = aState.mPlayer.mCharacterParameter.mHP;
        drawHP(aState.mPlayer);
    }
    drawFloar(aState);
    drawBullet(aState.mPlayer);
}

void Device::refresh(GameState& aState) {
    mUI.mScreen.clearRect(KRect(KGLUI::WIDTH, KGLUI::HEIGHT));

    aState.mBulletin.forcedDraw(mUI, CHARSET_MINI, AREA_BULLETIN);
    drawMap(aState.mMapping, aState.mPlayer);
    drawHP(aState.mPlayer);
    drawFloar(aState);
    drawBullet(aState.mPlayer);
}

void Device::drawMap(const Mapping& aMapping, const Hero& aPlayer) {
    aMapping.draw(mUI, aPlayer, AREA_MAP, 5);
}

void Device::drawHP(const Hero& aPlayer) {
    float perHP((float) aPlayer.mCharacterParameter.mHP / aPlayer.mCharacterParameter.mMHP); // 残HPの割合
    KRect hp(AREA_HPBAR.x + 1, AREA_HPBAR.y + 1, AREA_HPBAR.width * perHP - 2, AREA_HPBAR.height - 2);

    mUI.mScreen.drawRect(AREA_HPBAR, COLOR_HPBAR); // バーを描画
    // HPバーの色が徐々に変化
    if (perHP > 0.5) {
        float alpha(2 * perHP - 1.0);
        mUI.mScreen.drawRect(hp, ((int) (255 * alpha) << 24) + COLOR_MAXHP);
        mUI.mScreen.drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + COLOR_MIDHP);
    } else {
        float alpha(2 * perHP);
        mUI.mScreen.drawRect(hp, ((int) (255 * alpha) << 24) + COLOR_MIDHP);
        mUI.mScreen.drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + COLOR_MINHP);
    }
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

void Device::drawFloar(const GameState& aState) {
    static const int SIZE(CHARSET.mSize * 2);

    mUI.mScreen.clearRect(AREA_FLOAR);
    String floar(toString(aState.mFloarNumber) + "F");
    mUI.mScreen.drawText(
            CHARSET,
            floar,
            KVector(AREA_FLOAR.right() - CHARSET.getWidth(floar), AREA_FLOAR.bottom() - SIZE),
            0xff00ff00
            );
}

void Device::drawBullet(const Hero& aPlayer) {
    static const int SIZE(CHARSET.mSize * 2);

    const Item * const weapon(aPlayer.weapon());
    if (weapon) {
        if (weapon->mEquipped) {
            ItemType type(weapon->param().mItemType);
            if (type == EQUIPMENT_GUN || type == EQUIPMENT_BOW) {
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

