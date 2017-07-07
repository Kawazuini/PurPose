/**
 * @file   Device.cpp
 * @brief  Device
 * @author Maeda Takumi
 */
#include "Device.h"

#include "BackPack.h"
#include "Command.h"
#include "Hero.h"
#include "Item.h"
#include "Wallet.h"

const int Device::UI_SIZE(KGLUI::SIZE / 64); // BLOCK(64 × 40)

const KRect Device::AREA_BACKPACK(KVector(1, 2) * UI_SIZE, KVector(48, 35) * UI_SIZE);
const KRect Device::AREA_STATUS(KVector(5, 0) * UI_SIZE, KVector(46, 2) * UI_SIZE);
const KRect Device::AREA_SEEING(KVector(41, 33) * UI_SIZE, KVector(63, 35) * UI_SIZE);
const KRect Device::AREA_FLOOR(KVector(1, 0) * UI_SIZE, KVector(4, 2) * UI_SIZE);
const KRect Device::AREA_WEAPON(KVector(41, 25) * UI_SIZE, KVector(63, 29) * UI_SIZE);
const KRect Device::AREA_BULLET(KVector(59, 29) * UI_SIZE, KVector(63, 33) * UI_SIZE);

const color Device::COLOR_STATUS_BAR(0xff5a544b); // 海松茶
const color Device::COLOR_HP_MAX(0x003eb370); // 緑(透過値は描画時に決定)
const color Device::COLOR_HP_MID(0x00ffd900); // 黄(透過値は描画時に決定)
const color Device::COLOR_HP_MIN(0x00e60033); // 赤(透過値は描画時に決定)
const color Device::COLOR_STAMINA(0xffe6b422); // 黄金色

Device::Device(KGLUI& aUI) :
mUI(aUI),
mScreen(mUI.screen()) {
}

void Device::drawHPBar(const Character& aCharacter, const KRect& aRect) {
    mScreen.drawRect(aRect, COLOR_STATUS_BAR); // HPバーを描画
    float perHP((float) aCharacter.mCharacterParameter.mHP / aCharacter.mCharacterParameter.mMHP); // 残HPの割合
    KRect hp(aRect.x + 1, aRect.y + 1, aRect.width * perHP - 2, aRect.height - 2);

    // HPバーの色が徐々に変化
    if (perHP > 0.5f) {
        float alpha(2 * perHP - 1.0);
        mScreen.drawRect(hp, ((int) (255 * alpha) << 24) + COLOR_HP_MAX);
        mScreen.drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + COLOR_HP_MID);
    } else {
        float alpha(2 * perHP);
        mScreen.drawRect(hp, ((int) (255 * alpha) << 24) + COLOR_HP_MID);
        mScreen.drawRect(hp, ((int) (255 * (1.0 - alpha)) << 24) + COLOR_HP_MIN);
    }
}

void Device::update(GameState& aState) {
    drawPlayerStatus(aState.mPlayer);
    drawCharacterStatus(aState);
    drawFloor(aState);
    drawWeapon(aState);
    drawBullet(aState.mPlayer);
}

void Device::refresh(GameState& aState) {
    mScreen.clearRect(mUI.area());

    drawPlayerStatus(aState.mPlayer);
    drawFloor(aState);
    drawBullet(aState.mPlayer);
}

void Device::drawPlayerStatus(const Hero& aPlayer) {
    mScreen.clearRect(AREA_STATUS);

    const CharacterParameter & param(aPlayer.mCharacterParameter);

    KRect bar(AREA_STATUS.x, AREA_STATUS.centerY(), AREA_STATUS.width, AREA_STATUS.height / 4);
    drawHPBar(aPlayer, bar);

    bar.y = bar.bottom();
    mScreen.drawRect(bar, COLOR_STATUS_BAR); // スタミナバーを描画
    float pStamina((float) param.mStamina / param.mMaxStamina); // 残スタミナの割合
    KRect st(bar.x + 1, bar.y + 1, bar.width * pStamina - 2, bar.height - 2);
    mScreen.drawRect(st, COLOR_STAMINA);

    // 実値を描画
    StringStream status;
    status << "Lv." << std::setw(2) << param.mLevel << "  HP : " << std::setw(3) << param.mHP << " / " << std::setw(3) << param.mMHP << "  St : " << std::setw(3) << param.mStamina << " / " << std::setw(3) << param.mMaxStamina;

    String sst(status.str());
    mScreen.drawText(CHARSET_SMALL, sst, KVector(AREA_STATUS.x, 0), 0xffffffff);

    // お金を描画(右寄せ)
    String money("$" + toString(aPlayer.wallet().money()));
    mScreen.drawText(
            CHARSET_SMALL,
            money,
            AREA_STATUS.right() - CHARSET_SMALL.getWidth(money),
            0xffffffff
            );
}

