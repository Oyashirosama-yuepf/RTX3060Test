#ifndef OPENDDS_MSG_COMMON_CPU_STATES_TRAITS_H_
#define OPENDDS_MSG_COMMON_CPU_STATES_TRAITS_H_

#include <holo_base_msg/common/CpuStatesC.h>
#include <holo_base_msg/common/CpuStatesS.h>
#include <holo_base_msg/common/CpuStatesTypeSupportC.h>
#include <holo_base_msg/common/CpuStatesTypeSupportImpl.h>
#include <holo_base_msg/common/CpuStatesTypeSupportS.h>
#include <opendds_wrapper/traits.h>

namespace opendds_wrapper
{
/* CpuStates traits */

template <>
struct DefaultMessageTraits<::holo_base_msg::common::CpuStates>
{
    using ValueType   = ::holo_base_msg::common::CpuStates;
    using MessageType = ::holo_base_msg::common::CpuStates;
};

}  // namespace opendds_wrapper

#endif
