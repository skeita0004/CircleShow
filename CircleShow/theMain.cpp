#include <DxLib.h>
#include <WinSock2.h>
#include <WS2tcpip.h>

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

int APIENTRY WinMain(_In_     HINSTANCE hInstance,
					 _In_opt_ HINSTANCE hPrevInstance,
					 _In_     LPSTR     lpCmdLine,
					 _In_     INT       nCmdShow)
{

}
