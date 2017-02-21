/**
 * @file   Orrchestra.h
 * @brief  Orchestra
 * @author Maeda Takumi
 */
#ifndef ORCHESTRA_H
#define ORCHESTRA_H

#include "MusicScore.h"

/**
 * @brief  \~english  Orchestra(One time contract of performance)
 * @brief  \~japanese オーケストラ(演奏契約は一度きり)
 * @author \~ Maeda Takumi
 */
class Orchestra : private KNonCopy {
private:
    /* 演奏環境           */ KMidi mConcertHall;
    /* 指揮者             */ KThread mConducter;
    /* 暗幕               */ KMutex mBlackout;
    /* 楽譜               */ MusicScore mMusicScore;
    /* 演奏中か           */ bool mPlaying;

    static void* Conduct(void* args);
public:
    Orchestra();
    ~Orchestra();

    void setScore(const MusicScore& aMusicScore);
    void play();
    void stop();
};

#endif /* ORCHESTRA_H */

