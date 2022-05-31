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
#ifndef _HOLOBAG_BASE_SERIALIZED_TAG_MESSAGE_HPP_
#define _HOLOBAG_BASE_SERIALIZED_TAG_MESSAGE_HPP_

#include <holo/core/types.h>

#include <string>

namespace holo
{
namespace bag
{
class TagMessage
{
public:
    int64_t                                  time_stamp;
    std::string                              tag;
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_SERIALIZED_TAG_MESSAGE_HPP_
