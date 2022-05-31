#include <holo/container/unordered_map.h>

template class std::unordered_map<std::string, std::string, std::hash<std::string>, std::equal_to<std::string>,
                                  holo::core::Allocator<std::pair<std::string const, std::string>, 10U>>;

template class std::unordered_multimap<std::string, std::string, std::hash<std::string>, std::equal_to<std::string>,
                                       holo::core::Allocator<std::pair<std::string const, std::string>, 10U>>;
