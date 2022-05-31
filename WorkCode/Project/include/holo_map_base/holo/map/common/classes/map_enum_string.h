/*!
*  \brief enum and string conversion
*  \author dz
*  \date 2018-05-29
*  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
*  \attention Please refer to COPYRIGHT.txt for terms of copyright notice.
*/
#ifndef HOLO_MAP_COMMON_MAP_ENUM_STRING_H_
#define HOLO_MAP_COMMON_MAP_ENUM_STRING_H_

#include <map>
#include <holo/map/common/common_type_define.h>

namespace holo
{
namespace map
{

class EnumString
{
public:

    /**
     * @brief Given a string, return the associated enum value
     * @tparam data type (usually defined in map::format)
     * @param[in] _map enum2str map defined in map::format
     * @param[in] _str string (without type spcifier)
     * @param[out] _enum associated enum
     * @return true if enum can be found
     */
    template <typename T>
    static bool GetEnum(
            const std::map<std::string, T>& _map,
            const std::string& _str,
            T& _enum)
    {
        for (const auto& val: _map)
        {
            if (val.first == _str)
            {
                _enum = val.second;
                return true;
            }
        }
        return false;
    }

    /**
     * @brief Given an enum value, return the associated string
     * @tparam data type (usually defined in map::format)
     * @param[in] _map enum2str map defined in map::format
     * @param[in] _enum enum value
     * @param[out] _str string (without type spcifier)
     * @return true if this enum has associated string
     */
    template <typename T>
    static bool GetString(
            const std::map<std::string, T>& _map,
            const T& _enum,
            std::string& _str)
    {
        for (const auto& val: _map)
        {
            if (val.second == _enum)
            {
                _str = val.first;
                return true;
            }
        }
        _str = "";
        return false;
    }

    /**
     * @brief Get string list representing all enum elements
     * @tparam data type (usually defined in map::format)
     * @param[in] _map enum2str map defined in map::format
     * @return string list.
     */
    template <typename T>
    static std::vector<std::string> GetStringList(
            const std::map<std::string, T>& _map)
    {
        std::vector<std::string> strlist;
        strlist.reserve(_map.size());
        for (const auto& val: _map)
        {
            strlist.push_back(val.first);
        }
        return strlist;
    }
};


} // namespace map
} // namespace holo

#endif /*HOLO_MAP_COMMON_MAP_ENUM_STRING_H_*/
