#pragma once
#include <fstream>
#include <vector>
#include <queue>
#include <bits/unique_ptr.h>


namespace Signature
{
    using  std::queue<std::unique_ptr<std::string>>
class Reader 
{
    public:
        Reader(const std::string&  filename, const size_t&  chunk_size);
        ~Reader();
        
        void Run(std::queue<std::unique_ptr<std::string>>& sigqueue);

        
    private:
        std::ifstream instream_;
        std::vector<char> buffer_;
        size_t slice_s_;
};

    
} // namespace Signature

