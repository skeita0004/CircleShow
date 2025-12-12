#pragma once
#include <vector>
#include "ClientData.h"

class Server
{
public:
    Server();
    ~Server();

	void Send(char* _pBuffer, const int _bufferSize);
    void Receive(const char* _pBuffer, const int _bufferSize, const size_t _clientIndex);

private:
    std::vector<ClientData> clientsData_;  // クライアントのデータ
};
