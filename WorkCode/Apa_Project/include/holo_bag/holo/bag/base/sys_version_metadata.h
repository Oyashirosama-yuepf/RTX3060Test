/**
 * @file sysversion_metadata.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the param metadata
 * @version 0.1
 * @date 2020-08-03
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#ifndef _HOLOBAG_BASE_SYSVERSION_METADATA_HPP_
#define _HOLOBAG_BASE_SYSVERSION_METADATA_HPP_

#include <string>

namespace holo
{
namespace bag
{
class SysVersionMetadata
{
public:
    std::string category;
    std::string type;
    std::string version;

    bool operator==(const holo::bag::SysVersionMetadata& rhs) const
    {
        return category == rhs.category && type == rhs.type && version == rhs.version;
    }
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_SYSVERSION_METADATA_HPP_
