#include <iostream>
#include "WSAIncluding.h"
#include "Server.h"


int main()
{
	char buff[sizeof(Circle) * 256 + sizeof(UINT8)];
	Server server;

	server.Send(buff, sizeof(buff));
	std::cout << "サーバー予定" "やってこー" << std::endl;
	int count = static_cast<int>(buff[0]);
	std::cout << "クライアント数" << count << std::endl;
	std::cout << std::endl;

	size_t size = sizeof(Circle);
	for (int i = 0; i < count; i++)
	{
		char* p = &buff[size * i + sizeof(UINT8)];
		Circle pCir;
		memcpy(&pCir, p, sizeof(Circle));
		std::cout << pCir.i << std::endl;
	}
	return 0;
}
