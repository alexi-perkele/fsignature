#include "reader.hpp"
#include <iostream>


Signature::Reader::Reader(const std::string& filename)
{
    std::cout << "will read u all" << std::endl;
}

Signature::Reader::~Reader()
{
    std::cout << "the end is near" << std::endl;
}
