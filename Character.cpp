/**
 * @file   Character.cpp
 * @brief  Character
 * @author Maeda Takumi
 */
#include "Character.h"

#include "Action.h"
#include "Effect.h"
#include "GameState.h"
#include "Item.h"
#include "Special.h"
#include "Tile.h"

const int Character::CIRCLE_QUALITY(16);

Character::Character(const int& aID) :
mCharacterParameter(aID),
mWhoKilleMe(NULL),
mTurn(false),
mWaitTurn(0),
mDirection(KVector(0.0f, 0.0f, -1.0f)),
mBody(mPosition, mCharacterParameter.mSize / 2.0f),
mWeapon{NULL, NULL, NULL}

,
mWeaponIndex(0),
mShield(NULL),
mHeadEquipment(NULL),
mBodyEquipment(NULL),
mFootEquipment(NULL) {
    static const float ANGLE(2 * Math::PI / CIRCLE_QUALITY);
    static const KVector AXIS(0, 1, 0);

    KVector bodyCircle(mDirection * mBody.mRadius);
    for (int i = 0; i < CIRCLE_QUALITY; ++i) {
        mBodyCircle.push_back(bodyCircle.rotate(KQuaternion(AXIS, i * ANGLE)));
    }
    KVector attackCircle(mDirection * (mBody.mRadius + mCharacterParameter.mAttackRange));
    for (int i = 0; i < CIRCLE_QUALITY; ++i) {
        mAttackCircle.push_back(attackCircle.rotate(KQuaternion(AXIS, i * ANGLE)));
    }
}

void Character::draw() const {
    static const float ANGLE(2 * Math::PI / CIRCLE_QUALITY);
    static const KVector BASE(0, 0, -1);
    static const KVector AXIS(0, 1, 0);

    KShading::ColorShading->ON();
    
    // ダメージ判定の描画
    glBegin(GL_LINE_LOOP);
    glColor4f(0, 1, 0, 1);
    for (int i = 0; i < CIRCLE_QUALITY; ++i) {
        KVector vert(mBodyCircle[i] + mPosition);
        vert.y = 0.01;
        glVertex3f(DEPLOY_VEC(vert));
    }
    glEnd();
    // 攻撃範囲の描画
    glBegin(GL_LINE_LOOP);
    glColor4f(1, 0, 0, 1);
    for (int i = 0; i < CIRCLE_QUALITY; ++i) {
        KVector vert(mAttackCircle[i] + mPosition);
        vert.y = 0.01;
        glVertex3f(DEPLOY_VEC(vert));
    }
    glEnd();

    // 武器装備時の攻撃範囲
    if (mWeapon[mWeaponIndex] && mWeapon[mWeaponIndex]->param().mItemType == WEAPON_SWORD) {
        glColor4f(1, 1, 0, 1);
        glBegin(GL_LINE_LOOP);
        KVector attackCircle(BASE * (mBody.mRadius + mCharacterParameter.mAttackRange + mWeapon[mWeaponIndex]->param().mEffectiveRange));
        for (int i = 0; i < CIRCLE_QUALITY; ++i) {
            KVector circlePoint(mPosition + attackCircle.rotate(KQuaternion(AXIS, i * ANGLE)));
            circlePoint.y = 0.01;
            glVertex3f(DEPLOY_VEC(circlePoint));
        }
        glEnd();
    }
}

void Character::update(GameState& aState) {
    if (mTurn) {
        if (mWaitTurn > 0) {
            wait();
        } else {
            Action act(mCharacterParameter.mAI.nextAction(aState, *this));
            switch (act.mType) {
                case Action::TYPE_WAIT: wait();
                    break;
                case Action::TYPE_MOVE: move(aState, act.mPosition);
                    break;
                case Action::TYPE_ATTACK: attack(aState);
                    break;
                case Action::TYPE_NOTHING: break;
            }
        }
    }
    mPrePosition = mPosition;
}

void Character::turnStart() {
    mTurn = true;
}

