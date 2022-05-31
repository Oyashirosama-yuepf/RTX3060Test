#ifndef HOLO_IO_NUMERICS_MATRIX_H_
#define HOLO_IO_NUMERICS_MATRIX_H_

#include <holo/numerics/matrix.h>
#include <yaml-cpp/yaml.h>

namespace YAML
{
template <typename T, int32_t R, int32_t C>
struct convert<holo::numerics::MatrixT<T, R, C>>
{
    using ValueType = holo::numerics::MatrixT<T, R, C>;
    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["row"] = static_cast<uint32_t>(rhs.GetRows());
        node["col"] = static_cast<uint32_t>(rhs.GetCols());

        for (std::size_t row = 0; row < rhs.GetRows(); ++row)
        {
            for (std::size_t col = 0; col < rhs.GetCols(); ++col)
            {
                node["value"][row].push_back(rhs(row, col));
            }
            node["value"][row].SetStyle(YAML::EmitterStyle::Flow);
        }
        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            if (!((node["row"].as<uint32_t>() == R) && (node["col"].as<uint32_t>() == C)))
            {
                return false;
            }

            for (size_t row = 0; row < node["row"].as<uint32_t>(); ++row)
            {
                size_t i = 0U;
                for (YAML::const_iterator it = node["value"][row].begin(); it != node["value"][row].end(); ++it)
                {
                    rhs(row, i++) = it->as<typename ValueType::ScalarType>();
                }
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
struct convert<holo::numerics::MatrixT<T, -1, -1>>
{
    using ValueType = holo::numerics::MatrixT<T, -1, -1>;
    static Node encode(ValueType const& rhs)
    {
        Node node;
        node["row"] = rhs.GetRows();
        node["col"] = rhs.GetCols();

        for (std::size_t row = 0; row < rhs.GetRows(); ++row)
        {
            for (std::size_t col = 0; col < rhs.GetCols(); ++col)
            {
                node["value"][row].push_back(rhs(row, col));
            }
            node["value"][row].SetStyle(YAML::EmitterStyle::Flow);
        }

        return node;
    }

    static bool decode(Node const& node, ValueType& rhs)
    {
        try
        {
            rhs.Resize(node["row"].as<uint32_t>(), node["col"].as<uint32_t>());

            for (size_t row = 0; row < node["row"].as<uint32_t>(); ++row)
            {
                size_t i = 0U;
                for (YAML::const_iterator it = node["value"][row].begin(); it != node["value"][row].end(); ++it)
                {
                    rhs(row, i++) = it->as<typename ValueType::ScalarType>();
                }
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
