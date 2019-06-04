#pragma once
#include <fstream>
#include <vector>
#include <queue>
#include <memory>
#include <mutex>


namespace Signature
{
    using Queue = std::queue<std::unique_ptr<std::string>>;
class Reader 
{
    public:
        Reader(const std::string&  filename, const size_t&  chunk_size);
        ~Reader();
        
        void Run(Queue& sigqueue);

        
    private:
        std::ifstream instream_;
        std::vector<char> buffer_;
        size_t slice_s_;
        std::mutex sigmutex;
};

    
} // namespace Signature

