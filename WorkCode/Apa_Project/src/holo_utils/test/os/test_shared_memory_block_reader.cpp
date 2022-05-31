#include <holo/os/shared_memory_block.h>
#include <chrono>
#include <iostream>
#include <string>
#include <thread>

int main()
{
    holo::os::SharedMemoryBlockReader reader("test_block");
    int                               count = 0;
    char                              msg[1024]{0};
    int                               read_size = 0;

    while (true)
    {
        if (0 == count)
        {
            std::cout << "wait for share memory init by writer" << std::endl;
            count = reader.GetBlockCount();
            if (0 == count)
            {
                std::this_thread::sleep_for(std::chrono::milliseconds(1));
                continue;
            }
        }

        for (int i = 0; i < count; ++i)
        {
            read_size = reader.Read((holo::uint8_t*)msg, 1024, i);
            std::cout << "read_size: " << read_size << " index:" << i << std::endl;
            msg[read_size] = '\0';
            std::cout << "msg: " << msg << std::endl;
            std::cout << "data version: " << reader.GetBlockDataVersion(i) << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
        }

        std::cout << "next loop" << std::endl;
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }
}
