/**
 * @file serialized_bag_message.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the serialized bag message
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#ifndef _HOLOBAG_BASE_SERIALIZED_BAG_MESSAGE_HPP_
#define _HOLOBAG_BASE_SERIALIZED_BAG_MESSAGE_HPP_

#include <holo/core/types.h>
#include <holo/container/vector.h>

#include <string>

namespace holo
{
namespace bag
{
class SerializedBagMessage
{
public:
    holo::container::Vector<::holo::uint8_t, std::numeric_limits<size_t>::max()> serialized_data;
    int64_t                                           time_stamp;
    std::string                                       topic_name;

    SerializedBagMessage()
    {
    }

    SerializedBagMessage(SerializedBagMessage const& other)
      : serialized_data(other.serialized_data), time_stamp(other.time_stamp), topic_name(other.topic_name)
    {
    }

    SerializedBagMessage(SerializedBagMessage&& other)
      : serialized_data(other.serialized_data), time_stamp(other.time_stamp), topic_name(other.topic_name)
    {
    }

    SerializedBagMessage operator=(SerializedBagMessage const& other)
    {
        serialized_data = other.serialized_data;
        time_stamp = other.time_stamp;
        topic_name = other.topic_name;
        return *this;
    }

    SerializedBagMessage operator=(SerializedBagMessage&& other)
    {
        serialized_data = other.serialized_data;
        time_stamp = other.time_stamp;
        topic_name = other.topic_name;
        return *this;
    }
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_SERIALIZED_BAG_MESSAGE_HPP_
