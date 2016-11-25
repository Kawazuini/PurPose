/**
 * @file main.cpp
 * @brief PurPose's main file
 */
#include <thread>

#include "main.h"
#include "PurPose.h"

int WINAPI WinMain(
        HINSTANCE aInst,
        HINSTANCE aPrevInst,
        LPSTR aCmdLine,
        int aCmdShow
        ) {
    KWindow::MainArgs args{aInst, aPrevInst, aCmdLine, aCmdShow};

    KWindow * const window = new KWindow(&args, KWindow::SIZE, "PurPose");
    window->setClearColor(BACK_COLOR);
    PurPose * const game = new PurPose(window);
    window->setListener(game);
    try {
        window->show();
    } catch (Error& e) {
        message(e.what(), "初期化エラー");
        return 0;
    }

    game->start(FPS);

    delete window;
    delete game;

    return 0;
}
