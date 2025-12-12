#include "Server.h"
#include <cassert>

Server::Server()
{
	
}

Server::~Server()
{
}

void Server::Receive(const char* _pBuffer, const int _bufferSize, const size_t _clientIndex)
{
	assert(0 <= _clientIndex && _clientIndex <= clientsData_.size()
		&& "範囲外アクセスが発生するよ！");

	ClientData& clientData{ clientsData_.at(_clientIndex) };

	assert(clientData.useFlag_ && "使われていないクライアントからデータを受け取った");
	assert(sizeof(Circle) <= _bufferSize && "書き込むバッファのサイズが足りないよ！");

	clientData.circle_.Load(_pBuffer);
	// MEMO: 安全性向上のためにサイズも送るようにしたい
	// clientData.circle_.Load(_pBuffer, _bufferSize);
}

void Server::Send(char* _pBuffer, const int _bufferSize)
{
	size_t CLIENT_COUNT = clientsData_.size();
	char buff[sizeof(Circle) * 256 + sizeof(UINT8)];

	buff[0] = CLIENT_COUNT;
	for (size_t i = 0; i < CLIENT_COUNT; i++)
	{
		char* p = &buff[sizeof(Circle) * i + sizeof(UINT8)];
		memcpy(p, &clientsData_[i].circle_, sizeof(Circle));
	}
    
	memcpy(_pBuffer, &buff, _bufferSize);
}
