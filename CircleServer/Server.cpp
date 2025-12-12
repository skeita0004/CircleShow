#include "Server.h"
#include <cassert>

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
