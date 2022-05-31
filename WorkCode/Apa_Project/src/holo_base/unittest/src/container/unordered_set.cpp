#include <holo/container/unordered_set.h>

template class std::unordered_set<std::string, std::hash<std::string>, std::equal_to<std::string>,
                                  holo::core::Allocator<std::string, 10U>>;

template class std::unordered_multiset<std::string, std::hash<std::string>, std::equal_to<std::string>,
                                       holo::core::Allocator<std::string, 10U>>;
