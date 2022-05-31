#include <holo/container/set.h>

template class std::set<bool, std::less<bool>, holo::core::Allocator<bool, 10U>>;

template class std::multiset<bool, std::less<bool>, holo::core::Allocator<bool, 10U>>;
