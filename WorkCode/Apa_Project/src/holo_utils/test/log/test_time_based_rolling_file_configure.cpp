#include <iostream>
#include <thread>
#include <chrono>
#include <stdlib.h>
#include <signal.h>
#include <holo/log/hololog.h>

using namespace holo;
using namespace log;

void signalHandler(int sig)
{
    HoloLogger::Shutdown();
    signal(sig, SIG_DFL);
    raise(sig);
}

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    signal(SIGSEGV, signalHandler);
    signal(SIGINT, signalHandler);

    if (argc != 2)
    {
        std::cout << "usage:" << argv[0] << " log_file" << std::endl;
        return 0;
    }

    std::cout << "start test:" << std::endl;

    TimeBasedRollingFileConfigure rolling_file("roll_file", "time_based");
    //rolling_file.SetFilenamePattern("time_based.%d{yyyy-MM-dd-HH-mm-ss}.log");
    rolling_file.SetFilenamePattern("time_based.%d-%H-%M-%S.%q");
    //rolling_file.SetLevel(LogLevel::ERROR);
    
    HoloLogger::Add(rolling_file);

    int a=454, b=8995;
    float c=56.7;

    while(true)
    {
        LOG(TRACE) << "skskdklkslklksd" << 8993 << "  " << 88888; 

        LOG(DEBUG) << "a:" << a << "b:" << b << "c:" << c << std::endl;

        LOG(INFO) << std::hex << "a:" << a << "b:" << b << std::endl;

        LOG(WARNING) << std::hex << "a:" << a << "b:" << b << std::endl;

        LOG(ERROR) << std::hex << "a:" << a << "b:" << b << std::endl;

        LOG(FATAL) << std::hex << "a:" << a << "b:" << b << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    std::cout << "end test log:" << std::endl;

    return 0;
}
