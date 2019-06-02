#include "logger.hpp"
#include <iostream>


Signature::Logger::Logger(const std::string& filename, const size_t block): file_sink(filename), block_size(block)
{
    std::cout << "Logger start" << std::endl;
}

Signature::Logger::~Logger()
{
    std::cout << "Logger terminate" << std::endl;
}
