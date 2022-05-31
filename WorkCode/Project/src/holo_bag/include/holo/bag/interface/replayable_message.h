// Copyright 2018 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef _HOLOBAG_INTERFACE_REPLAYABLE_MESSAGE_HPP_
#define _HOLOBAG_INTERFACE_REPLAYABLE_MESSAGE_HPP_

#include <holo/bag/base/serialized_bag_message.h>

#include <chrono>
#include <memory>

namespace holo
{
namespace bag
{
class ReplayableMessage
{
public:
    std::shared_ptr<SerializedBagMessage> message_;
    holo::int64_t                         time_since_start_;

    ReplayableMessage()
    {
    }

    ReplayableMessage(ReplayableMessage const& other)
      : message_(other.message_), time_since_start_(other.time_since_start_)
    {
    }

    ReplayableMessage(ReplayableMessage&& other) 
      : message_(other.message_), time_since_start_(other.time_since_start_)
    {
    }

    ReplayableMessage operator=(ReplayableMessage const& other)
    {
        message_          = other.message_;
        time_since_start_ = other.time_since_start_;
        return *this;
    }

    ReplayableMessage operator=(ReplayableMessage&& other)
    {
        message_  = other.message_;
        time_since_start_ = other.time_since_start_;
        return *this;
    }
};

}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_INTERFACE_REPLAYABLE_MESSAGE_HPP_
