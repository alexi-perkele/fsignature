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
    m_instream.open(infile, std::ifstream::binary);
    if (!m_instream.is_open()) throw std::runtime_error("can't open input file");
    m_ofstream.open(outfile, std::ofstream::binary|std::ofstream::trunc);
    if (!m_ofstream.is_open()) throw std::runtime_error("can't open output file");

    m_instream.seekg(0, m_instream.end);
    size_t file_len = m_instream.tellg();
    m_instream.seekg(0, m_instream.beg);
    std::cout << "File size: " << file_len << std::endl;
    if(file_len < m_slice_s) throw std::runtime_error("bad file size.");
    m_instream.seekg(0, m_instream.beg);
}


void Signature::Worker::Read(Queue &sigqueue) {
    std::cout << "file processing start" << std::endl;
    while (!m_instream.eof()) {
        m_instream.read(m_buffer.data(), m_slice_s);

        std::unique_ptr<std::string> strPtr(new std::string(m_buffer.begin(), m_buffer.end()));
        std::fill(m_buffer.begin(), m_buffer.end(), 0);
        std::lock_guard<std::mutex> lck(m_sigmutex);
        sigqueue.push(std::move(strPtr));
        m_condVar.notify_one();
    }

    std::lock_guard<std::mutex> lck(m_sigmutex);
    std::cout << "file read done" << std::endl;
    std::unique_ptr<std::string> strPtr(new std::string());
    sigqueue.push(std::move(strPtr));
    m_condVar.notify_one();
}


void Signature::Worker::Log(Signature::Queue &sigquue) {
    std::cout << "computing crc32 hash" << std::endl;
    while (true) {
        std::unique_lock<std::mutex> locker(m_sigmutex);
        m_condVar.wait(locker, [&] { return !sigquue.empty(); });
        auto val = std::move(sigquue.front());
        if (val->empty()) return;
        sigquue.pop();
        locker.unlock();

        boost::crc_32_type result;
        result.process_bytes(val->c_str(), val->length());
        m_ofstream << std::hex << std::uppercase << result.checksum() << std::endl;
        if(m_ofstream.fail()) throw std::runtime_error("file write error.");
    }
}

Signature::Worker::~Worker() {
    if(m_instream.is_open()) m_instream.close();
    if(m_ofstream.is_open()) m_ofstream.close();
}
