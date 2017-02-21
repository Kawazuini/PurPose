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
    // triad
    static const Chord C, C_E, F, G_B, Am;
    // tetrad
    static const Chord C7, D7, Dm7, Dm7_G, E7, Em7, G7, Gm7, A7, Am7;

    // chord progression
    static const Vector<ChordProgression> CP_LIST;


    Composer() = default;
    virtual ~Composer() = default;
public:
    static MusicScore compose(const int& aBPM);
};

#endif /* COMPOSER_H */

