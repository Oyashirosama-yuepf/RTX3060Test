#ifndef HOLO_IO_NUMERICS_VECTOR_H_
#define HOLO_IO_NUMERICS_VECTOR_H_

#include <holo/numerics/vector.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T, int32_t S>
struct convert<holo::numerics::VectorT<T, S>>
{
    using ValueType = holo::numerics::VectorT<T, S>;
    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["size"] = rhs.GetSize();
        for (size_t i = 0; i < rhs.GetSize(); ++i)
        {
            node["value"].push_back(rhs(i));
        }
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (!(node["size"].as<uint32_t>() == S))
            {
                return false;
            }

            size_t i = 0U;
            for (YAML::const_iterator it = node["value"].begin(); it != node["value"].end(); ++it)
            {
                rhs(i++) = it->as<typename ValueType::ScalarType>();
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};

template <typename T>
struct convert<holo::numerics::VectorT<T, -1>>
{
    using ValueType = holo::numerics::VectorT<T, -1>;
    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["size"] = rhs.GetSize();
        for (size_t i = 0; i < rhs.GetSize(); ++i)
        {
            node["value"].push_back(rhs(i));
        }
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.Resize(node["size"].as<uint32_t>());
            size_t i = 0U;
            for (YAML::const_iterator it = node["value"].begin(); it != node["value"].end(); ++it)
            {
                rhs(i++) = it->as<typename ValueType::ScalarType>();
            }
            return true;
        }
        catch (...)
        {
            return false;
        }
    }
};
}  // namespace YAML

#endif
