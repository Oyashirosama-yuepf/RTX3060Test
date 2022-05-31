#include <iostream>
#include <holo/log/hololog.h>

using namespace holo;
using namespace log;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    if (argc != 2)
    {
        std::cout << "usage:" << argv[0] << " log_file" << std::endl;
        return 0;
    }

    std::cout << "start test:" << std::endl;

    RollingFileConfigure rolling_file("roll_file", argv[1]);
    rolling_file.SetAsync(true);
    //rolling_file.SetLevel(LogLevel::WARN);
    
    HoloLogger::Add(rolling_file);

    int a=454, b=8995;
    float c=56.7;

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
