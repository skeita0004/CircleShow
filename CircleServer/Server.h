#pragma once
#include <vector>
#include "ClientData.h"

class Server
{
public:
    Server();
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
    /// サーバの更新処理
    /// </summary>
    bool Update();

    /// <summary>
    /// クライアントのインデクスを取得する
    /// </summary>
    /// <returns>クライアントの接続情報</returns>
    const size_t GetIndex(const SOCKADDR_IN& _sockAddrIn);

    /// <summary>
    /// 送信処理
    /// </summary>
    /// <param name="_pBuffer">バッファのポインタ</param>
    /// <param name="_bufferSize">バッファサイズ</param>
    void Send(char* _pBuffer, const int _bufferSize);
    /// <summary>
    /// 受信処理
    /// </summary>
    /// <param name="_pBuffer">バッファのポインタ</param>
    /// <param name="_bufferSize">バッファサイズ</param>
    /// <param name="_clientIndex">クライアントのインデクス</param>
    void Receive(const char* _pBuffer, const int _bufferSize, const size_t _clientIndex);

private:
    std::vector<ClientData> clientsData_;  // クライアントのデータ
};
