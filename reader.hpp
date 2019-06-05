#pragma once
#include <fstream>
#include <vector>
#include <queue>
#include <memory>
#include <mutex>
#include <condition_variable>


namespace Signature
{
    using Queue = std::queue<std::unique_ptr<std::string>>;
class Worker
{
    public:
        Worker(const std::string&  filename, const size_t&  chunk_size);
        ~Worker();
        
        void Read(Queue &sigqueue);
        void Log(Queue& sigquue);

        
    private:
        std::ifstream m_instream;
        std::vector<char> m_buffer;
        size_t m_slice_s;
        std::mutex m_sigmutex;
        std::condition_variable m_condVar;
        bool m_dataReady;
};

} // namespace Signature

