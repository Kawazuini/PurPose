/**
 * @file   Orrchestra.cpp
 * @brief  Orchestra
 * @author Maeda Takumi
 */
#include "Orchestra.h"

const int Orchestra::CHANNEL_SE(15);

Orchestra::Orchestra() :
mConducter(Conduct, this),
mPlaying(false) {
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

void Orchestra::setScore(const MusicScore& aMusicScore) {
    if (mPlaying) mBlackout.lock();
    {
        mMusicScore = aMusicScore;
        for (int i = 0; i < MusicScore::MAX_PLAYERS; ++i) {
            mConcertHall.set(i, mMusicScore.mPlayers[i]);
        }
    }
    if (mPlaying) mBlackout.unlock();
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

void Orchestra::playSE(const KMidi::Instrument& aInst, const KMidi::Note& aNote) {
    mConcertHall.set(CHANNEL_SE, aInst);
    mConcertHall.play(CHANNEL_SE, aNote);
}

