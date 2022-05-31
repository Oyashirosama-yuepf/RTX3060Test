#include <holo/thread/thread_pool.h>

template std::future<uint32_t> holo::thread::ThreadPool::AddTask([]() -> uint32_t {
    static constexpr uint32_t ret{2U};
    return ret;
});
