#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <boost/uuid/detail/md5.hpp>
#include <boost/algorithm/hex.hpp>
#include <iostream>
#include <memory>
#include <queue>
#include <thread>

#include "reader.hpp"

namespace po = boost::program_options;

int main(int argc, char **argv) {
    
    po::options_description desc(
        "\n File signature computation.\n Process file by chunks and get crc32 of each"
    );
    desc.add_options()
        ("help", "help and description")
        ("file", po::value<std::string>()->default_value("sig_test"), "file to process")
        ("size", po::value<size_t>()->default_value(1024), "block size bytes")
        ("output", po::value<std::string>()->default_value("sig.out"), "output file");
        
    po::variables_map var_map;
    
    try {
        po::store(po::parse_command_line(argc,argv, desc), var_map);
        po::notify(var_map);
    }
    catch (po::error const& e) {
        std::cerr << e.what() << '\n';
        exit( EXIT_FAILURE );
    }
    
    
    if (var_map.count("help")) {
        std::cout << desc << "\n";
    return 1;
    }
    
    
    std::cout << "file:  " << var_map["file"].as<std::string>() << ".\n";
    std::cout << "chunk size:  " << var_map["size"].as<size_t>() << " bytes" << ".\n";
    std::cout << "output to:  " << var_map["output"].as<std::string>() << ".\n";
    
    auto input_file = var_map["file"].as<std::string>();
    auto block_size = var_map["size"].as<size_t>();
    auto output_file = var_map["output"].as<std::string>();

    Signature::Queue sigqueue;
    std::vector<std::thread> threads;

    try {
        std::unique_ptr<Signature::Worker> rdr(new Signature::Worker(input_file, output_file, block_size));
        threads.push_back(std::thread(&Signature::Worker::Read, rdr.get(), std::ref(sigqueue) ));
        threads.push_back(std::thread(&Signature::Worker::Log, rdr.get(), std::ref(sigqueue) ));

        std::for_each(threads.begin(), threads.end(),
                      std::mem_fn(&std::thread::join));
    }

    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
        exit(EXIT_FAILURE);
    }

    return 0;
}
