/**
 * @file   MusicScore.cpp
 * @brief  MusicScore
 * @author Maeda Takumi
 */
#ifndef MUSICSCORE_H
#define MUSICSCORE_H

#include "main.h"

#define MAX_PLAYERS 16

class MusicScore {
public:

    enum Phonetic {
        /** 全音符   */ p1,
        /** 2分音符  */ p2,
        /** 4分音符  */ p4,
        /** 8分音符  */ p8,
        /** 16分音符 */ p16,
    };

    struct Note {
        /** @brief 音程    */ KMidi::Tone mTone;
        /** @brief 音価    */ Phonetic mPhonetic;
        /** @brief 強さ(%) */ int mVeloPercent;

        Note(
                KMidi::Tone aTone = KMidi::C4,
                Phonetic aPhonetic = p4,
                int aVeloPercent = 0
                ) :
        mTone(aTone),
        mPhonetic(aPhonetic),
        mVeloPercent(aVeloPercent) {
        }
    };

    using Players = KMidi::Instrument[MAX_PLAYERS];
    using Score = Vector<Note>[MAX_PLAYERS];

private:
    KThread mConducter;
    KMutex mDestructor;

    KMidi mMidi;

    int mBPM;
    Players mPlayers;
    Vector<KMidi::Note> mScore[MAX_PLAYERS];

    static void* Condocter(void* args);
public:
    MusicScore(
            const int& aBPM,
            const Players& aPlayers,
            const Score& aScore
            );
    virtual ~MusicScore();

    inline int toMilli(const Phonetic& aPhonetic) {
        const double bps((double) 60 / mBPM);
        switch (aPhonetic) {
            case p1: return bps * 4 * 1000;
            case p2: return bps * 2 * 1000;
            case p4: return bps * 1000;
            case p8: return bps / 2 * 1000;
            case p16:return bps / 4 * 1000;
        }
    };

    inline KMidi::Note convertNote(const Note& aNote) {
        return KMidi::Note{
            aNote.mTone,
            toMilli(aNote.mPhonetic),
            (int) ((double) aNote.mVeloPercent / 100 * 127)
        };
    };
};

#endif /* MUSICSCORE_H */

