#include <assert.h>
#include <holo/log/hololog.h>
#include <iostream>

using namespace holo;
using namespace log;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::size_t all     = std::hash<LogLevel>{}(LogLevel::ALL);
    std::size_t trace   = std::hash<LogLevel>{}(LogLevel::TRACE);
    std::size_t debug   = std::hash<LogLevel>{}(LogLevel::DEBUG);
    std::size_t info    = std::hash<LogLevel>{}(LogLevel::INFO);
    std::size_t warning = std::hash<LogLevel>{}(LogLevel::WARNING);
    std::size_t error   = std::hash<LogLevel>{}(LogLevel::ERROR);
    std::size_t fatal   = std::hash<LogLevel>{}(LogLevel::FATAL);
    std::size_t off     = std::hash<LogLevel>{}(LogLevel::OFF);

    assert(all == 0);
    assert(trace == 0);
    assert(debug == 10000);
    assert(info == 20000);
    assert(warning == 30000);
    assert(error == 40000);
    assert(fatal == 50000);
    assert(off == 60000);

    std::cout << "all:" << all << std::endl;
    std::cout << "trace:" << trace << std::endl;
    std::cout << "debug:" << debug << std::endl;
    std::cout << "info:" << info << std::endl;
    std::cout << "warning:" << warning << std::endl;
    std::cout << "error:" << error << std::endl;
    std::cout << "fatal:" << fatal << std::endl;
    std::cout << "off:" << off << std::endl;

    return 0;
}
