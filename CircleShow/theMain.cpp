#include <DxLib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>
#include <format>
#include <string>

#pragma comment(lib, "ws2_32.lib")

struct Circle
{
	void Load(char* p);//ネットワークから受信したデータを変換して受け取る
	void Store(char* p);//ネットワークに送信するデータを変換して送る
	int color;
	int x;
	int y;
	int r;
};

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

    // while書く

    closesocket(sock);
    WSACleanup();
    return 0;
}
