#pragma once
#include <vector>
#include "ClientData.h"

class Server
{
public:
    Server(const SOCKADDR_IN& _localSockAddr);
    ~Server();

    /// <summary>
    /// クライアントが接続時の処理
    /// </summary>
    /// <param name="_sock">クライアントとのソケット</param>
    /// <param name="_sockAddrIn">クライアントの接続情報</param>
    void JoinClient(const SOCKET _sock, const SOCKADDR_IN& _sockAddrIn);

    /// <summary>
    /// クライアントが切断時の処理
    /// </summary>
    /// <param name="_sock">クライアントとのソケット</param>
    /// <param name="_sockAddrIn">クライアントの接続情報</param>
    void LeaveClient(const SOCKET _sock, const SOCKADDR_IN& _sockAddrIn);

    /// <summary>
    /// 初期化処理
    /// </summary>
    void Initialize();

    /// <summary>
    /// サーバの更新処理
    /// </summary>
    void Update();

    /// <summary>
    /// クライアントのインデクスを取得する
    /// </summary>
    /// <returns>クライアントの接続情報</returns>
    const size_t GetIndex(const SOCKADDR_IN& _sockAddrIn);

    /// <summary>
    /// 全クライアントに送信処理
    /// </summary>
    void SendAll();
    /// <summary>
    /// 受信処理
    /// </summary>
    /// <param name="_pBuffer">バッファのポインタ</param>
    /// <param name="_bufferSize">バッファサイズ</param>
    /// <param name="_clientIndex">クライアントのインデクス</param>
    void Receive(const char* _pBuffer, const int _bufferSize, const size_t _clientIndex);

private:
    SOCKADDR_IN localSockAddrIn_;  // サーバ自身のインターネットのソケットアドレス
    SOCKET listenerSock_;  // 受付用ソケット
    std::vector<ClientData> clientsData_;  // クライアントのデータ
};
