#include <holo/log/hololog.h>
#include <chrono>
#include <iostream>
#include <thread>

using namespace holo;
using namespace log;

static constexpr int g_num = 100 * 10000;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    ConsoleConfigure console("console");
    console.SetAsync(true);

    HoloLogger::Add(console);

    std::cout << "start test:" << std::endl;

    std::chrono::milliseconds start_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    for (uint32_t i = 0; i < g_num; i++)
    {
        LOG(INFO) << "test log performance.  " << i;
    }

    std::chrono::milliseconds end_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    LOG(INFO) << "start:" << start_ms.count() << std::endl;
    LOG(INFO) << "end:" << end_ms.count() << std::endl;
    LOG(INFO) << "end - start:" << end_ms.count() - start_ms.count() << std::endl;

    std::cout << std::endl << "end test" << std::endl;

    return 0;
}