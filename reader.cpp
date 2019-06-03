#include "reader.hpp"
#include <cmath>
#include <iostream>
#include <memory>


Signature::Reader::Reader(const std::string &filename, const size_t &chunk_size) :
        instream_(filename, std::ifstream::binary), buffer_(chunk_size, 0), slice_s_(chunk_size) {
    std::cout << "will read u all" << std::endl;
    //  buffer_(slice_s_, 0);
    if (instream_) {
        std::cout << "File opened" << std::endl;
    }

}


void Signature::Reader::Run(std::queue<std::unique_ptr<std::string>> &sigqueue) {
    instream_.seekg(0, instream_.end);
    int file_len = instream_.tellg();
    instream_.seekg(0, instream_.beg);

    std::cout << "File size: " << file_len << std::endl;

    instream_.is_open() ? std::cout << "OPEN" << std::endl : std::cout << "NOT OPEN" << std::endl;
    while (!instream_.eof()) {
        instream_.read(buffer_.data(), slice_s_);
        std::unique_ptr<std::string> strPtr(new std::string(buffer_.begin(), buffer_.end()));

        std::cout << "File read done " << *strPtr << std::endl;
        sigqueue.push(std::move(strPtr));
        std::fill(buffer_.begin(), buffer_.end(), 0);
    }
}


Signature::Reader::~Reader() {
    std::cout << "the end is near" << std::endl;
    instream_.close();
}
