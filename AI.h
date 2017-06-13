/**
 * @file   AI.h
 * @brief  AI
 * @author Maeda Takumi
 */
#ifndef AI_H
#define AI_H

#include "main.h"

class Action;
class Character;
class GameState;

/**
 * @brief  AI
 * @author Maeda Takumi
 */
class AI final {
private:
    /* 視野角   */ static const float VIEW_ANGLE;

    /* AIの状態 */
    enum State {
        /* 索敵 */ STATE_SEARCH,
        /* 警戒 */ STATE_VIGILANCE,
        /* 敵対 */ STATE_HOSTILITY,
    } mState;
    /* ターゲット座標 */ KVector mTarget;

    /* アクション決定関数   */
    using AIFunction = Action(AI::*)(const GameState& aState, Character& aCharacter);
    /* アクション決定関数群 */ static const Vector<AIFunction> AI_FUNCTION;

    Action player(const GameState& aState, Character& aCharacter);
    Action merchant(const GameState& aState, Character& aCharacter);
    Action sloth(const GameState& aState, Character& aCharacter);
    Action berserk(const GameState& aState, Character& aCharacter);
    Action coward(const GameState& aState, Character& aCharacter);
public:

    /**
     * @brief \~english  Type of AI
     * @brief \~japanese AIの種類
     */
    enum Type {
        /** \~japanese プレイヤー移譲 */ TYPE_PLAYER,
        /** \~japanese 商人(敵対無し) */ TYPE_MERCHANT,
        /** \~japanese 怠慢型 */ TYPE_SLOTH,
        /** \~japanese 暴力型 */ TYPE_BERSERK,
        /** \~japanese 逃避型 */ TYPE_COWARD,
    } mType;

    /**
     * @param aType
     * \~english  Type of AI
     * \~japanese AIの種類
     */
    AI(const Type& aType = TYPE_SLOTH);
    /**
     * @param aType
     * \~english  String of AI Type
     * \~japanese AI分類文字列
     */
    AI(const String& aType);
    ~AI() = default;

    /**
     * \~english
     * @brief get next Action.
     * @param aState     state of game
     * @param aCharacter act Character
     * @return 
     * \~japanese
     * @brief 次に行う行動を取得します。
     * @param aState     ゲーム状態
     * @param aCharacter 行動を行うキャラクター
     * @return 
     */
    Action nextAction(const GameState& aState, Character& aCharacter);

    /**
     * \~english
     * @brief check whether there are players in the field of view.
     * @param aState     state of game
     * @param aCharacter act Character
     * @return there are players in the field of view
     * \~japanese
     * @brief 視野にプレイヤーがいるかを確認します。
     * @param aState     ゲーム状態
     * @param aCharacter 行動を行うキャラクター
     * @return 視野にプレイヤーがいるか
     */
    bool checkPlayer(const GameState& aState, const Character& aCharacter);

    /**
     * \~english
     * @brief convert string to AI Type.
     * @param aType String to convert
     * @return AI Type
     * \~japanese
     * @brief 文字列をAI種別に変換します。
     * @param aType 変換文字列
     * @return AI種別
     */
    static inline Type toAIType(const String& aType) {
        if (aType == "Player") return TYPE_PLAYER;
        if (aType == "Merchant") return TYPE_MERCHANT;
        if (aType == "Sloth") return TYPE_SLOTH;
        if (aType == "Berserk")return TYPE_BERSERK;
        if (aType == "Coward") return TYPE_COWARD;
        return TYPE_SLOTH;
    }
};

#endif /* AI_H */

