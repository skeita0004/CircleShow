#include "Server.h"
#include <cassert>
#include "BufferSize.h"

Server::Server(const SOCKADDR_IN& _localSockAddr) :
    localSockAddrIn_{ _localSockAddr },
    listenerSock_{ INVALID_SOCKET }
{
	
}

Server::~Server()
{
    closesocket(listenerSock_);
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
        // ソケットが一致するクライアントのデータを探す
        if (clientData.sock_ == _sock)
        {
            // 未使用状態にする
            clientData.useFlag_ = false;
            // ソケット、サークルのデータをリセット
            clientData.sock_ = INVALID_SOCKET;
            clientData.circle_ = Circle();
        }
    }
}

void Server::ReceiveAll()
{
    for (auto itr = clientsData_.begin();
        itr != clientsData_.end();
        itr++)
    {
        const size_t CLIENT_INDEX{ itr - clientsData_.begin() };

        int ret{};

        char buff[RECEIVE_BUFFER_SIZE]{};
        ret = recv(itr->sock_, buff, RECEIVE_BUFFER_SIZE, 0);

        Receive(buff, RECEIVE_BUFFER_SIZE, CLIENT_INDEX);
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

    while (true)
    {
        SOCKADDR_IN remoteSockAddrIn = {};
        int length = sizeof(remoteSockAddrIn);
        SOCKET sock{ accept(listenerSock_, reinterpret_cast<SOCKADDR*>(&remoteSockAddrIn), &length) };

        if (sock == INVALID_SOCKET)
        {  // 了承したソケットが無効なら接続者なし
            break;
        }

        // 参加処理する
        JoinClient(sock, remoteSockAddrIn);

        // まだいるかもしれないからループループする
    }

    ReceiveAll();

    SendAll();
}

void Server::SendAll()
{
	size_t CLIENT_COUNT = clientsData_.size();
	char buff[SEND_BUFFER_SIZE]{};

	buff[0] = CLIENT_COUNT;
	for (size_t i = 0; i < CLIENT_COUNT; i++)
	{
		char* p = &buff[sizeof(Circle) * i + sizeof(UINT8)];
        clientsData_[i].circle_.Store(p);
		//memcpy(p, &clientsData_[i].circle_, sizeof(Circle));
	}
    int writeLength{ sizeof(Circle) * CLIENT_COUNT + sizeof(UINT8) };
    
    // 全クライアントに送信する
    for (ClientData& client : clientsData_)
    {
        if (client.sock_ == INVALID_SOCKET)
        {  // 無効ソケットなら使ってない判定
            client.useFlag_ = false;
        }
        if (client.useFlag_ == false)
        {  // 使っていないなら早期回帰
            continue;
        }

        // 送信！
        send(client.sock_, buff, writeLength, 0);
    }
}
