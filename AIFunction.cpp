/**
 * @file   AIFunction.cpp
 * @brief  AI
 * @author Maeda Takumi
 */
#include "AI.h"

#include "Action.h"
#include "GameState.h"

Action AI::player(const GameState& aState, Character& aCharacter) {
    return Action(Action::TYPE_NOTHING);
}

Action AI::merchant(const GameState& aState, Character& aCharacter) {
    return sloth(aState, aCharacter);
}

Action AI::sloth(const GameState& aState, Character& aCharacter) {
    return Action(Action::TYPE_WAIT);
}

Action AI::berserk(const GameState& aState, Character& aCharacter) {
    KVector pos(aCharacter.position());
    KVector player(aState.mPlayer.position());

    // 聴覚優先で状態遷移
    if ((player - pos).length() < aCharacter.mCharacterParameter.mPER) {
        mTarget = player;
        mState = STATE_HOSTILITY;
        aCharacter.lookAt(mTarget - pos); // mTargetを見る

        // 攻撃できるときは攻撃
        if ((mTarget - pos).length() <= (aState.mPlayer.size() + aCharacter.size() + aCharacter.mCharacterParameter.mAttackRange)) {
            return Action(Action::TYPE_ATTACK);
        }
        return Action(Action::TYPE_MOVE, mTarget);
    }

    switch (mState) {
        case STATE_SEARCH:
        {
            KVector dir(aCharacter.direction());

            // 移動先が壁 -> 新しく進む方向を水平8方向より選択
            while (aState.getMap(pos + dir.normalization() * MAP_SCALE) == MapChip::WALL && !dir.isZero()) {
                dir = KVector(random(3) - 1, 0, random(3) - 1);
            }

            // 距離関係なく視野に入ったら[警戒]に遷移
            if (checkPlayer(aState, aCharacter)) {
                mState = STATE_VIGILANCE;
                mTarget = aState.mPlayer.position();
            }

            aCharacter.lookAt(dir);
            return Action(Action::TYPE_MOVE, pos + dir);
        }
        case STATE_VIGILANCE:
        {
            // プレイヤーを見つける -> ターゲット座標の更新(近距離にいたら[敵対]に遷移)
            // 見つけられなかった   -> [索敵]に遷移
            if (checkPlayer(aState, aCharacter)) {
                mTarget = aState.mPlayer.position();
                if ((mTarget - pos).length() < aCharacter.mCharacterParameter.mPER * 3) {
                    mState = STATE_HOSTILITY;
                }
            } else if ((mTarget - pos).length() < MAP_SCALE) {
                mState = STATE_SEARCH;
            }
            aCharacter.lookAt(mTarget - pos); // mTargetを見る
            return Action(Action::TYPE_MOVE, mTarget);
        }
        case STATE_HOSTILITY:
        {
            // プレイヤーを見つける -> ターゲット座標の更新(攻撃範囲にいたら攻撃)
            // 見つけられなかった   -> 一定距離以上なら[警戒]に遷移
            if (checkPlayer(aState, aCharacter)) {
                mTarget = aState.mPlayer.position();
                // 攻撃できるときは攻撃
                if ((mTarget - pos).length() <= (aState.mPlayer.size() + aCharacter.size() + aCharacter.mCharacterParameter.mAttackRange)) {
                    return Action(Action::TYPE_ATTACK);
                }
            } else if ((mTarget - pos).length() < MAP_SCALE) {
                mState = STATE_VIGILANCE;
            }
            aCharacter.lookAt(mTarget - pos); // mTargetを見る
            return Action(Action::TYPE_MOVE, mTarget);
        }
    }
}

Action AI::coward(const GameState& aState, Character& aCharacter) {
    KVector position(aCharacter.position());
    KVector PtoMe(position - aState.mPlayer.position()); // プレイヤーから自分への方向ベクトル
    return Action(Action::TYPE_MOVE, position + PtoMe); // プレイヤーから遠ざかる
}

