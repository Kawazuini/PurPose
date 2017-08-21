/**
 * @file   Enemy.cpp
 * @brief  Enemy
 * @author Maeda Takumi
 */
#include "Enemy.h"

#include "GameState.h"
#include "Special.h"

const int Enemy::TEX_SIZE(512);

Enemy::Enemy(const int& aID, const int& aLevel) :
Character(aID),
mImageDirection(DIRECTION_FRONT),
mImage(IDI_CHARACTER + mCharacterParameter.mTextureNumber),
mTexture(TEX_SIZE),
mHaribote(mPosition, mCharacterParameter.mSize, mTexture),
mDamageFrame(-1),
mPreHP(0) {
    mTexture.drawImage(mImage, KRect(TEX_SIZE, TEX_SIZE), KVector());
    mTexture.reflect();

    Character::levelUp(aLevel - 1);
    mCharacterParameter.mHP = mCharacterParameter.mMHP;
    mPreHP = mCharacterParameter.mHP;
}

void Enemy::update(GameState& aState) {
    Character::update(aState);

    static const KVector AXIS(0, 1, 0);
    static const KRect TEXTURE_AREA(TEX_SIZE, TEX_SIZE);
    static const KRect TEXTURE_FRONT(0, 0, TEX_SIZE, TEX_SIZE);
    static const KRect TEXTURE_BACK(TEX_SIZE, 0, TEX_SIZE, TEX_SIZE);
    static const KRect TEXTURE_LEFT(0, TEX_SIZE, TEX_SIZE, TEX_SIZE);
    static const KRect TEXTURE_RIGHT(TEX_SIZE, TEX_SIZE, TEX_SIZE, TEX_SIZE);
    static const float ANGLE_FRONT(Math::PI / 4);
    static const float ANGLE_BACK(Math::PI / 4 * 3);

    // 画像方向の決定
    float angle(mHaribote.normal().angle(mDirection));
    float sideAngle(mHaribote.normal().cross(AXIS).angle(mDirection));
    if (angle < ANGLE_FRONT) {
        if (mImageDirection != DIRECTION_FRONT) {
            mImageDirection = DIRECTION_FRONT;
            mTexture.clearRect(TEXTURE_AREA);
            mTexture.drawImage(mImage, TEXTURE_FRONT, KVector());
            mTexture.reflect();
        }
    } else if (ANGLE_BACK < angle) {
        if (mImageDirection != DIRECTION_BACK) {
            mImageDirection = DIRECTION_BACK;
            mTexture.clearRect(TEXTURE_AREA);
            mTexture.drawImage(mImage, TEXTURE_BACK, KVector());
            mTexture.reflect();
        }
    } else if (sideAngle < Math::HALF_PI) {
        if (mImageDirection != DIRECTION_LEFT) {
            mImageDirection = DIRECTION_LEFT;
            mTexture.clearRect(TEXTURE_AREA);
            mTexture.drawImage(mImage, TEXTURE_LEFT, KVector());
            mTexture.reflect();
        }
    } else if (Math::HALF_PI < sideAngle) {
        if (mImageDirection != DIRECTION_RIGHT) {
            mImageDirection = DIRECTION_RIGHT;
            mTexture.clearRect(TEXTURE_AREA);
            mTexture.drawImage(mImage, TEXTURE_RIGHT, KVector());
            mTexture.reflect();
        }
    }

    // ダメージ描画
    if (mPreHP != mCharacterParameter.mHP) {
        if (mDamageFrame != -1) {
            // 前の表示が残っているときは表示の初期化
            mTexture.clearRect(TEXTURE_AREA);
            KRect rect;
            switch (mImageDirection) {
                case DIRECTION_FRONT: rect = TEXTURE_FRONT;
                    break;
                case DIRECTION_BACK: rect = TEXTURE_BACK;
                    break;
                case DIRECTION_LEFT: rect = TEXTURE_LEFT;
                    break;
                case DIRECTION_RIGHT: rect = TEXTURE_RIGHT;
                    break;
            }
            mTexture.drawImage(mImage, rect, KVector());
        }

        String damage(toString(mPreHP - mCharacterParameter.mHP));
        mTexture.drawText(CHARSET_LARGE, damage, KVector((CHARSET_LARGE.getWidth(damage) + TEX_SIZE) / 2), 0xffff0000);
        mTexture.reflect();

        mPreHP = mCharacterParameter.mHP;
        mDamageFrame = 0.5_s;
    }

    if (mDamageFrame) {
        --mDamageFrame;
    } else {
        --mDamageFrame;
        mTexture.clearRect(TEXTURE_AREA);
        KRect rect;
        switch (mImageDirection) {
            case DIRECTION_FRONT: rect = TEXTURE_FRONT;
                break;
            case DIRECTION_BACK: rect = TEXTURE_BACK;
                break;
            case DIRECTION_LEFT: rect = TEXTURE_LEFT;
                break;
            case DIRECTION_RIGHT: rect = TEXTURE_RIGHT;
                break;
        }
        mTexture.drawImage(mImage, rect, KVector());
        mTexture.reflect();
    }
}

void Enemy::attack(GameState& aState) {
    Character::attack(aState);
    if (
            KSphere(mPosition, mSize + mCharacterParameter.mAttackRange)
            * KSphere(aState.mPlayer.position(), aState.mPlayer.size())
            ) {
        Special::add(Special(SPECIAL_DAMAGE, mCharacterParameter.mSTR, this, &aState.mPlayer));
    }
    turnEnd();
}

void Enemy::syncPosition() {
    mHaribote.translate(mPosition);
}

