/**
 * @file topic_metadata.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the topic metadata
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#ifndef _HOLOBAG_BASE_TOPIC_METADATA_HPP_
#define _HOLOBAG_BASE_TOPIC_METADATA_HPP_

#include <string>

namespace holo
{
namespace bag
{
class TopicMetadata
{
public:
    std::string name;
    std::string type;
    std::string type_version;
    std::string serialization_format;
    // Serialized std::vector<rclcpp::QoS> as a YAML string
    // std::string offered_qos_profiles;

    bool operator==(const holo::bag::TopicMetadata& rhs) const
    {
        return name == rhs.name && type == rhs.type && serialization_format == rhs.serialization_format;
    }
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_TOPIC_METADATA_HPP_
