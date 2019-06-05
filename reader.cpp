#include "reader.hpp"
#include <cmath>
#include <iostream>
#include <memory>


Signature::Worker::Worker(const std::string &filename, const size_t &chunk_size) :
        m_instream(filename, std::ifstream::binary)
        , m_buffer(chunk_size, 0), m_slice_s(chunk_size)
        , m_dataReady(false)
        {
    std::cout << "will read u all" << std::endl;//  m_buffer(m_slice_s, 0);
    if (m_instream) {
        std::cout << "File opened" << std::endl;
    }

}


void Signature::Worker::Read(Queue &sigqueue) {
    m_instream.seekg(0, m_instream.end);
    int file_len = m_instream.tellg();
    m_instream.seekg(0, m_instream.beg);

    std::cout << "File size: " << file_len << std::endl;

    m_instream.is_open() ? std::cout << "OPEN" << std::endl : std::cout << "NOT OPEN" << std::endl;

  //  std::unique_lock<std::mutex> locker(m_sigmutex, std::defer_lock);

    while (!m_instream.eof()) {
        m_instream.read(m_buffer.data(), m_slice_s);

            std::unique_ptr<std::string> strPtr(new std::string(m_buffer.begin(), m_buffer.end()));

            std::cout << "File read block" << std::endl;
            std::lock_guard<std::mutex> lck(m_sigmutex);
            sigqueue.push(std::move(strPtr));
            m_condVar.notify_one();
           // locker.unlock();
            std::fill(m_buffer.begin(), m_buffer.end(), 0);
        }
      //  locker.lock();
        std::cout << "END OF FILE!!" << std::endl;
        std::unique_ptr<std::string> strPtr(new std::string());
        std::lock_guard<std::mutex> lck(m_sigmutex);
        sigqueue.push(std::move(strPtr));

    }


void Signature::Worker::Log(Signature::Queue &sigquue) {


    while(true){
        std::unique_lock<std::mutex> locker(m_sigmutex);
        m_condVar.wait(locker, [&]{return !sigquue.empty();});
        std::cout << "start log" << std::endl;
        auto val = std::move(sigquue.front());
        sigquue.pop();
        locker.unlock();
        if (val->empty()) return;
    }
}

Signature::Worker::~Worker() {
    std::cout << "the end is near" << std::endl;
    m_instream.close();
}
