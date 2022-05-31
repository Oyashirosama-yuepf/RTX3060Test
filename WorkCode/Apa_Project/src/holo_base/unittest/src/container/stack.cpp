#include <holo/container/set.h>

template class std::set<std::string, std::less<std::string>, holo::core::Allocator<std::string, 10U>>;

template class std::multiset<std::string, std::less<std::string>, holo::core::Allocator<std::string, 10U>>;
