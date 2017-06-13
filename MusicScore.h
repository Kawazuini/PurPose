/**
 * @file   MusicScore.cpp
 * @brief  MusicScore
 * @author Maeda Takumi
 */
#ifndef MUSICSCORE_H
#define MUSICSCORE_H

#include "main.h"

/**
 * @brief \~english  Music Score
 * @brief \~japanese 楽譜
 * @author \~ Maeda Takumi
 */
class MusicScore {
public:
    /**
     * @brief \~english  max of player number
     * @brief \~japanese 最大演奏楽器数
     */
    static const int MAX_PLAYERS;

    /**
     * @brief \~english  phonetic sign
     * @brief \~japanese 音価記号
     */
    enum Phonetic {
        /** \~japanese 全音符   */ p1,
        /** \~japanese 2分音符  */ p2,
        /** \~japanese 4分音符  */ p4,
        /** \~japanese 8分音符  */ p8,
        /** \~japanese 16分音符 */ p16,
    };

    /**
     * @brief \~english  dynamics sign
     * @brief \~japanese 強弱記号
     */
    enum Dynamics {
        /** \~japanese ピアニッシシモ   */ ppp,
        /** \~japanese ピアニッシモ     */ pp,
        /** \~japanese ピアノ           */ p,
        /** \~japanese メゾピアノ       */ mp,
        /** \~japanese メゾフォルテ     */ mf,
        /** \~japanese フォルテ         */ f,
        /** \~japanese フォルティシモ   */ ff,
        /** \~japanese フォルティシシモ */ fff,
    };

    /**
     * @brief \~english  music note
     * @brief \~japanese 音符
     */
    struct Note {
        /** @brief 音程 */ KMidi::Tone mTone;
        /** @brief 音価 */ Phonetic mPhonetic;
        /** @brief 強弱 */ Dynamics mDynamics;

        /**
         * \~english
         * @param aTone     tone
         * @param aPhonetic long of sound
         * @param aDynamics sound velocity
         * \~japanese
         * @param aTone     音程
         * @param aPhonetic 音の長さ
         * @param aDynamics 音の強さ
         */
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

    /**
     * @brief \~english  instruments
     * @brief \~japanese 演奏楽器
     */
    using Players = Vector<KMidi::Instrument>;
    /**
     * @brief \~english  music notes
     * @brief \~japanese 楽譜
     */
    using Score = Vector<Vector<Note>>;
    /**
     * @brief \~english  beat per minute
     * @brief \~japanese 分間拍数
     */
    int mBPM;
    /**
     * @brief \~english  instruments
     * @brief \~japanese 演奏楽器
     */
    Players mPlayers;
    /**
     * @brief \~english  score
     * @brief \~japanese 楽譜
     */
    Vector<Vector<KMidi::Note>> mScore;

    MusicScore();
    /**
     * \~english
     * @param aBPM     beat per minute
     * @param aPlayers instruments
     * @param aScore   score
     * \~japanese
     * @param aBPM     分間拍数
     * @param aPlayers 演奏楽器
     * @param aScore   楽譜
     */
    MusicScore(
            const int& aBPM,
            const Players& aPlayers,
            const Score& aScore
            );
    ~MusicScore() = default;

    /**
     * \~english
     * @brief  convert sound symbol to numeric value.
     * @param  aPhonetic phonetic
     * @return value representing long
     * \~japanese
     * @brief  音価記号を数値に変換します。
     * @param  aPhonetic 音価記号
     * @return 長さを表す数値
     */
    int convertPhonetic(const Phonetic& aPhonetic);
    /**
     * \~english
     * @brief  convert dynamic symbols to numbers.
     * @param  aDynamics phonetic
     * @return value representing strength
     * \~japanese
     * @brief  強弱記号を数値に変換します。
     * @param  aDynamics 強弱記号
     * @return 強さを表す数値
     */
    int convertDynamics(const Dynamics& aDynamics);
    /**
     * \~english
     * @brief  convert note to information for MIDI.
     * @param  aNote music note
     * @return info for MIDI
     * \~japanese
     * @brief  音符をMIDI用の情報に変換します。
     * @param  aNote 音符
     * @return MIDI音情報
     */
    KMidi::Note convertNote(const Note& aNote);
};

#endif /* MUSICSCORE_H */

