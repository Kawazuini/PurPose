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
    /**
     * @brief \~english  concert hall
     * @brief \~japanese 演奏会場
     */
    KMidi mConcertHall;
    /**
     * @brief \~english  orchestra manager
     * @brief \~japanese 演奏管理者
     */
    KThread mConducter;
    /**
     * @brief \~english  blackout
     * @brief \~japanese 暗幕
     */
    KMutex mBlackout;
    /**
     * @brief \~english  music score
     * @brief \~japanese 楽譜
     */
    MusicScore mMusicScore;

    /**
     * @brief \~english  whether playing
     * @brief \~japanese 演奏中か
     */
    bool mPlaying;

    static void* Conduct(void* args);
public:
    Orchestra(const MusicScore& aMusicScore);
    ~Orchestra();

    void play();
    void stop();
};

#endif /* ORCHESTRA_H */

