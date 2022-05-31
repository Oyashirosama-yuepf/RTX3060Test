#include <iostream>
#include <holo/log/hololog.h>

using namespace holo::log;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    int   a = 6731;
    int   b = 89298;
    float c = 56.7;

    LOG(TRACE) << "skskdklkslklksd" << 8993 << "  " << 88888; 

    LOG(DEBUG) << "a:" << a << "b:" << b << "c:" << c << std::endl;

    LOG(INFO) << std::hex << "a:" << a << "b:" << b << std::endl;

    LOG(WARNING) << std::hex << "a:" << a << "b:" << b << std::endl;

    LOG(ERROR) << std::hex << "a:" << a << "b:" << b << std::endl;

    LOG(FATAL) << std::hex << "a:" << a << "b:" << b << std::endl;

    return 0;
}
