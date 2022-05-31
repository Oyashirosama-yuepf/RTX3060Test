#include <holo/core/exception.h>
#include <holo/os/utils.h>

#include <sys/types.h>
#include <unistd.h>
#include <thread>

#if defined(__linux__)
#include <sys/syscall.h>
#elif defined(__QNX__) || defined(__QNXNTO__)
#else
#error "unkown platform, please check it."
#endif

namespace holo
{
namespace os
{
holo::int32_t Utils::GetTid()
{
    pid_t tid{-1};

#if defined(__linux__)
#ifndef __NR_gettid
#define __NR_gettid 224
#endif
    tid = syscall(__NR_gettid);
#elif defined(__QNX__) || defined(__QNXNTO__)
    tid = gettid();
#else
#error "unkown platform, please check it."
#endif

    if (tid == -1)
    {
        throw holo::exception::RuntimeErrorException{"get tid failed"};
    }

    return tid;
}

holo::int32_t Utils::GetPid()
{
    return static_cast<holo::int32_t>(getpid());
}

holo::int32_t Utils::GetPpid()
{
    return static_cast<holo::int32_t>(getppid());
}
}  // namespace os
}  // namespace holo
