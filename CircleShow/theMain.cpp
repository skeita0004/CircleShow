#include <WinSock2.h>
#include <WS2tcpip.h>
#include <DxLib.h>
#include "Circle.h"

#pragma comment(lib, "ws2_32.lib")

//ウィンドウサイズ
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

int APIENTRY WinMain(_In_     HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_     LPSTR     lpCmdLine,
					 _In_     INT       nCmdShow)
{
    //DxLibの初期化・ウィンドウ処理
    ChangeWindowMode(true);
    SetWindowSizeChangeEnableFlag(false, false);
    SetMainWindowText("Client");
    SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
    SetBackgroundColor(0, 0, 0);
    SetAlwaysRunFlag(1);
    
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetDrawScreen(DX_SCREEN_BACK);

    while (true)
    {
        ClearDrawScreen();

        //動作確認用の円
        DrawCircle(WIN_WIDTH / 2, WIN_HEIGHT / 2, 10, GetColor(255, 0, 0));

        ScreenFlip();
        WaitTimer(16);
        if (ProcessMessage() == -1)
        {
            break;
        }
        if (CheckHitKey(KEY_INPUT_ESCAPE))
        {
            break;
        }
    }

    DxLib_End();
    return 0;
}
