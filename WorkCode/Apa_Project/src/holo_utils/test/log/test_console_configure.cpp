#include <holo/log/hololog.h>
#include <iostream>

using namespace holo;
using namespace log;

std::string appendPattern()
{
    return "[A72]";
}
int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "start test:" << std::endl;

    ConsoleConfigure console("console1");
    console.SetLevel(LogLevel::OFF);

    ConsoleConfigure console2("console2");
    console2.SetColor(LogLevel::TRACE, Color::LIGHT_RED);
    console2.SetColor(LogLevel::DEBUG, Color::LIGHT_PINK);
    console2.SetColor(LogLevel::INFO, Color::LIGHT_GREEN);
    console2.SetColor(LogLevel::WARNING, Color::LIGHT_BLUE);
    console2.SetColor(LogLevel::ERROR, Color::LIGHT_YELLOW);
    console2.SetColor(LogLevel::FATAL, Color::LIGHT_CYAN);
    //    console2.SetLevel(LogLevel::ERROR);
    //   console2.SetMaxLevel(LogLevel::ERROR);
    // console2.SetPatternFunction(appendPattern);
    // console2.SetPattern("%m%n");

    HoloLogger::Add(console);
    HoloLogger::Add(console2);

    HoloLogger::SetLogLevel(LogLevel::ALL);
    // HoloLogger::SetMaxLogLevel(LogLevel::INFO);
    //  HoloLogger::SetMaxLogLevel("console2", LogLevel::FATAL);
    HoloLogger::SetMaxLogLevel("console1", LogLevel::ALL);
    int   a = 454, b = 8995;
    float c = 56.7;

    LOG(TRACE) << "skskdklkslklksd" << 8993 << "  " << 88888;

    LOG(DEBUG) << "a:" << a << "b:" << b << "c:" << c << std::endl;

    LOG(INFO) << std::hex << "a:" << a << "b:" << b << std::endl;

    LOG(WARNING) << std::hex << "a:" << a << "b:" << b << std::endl;

    LOG(ERROR) << std::hex << "a:" << a << "b:" << b << std::endl;

    LOG(FATAL) << std::hex << "a:" << a << "b:" << b << std::endl;

    std::cout << "end test:" << std::endl;

    return 0;
}
