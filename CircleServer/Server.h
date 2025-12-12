#pragma once
#include <vector>
#include "ClientData.h"

class Server
{
public:
	Server();
	~Server();

	void Receive(const char* _pBuffer, const int _bufferSize);
	void Send(char* _pBuffer, const int _bufferSize);
private:
	std::vector<ClientData> clientsData_;  // クライアントのデータ
};
