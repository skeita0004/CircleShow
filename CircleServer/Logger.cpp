#include "Logger.h"
#include <iostream>

Logger::Logger()
{
}

Logger::~Logger()
{
}

void Logger::WriteLine(const std::string_view _message)
{
    std::cout << _message << std::endl;
}
