#include "reader.hpp"
#include <cmath>
#include <iostream>
#include <memory>
#include <boost/crc.hpp>


Signature::Worker::Worker(const std::string &infile, const std::string& outfile, const size_t &chunk_size) :
         m_buffer(chunk_size, 0)
         , m_slice_s(chunk_size)
         , m_dataReady(false)
{
    try
    {
        m_instream.open(infile, std::ifstream::binary);
        m_ofstream.open(outfile, std::ofstream::binary|std::ofstream::trunc);
    }
    catch (std::ios_base::failure& e) {
        std::cerr << e.what() << '\n';
        throw;
    }
    catch(const std::exception& e)
    {
        std::cout << e.what() << std::endl;
        throw;
    }
}


void Signature::Worker::Read(Queue &sigqueue) {
    m_instream.seekg(0, m_instream.end);
    int file_len = m_instream.tellg();
    m_instream.seekg(0, m_instream.beg);

    std::cout << "File size: " << file_len << std::endl;

    while (!m_instream.eof()) {
        m_instream.read(m_buffer.data(), m_slice_s);

        std::unique_ptr<std::string> strPtr(new std::string(m_buffer.begin(), m_buffer.end()));
        std::fill(m_buffer.begin(), m_buffer.end(), 0);
        std::cout << "File read block" << std::endl;
        std::lock_guard<std::mutex> lck(m_sigmutex);
        sigqueue.push(std::move(strPtr));
        m_condVar.notify_one();
    }

    std::lock_guard<std::mutex> lck(m_sigmutex);
    std::cout << "END OF FILE!!" << std::endl;
    std::unique_ptr<std::string> strPtr(new std::string());
    sigqueue.push(std::move(strPtr));
}


void Signature::Worker::Log(Signature::Queue &sigquue) {

    while (true) {
        std::unique_lock<std::mutex> locker(m_sigmutex);
        m_condVar.wait(locker, [&] { return !sigquue.empty(); });
        std::cout << "start log" << std::endl;
        auto val = std::move(sigquue.front());
        if (val->empty()) return;
        sigquue.pop();
        locker.unlock();
        boost::crc_32_type result;
        result.process_bytes(val->c_str(), val->length());
        std::cout<< std::hex << std::uppercase << result.checksum() << std::endl;
        m_ofstream << std::hex << std::uppercase << result.checksum() << std::endl;
    }
}

Signature::Worker::~Worker() {
    std::cout << "the end is near" << std::endl;
    m_instream.close();
    m_ofstream.close();
}
