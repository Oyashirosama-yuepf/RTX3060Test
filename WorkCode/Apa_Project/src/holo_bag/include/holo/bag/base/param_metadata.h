/**
 * @file param_metadata.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the param metadata
 * @version 0.1
 * @date 2020-08-03
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#ifndef _HOLOBAG_BASE_PARAM_METADATA_HPP_
#define _HOLOBAG_BASE_PARAM_METADATA_HPP_

#include <string>

namespace holo
{
namespace bag
{
class ParamMetadata
{
public:
    std::string path;
    std::string name;
    std::string file;

    bool operator==(const holo::bag::ParamMetadata& rhs) const
    {
        return path == rhs.path && name == rhs.name && file == rhs.file;
    }
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_PARAM_METADATA_HPP_
