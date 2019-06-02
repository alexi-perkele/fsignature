#pragma once

#include <fstream>

namespace Signature
{
class Logger
{
    public:
        Logger(const std::string& filename, const size_t block);
        ~Logger();
    private:
        const std::string file_sink;
        const size_t block_size;
        int bazz;
};
    
} // namespace Signature


