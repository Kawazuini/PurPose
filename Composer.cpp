/**
 * @file   Composer.cpp
 * @brief  Conposer
 * @author Maeda Takumi
 */
#include "Composer.h"

const Composer::Chord Composer::NONE;

const Composer::Chord Composer::C{KMidi::C3, KMidi::C4, KMidi::E4, KMidi::G4};
const Composer::Chord Composer::C_E{KMidi::E3, KMidi::C5, KMidi::E4, KMidi::G4};
const Composer::Chord Composer::C_G{KMidi::G3, KMidi::C5, KMidi::E5, KMidi::G4};
const Composer::Chord Composer::Cdim{KMidi::C3, KMidi::C4, KMidi::E4_, KMidi::G4_, KMidi::A4};
const Composer::Chord Composer::C7{KMidi::C3, KMidi::C4, KMidi::E4, KMidi::G4, KMidi::B4_};
const Composer::Chord Composer::C7_E{KMidi::E3, KMidi::C5, KMidi::E4, KMidi::G4, KMidi::B4_};
const Composer::Chord Composer::CM7{KMidi::C3, KMidi::C4, KMidi::E4, KMidi::G4, KMidi::B4};
const Composer::Chord Composer::Cadd9{KMidi::C3, KMidi::C4, KMidi::E4, KMidi::G4, KMidi::D5};

const Composer::Chord Composer::D{KMidi::D3, KMidi::D4, KMidi::_F4, KMidi::A4};
const Composer::Chord Composer::Dm{KMidi::D3, KMidi::D4, KMidi::F4, KMidi::A4};
const Composer::Chord Composer::D7{KMidi::D3, KMidi::D4, KMidi::_F4, KMidi::A4, KMidi::C5};
const Composer::Chord Composer::D7_9{KMidi::D3, KMidi::D4, KMidi::_F4, KMidi::A4, KMidi::C5, KMidi::E5};
const Composer::Chord Composer::D7__F{KMidi::_F3, KMidi::D5, KMidi::_F4, KMidi::A4, KMidi::C5};
const Composer::Chord Composer::Dm7{KMidi::D3, KMidi::D4, KMidi::F4, KMidi::A4, KMidi::C5};
const Composer::Chord Composer::Dm7_G{KMidi::G3, KMidi::D4, KMidi::F4, KMidi::A4, KMidi::C5};
const Composer::Chord Composer::DmM7{KMidi::D3, KMidi::D4, KMidi::F4, KMidi::A4, KMidi::_C5};
const Composer::Chord Composer::DmM7__C{KMidi::_C3, KMidi::D4, KMidi::_C4, KMidi::F4, KMidi::A4};
const Composer::Chord Composer::Dm7_5_A_{KMidi::A3_, KMidi::D5, KMidi::A4_, KMidi::C5, KMidi::F5};

const Composer::Chord Composer::Em{KMidi::E3, KMidi::E4, KMidi::G4, KMidi::B4};
const Composer::Chord Composer::Em_B{KMidi::B2, KMidi::E4, KMidi::_G4, KMidi::B3};
const Composer::Chord Composer::E_dim{KMidi::E3_, KMidi::E4_, KMidi::G4_, KMidi::A4, KMidi::C5};
const Composer::Chord Composer::Esus4{KMidi::E3, KMidi::E4, KMidi::A4, KMidi::A4, KMidi::B4};
const Composer::Chord Composer::E7{KMidi::E3, KMidi::E4, KMidi::_G4, KMidi::B4, KMidi::D5};
const Composer::Chord Composer::E7aug{KMidi::E3, KMidi::E4, KMidi::_G4, KMidi::C5, KMidi::D5};
const Composer::Chord Composer::E7sus4_B{KMidi::B2, KMidi::E4, KMidi::B3, KMidi::D4, KMidi::A4};
const Composer::Chord Composer::E7__G{KMidi::_G3, KMidi::E5, KMidi::_G4, KMidi::B4, KMidi::D5};
const Composer::Chord Composer::Em7{KMidi::E3, KMidi::E4, KMidi::G4, KMidi::B4, KMidi::D5};
const Composer::Chord Composer::E7_9_13{KMidi::E3, KMidi::E4, KMidi::_G4, KMidi::B4, KMidi::D5, KMidi::F5, KMidi::C6};
const Composer::Chord Composer::E_M7_F{KMidi::F3, KMidi::E4_, KMidi::G4, KMidi::B4_, KMidi::D5};

