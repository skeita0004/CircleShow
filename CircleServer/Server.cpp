#include "Server.h"
#include <cassert>

Server::Server()
{
	
}

Server::~Server()
{
}

void Server::JoinClient(const SOCKET _sock, const SOCKADDR_IN& _sockAddrIn)
{
    // 既にクライアントが登録されていないかチェック
    for (ClientData& clientData : clientsData_)
    {
        if (clientData.useFlag_ && clientData.sock_ == _sock)
            return;
    }

    for (ClientData& clientData : clientsData_)
    {
        // 使用中のデータはスキップ
        if (clientData.useFlag_)
            continue;

        // 空いているデータ使用する
        clientData.useFlag_ = true;
        clientData.sock_ = _sock;
        clientData.circle_ = Circle();
        
        return;
    }

    // 全て使用中だったから新たに追加
    clientsData_.push_back(ClientData{ true,Circle(),_sock });
}

void Server::LeaveClient(const SOCKET _sock, const SOCKADDR_IN& _sockAddrIn)
{
    for (ClientData& clientData : clientsData_)
    {
        if (clientData.sock_ == _sock)
        {
            clientData.useFlag_ = false;
            clientData.sock_ = INVALID_SOCKET;
            clientData.circle_ = Circle();
        }
    }
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
        clientsData_[i].circle_.Store(p);
		//memcpy(p, &clientsData_[i].circle_, sizeof(Circle));
	}
    
	memcpy(_pBuffer, &buff, _bufferSize);
}
