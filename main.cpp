/**
 * @file   main.cpp
 * @brief  PurPose's main file
 * @author Maeda Takumi
 */
#include "main.h"
#include "PurPose.h"

/**
 * @brief windows main function
 * @param  aInst     
 * @param  aPrevInst 
 * @param  aCmdLine   
 * @param  aCmdShow  
 * @return result of main function
 */
int WINAPI _tWinMain(
        HINSTANCE aInst,
        HINSTANCE aPrevInst,
        LPSTR aCmdLine,
        int aCmdShow
        ) {
    KWindow::MainArgs args{aInst, aPrevInst, aCmdLine, aCmdShow};

    KWindow window(&args, KWindow::SIZE, "PurPose");
    PurPose game(window);
    window.setListener(&game);
    try {
        window.show();
    } catch (Error& e) {
        message(e.what(), "初期化エラー");
        return 0;
    }
    game.start(FPS);

    return 0;
}
