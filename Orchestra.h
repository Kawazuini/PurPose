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
class Orchestra final : private KNonCopy {
private:
    /* SE専用チャンネル   */ static const int CHANNEL_SE;

    /* 演奏環境           */ KMidi mConcertHall;
    /* 指揮者             */ KThread mConducter;
    /* 暗幕               */ KMutex mBlackout;
    /* 楽譜               */ MusicScore mMusicScore;
    /* 演奏中か           */ bool mPlaying;
    /* 音量               */ double mVolume;

    /* 演奏関数           */ static void* Conduct(void* args);
public:
    Orchestra();
    ~Orchestra();

    /**
     * \~english
     * @brief set music score.
     * @param aMusicScore music score
     * \~japanese
     * @brief 楽譜を設定します。
     * @param aMusicScore 楽譜
     */
    void setScore(const MusicScore& aMusicScore);
    /// @brief \~english  play music.
    /// @brief \~japanese 音楽を流します。
    void play();
    /// @brief \~english  stop music.
    /// @brief \~japanese 音楽を止めます。
    void stop();

    /**
     * \~english
     * @brief play SE.
     * @param aInst instrument
     * @param aNote sound information
     * \~japanese
     * @brief SEを流します。
     * @param aInst 楽器
     * @param aNote 音情報
     */
    void playSE(
            const KMidi::Instrument& aInst,
            const KMidi::Note& aNote
            );
    
    void changeVolume(const double& aAmount);
    const double& volume();
};

#endif /* ORCHESTRA_H */

