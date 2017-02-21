/**
 * @file   Composer.cpp
 * @brief  Conposer
 * @author Maeda Takumi
 */
#include "Composer.h"

const Composer::Chord Composer::NONE;
const Composer::Chord Composer::C{KMidi::C3, KMidi::C4, KMidi::E4, KMidi::G4};
const Composer::Chord Composer::C_E{KMidi::E3, KMidi::C5, KMidi::E4, KMidi::G4};
const Composer::Chord Composer::F{KMidi::F3, KMidi::F4, KMidi::A4, KMidi::C5};
const Composer::Chord Composer::G_B{KMidi::B2, KMidi::G4, KMidi::B3, KMidi::D4};
const Composer::Chord Composer::Am{KMidi::A2, KMidi::A3, KMidi::C4, KMidi::E4};
const Composer::Chord Composer::C7{KMidi::C3, KMidi::C4, KMidi::E4, KMidi::G4, KMidi::B4_};
const Composer::Chord Composer::D7{KMidi::D3, KMidi::D4, KMidi::_F4, KMidi::A5, KMidi::C5};
const Composer::Chord Composer::Dm7{KMidi::D3, KMidi::D4, KMidi::F4, KMidi::A4, KMidi::C5};
const Composer::Chord Composer::Dm7_G{KMidi::G3, KMidi::D4, KMidi::F4, KMidi::A4, KMidi::C5};
const Composer::Chord Composer::E7{KMidi::E3, KMidi::E4, KMidi::_G4, KMidi::B4, KMidi::D5};
const Composer::Chord Composer::Em7{KMidi::E3, KMidi::E4, KMidi::G4, KMidi::B4, KMidi::D5};
const Composer::Chord Composer::G7{KMidi::G3, KMidi::G4, KMidi::B4, KMidi::D5, KMidi::F5};
const Composer::Chord Composer::Gm7{KMidi::G3, KMidi::G4, KMidi::B4_, KMidi::D5, KMidi::F5};
const Composer::Chord Composer::A7{KMidi::A2, KMidi::A3, KMidi::_C4, KMidi::E4, KMidi::G4};
const Composer::Chord Composer::Am7{KMidi::A2, KMidi::A3, KMidi::C4, KMidi::E5, KMidi::G5};

const Vector<Composer::ChordProgression> Composer::CP_LIST{
    Composer::ChordProgression
    {C, NONE, NONE, NONE, G_B, NONE, NONE, NONE, F, NONE, NONE, NONE, G7, NONE, NONE, NONE,},
    Composer::ChordProgression
    {C, NONE, Am7, NONE, F, NONE, C, NONE, C, NONE, Am7, NONE, F, NONE, C, NONE,},
    Composer::ChordProgression
    {C, NONE, E7, NONE, A7, NONE, D7, NONE, F, NONE, G7, NONE, C, NONE, G7, NONE,},
    Composer::ChordProgression
    {C, NONE, NONE, NONE, Em7, NONE, NONE, NONE, F, NONE, NONE, NONE, G7, NONE, NONE, NONE,},
    Composer::ChordProgression
    {Am, NONE, NONE, NONE, Gm7, NONE, C7, NONE, F, C_E, Dm7, NONE, Dm7_G, NONE, NONE, NONE,},
};

MusicScore Composer::compose(const int& aBPM) {
    MusicScore::Score score(MusicScore::MAX_PLAYERS, Vector<MusicScore::Note>(64 * 5, MusicScore::Note()));

    // ♪作曲♪
    for (int c = 0; c < 5; ++c) {
        ChordProgression cp(CP_LIST[c]);
        for (int i = 0; i < 16; ++i) {
            int noneCount(0);
            for (int j = i + 1; j < 16 && cp[j].empty(); ++j, ++noneCount);
            MusicScore::Phonetic phon;
            switch (noneCount) {
                case 0: phon = MusicScore::p4;
                    break;
                case 1: phon = MusicScore::p2;
                    break;
                case 3: phon = MusicScore::p1;
                    break;
            }
            for (int j = 1, j_e(cp[i].size()); j < j_e; ++j) {
                score[j - 1][c * 64 + i * 4] = MusicScore::Note(cp[i][j], phon, MusicScore::mf);
            }
            score[4][c * 64 + i * 4] = MusicScore::Note(cp[0][0], phon, MusicScore::p);
        }
    }

    return MusicScore(aBPM, MusicScore::Players{KMidi::Flute, KMidi::Clarinet, KMidi::SopranoSax, KMidi::Trumpet, KMidi::Tuba,}, score);
}

