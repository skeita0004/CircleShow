#pragma once
#include <string>
#include <string_view>
#include <vector>

/// <summary>
/// ロガークラス
/// </summary>
class Logger
{
public:
    Logger();
    ~Logger();

    /// <summary>
    /// ログを1行書き込む
    /// </summary>
    /// <param name="_message">メッセージ内容</param>
    void WriteLine(const std::string_view _message);

private:
    std::vector<std::string> messages_;  // ログのメッセージ貯め
};
