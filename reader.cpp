#include "reader.hpp"
#include <iostream>



Signature::Reader::Reader(const std::string& filename, const size_t& chunk_size) : instream_(filename, std::ifstream::binary), buffer_(chunk_size,0), slice_s_(chunk_size)
{
    std::cout << "will read u all" << std::endl;
  //  buffer_(slice_s_, 0);
    if (instream_)
    {
        std::cout << "File opened" << std::endl;
    }
    
}


void Signature::Reader::Run()
{
    //instream_.seekg(0, instream_.end);
    int file_len =  instream_.tellg();
    instream_.seekg(0, instream_.beg);
    
    std::cout << "File size: " << file_len << std::endl;
    
    int iter = file_len/slice_s_;
    std::cout << "total chunks: " << iter << std::endl;
    instream_.is_open() ? std::cout << "OPEN" << std::endl : std::cout<< "NOT OPEN" << std::endl;
    instream_.read(buffer_.data(),  slice_s_);
    std::cout << "File read done" << std::endl;
    
    for(const auto i : buffer_)
    {
        std::cout << i;
    }
    std::cout << std::endl;

}


Signature::Reader::~Reader()
{
    std::cout << "the end is near" << std::endl;
    instream_.close();
}
