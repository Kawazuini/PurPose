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
    Sloth,
    Berserk,
    Coward,
};

static inline AIType toAIType(const String& aType) {
    if (aType == "Sloth") return Sloth;
    if (aType == "Berserk") return Berserk;
    if (aType == "Coward") return Coward;
    return Sloth;
}

#endif /* AITYPE_H */

