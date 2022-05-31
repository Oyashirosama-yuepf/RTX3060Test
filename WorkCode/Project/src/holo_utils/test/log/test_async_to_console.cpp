#include <holo/log/hololog.h>
#include <iostream>

using namespace holo;
using namespace log;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "start test:" << std::endl;

    ConsoleConfigure console("console");
    console.SetAsync(true);
    // console.SetLevel(LogLevel::WARN);

    HoloLogger::Add(console);

    int   a = 454, b = 8995;
    float c = 56.7;

    LOG(TRACE) << "skskdklkslklksd" << 8993 << "  " << 88888;

    LOG(DEBUG) << "a:" << a << "b:" << b << "c:" << c << std::endl;

    LOG(INFO) << std::hex << "a:" << a << "b:" << b << std::endl;

    LOG(WARNING) << std::hex << "a:" << a << "b:" << b << std::endl;

    LOG(ERROR) << std::hex << "a:" << a << "b:" << b << std::endl;

    LOG(FATAL) << std::hex << "a:" << a << "b:" << b << std::endl;

    std::cout << "end test:" << std::endl << std::endl;
    std::cout << "press any key to continue!" << std::endl;

    std::getchar();

    return 0;
}
