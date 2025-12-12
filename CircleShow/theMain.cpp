#include <WinSock2.h>
#include <WS2tcpip.h>
#include <format>
#include <string>
#include <DxLib.h>


#pragma comment(lib, "ws2_32.lib")

//ウィンドウサイズ
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

namespace
{
    const uint16_t SV_PORT{8888};
    const char*    SERVER_IPADDRESS{"192.168.42.3"};
}

int APIENTRY WinMain(_In_     HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_     LPSTR     lpCmdLine,
					 _In_     INT       nCmdShow)
{
    WSADATA wsaData{};
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) not_eq 0)
    {
        std::string errorMsg{ std::format("Error WSAStartup. Error Code : {}", WSAGetLastError()) };
        MessageBox(nullptr, errorMsg.c_str(), "ERROR!", MB_OK bitor MB_ICONERROR);
        return -1;
    }

    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET)
    {
        std::string errorMsg{ std::format("Error socket. Error Code : {}", WSAGetLastError()) };
        MessageBox(nullptr, errorMsg.c_str(), "ERROR!", MB_OK bitor MB_ICONERROR);
        return -1;
    }

    SOCKADDR_IN serverAddress{};
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port   = htons(SV_PORT);
    inet_pton(AF_INET, SERVER_IPADDRESS, &serverAddress.sin_addr.s_addr);

    int serverAddressLength = sizeof(serverAddress);
    if (connect(sock, (SOCKADDR*)&serverAddress, serverAddressLength) == SOCKET_ERROR)
    {
        std::string errorMsg{ std::format("Error connect. Error Code : {}", WSAGetLastError()) };
        MessageBox(nullptr, errorMsg.c_str(), "ERROR!", MB_OK bitor MB_ICONERROR);
        return -1;
    }
  
    //DxLibの初期化・ウィンドウ処理
    ChangeWindowMode(true);
    SetWindowSizeChangeEnableFlag(false, false);
    SetMainWindowText("Client");
    SetGraphMode(WIN_WIDTH, WIN_HEIGHT, 32);
    
    if (DxLib_Init() == -1)
    {
        return -1;
    }

    SetBackgroundColor(0, 0, 0);
    SetDrawScreen(DX_SCREEN_BACK);
    SetAlwaysRunFlag(1);

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
    closesocket(sock);
    WSACleanup();
    return 0;
}
