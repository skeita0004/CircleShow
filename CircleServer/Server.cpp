#include "Server.h"
#include <cassert>

namespace
{
    static const size_t SERVER_SEND_BUFFER_SIZE{ sizeof(Circle) * 256 + sizeof(UINT8) };
}

Server::Server(const SOCKADDR_IN& _localSockAddr) :
    localSockAddrIn_{ _localSockAddr }
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

void Server::Initialize()
{
    int ret = 0;

    // 受信用ソケットの作成
    listenerSock_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (listenerSock_ == INVALID_SOCKET)
    {
        throw std::exception{ "無効なソケット" };
    }

    ret = bind(listenerSock_, reinterpret_cast<SOCKADDR*>(&localSockAddrIn_), sizeof(localSockAddrIn_));
    if (ret == SOCKET_ERROR)
    {
        throw std::exception{ "IPアドレスのバインドに失敗" };
    }

    ret = listen(listenerSock_, UINT8_MAX);
    if (ret == SOCKET_ERROR)
    {
        throw std::exception{ "リスンソケットの受付開始に失敗" };
    }
}

void Server::Update()
{
    int ret = 0;

    SOCKADDR_IN remoteSockAddrIn = {};
    int length = sizeof(remoteSockAddrIn);
    ret = accept(listenerSock_, reinterpret_cast<SOCKADDR*>(&remoteSockAddrIn), &length);


}

void Server::Send(char* _pBuffer, const int _bufferSize)
{
    assert(_bufferSize <= SERVER_SEND_BUFFER_SIZE && "バッファのサイズが足りない");

	size_t CLIENT_COUNT = clientsData_.size();
	char buff[SERVER_SEND_BUFFER_SIZE]{};

	buff[0] = CLIENT_COUNT;
	for (size_t i = 0; i < CLIENT_COUNT; i++)
	{
		char* p = &buff[sizeof(Circle) * i + sizeof(UINT8)];
        clientsData_[i].circle_.Store(p);
		//memcpy(p, &clientsData_[i].circle_, sizeof(Circle));
	}
    
	memcpy(_pBuffer, &buff, _bufferSize);
}