const Composer::Chord Composer::F{KMidi::F3, KMidi::F4, KMidi::A4, KMidi::C5};
const Composer::Chord Composer::F_C{KMidi::C3, KMidi::F4, KMidi::A4, KMidi::C4};
const Composer::Chord Composer::F_G{KMidi::G3, KMidi::F4, KMidi::A4, KMidi::C4};
const Composer::Chord Composer::F_A{KMidi::A3, KMidi::F5, KMidi::A4, KMidi::C5};
const Composer::Chord Composer::F6{KMidi::F3, KMidi::F4, KMidi::A4, KMidi::C5, KMidi::D5};
const Composer::Chord Composer::F7{KMidi::F3, KMidi::F4, KMidi::A4, KMidi::C5, KMidi::E5_};
const Composer::Chord Composer::FM7{KMidi::F3, KMidi::F4, KMidi::A4, KMidi::C5, KMidi::E5};
const Composer::Chord Composer::FM7_9{KMidi::F3, KMidi::F4, KMidi::A4, KMidi::C5, KMidi::E5, KMidi::G5};
const Composer::Chord Composer::Fm6{KMidi::F3, KMidi::F4, KMidi::A4_, KMidi::C5, KMidi::D5};
const Composer::Chord Composer::_Fdim{KMidi::_F3, KMidi::_F4, KMidi::A4, KMidi::C5, KMidi::D5};

const Composer::Chord Composer::G{KMidi::G3, KMidi::G4, KMidi::B4, KMidi::D5};
const Composer::Chord Composer::G_C{KMidi::C3, KMidi::G4, KMidi::B4, KMidi::D5};
const Composer::Chord Composer::G_B{KMidi::B2, KMidi::G4, KMidi::B3, KMidi::D4};
const Composer::Chord Composer::G6{KMidi::G3, KMidi::G4, KMidi::B4, KMidi::D5, KMidi::E5};
const Composer::Chord Composer::G7{KMidi::G3, KMidi::G4, KMidi::B4, KMidi::D5, KMidi::F5};
const Composer::Chord Composer::G7_B{KMidi::B2, KMidi::G4, KMidi::B3, KMidi::D4, KMidi::F4};
const Composer::Chord Composer::G7_13{KMidi::G3, KMidi::G4, KMidi::B4, KMidi::D5, KMidi::F5, KMidi::E6};
const Composer::Chord Composer::Gm7{KMidi::G3, KMidi::G4, KMidi::B4_, KMidi::D5, KMidi::F5};

const Composer::Chord Composer::Am{KMidi::A2, KMidi::A3, KMidi::C4, KMidi::E4};
const Composer::Chord Composer::Am_G{KMidi::G3, KMidi::A3, KMidi::C4, KMidi::E4};
const Composer::Chord Composer::A7{KMidi::A2, KMidi::A3, KMidi::_C4, KMidi::E4, KMidi::G4};
const Composer::Chord Composer::A7_13{KMidi::A2, KMidi::A3, KMidi::_C4, KMidi::E4, KMidi::G4, KMidi::F5};
const Composer::Chord Composer::A7_9_13{KMidi::A2, KMidi::A3, KMidi::_C4, KMidi::E4, KMidi::G4, KMidi::B4_, KMidi::F5};
const Composer::Chord Composer::Am7{KMidi::A2, KMidi::A3, KMidi::C4, KMidi::E4, KMidi::G4};
const Composer::Chord Composer::Am7_9{KMidi::A2, KMidi::A3, KMidi::C4, KMidi::E4, KMidi::G4, KMidi::B4};

