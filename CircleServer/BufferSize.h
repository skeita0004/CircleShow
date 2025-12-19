#pragma once
#include "Circle.h"
#include <cstdint>

/// <summary>
/// <para>バッファサイズ</para>
/// <para>円構造体 × 最大クライアント数 + 人数用1byte</para>
/// </summary>
static const size_t SEND_BUFFER_SIZE{ sizeof(Circle) * UINT8_MAX + sizeof(uint8_t) };
static const size_t RECEIVE_BUFFER_SIZE{ sizeof(Circle) };