void Character::turnEnd() {
    mTurn = false;
}

bool Character::turn() const {
    return mTurn;
}

void Character::levelUp(const int& aLevel) {
    mCharacterParameter.mLevel += aLevel;
    mCharacterParameter.mMHP += mCharacterParameter.mIncreaseMHP * aLevel;
    mCharacterParameter.mSTR += mCharacterParameter.mIncreaseSTR * aLevel;

}

void Character::levelUp(GameState& aState, const int& aLevel) {
    levelUp(aLevel);
    aState.mBulletin.write(Message(mCharacterParameter.mName + "はレベルが" + toString(mCharacterParameter.mLevel) + "に上がった。", 0xffff0000));
}

void Character::wait() {
    --mWaitTurn;
    turnEnd();
}

void Character::move(GameState& aState, const KVector& aPosition) {
    static const KVector AXIS(0, 1, 0);
    if (mTurn) {
        // 移動方向の単位ベクトル
        KVector dirNorm((aPosition - mPosition).extractVertical(AXIS).normalization());
        mPosition += dirNorm * mCharacterParameter.mAGI + aState.mGravity;
        resolveOverlap(aState);
        syncPosition();
        turnEnd();
    }
}

void Character::resolveOverlap(const GameState& aState) {
    // 壁へのめり込み解消
    const List<KPolygon*>& walls(aState.wallList());
    for (KPolygon* i : walls) {
        KVector wallN(i->mNormal); // 壁の法線ベクトル
        KVector radiusN(wallN * mBody.mRadius); // 半径の長さを持った壁の法線方向のベクトル
        KSegment moveP(// 壁に垂直な移動線分
                mPrePosition + radiusN,
                mPrePosition - radiusN
                + (mPosition - mPrePosition).extractParallel(wallN)
                );
        KVector hit(i->hitPoint(moveP));
        if (i->operator*(hit)) {
            // 壁へのめり込み距離
            float overlap(moveP.length() -(hit - mPrePosition).length() - mBody.mRadius);
            mPosition += wallN * overlap;
        }
    }
    // キャラクター同士のめり込み解消
    const List<Character*>& characters(aState.charList());
    for (Character* i : characters) {
        if (mBody * i->body() && i != this) { // 自分以外のキャラクターと衝突
            mPosition = i->position() + (mPosition - i->position()).normalization() * (mBody.mRadius + i->size());
        }
    }
}

Item* Character::checkItem(GameState& aState) const {
    float rad(mBody.mRadius + Item::PICKABLE_RANGE);
    for (Item* i : aState.itemList()) {
        if ((i->mEntity.position() - mPosition).length() < rad) return i;
    }
    return NULL;
}

void Character::lookAt(const KVector& aDirection) {
    static const KVector AXIS(0, 1, 0);
    // 2段階回転
    KQuaternion rotate(mDirection.extractVertical(AXIS).roundAngle(aDirection.extractVertical(AXIS)));
    mDirection = mDirection.rotate(rotate);
    mDirection = mDirection.rotate(mDirection.roundAngle(aDirection));
}

void Character::attack(GameState& aState) {
    if (mTurn) {
        aState.mBulletin.write(mCharacterParameter.mName + "の攻撃!");
        if (!mWeapon[mWeaponIndex]) { // 武器を装備していない
            mWaitTurn = mCharacterParameter.mAttackCost;
        } else {
            weaponAttack(aState);
        }
    }
}