const Composer::Chord Composer::B__C{KMidi::C3, KMidi::B3_, KMidi::D4, KMidi::F4};
const Composer::Chord Composer::B_6{KMidi::B2_, KMidi::B3_, KMidi::D4, KMidi::F4, KMidi::G4};
const Composer::Chord Composer::Bm7_11{KMidi::B2, KMidi::B3, KMidi::D4, KMidi::_F4, KMidi::A4, KMidi::E5};
const Composer::Chord Composer::B_M7{KMidi::B2_, KMidi::B3_, KMidi::D4, KMidi::F4, KMidi::A4};
const Composer::Chord Composer::B_7_9_11{KMidi::B2_, KMidi::B3_, KMidi::D4, KMidi::F4, KMidi::A4_, KMidi::C5, KMidi::E5};

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
    Composer::ChordProgression
    {C, NONE, G_B, NONE, Am7, NONE, Em7, NONE, F, NONE, C_E, NONE, Dm7, NONE, G7, NONE,},
    Composer::ChordProgression
    {C, NONE, F_A, NONE, G_B, NONE, E7__G, NONE, Am, NONE, D7__F, NONE, C, NONE, Am, G_B,},
    Composer::ChordProgression
    {C, NONE, G_B, NONE, F_A, NONE, C_G, NONE, Dm, NONE, DmM7__C, NONE, F_C, NONE, Dm7_G, G7,},
    Composer::ChordProgression
    {Am, G, F, G, Am, G, F, G, C, Dm, C_E, F, Dm7_G, NONE, G7, NONE,},
    Composer::ChordProgression
    {G_C, NONE, C, NONE, G_C, NONE, C, NONE, FM7, NONE, F6, NONE, Dm7, NONE, Dm7_G, NONE,},
    Composer::ChordProgression
    {C, NONE, Em7, NONE, Dm7, NONE, A7, NONE, Dm7, NONE, E7, NONE, Dm7_G, NONE, NONE, NONE,},
    Composer::ChordProgression
    {C, NONE, B_6, NONE, A7, NONE, A7, NONE, Dm7, NONE, Fm6, NONE, C, NONE, Dm7_G, NONE,},
    Composer::ChordProgression
    {C, NONE, G_C, NONE, B__C, NONE, F, NONE, F, NONE, Dm7, NONE, Dm7_G, NONE, C, NONE,},
    Composer::ChordProgression
    {CM7, NONE, NONE, NONE, CM7, NONE, Dm7, Em7, Dm7_G, NONE, NONE, NONE, Dm7_G, NONE, NONE, NONE,},
    Composer::ChordProgression
    {C, NONE, C7_E, NONE, F, NONE, Fm6, NONE, E7, A7_9_13, Dm7, G7_13, C, NONE, NONE, NONE,},
    Composer::ChordProgression
    {F6, NONE, G6, NONE, Am7, NONE, G6, NONE, Dm7, NONE, Em7, NONE, F7, NONE, NONE, NONE,},
    Composer::ChordProgression
    {Cadd9, NONE, NONE, NONE, Bm7_11, NONE, E7_9_13, NONE, Am7_9, NONE, FM7_9, NONE, Em7, Am7, Dm7, G7,},
    Composer::ChordProgression
    {Am7, NONE, Em7, NONE, Dm7, NONE, Dm7_G, NONE, CM7, NONE, NONE, NONE, CM7, NONE, NONE, NONE,},
    Composer::ChordProgression
    {C, NONE, Em_B, NONE, Am, NONE, Am_G, NONE, FM7, NONE, Em7, NONE, Dm7, NONE, G_B, NONE, G_B, F_G,},
    Composer::ChordProgression
    {C, NONE, Am7, NONE, Dm7, NONE, G7, NONE, Dm, A7, Dm, G7, C, NONE, C, NONE,},
    Composer::ChordProgression
    {Dm7, NONE, CM7, NONE, Dm7, NONE, CM7, NONE, B_M7, NONE, Am7, NONE, Gm7, NONE, FM7, E_M7_F,},
    Composer::ChordProgression
    {C, NONE, Dm7_G, G7, C, E7aug, F, _Fdim, C_G, Am7, Dm7, G7, C, Am7, Dm7, G7,},
    Composer::ChordProgression
    {FM7, NONE, Em7, Am7, FM7, NONE, Em7, Am7, FM7, NONE, Em7, Am7, FM7, NONE, Dm7_G, NONE,},
    Composer::ChordProgression
    {Am7, NONE, NONE, NONE, D7_9, NONE, NONE, NONE, Dm7_G, NONE, NONE, NONE, C, NONE, NONE, NONE,},
    Composer::ChordProgression
    {C, NONE, G7_B, NONE, C, NONE, G7_B, NONE, C, NONE, E7sus4_B, E7__G, B_7_9_11, A7, Dm7_5_A_, G7,},
    Composer::ChordProgression
    {C, A7_13, DmM7, Dm, G7, NONE, Cdim, C, Em7, E_dim, Dm7, G7_13, Dm7, G7_13, C, G7,},
    Composer::ChordProgression
    {Am, NONE, E7, NONE, G, NONE, D, NONE, F, NONE, C, NONE, Dm, NONE, E7, NONE,},
    Composer::ChordProgression
    {Dm7_G, NONE, G7, NONE, CM7, NONE, FM7, NONE, Esus4, NONE, E7, NONE, Am, NONE, Am, NONE},
    Composer::ChordProgression
    {C, Em_B, Am, Em, Dm, Am, F, G7, C, Em_B, Am, Em, Dm, Em, Dm7_G, NONE},
};

MusicScore Composer::compose() {
    // ♪作曲♪
    // 15個のコード進行(4小説編成)をランダムに繋ぎ合わせる
    MusicScore::Score score(MusicScore::MAX_PLAYERS, Vector<MusicScore::Note>(64 * 15, MusicScore::Note()));

    for (int c = 0; c < 15; ++c) {
        ChordProgression cp(CP_LIST[random(CP_LIST.size())]);
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
            score[6][c * 64 + i * 4] = MusicScore::Note(cp[0][0], phon, MusicScore::p);
        }
    }

    return MusicScore(
            random(60) + 60,
            MusicScore::Players {
        static_cast<KMidi::Instrument> (random(80)), // KMidi::ContraBass, KMidi::Cello, KMidi::Viola, KMidi::Violin, KMidi::Clarinet, KMidi::Flute, KMidi::OrchestralHarp,
        static_cast<KMidi::Instrument> (random(80)),
        static_cast<KMidi::Instrument> (random(80)),
        static_cast<KMidi::Instrument> (random(80)),
        static_cast<KMidi::Instrument> (random(80)),
        static_cast<KMidi::Instrument> (random(80)),
        static_cast<KMidi::Instrument> (random(80)),
    },
    score
            );
}

