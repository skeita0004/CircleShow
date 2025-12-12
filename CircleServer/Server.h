#pragma once
#include <vector>
#include "ClientData.h"

class Server
{
public:
	Server();
	~Server();

private:
	std::vector<ClientData> clientsData_;  // クライアントのデータ
};
