/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file std_serializer.h
 * @brief This header file defines the std::_ like serializer helpers.
 * @author zhengshulei@holomatic.com
 * @date 2021-10-08
 */
#ifndef HOLO_MAP_ADASIS_STD_SERIALIZER_H_
#define HOLO_MAP_ADASIS_STD_SERIALIZER_H_

#include <holo/map/adasis/serialization/serializer.h>

#include <list>
#include <map>
#include <set>
#include <string>
#include <vector>

namespace holo
{
namespace map
{
namespace adasis
{
namespace serialization
{
// Serialization traits for std::pair container
template <class T1, class T2>
struct SerializationTraits<std::pair<T1, T2> >
{
    using serializable_t = std::pair<T1, T2>;

    static const bool IS_ARRAY_BASE_TYPE = false;

    static Serializer& Store(Serializer& s, const serializable_t& x)
    {
        return s << x.first << x.second;
    }
    static Deserializer& Retrieve(Deserializer& s, serializable_t& x)
    {
        return s >> x.first >> x.second;
    }
};

template <class iterator_t>
Serializer& StoreContainerRange(Serializer& s, iterator_t it_bgn,
                                iterator_t it_end)
{
    for (iterator_t it = it_bgn; it != it_end; ++it)
    {
        s << *it;
    }
    return s;
}

template <class iterator_t>
Deserializer& RetrieveContainerRange(Deserializer& s, iterator_t it_bgn,
                                     iterator_t it_end)
{
    for (iterator_t it = it_bgn; it != it_end; ++it)
    {
        s >> *it;
    }
    return s;
}

// serialize a std::-like container
template <class C>
inline Serializer& StoreContainer(Serializer& s, const C& x)
{
#if 0
    s << holo::uint32_t(x.size());
#endif
    s << holo::uint8_t(x.size());
    return StoreContainerRange(s, x.begin(), x.end());
}

// deserialize a std::list-like container
template <class C, class value_t>
Deserializer& RetrieveListContainer(Deserializer& s, C& x, const value_t*)
{
    uint32_t n;
    s >> n;
    x = C();
    value_t val;
    while (n--)
    {
        s >> val;
        x.push_back(val);
    }
    return s;
}

// deserialize a std::list-like container
template <class C>
inline Deserializer& RetrieveListContainer(Deserializer& s, C& x)
{
    return RetrieveListContainer(s, x, (0 ? (&(*x.begin())) : 0));
}

// deserialize a std::vector-like container
template <class C>
inline Deserializer& RetrieveVectorContainer(Deserializer& s, C& x)
{
#if 0
    holo::uint32_t n;
#endif
    holo::uint8_t n;
    s >> n;
    x.resize(n);
    return RetrieveContainerRange(s, x.begin(), x.end());
}

// Serialization traits for std::list container
template <class T, class Allocator>
struct SerializationTraits<std::list<T, Allocator> >
{
    using serializable_t = std::list<T, Allocator>;

    static const bool IS_ARRAY_BASE_TYPE = false;

    static Serializer& Store(Serializer& s, const serializable_t& x)
    {
        return StoreContainer(s, x);
    }
    static Deserializer& Retrieve(Deserializer& s, serializable_t& x)
    {
        return RetrieveListContainer(s, x);
    }
};

template <class C, bool OPTIMIZED>
struct VectorContainerSerializeHelper
{
    static inline Deserializer& Retrieve(Deserializer& s, C& x)
    {
        return RetrieveVectorContainer(s, x);
    }
    static inline Serializer& Store(Serializer& s, const C& x)
    {
        return StoreContainer(s, x);
    }
};

template <class C>
struct VectorContainerSerializeHelper<C, true>
{
    static inline Deserializer& Retrieve(Deserializer& s, C& x)
    {
#if 0
        holo::uint32_t n;
#endif
        holo::uint8_t n;
        s >> n;
        x.resize(n);
        if (n)
        {
            s.ReadArray(n, &(x[0]));
        }
        return s;
    }
    static inline Serializer& Store(Serializer& s, const C& x)
    {
#if 0
        holo::uint32_t n = holo::uint32_t(x.size());
#endif
        holo::uint8_t n = holo::uint8_t(x.size());
        s << n;
        if (n)
        {
            s.WriteArray(n, &(x[0]));
        }
        return s;
    }
};

// Serialization traits for std::vector container
template <class T, class Allocator>
struct SerializationTraits<std::vector<T, Allocator> >
{
    using serializable_t = std::vector<T, Allocator>;

    static const bool IS_ARRAY_BASE_TYPE = false;

    static Serializer& Store(Serializer& s, const serializable_t& x)
    {
        return VectorContainerSerializeHelper<
            serializable_t,
            SerializationTraits<T>::IS_ARRAY_BASE_TYPE>::Store(s, x);
    }
    static Deserializer& Retrieve(Deserializer& s, serializable_t& x)
    {
        return VectorContainerSerializeHelper<
            serializable_t,
            SerializationTraits<T>::IS_ARRAY_BASE_TYPE>::Retrieve(s, x);
    }
};

// Serialization traits for std::string container
template <class charT, class traits, class Allocator>
struct SerializationTraits<std::basic_string<charT, traits, Allocator> >
{
    using serializable_t = std::basic_string<charT, traits, Allocator>;

    static const bool IS_ARRAY_BASE_TYPE = false;

    static Serializer& Store(Serializer& s, const serializable_t& x)
    {
        s << uint32_t(x.size());
        if (x.size())
        {
            s.WriteString(x.size() + 1, x.c_str());
        }
        return s;
    }
    static Deserializer& Retrieve(Deserializer& s, serializable_t& x)
    {
        uint32_t sz;
        s >> sz;
        if (sz)
        {
            charT* t = new charT[sz + 1];
            s.ReadString(sz + 1, t);
            x = t;
            delete[] t;
        }
        else
        {
            x = "";
        }
        return s;
    }
};

// deserialize a std::set-like container
template <class C, class value_t>
Deserializer& RetrieveSetContainer(Deserializer& s, C& x, const value_t*)
{
    uint32_t n;
    s >> n;
    x = C(); // empty set
    value_t elem;
    while (n--)
    {
        s >> elem;
        x.insert(elem);
    }
    return s;
}

// deserialize a std::set-like container
template <class C>
inline Deserializer& RetrieveSetContainer(Deserializer& s, C& x)
{
    return RetrieveSetContainer(s, x, (0 ? (&(*x.begin())) : 0));
}

// Serialization traits for std::set container
template <class Key, class Compare, class Allocator>
struct SerializationTraits<std::set<Key, Compare, Allocator> >
{
    using serializable_t = std::set<Key, Compare, Allocator>;

    static const bool IS_ARRAY_BASE_TYPE = false;

    static Serializer& Store(Serializer& s, const serializable_t& x)
    {
        return StoreContainer(s, x);
    }
    static Deserializer& Retrieve(Deserializer& s, serializable_t& x)
    {
        return RetrieveSetContainer(s, x);
    }
};

// Serialization traits for std::set container
template <class Key, class Compare, class Allocator>
struct SerializationTraits<std::multiset<Key, Compare, Allocator> >
{
    using serializable_t = std::multiset<Key, Compare, Allocator>;

    static const bool IS_ARRAY_BASE_TYPE = false;

    static Serializer& Store(Serializer& s, const serializable_t& x)
    {
        return StoreContainer(s, x);
    }
    static Deserializer& Retrieve(Deserializer& s, serializable_t& x)
    {
        return RetrieveSetContainer(s, x);
    }
};

// Serialization traits for std::map container
template <class Key, class T, class Compare, class Allocator>
struct SerializationTraits<std::map<Key, T, Compare, Allocator> >
{
    using serializable_t = std::map<Key, T, Compare, Allocator>;

    static const bool IS_ARRAY_BASE_TYPE = false;

    static Serializer& Store(Serializer& s, const serializable_t& x)
    {
        return StoreContainer(s, x);
    }
    static Deserializer& Retrieve(Deserializer& s, serializable_t& x)
    {
        uint32_t n;
        s >> n;
        x = std::map<Key, T, Compare, Allocator>();
        Key k;
        T v;
        while (n--)
        {
            s >> k >> v;
            x[k] = v;
        }
        return s;
    }
};

// Serialization traits for std::map container
template <class Key, class T, class Compare, class Allocator>
struct SerializationTraits<std::multimap<Key, T, Compare, Allocator> >
{
    using serializable_t = std::multimap<Key, T, Compare, Allocator>;

    static const bool IS_ARRAY_BASE_TYPE = false;

    static Serializer& Store(Serializer& s, const serializable_t& x)
    {
        return StoreContainer(s, x);
    }
    static Deserializer& Retrieve(Deserializer& s, serializable_t& x)
    {
        return RetrieveSetContainer(s, x);
    }
};

// serialize a fixed size std::-like container
template <class C>
inline Serializer& StoreFixedSizeContainer(Serializer& s, const C& x)
{
    return StoreContainerRange(s, x.begin(), x.end());
}

// deserialize a fixed-size vector-like container
template <class C>
inline Deserializer& RetrieveFixedSizeVectorContainer(Deserializer& s, C& x)
{
    return RetrieveContainerRange(s, x.begin(), x.end());
}

template <class iterator_t, class const_iterator_t, bool OPTIMIZED>
struct FixedSizeVectorContainerSerializeHelper
{
    static inline Deserializer& Retrieve(Deserializer& s, iterator_t bgn,
                                         iterator_t end)
    {
        return RetrieveContainerRange(s, bgn, end);
    }
    static inline Serializer& Store(Serializer& s, const_iterator_t bgn,
                                    const_iterator_t end)
    {
        return StoreContainerRange(s, bgn, end);
    }
};

template <class iterator_t, class const_iterator_t>
struct FixedSizeVectorContainerSerializeHelper<iterator_t, const_iterator_t,
                                               true>
{
    static inline Deserializer& Retrieve(Deserializer& s, iterator_t bgn,
                                         iterator_t end)
    {
        uint32_t n = uint32_t(end - bgn);
        if (n)
        {
            s.ReadArray(n, &(*(bgn)));
        }
        return s;
    }
    static inline Serializer& Store(Serializer& s, const_iterator_t bgn,
                                    const_iterator_t end)
    {
        uint32_t n = uint32_t(end - bgn);
        if (n)
        {
            s.WriteArray(n, &(*(bgn)));
        }
        return s;
    }
};

// deserialize a std::stack-like container
template <class C, class value_t>
Deserializer& RetrieveStackContainer(Deserializer& s, C& x, const value_t*)
{
    uint32_t n;
    s >> n;
    x = C(); // empty stack
    value_t elem;
    while (n--)
    {
        s >> elem;
        x.push(elem);
    }
    return s;
}

// deserialize a std::stack-like container
template <class C>
inline Deserializer& RetrieveStackContainer(Deserializer& s, C& x)
{
    return RetrieveStackContainer(s, x, (0 ? (&(*x.begin())) : 0));
}

} // namespace serialization
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_STD_SERIALIZER_H_ */