void Character::weaponAttack(GameState& aState) {
    switch (mWeapon[mWeaponIndex]->param().mItemType) {
        case WEAPON_SWORD:
        {
            bool hit(false);
            KSphere reach(mPosition, mBody.mRadius + mCharacterParameter.mAttackRange + mWeapon[mWeaponIndex]->param().mEffectiveRange);
            for (Character* i : aState.charList()) {
                if (i != this) { // 自分は殴らない。
                    if (reach * i->body()) {
                        if ((i->position() - mPosition).angle(mDirection) < mWeapon[mWeaponIndex]->param().mEffectiveAngle / 180 * Math::PI) {
                            Special::add(Special(SPECIAL_DAMAGE, mCharacterParameter.mSTR + mWeapon[mWeaponIndex]->param().mPower, this, i));
                            hit = true;
                        }
                    }
                }
            }
            if (!hit) aState.mBulletin.write(mCharacterParameter.mName + "は空振りしてしまった。");

            mWaitTurn = mWeapon[mWeaponIndex]->param().mCost;
            break;
        }
        case WEAPON_BOW:
        {
            if (!mWeapon[mWeaponIndex]->mMagazine.empty()) {
                Item * bullet(mWeapon[mWeaponIndex]->mMagazine.back());
                mWeapon[mWeaponIndex]->mMagazine.pop_back();

                bullet->embody();
                bullet->mEntity.setPosition(mPosition + mDirection * (mCharacterParameter.mSize + bullet->mEntity.radius()));

                bullet->mEntity.applyForce(mDirection * (mWeapon[mWeaponIndex]->param().mPower + mCharacterParameter.mSTR));
                bullet->mOwener = this;
                mWaitTurn = mWeapon[mWeaponIndex]->param().mCost;
            } else aState.mBulletin.write("弾が装填されていない!");
            break;
        }
        case WEAPON_GUN:
        {
            bool shot(false); // 一回でも発砲できたか
            for (int i = 0, i_e = mWeapon[mWeaponIndex]->param().mBurst; i < i_e; ++i) { // 発射数で繰り返し
                if (!mWeapon[mWeaponIndex]->mMagazine.empty()) {// 弾倉が空でない
                    shot = true;

                    Item * bullet(mWeapon[mWeaponIndex]->mMagazine.back());
                    mWeapon[mWeaponIndex]->mMagazine.pop_back();

                    bullet->embody();
                    bullet->mEntity.setPosition(mPosition + mDirection * (mCharacterParameter.mSize + bullet->mEntity.radius()));
                    bullet->mEntity.applyForce(mDirection * (mWeapon[mWeaponIndex]->param().mPower));
                    bullet->mOwener = this;

                    new Effect(Effect::EFFECT_GUNSHOT, 2000, mPosition);

                    mWaitTurn = bullet->param().mCost; // 発砲には銃弾のコストを使用
                } else {
                    if (!shot) aState.mBulletin.write("弾が装填されていない!");
                    break;
                }
            }
            break;
        }
    }
}

void Character::use(GameState& aState, Item& aItem) {
    if (!aItem.param().mUsable) {
        aState.mBulletin.write(aItem.param().mName + "は使用できない!");
        return;
    }
    if (mTurn) {
        aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.param().mName + "を使った。");
        aItem.special(this);
        mWaitTurn = aItem.param().mCost;
        delete &aItem;
        turnEnd();
    }
}

void Character::equip(GameState& aState, Item& aItem) {
    // 装備箇所の確定
    bool notEquip(false); // 装備箇所がない
    Item ** target(NULL); // 装備箇所
    switch (aItem.param().mItemType) {
        case WEAPON_SWORD:
        case WEAPON_BOW:
        case WEAPON_GUN:
            target = &mWeapon[mWeaponIndex];
            break;
        case EQUIPMENT_SHIELD: target = &mShield;
            break;
        case EQUIPMENT_HEAD: target = &mHeadEquipment;
            break;
        case EQUIPMENT_BODY: target = &mBodyEquipment;
            break;
        case EQUIPMENT_FOOT: target = &mFootEquipment;
            break;
        default: notEquip = true;
    }
    // 装備不可(メッセージだけで何も起こらない)
    if (notEquip) {
        aState.mBulletin.write(aItem.param().mName + "を装備できる箇所がない!");
    } else if (!aItem.param().mEquippable) {
        aState.mBulletin.write(aItem.param().mName + "は装備できない!");
    } else if (aItem.mEquipped) {
        aState.mBulletin.write(aItem.param().mName + "は既に装備している!");
    } else
        // 装備可能(元装備の解除と装備、ターンの終了)
        if (mTurn) {
        bool equippable(true);
        if (*target) { // 元装備が存在する
            equippable = takeOff(aState, **target, false);
        }

        if (equippable) {
            *target = &aItem; // 装備
            aItem.mEquipped = true;

            aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.param().mName + "を装備した。");
            turnEnd();
        }
    }
}

