/**
 * @file   Orrchestra.cpp
 * @brief  Orchestra
 * @author Maeda Takumi
 */
#include "Orchestra.h"

Orchestra::Orchestra(const MusicScore& aMusicScore) :
mConducter(Conduct, this),
mMusicScore(aMusicScore),
mPlaying(false) {
    for (int i = 0; i < MusicScore::MAX_PLAYERS; ++i) {
        mConcertHall.set(i, mMusicScore.mPlayers[i]);
    }
}

Orchestra::~Orchestra() {
    if (!mPlaying) mBlackout.unlock();
    mConducter.stop();
}

void* Orchestra::Conduct(void* args) {
    ((Orchestra*) args)->mBlackout.lock();
    Orchestra & orche(*(Orchestra*) args);
    MusicScore & score(orche.mMusicScore);

    int seekence(0);
    int length(score.mScore[0].size());
    int sleep(score.convertPhonetic(MusicScore::p16)); // 指揮棒を16分で振る
    orche.mBlackout.unlock();

    while (true) {
        orche.mBlackout.lock();
        KMidi::Note note;
        for (int i = 0; i < MusicScore::MAX_PLAYERS; ++i) {
            note = score.mScore[i][seekence];
            if (note.mTone != KMidi::C0) orche.mConcertHall.play(i, note);
        }
        if (length <= ++seekence) seekence = 0; // ループ
        orche.mBlackout.unlock();
        Sleep(sleep);

        pthread_testcancel();
    }
}

void Orchestra::play() {
    if (!mPlaying) {
        mPlaying = true;
        mBlackout.unlock();
    }
}

void Orchestra::stop() {
    if (mPlaying) {
        mPlaying = false;
        mBlackout.lock();
        mConcertHall.stop();
    }
}

