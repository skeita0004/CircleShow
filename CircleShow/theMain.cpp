#include <WinSock2.h>
#include <WS2tcpip.h>
#pragma comment(lib,"ws2_32.lib")

struct Circle
{
	void Load(char* p);
	void Store(char* p);
	int color;
	int x;
	int y;
	int r;
};