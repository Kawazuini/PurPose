/**
 * @file   Composer.h
 * @brief  Conposer
 * @author Maeda Takumi
 */
#ifndef COMPOSER_H
#define COMPOSER_H

#include "MusicScore.h"

class Composer {
private:
    using Chord = Vector<KMidi::Tone>;
    using ChordProgression = Vector<Chord>;

    static const Chord NONE;
    static const Chord C, C_E, C_G, Cdim, C7, C7_E, CM7, Cadd9;
    static const Chord D, Dm, D7, D7_9, D7__F, Dm7, Dm7_G, DmM7, DmM7__C, Dm7_5_A_;
    static const Chord Em, Em_B, E_dim, Esus4, E7, E7aug, E7sus4_B, E7__G, Em7, E7_9_13, E_M7_F;
    static const Chord F, F_C, F_G, F_A, F6, F7, FM7, FM7_9, Fm6, _Fdim;
    static const Chord G, G_C, G_B, G6, G7, G7_B, G7_13, Gm7;
    static const Chord Am, Am_G, A7, A7_13, A7_9_13, Am7, Am7_9;
    static const Chord B__C, B_6, Bm7_11, B_M7, B_7_9_11;

    // chord progression
    static const Vector<ChordProgression> CP_LIST;


    Composer() = default;
    virtual ~Composer() = default;
public:
    static MusicScore compose(const int& aBPM);
};

#endif /* COMPOSER_H */