bool Character::takeOff(GameState& aState, Item& aItem, const bool& aMessage) {
    if (mTurn) {
        // 装備箇所の確認
        Item ** target(NULL);
        if (mWeapon[0] == &aItem) target = &mWeapon[0];
        else if (mWeapon[1] == &aItem) target = &mWeapon[1];
        else if (mWeapon[2] == &aItem) target = &mWeapon[2];
        else if (mShield == &aItem) target = &mShield;
        else if (mHeadEquipment == &aItem) target = &mHeadEquipment;
        else if (mBodyEquipment == &aItem) target = &mBodyEquipment;
        else if (mFootEquipment == &aItem) target = &mFootEquipment;
        else {
            aState.mBulletin.write(aItem.param().mName + "は装備されていない!");
            return false;
        };

        // 呪われた装備(メッセージのみで何も起きない)
        if (!(*target)->mTakeoffable) {
            aState.mBulletin.write(aItem.param().mName + "は装備から外せない!");
            return false;
        }

        // 装備を外す
        (*target)->mEquipped = false;
        *target = NULL;
        if (aMessage) aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.param().mName + "を外した。");
        turnEnd();
        return true;
    }
    return false;
}

void Character::throwing(GameState& aState, Item& aItem) {
    if (mTurn) {
        // 装備してたら装備を外したうえで投げる
        bool throwable(true);
        if (aItem.mEquipped) throwable = takeOff(aState, aItem, false);
        if (throwable) {
            aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.param().mName + "を投げた。");
            aState.addItem(aItem);
            {
                aItem.embody();
                aItem.mEntity.setPosition(mPosition + mDirection * (mCharacterParameter.mSize + aItem.mEntity.radius()));
                aItem.mEntity.applyForce(mDirection * mCharacterParameter.throwPower());
                aItem.mOwener = this;
            }
            turnEnd();
        }
    }
}

void Character::putting(GameState& aState, Item& aItem) {
    static const KVector AXIS(0, 1, 0);
    if (mTurn) {
        // 装備してたら装備を外したうえで投げる
        bool throwable(true);
        if (aItem.mEquipped) {
            throwable = takeOff(aState, aItem, false);
        }
        if (throwable) {
            aState.mBulletin.write(mCharacterParameter.mName + "は" + aItem.param().mName + "を置いた。");
            aState.addItem(aItem);
            {
                aItem.embody();
                KVector horizon(mDirection.extractVertical(AXIS).normalization());
                KVector putPosition(mPosition + horizon * (mCharacterParameter.mSize + aItem.mEntity.radius()));
                aItem.mEntity.setPosition(KVector(putPosition.x, 0, putPosition.z));
            }
            turnEnd();
        }
    }
}

void Character::setPosition(const GameState& aState, const KVector& aPosition) {
    mPosition = aPosition;
    mPrePosition = aPosition;
    resolveOverlap(aState);
    mPrePosition = mPosition;
    syncPosition();
}

const KSphere& Character::body() const {
    return mBody;
}

const KVector& Character::position() const {
    return mPosition;
}

const KVector& Character::direction() const {
    return mDirection;
}

float Character::size() const {
    return mBody.mRadius;
}

const Item * const * Character::weapon() const {
    return mWeapon;
}

const int& Character::weaponIndex() const {
    return mWeaponIndex;
}

const Item * Character::shield() const {
    return mShield;
}

const Item * Character::headEquipment() const {
    return mHeadEquipment;
}

const Item * Character::bodyEquipment() const {
    return mBodyEquipment;
}

const Item * Character::footEquipment() const {
    return mFootEquipment;
}

