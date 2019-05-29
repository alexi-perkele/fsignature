#include <fstream>

#pragma once

namespace Signature
{
class Reader 
{
    public:
        Reader(const std::string& filename);
        ~Reader();
        int blah;
    private:
        int foo;
};

    
} // namespace Signature

