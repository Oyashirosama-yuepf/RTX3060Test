#include <iostream>
#include <holo/log/hololog.h>

using namespace holo;
using namespace log;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::cout << "start test:" << std::endl;

    ConsoleConfigure console("console");
    //console.SetLevel(LogLevel::ERROR);


    for (int i=0; i<100; i++)
    {
        LOG_EVERY_N(ERROR, 10) << "test LOG_EVERY_N :" << i << std::endl;
    }

    std::cout << "end test:" << std::endl;

    return 0;
}
