#include "ClientData.h"
#include <cassert>


ClientData::ClientData() :
    ClientData{ false, {}, INVALID_SOCKET }
{
}

ClientData::ClientData(const bool _useFlag, const Circle& _circle, const SOCKET _sock) :
    useFlag_{ _useFlag },
    circle_{ _circle },
    sock_{ _sock },
    needSend_{ true }
{
}
