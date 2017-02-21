/**
 * @file   MusicScore.cpp
 * @brief  MusicScore
 * @author Maeda Takumi
 */
#ifndef MUSICSCORE_H
#define MUSICSCORE_H

#include "main.h"

class MusicScore {
public:
    static const int MAX_PLAYERS;

    /**
     * @brief \~english  phonetic sign
     * @brief \~japanese 音価記号
     */
    enum Phonetic {
        /** 全音符   */ p1,
        /** 2分音符  */ p2,
        /** 4分音符  */ p4,
        /** 8分音符  */ p8,
        /** 16分音符 */ p16,
    };

    /**
     * @brief \~english  dynamics sign
     * @brief \~japanese 強弱記号
     */
    enum Dynamics {
        /** ピアニッシシモ   */ ppp,
        /** ピアニッシモ     */ pp,
        /** ピアノ           */ p,
        /** メゾピアノ       */ mp,
        /** メゾフォルテ     */ mf,
        /** フォルテ         */ f,
        /** フォルティシモ   */ ff,
        /** フォルティシシモ */ fff,
    };

    struct Note {
        /** @brief 音程 */ KMidi::Tone mTone;
        /** @brief 音価 */ Phonetic mPhonetic;
        /** @brief 強弱 */ Dynamics mDynamics;

        Note(
                KMidi::Tone aTone = KMidi::C0,
                Phonetic aPhonetic = p4,
                Dynamics aDynamics = mp
                ) :
        mTone(aTone),
        mPhonetic(aPhonetic),
        mDynamics(aDynamics) {
        }
    };

    using Players = Vector<KMidi::Instrument>;
    using Score = Vector<Vector<Note>>;
    int mBPM;
    Players mPlayers;
    Vector<Vector<KMidi::Note>> mScore;
private:
public:
    MusicScore();
    MusicScore(
            const int& aBPM,
            const Players& aPlayers,
            const Score& aScore
            );
    ~MusicScore() = default;

    int convertPhonetic(const Phonetic& aPhonetic);
    int convertDynamics(const Dynamics& aDynamics);
    KMidi::Note convertNote(const Note& aNote);
};

#endif /* MUSICSCORE_H */

