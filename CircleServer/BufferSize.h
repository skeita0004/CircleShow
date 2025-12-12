#pragma once
#include "StubCircle.h"
#include <cstdint>

/// <summary>
/// <para>バッファサイズ</para>
/// <para>円構造体 × 最大クライアント数 + 人数用1byte</para>
/// </summary>
static const size_t BUFFER_SIZE{ sizeof(Circle) * UINT8_MAX + sizeof(uint8_t) };
