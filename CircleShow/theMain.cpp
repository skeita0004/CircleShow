#include <WinSock2.h>
#include <WS2tcpip.h>
#include <format>
#include <string>
#include <vector>
#include <DxLib.h>
#include "Circle.h"
#include <cstdlib>

#pragma comment(lib, "ws2_32.lib")


namespace
{
    //ウィンドウサイズ
    const int WIN_WIDTH{ 800 };
    const int WIN_HEIGHT{ 600 };

    const uint16_t SV_PORT{ 8888 };
    //const char*    SERVER_IPADDRESS{"192.168.42.55"};
    const char*    SERVER_IPADDRESS{ "127.0.0.1" };
}

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
    if (DxLib_Init() == -1)
    {
        return -1;
    }

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

    unsigned long args{0x01};
    if (ioctlsocket(sock, FIONBIO, &args) == SOCKET_ERROR)
    {
        std::string errorMsg{ std::format("Error ioctlsocket. Error Code : {}", WSAGetLastError()) };
        MessageBox(nullptr, errorMsg.c_str(), "ERROR!", MB_OK bitor MB_ICONERROR);
        return -1;
    }



    SetBackgroundColor(0, 0, 0);
    SetDrawScreen(DX_SCREEN_BACK);
    SetAlwaysRunFlag(1);

    // 円をつくる
    Circle myCircle{
        .color{GetColor(GetRand(256), GetRand(256), GetRand(256))},
        .x{0},
        .y{0},
        .r{10}
    };

    std::vector<Circle> circles{};

    while (true)
    {
        ClearDrawScreen();

        // マウスの入力取る
        GetMousePoint(&myCircle.x, &myCircle.y);

        // ---------------構造体を送信する----------------
        // 変換
        //char* sendData{}; 
        //sendData = (char*)malloc(sizeof(myCircle)); // ここでmalloc!
        // malloc しないでください そもそもヒープ領域を使わないでください せめて動的確保したヒープ領域を free し忘れないでください 本当に
        //if (sendData == NULL) // malloc失敗
        //{
        //    std::string errorMsg{ "Error malloc." };
        //    MessageBox(nullptr, errorMsg.c_str(), "ERROR!", MB_OK bitor MB_ICONERROR);
        //    return -1;
        //}

        char sendData[sizeof(myCircle)]{};

        myCircle.Store(sendData);

        //printfDx("x: %d, y: %d, r: %d, color: %06x\n", myCircle.x, myCircle.y, myCircle.r, myCircle.color);

        // 送信
        int retVal = send(sock, sendData, sizeof(myCircle), 0);
        if (retVal == SOCKET_ERROR and WSAGetLastError() != WSAEWOULDBLOCK)
        {
            std::string errorMsg{ std::format("Error send (Sending my circle data). Error Code : {}", WSAGetLastError()) };
            MessageBox(nullptr, errorMsg.c_str(), "ERROR!", MB_OK bitor MB_ICONERROR);
            return -1;
        }

        // -------------受信を行う-------------------

        // 受信用ポインタ変数
        char recvRawData[sizeof(Circle)]{};

        // まず人数を取得
        size_t recvDataSize{};
        size_t userNum{0};
        retVal = recv(sock, recvRawData, sizeof(char), 0);
        if (retVal == SOCKET_ERROR and WSAGetLastError() != WSAEWOULDBLOCK)
        {
            std::string errorMsg{ std::format("Error recv (Receiving my circle data). Error Code : {}", WSAGetLastError()) };
            MessageBox(nullptr, errorMsg.c_str(), "ERROR!", MB_OK bitor MB_ICONERROR);
            return -1;
        }
        memcpy_s(&userNum, sizeof(userNum), recvRawData, sizeof(char));
        recvDataSize = sizeof(Circle) * userNum;

        // 本命のデータをユーザ分取得
        retVal = recv(sock, recvRawData, recvDataSize, 0);
        if (retVal == SOCKET_ERROR and WSAGetLastError() != WSAEWOULDBLOCK)
        {
            std::string errorMsg{ std::format("Error recv (Receiving my circle data). Error Code : {}", WSAGetLastError()) };
            MessageBox(nullptr, errorMsg.c_str(), "ERROR!", MB_OK bitor MB_ICONERROR);
            return -1;
        }

        if (userNum > 0)  // 受信して人数がいるなら更新
        {
            circles.clear();
        }
        // 人数分のfor
        for (int i = 0; i < userNum; i++)
        {
            // ここの処理すごく二度手間感ある…
            circles.push_back(Circle{});

            // 変換してメンバたちに代入
            // (Circleの方で実装)
            circles[i].Load(recvRawData + sizeof(Circle) * i);
        }

        // 表示
        for (auto& circle : circles)
        {
            DrawCircle(circle.x, circle.y, circle.r, circle.color);
        }

        //Circle circle;
        //circle.x = 0;
        //circle.y = 0;
        //circle.r = 30;
        //circle.color = GetColor(255, 0, 0);
        //
        ////円表示
        //DrawCircle(circle.x, circle.y, circle.r, circle.color);
        //
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
