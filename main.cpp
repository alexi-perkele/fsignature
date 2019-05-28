#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>
#include <iostream>

namespace po = boost::program_options;

int main(int argc, char **argv) {
    
    po::options_description desc(
        "\n File signature computation.\n Process file by chunks and get md5 of each"
    );
    desc.add_options()
        ("help", "help and description")
        ("file", po::value<std::string>()->default_value("sig_test"), "file to process")
        ("size", po::value<unsigned int>()->default_value(1024), "chunk size Kb");
        
    po::variables_map var_map;
    //po::store(po::command_line_parser(argc, argv).options(desc), var_map);
    
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
    std::cout << "chunk size:  " << var_map["size"].as<unsigned int>() << ".\n";

    
    std::cout << "Hello, world!" << std::endl;
    return 0;
}
