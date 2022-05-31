#include <holo/os/shared_memory_block.h>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main()
{
    holo::os::SharedMemoryBlockWriter writer("test_block");
    int                               capacity   = 1024;
    int                               count      = 50;
    int                               index      = 0;
    int                               write_size = 0;
    writer.Init(capacity, count);

    while (true)
    {
        for (int i = 0; i < count; ++i)
        {
            std::string msg = "this  is write msg, msg id=" + std::to_string(index++);
            write_size      = writer.Write((holo::uint8_t*)msg.c_str(), msg.length(), i);
            (void)write_size;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }
        // std::cout << "next loop" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
