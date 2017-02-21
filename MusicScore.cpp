/**
 * @file   MusicScore.cpp
 * @brief  MusicScore
 * @author Maeda Takumi
 */
#include "MusicScore.h"

const int MusicScore::MAX_PLAYERS(16);

MusicScore::MusicScore() :
mBPM(60),
mPlayers(MAX_PLAYERS, KMidi::AcousticGrandPiano),
mScore(MAX_PLAYERS) {
}

MusicScore::MusicScore(
        const int& aBPM,
        const Players& aPlayers,
        const Score& aScore
        ) : MusicScore() {
    mBPM = aBPM;
    int playerCount(aPlayers.size());
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        if (i < playerCount) mPlayers[i] = aPlayers[i];
        for (Note j : aScore[i]) {
            KMidi::Note n(convertNote(j));
            mScore[i].push_back(convertNote(j));
        }
    }
}

int MusicScore::convertPhonetic(const Phonetic& aPhonetic) {
    const double bps((double) 60 / mBPM);
    switch (aPhonetic) {
        case p1: return bps * 4 * 1000;
        case p2: return bps * 2 * 1000;
        case p4: return bps * 1000;
        case p8: return bps / 2 * 1000;
        case p16:return bps / 4 * 1000;
    }
}

int MusicScore::convertDynamics(const Dynamics& aDynamics) {
    static const double PER_DYNAMICS(127 / 9);
    return (aDynamics + 1) * PER_DYNAMICS;
}

KMidi::Note MusicScore::convertNote(const Note& aNote) {
    return KMidi::Note{
        aNote.mTone,
        convertPhonetic(aNote.mPhonetic),
        convertDynamics(aNote.mDynamics)
    };
}

