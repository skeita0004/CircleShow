#pragma once
#include "WSAIncluding.h"
#include "Circle.h"


/// <summary>
/// クライアントデータ
/// </summary>
struct ClientData
{
    ClientData();
    ClientData(
        const bool _useFlag,
        const Circle& _circle,
        const SOCKET _sock);

    bool needSend_;  // サーバからデータを送信する必要があるか
    bool useFlag_;   // 使われているか
    Circle circle_;  // 円のデータ
    SOCKET sock_;    // ソケット
};
