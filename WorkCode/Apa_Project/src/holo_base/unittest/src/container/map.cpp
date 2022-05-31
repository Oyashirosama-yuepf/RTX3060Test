#include <holo/container/map.h>

template class std::map<std::string, std::string, std::less<std::string>,
                        holo::core::Allocator<std::pair<std::string, std::string>, 10U>>;

template class std::multimap<std::string, std::string, std::less<std::string>,
                             holo::core::Allocator<std::pair<std::string, std::string>, 10U>>;
