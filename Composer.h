/**
 * @file   Composer.h
 * @brief  Conposer
 * @author Maeda Takumi
 */
#ifndef COMPOSER_H
#define COMPOSER_H

#include "MusicScore.h"

/**
 * @brief  \~english  make music
 * @brief  \~japanese 作曲家
 * @author \~ Maeda Takumi
 */
class Composer final {
private:
    /* 和音       */ using Chord = Vector<KMidi::Tone>;
    /* コード進行 */ using ChordProgression = Vector<Chord>;

    /* ----- 和音 -----*/
    static const Chord NONE;
    static const Chord C, C_E, C_G, Cdim, C7, C7_E, CM7, Cadd9;
    static const Chord D, Dm, D7, D7_9, D7__F, Dm7, Dm7_G, DmM7, DmM7__C, Dm7_5_A_;
    static const Chord Em, Em_B, E_dim, Esus4, E7, E7aug, E7sus4_B, E7__G, Em7, E7_9_13, E_M7_F;
    static const Chord F, F_C, F_G, F_A, F6, F7, FM7, FM7_9, Fm6, _Fdim;
    static const Chord G, G_C, G_B, G6, G7, G7_B, G7_13, Gm7;
    static const Chord Am, Am_G, A7, A7_13, A7_9_13, Am7, Am7_9;
    static const Chord B__C, B_6, Bm7_11, B_M7, B_7_9_11;

    /* コード進行表 */
    static const Vector<ChordProgression> CP_LIST;

    Composer() = default;
    virtual ~Composer() = default;
public:
    /**
     * \~english
     * @brief  make new MusicScore
     * @return new MusicScore
     * \~japanese
     * @brief  新しく楽譜を編成します。
     * @return 楽譜
     */
    static MusicScore compose();
};

#endif /* COMPOSER_H */

