#include <iostream>
#include <chrono>
#include <thread>
#include "WSAIncluding.h"
#include "Server.h"
#include "BufferSize.h"
#include <format>
using std::cout;
using std::endl;

unsigned short SERVER_PORT = 8888;
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
    result = inet_pton(AF_INET, "192.168.42.144", &sockAddr.sin_addr.s_addr);
  
    Server server = { sockAddr };
    server.Initialize();
    while (true)
    {
        server.Update();
        //std::chrono::
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    return 0;
}
