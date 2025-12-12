#include "Server.h"


Server::Server()
{
	
}

Server::~Server()
{
}

void Server::Receive(const char* _pBuffer, const int _bufferSize)
{
}

void Server::Send(char* _pBuffer, const int _bufferSize)
{
	size_t CLIENT_COUNT = clientsData_.size();
	char buff[sizeof(Circle) * 256 + sizeof(UINT8)];

	buff[0] = CLIENT_COUNT;
	for (size_t i = 0; i < CLIENT_COUNT; i++)
	{
		char* p = &buff[sizeof(Circle) * i + sizeof(UINT8)];
        clientsData_[i].circle_.Store(p);
		//memcpy(p, &clientsData_[i].circle_, sizeof(Circle));
	}
    
	memcpy(_pBuffer, &buff, _bufferSize);
}
