/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc300_can_interface.h
 * @brief define the mdc can interface class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-12-30
 */

#ifndef HOLO_SENSORS_CMW_APP_INTERFACE_MDC300_CAN_INTERFACE_H
#define HOLO_SENSORS_CMW_APP_INTERFACE_MDC300_CAN_INTERFACE_H

#include <holo/sensors/common/interface.h>
#include <holo/sensors/format/holocan.h>
#include <holo/utils/yaml.h>

#include <holo/sensors/interface/mdc300/generated/includes/impl_type_canbusdataparam.h>
#include <holo/sensors/interface/mdc300/generated/includes/impl_type_cansetdataresult.h>
#include <holo/sensors/interface/mdc300/generated/includes/mdc/sensor/canrxserviceinterface_common.h>
#include <holo/sensors/interface/mdc300/generated/includes/mdc/sensor/canrxserviceinterface_proxy.h>
#include <holo/sensors/interface/mdc300/generated/includes/mdc/sensor/cantxserviceinterface_common.h>
#include <holo/sensors/interface/mdc300/generated/includes/mdc/sensor/cantxserviceinterface_skeleton.h>

static constexpr int32_t MDC_CAN_CHANNELS = 12;

namespace holo
{
namespace sensors
{
namespace interface
{
using holo::sensors::common::InterfaceT;

struct MdcCanInterfaceParam
{
    int32_t channel;
};

template <typename T>
class MdcCanInterface : public InterfaceT<T>
{
public:
    using CanRxProxy    = ::mdc::sensor::proxy::CanRxServiceInterfaceProxy;
    using CanTxSkeleton = ::mdc::sensor::skeleton::CanTxServiceInterfaceSkeleton;

    MdcCanInterface() = delete;
    MdcCanInterface(const MdcCanInterfaceParam& param);
    MdcCanInterface(const holo::yaml::Node& node);

    void CanEventSend(const holo::sensors::format::HoloCanPacket& packet);
    void CanMethodSend(const holo::sensors::format::HoloCanPacket& packet);
    void CanMethodSend(const std::vector<holo::sensors::format::HoloCanPacket> packets);

private:
    void Init(int32_t channelId);
    void ServiceAvailabilityCallback(::ara::com::ServiceHandleContainer<CanRxProxy::HandleType> handles,
                                     ::ara::com::FindServiceHandle                              handler);
    void CanDataEventCallback();
    void Convert(const holo::sensors::format::HoloCanPacket& input, Element& output);
    void Convert(const Element& input, holo::sensors::format::HoloCanPacket& output);

private:
    int32_t                        instance_;
    std::mutex                     can_read_mutex_;
    std::unique_ptr<CanRxProxy>    can_proxy_;
    std::mutex                     can_send_mutex_;
    std::unique_ptr<CanTxSkeleton> can_skeleton_;
};

}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif
