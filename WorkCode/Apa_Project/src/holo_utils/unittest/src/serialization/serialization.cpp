#include <holo/serialization/serialization.h>

template class holo::serialization::Serializer<true>;
template class holo::serialization::Deserializer<true>;
template class holo::serialization::Serializer<false>;
template class holo::serialization::Deserializer<false>;
