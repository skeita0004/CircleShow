#include <iostream>
#include "WSAIncluding.h"
#include "Server.h"
#include "BufferSize.h"
using std::cout;
using std::endl;

int main()
{
    std::cout << BUFFER_SIZE << std::endl;

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

    Server server = {};

    while (true)
    {
        server.Update();
    }

    return 0;
}
