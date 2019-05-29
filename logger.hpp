#pragma once

#include <fstream>

namespace Signature
{
class Logger
{
    public:
        Logger(const std::string& filename);
        ~Logger();
    private:
        int bazz;
};
    
} // namespace Signature


