#include <holo/container/vector.h>

template class holo::container::details::Vector<bool, 10U, std::allocator<bool>>;

template class holo::container::details::Vector<bool, std::numeric_limits<size_t>::max(), std::allocator<bool>>;

template class holo::container::details::Vector<bool, 0U, std::allocator<bool>>;
