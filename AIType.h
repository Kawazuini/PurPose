/**
 * @file   AIType.h
 * @brief  AIType
 * @author Maeda Takumi
 */
#ifndef AITYPE_H
#define AITYPE_H

#include "main.h"

/**
 * @brief \~english  type of AI
 * @brief \~japanese AIの種類
 */
enum AIType {
    AI_SLOTH,
    AI_BERSERK,
    AI_COWARD,
    AI_PLAYER,
};

static inline AIType toAIType(const String& aType) {
    if (aType == "Sloth") return AI_SLOTH;
    if (aType == "Berserk") return AI_BERSERK;
    if (aType == "Coward") return AI_COWARD;
    if (aType == "Player") return AI_PLAYER;
    return AI_SLOTH;
}

#endif /* AITYPE_H */

