/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc300_can_interface.cpp
 * @brief define the mdc can interface class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-12-30
 */

#include <holo/log/hololog.h>
#include <holo/sensors/interface/mdc300_can_interface.h>

#include <stdint.h>
#include <cassert>
#include <cstdlib>
#include <exception>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

namespace holo
{
namespace sensors
{
namespace interface
{
template <typename T>
MdcCanInterface<T>::MdcCanInterface(const MdcCanInterfaceParam& param)
    : InterfaceT<T>()
    , can_read_mutex_()
    , can_proxy_(nullptr)
    , can_send_mutex_()
    , can_skeleton_(nullptr)
{
    LOG(INFO) << "channel = " << static_cast<int32_t>(param.channel);
    Init(param.channel);
}

template <typename T>
MdcCanInterface<T>::MdcCanInterface(const holo::yaml::Node& node)
    : InterfaceT<T>()
    , can_read_mutex_()
    , can_proxy_(nullptr)
    , can_send_mutex_()
    , can_skeleton_(nullptr)
{
    MdcCanInterfaceParam param;
    param.channel = node["channel"].as<int32_t>();
    LOG(INFO) << "channel = " << static_cast<int32_t>(param.channel);
    Init(param.channel);
}

template <typename T>
void MdcCanInterface<T>::Init(int32_t channel)
{
    if (0 >= channel || channel > MDC_CAN_CHANNELS)
    {
        std::ostringstream oss;
        oss << "mdc can interface encounter invalid channel id: " << static_cast<int32_t>(channel);
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }
    instance_ = channel;
    can_skeleton_ = std::make_unique<CanTxSkeleton>(ara::com::InstanceIdentifier(instance_),
                                                 ara::com::MethodCallProcessingMode::kPoll);
    can_skeleton_->OfferService();
    CanRxProxy::StartFindService(
        [this](ara::com::ServiceHandleContainer<CanRxProxy::HandleType> handles, ara::com::FindServiceHandle handler) {
            MdcCanInterface::ServiceAvailabilityCallback(std::move(handles), handler);
        },
        instance_);
}

template <typename T>
void MdcCanInterface<T>::ServiceAvailabilityCallback(ara::com::ServiceHandleContainer<CanRxProxy::HandleType> handles,
                                                     ara::com::FindServiceHandle                              handler)
{
    (void)handler;
    for (uint32_t i = 0; i < handles.size(); i++)
    {
        int32_t instanceId = static_cast<int32_t>(handles[i].GetInstanceId());
        if (instanceId != instance_)
        {
            continue;
        }
        if (can_proxy_ == nullptr)
        {
            static constexpr int32_t BUFFER_DEPTH = 100;
            can_proxy_                                = std::make_unique<CanRxProxy>(handles[i]);
            can_proxy_->CanDataRxEvent.Subscribe(ara::com::EventCacheUpdatePolicy::kNewestN, BUFFER_DEPTH);
            can_proxy_->CanDataRxEvent.SetReceiveHandler(
                [this]() { MdcCanInterface::CanDataEventCallback(); });
        }
    }
}

template <typename T>
void MdcCanInterface<T>::CanDataEventCallback()
{
    std::unique_lock<std::mutex> lockread(can_read_mutex_);
    can_proxy_->CanDataRxEvent.Update();
    const auto& canMsgSamples = can_proxy_->CanDataRxEvent.GetCachedSamples();
    for (const auto& sample : canMsgSamples)
    {
        holo::sensors::format::HoloCanPacket packet;
        for (uint32_t i = 0; i < sample->elementList.size(); i++)
        {
            if (InterfaceT<T>::data_callback_)
            {
                Convert(sample->elementList[i], packet);
                InterfaceT<T>::data_callback_(packet);
            }
        }
    }
    lockread.unlock();
    can_proxy_->CanDataRxEvent.Cleanup();
}

template <typename T>
void MdcCanInterface<T>::Convert(const holo::sensors::format::HoloCanPacket& input, Element& output)
{
    output.timeStamp.second  = input.GetSec();
    output.timeStamp.nsecond = input.GetNsec();
    output.canId             = input.GetId();
    output.validLen          = input.GetDlc();
    output.data.resize(input.GetDlc());
    (void)std::memcpy(&output.data[0], input.GetData(), input.GetDlc());
}

template <typename T>
void MdcCanInterface<T>::Convert(const Element& input, holo::sensors::format::HoloCanPacket& output)
{
    output.SetHeaderDefault();
    output.SetSec(input.timeStamp.second);
    output.SetNsec(input.timeStamp.nsecond);
    output.SetId(input.canId);
    output.SetDlc(input.validLen);
    (void)std::memcpy(output.GetData(), &input.data[0], output.GetDlc());
}

template <typename T>
void MdcCanInterface<T>::CanEventSend(const holo::sensors::format::HoloCanPacket& packet)
{
    CanBusDataParam canDataParm;
    canDataParm.seq = 1;
    canDataParm.elementList.resize(1);
    Convert(packet, canDataParm.elementList[0]);

    std::unique_lock<std::mutex> locksend(can_send_mutex_);
    auto controlMcuMsg         = can_skeleton_->CanDataTxEvent.Allocate();
    controlMcuMsg->elementList = canDataParm.elementList;
    controlMcuMsg->seq         = canDataParm.seq;
    can_skeleton_->CanDataTxEvent.Send(std::move(controlMcuMsg));
    locksend.unlock();
}

template <typename T>
void MdcCanInterface<T>::CanMethodSend(const holo::sensors::format::HoloCanPacket& packet)
{
    CanBusDataParam canDataParm;
    canDataParm.seq = 1;
    canDataParm.elementList.resize(1);
    Convert(packet, canDataParm.elementList[0]);
    auto handle = can_proxy_->CanDataSetMethod(canDataParm);
    (void)handle;
}

template <typename T>
void MdcCanInterface<T>::CanMethodSend(const std::vector<holo::sensors::format::HoloCanPacket> packets)
{
    CanBusDataParam canDataParm;
    canDataParm.seq = 1;
    canDataParm.elementList.resize(packets.size());
    for (uint32_t i = 0; i < packets.size(); i++)
    {
        Convert(packets[i], canDataParm.elementList[i]);
    }
    auto handle = can_proxy_->CanDataSetMethod(canDataParm);
    (void)handle;
}

template class MdcCanInterface<holo::sensors::format::HoloCanPacket>;

}  // namespace interface
}  // namespace sensors
}  // namespace holo
