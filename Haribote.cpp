/**
 * @file   Haribote.cpp
 * @brief  Haribote
 * @author Maeda Takumi
 */
#include "Haribote.h"

#include "GameState.h"

Vector<Haribote*> Haribote::sDrawList;

Haribote::Haribote(
        const KVector& aPosition,
        const float& aSize,
        const KTexture& aTexture
        ) :
mDistance(0.0f),
mBoard(
Vector<KVector>{
    aPosition + KVector(aSize / 2.0f, -aSize / 2.0f),
    aPosition + KVector(-aSize / 2.0f, -aSize / 2.0f),
    aPosition + KVector(-aSize / 2.0f, aSize / 2.0f),
    aPosition + KVector(aSize / 2.0f, aSize / 2.0f),
},
&aTexture
        ) {
    KDrawer::remove();
    mBoard.remove();
    add();
}

Haribote::~Haribote() {
    remove();
}

void Haribote::draw() const {
    mBoard.draw();
}

const void Haribote::HARIBOTE_DRAW(const GameState& aState) {
    static KVector prePosition; // 1F前のカメラ位置
    const KVector & cameraPosition(KCamera::Position());

    if (prePosition != cameraPosition) {
        prePosition = cameraPosition;
        for (Haribote* i : sDrawList) { // カメラとの距離の計算(2乗)
            i->mDistance = (i->mBoard.position() - cameraPosition).lengthSquared();
        }
        // カメラから遠い順に並べる(透過値を考慮して奥から描画)
        std::sort(sDrawList.begin(), sDrawList.end(),
                [](const Haribote* x, const Haribote * y) -> bool {
                    return x->mDistance > y->mDistance;
                }
        );
    }

    KShading::PhongShading->ON();
    for (Haribote* i : sDrawList) i->draw();
}

void Haribote::update(GameState& aState) {
    static const KVector AXIS(0, 1, 0);

    // ハリボテは常にカメラに正面を向かせる
    KVector me2P(aState.mPlayer.position() - mBoard.position());
    // 2段階回転
    KQuaternion rotate(mBoard.normal().extractVertical(AXIS).roundAngle(me2P.extractVertical(AXIS)));
    if (!KVector(rotate).isZero()) {
        mBoard.rotate(rotate);
        mBoard.rotate(mBoard.normal().roundAngle(me2P));
    }
}

void Haribote::add() {
    remove(); // 2重追加防止
    Object::add();
    sDrawList.push_back(this);
}

void Haribote::remove() {
    Object::remove();
    for (auto i = sDrawList.begin(), i_e(sDrawList.end()); i != i_e; ++i) {
        if (*i == this) {
            sDrawList.erase(i);
            return;
        }
    }
}

void Haribote::translate(const KVector& aVec) {
    mBoard.translate(aVec);
}

const KVector& Haribote::normal() const {
    return mBoard.normal();
}

