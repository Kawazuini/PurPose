/**
 * @file   Rank.h
 * @brief \~english  Rank System
 * @brief \~japanese ランクシステム
 * @author Maeda Takumi
 */
#ifndef RANK_H
#define RANK_H

#include "main.h"

static const int RANK_COUNT = 8;

typedef enum {
    Sp = 8, // S+
    S = 7, A = 6, B = 5, C = 4,
    D = 3, E = 2, F = 1, G = 0,
} Rank;

static const float S_BORDER = static_cast<float> (S) / RANK_COUNT;
static const float A_BORDER = static_cast<float> (A) / RANK_COUNT;
static const float B_BORDER = static_cast<float> (B) / RANK_COUNT;
static const float C_BORDER = static_cast<float> (C) / RANK_COUNT;
static const float D_BORDER = static_cast<float> (D) / RANK_COUNT;
static const float E_BORDER = static_cast<float> (E) / RANK_COUNT;
static const float F_BORDER = static_cast<float> (F) / RANK_COUNT;
static const float G_BORDER = static_cast<float> (G) / RANK_COUNT;

static inline String rank2String(const Rank& aRank) {
    switch (aRank) {
        case Sp: return "S+";
        case S: return "S";
        case A: return "A";
        case B: return "B";
        case C: return "C";
        case D: return "D";
        case E: return "E";
        case F: return "F";
        case G: return "G";
    }
};

static inline Rank getRank(const float& aValue, const float& aMax) {
    float tmp = aValue / aMax;
    if (tmp == 1) return Sp;
    if (tmp > S_BORDER) return S;
    if (tmp > A_BORDER) return A;
    if (tmp > B_BORDER) return B;
    if (tmp > C_BORDER) return C;
    if (tmp > D_BORDER) return D;
    if (tmp > E_BORDER) return E;
    if (tmp > F_BORDER) return F;
    return G;
}

static inline float getValue(const Rank& aRank, const float& aMax) {
    float tmp = aMax / RANK_COUNT;
    return static_cast<int> (aRank) * tmp;
};

#endif /* RANK_H */

