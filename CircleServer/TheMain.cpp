#include <iostream>
#include <chrono>
#include <thread>
#include "WSAIncluding.h"
#include "Server.h"
#include "BufferSize.h"
#include <format>
#include <cstdint>

using std::cout;
using std::endl;

namespace
{
    const uint16_t SERVER_PORT{ 8888 };
    //const char IP_ADDRESS[]{ "127.0.0.1" };
    const char IP_ADDRESS[]{ "192.168.42.90" };
}

int main()
{
    std::cout << SEND_BUFFER_SIZE << std::endl;

    std::cout << "サーバー予定" "やってこー" << std::endl;

    WSAData wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0)
    {
        cout << "Error : WSAStartup" << endl;
        return 1;
    }
    cout << "Success : WSAStartup" << endl;

    // TCPリスンソケットの作成
    SOCKET listenSock = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSock == INVALID_SOCKET)
    {
        int errorCode = WSAGetLastError();
        cout << "Error :socket" << endl;
        return 1;
    }
    cout << "Success :socket" << endl;

    SOCKADDR_IN sockAddr{};
    memset(&sockAddr, 0, sizeof(sockAddr));
    sockAddr.sin_family = AF_INET;
    sockAddr.sin_port = htons(SERVER_PORT);
    sockAddr.sin_addr.s_addr = htonl(INADDR_ANY);

    int result{};
    result = inet_pton(AF_INET, IP_ADDRESS, &sockAddr.sin_addr.s_addr);
  
    Server server = { sockAddr };
    server.Initialize();
    while (true)
    {
        server.Update();
        //std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    return 0;
}
