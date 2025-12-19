#include <iostream>
#include <chrono>
#include <thread>
#include "WSAIncluding.h"
#include "Server.h"
#include "BufferSize.h"
using std::cout;
using std::endl;

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
    int result{};
    result = inet_pton(AF_INET, "127.0.0.1", &sockAddr.sin_addr.s_addr);

    Server server = { sockAddr };

    while (true)
    {
        server.Update();
        //std::chrono::
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
    }

    return 0;
}
