/*
g++ program-options.cpp -o bin/program-options -lboost_program_options
*/

#include <boost/program_options.hpp>
#include <iostream>
#include <iterator>

namespace po = boost::program_options;
using namespace std;

int main(int argc, char** argv) {
    try {
        po::options_description desc("Allowed options");
        desc.add_options()
            ("help", "display help message")
            ("compression", po::value<double>(), "set compression level")
        ;

        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);

        if(vm.count("help")) {
            cout << desc << "\n";
            return EXIT_SUCCESS;
        }

        if(vm.count("compression")) {
            cout << "Compression level was to : " << vm["compression"].as<double>() << "\n";
        } else {
            cout << "Compression level was not set \n";
        }

    } catch(exception e) {
        cerr << "error : " << e.what() << "\n";
        return EXIT_FAILURE;
    } catch(...) {
        cerr << "Exception of unknown type!\n";
    }

    return EXIT_SUCCESS;
}