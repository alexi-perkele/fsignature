#include "logger.hpp"
#include <iostream>


Signature::Logger::Logger(const std::string& filename)
{
    std::cout << "Logger start" << std::endl;
}

Signature::Logger::~Logger()
{
    std::cout << "Logger terminate" << std::endl;
}
