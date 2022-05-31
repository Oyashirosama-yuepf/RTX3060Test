#include <holo/thread/object_pool.h>
#include <string>

template class holo::thread::ObjectPool<std::string>;

template void holo::thread::ObjectPool<std::string>::Add();

template std::shared_ptr<std::string> holo::thread::ObjectPool<std::string>::Get();
