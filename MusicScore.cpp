/**
 * @file   MusicScore.cpp
 * @brief  MusicScore
 * @author Maeda Takumi
 */
#include "MusicScore.h"

MusicScore::MusicScore(
        const int& aBPM,
        const Players& aPlayers,
        const Score& aScore
        ) :
mConducter(Condocter, this),
mBPM(aBPM) {
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        mPlayers[i] = aPlayers[i];
        mMidi.set(i, mPlayers[i]);
        for (Note* j : aScore[i]) {
            mScore[i].push_back(convertNote(j));
        }
    }
    mDestructor.unlock();
}

MusicScore::~MusicScore() {
    mConducter.stop();
    for (int i = 0; i < MAX_PLAYERS; ++i) {
        for (KMidi::Note* j : mScore[i]) {
            if (j) delete j;
        }
    }
}

void* MusicScore::Condocter(void* args) {
    ((MusicScore*) args)->mDestructor.lock();
    MusicScore & score(*((MusicScore*) args));

    int seekence(0);
    int length(score.mScore[0].size());
    int sleep(score.toMilli(p16)); // 指揮棒を16分で振る
    score.mDestructor.unlock();

    while (true) {
        score.mDestructor.lock();
        KMidi::Note* note;
        for (int i = 0; i < MAX_PLAYERS; ++i) {
            note = score.mScore[i][seekence];
            if (note) score.mMidi.play(i, *note);
        }
        if (length <= ++seekence) seekence = 0; // ループ
        score.mDestructor.unlock();
        Sleep(sleep);

        pthread_testcancel();
    }
}