void Device::drawCharacterStatus(const GameState& aState) {
    mScreen.clearRect(AREA_SEEING);

    const Character * target(aState.mPlayer.whoIamSeeing(aState));
    if (target) {
        int line(AREA_SEEING.y);

        // キャラクター名
        mScreen.drawText(CHARSET_SMALL, target->mCharacterParameter.mName, KVector(AREA_SEEING.x, line), 0xffffffff);
        line += UI_SIZE;

        // HPバー
        drawHPBar(*target, KRect(KVector(AREA_SEEING.left(), line), KVector(AREA_SEEING.right(), line + UI_SIZE)));
        // 実数値
        String hp(toString(target->mCharacterParameter.mHP) + "/" + toString(target->mCharacterParameter.mMHP));
        mScreen.drawText(CHARSET_SMALL, hp, KVector(AREA_SEEING.centerX() - CHARSET_SMALL.getWidth(hp) / 2, line), 0xffffffff);
        line += UI_SIZE;
    }
}

void Device::drawBackPack(const BackPack& aBackPack) {
    aBackPack.draw(mUI, AREA_BACKPACK);
}

void Device::drawFloor(const GameState& aState) {
    static const int SIZE(CHARSET.mSize * 2);

    mScreen.clearRect(AREA_FLOOR);
    String floor("B" + toString(aState.mFloorNumber) + "F");
    mScreen.drawText(
            CHARSET,
            floor,
            KVector(AREA_FLOOR.right() - CHARSET.getWidth(floor), AREA_FLOOR.bottom() - SIZE),
            0xff00ff00
            );
}

void Device::drawWeapon(const GameState& aState) {
    static const int SIZE_CHARSET(CHARSET.mSize * 2);
    static const int SIZE_CHARSET_MINI(CHARSET_SMALL.mSize * 2);

    mScreen.clearRect(AREA_WEAPON);

    const Item * const * weapon(aState.mPlayer.weapon());
    int index(aState.mPlayer.weaponIndex());

    int line(0);
    for (int i = 0; i < 3; ++i) {
        String name(weapon[i] ? weapon[i]->param().mName : "NONE");
        if (i == index) {
            int width(CHARSET.getWidth(name));
            mScreen.drawText(
                    CHARSET,
                    name,
                    KVector(AREA_WEAPON.right() - width, AREA_WEAPON.y + line),
                    0xffffffff
                    );
            line += SIZE_CHARSET;
        } else {
            int width(CHARSET_SMALL.getWidth(name));
            mScreen.drawText(
                    CHARSET_SMALL,
                    name,
                    KVector(AREA_WEAPON.right() - width, AREA_WEAPON.y + line),
                    0xffffffff
                    );
            line += SIZE_CHARSET_MINI;
        }
    }
}

void Device::drawBullet(const Hero& aPlayer) {
    static const int SIZE(CHARSET.mSize * 2);

    mScreen.clearRect(AREA_BULLET);

    const Item * const * weapon(aPlayer.weapon());
    int index(aPlayer.weaponIndex());
    if (weapon[index]) {
        if (weapon[index]->mEquipped) {
            ItemType type(weapon[index]->param().mItemType);
            if (type == WEAPON_GUN || type == WEAPON_BOW) {

                mScreen.clearRect(AREA_BULLET);
                mScreen.drawText(
                        CHARSET,
                        toString(weapon[index]->mMagazine.size()),
                        AREA_BULLET.begin(),
                        0xffffffff
                        );
                mScreen.drawHLine(AREA_BULLET.left(), AREA_BULLET.right(), AREA_BULLET.centerY(), 0xffffffff);
                String rest(toString(aPlayer.backPack().lookCount(weapon[index]->param().mMagazineID)));
                mScreen.drawText(
                        CHARSET,
                        rest,
                        KVector(AREA_BULLET.right() - CHARSET.getWidth(rest), AREA_BULLET.bottom() - SIZE),
                        0xffffffff
                        );
            }
        }
    }
}

KGLUI& Device::UI() {
    return mUI;
}

const KGLUI& Device::UI() const {
    return mUI;
}

KTexture& Device::screen() {
    return mScreen;
}

