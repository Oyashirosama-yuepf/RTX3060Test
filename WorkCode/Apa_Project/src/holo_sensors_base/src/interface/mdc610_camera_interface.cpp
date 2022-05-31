/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc610_camera_interface.cpp
 * @brief define the mdc610 camera interface class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021-05-27
 */

#include <holo/log/hololog.h>
#include <holo/sensors/interface/mdc610_camera_interface.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace interface
{
template <typename ProxyType>
Mdc610CameraInterface<ProxyType>::Mdc610CameraInterface(const Mdc610CameraInterfaceParam& param)
  : Mdc610CameraInterfaceBaseT<ProxyType>()
  , running_(true)
  , counter_(0)
  , instance_(-1)
  , use_datalayer_timestamp_(true)
  , encoded_(false)
  , service_handle_()
  , proxy_(nullptr)
  , timediff_()
{
    Init(param);
}

template <typename ProxyType>
Mdc610CameraInterface<ProxyType>::Mdc610CameraInterface(const holo::yaml::Node& node)
  : Mdc610CameraInterfaceBaseT<ProxyType>()
  , running_(true)
  , counter_(0)
  , instance_(-1)
  , use_datalayer_timestamp_(true)
  , encoded_(false)
  , service_handle_()
  , proxy_(nullptr)
  , timediff_()
{
    Mdc610CameraInterfaceParam param;
    try
    {
        param.instance                = node["instance"].as<int32_t>();
        param.use_datalayer_timestamp = node["use_datalayer_timestamp"].as<holo::bool_t>("true");
    }
    catch (const std::exception& e)
    {
        std::ostringstream oss;
        oss << "mdc610 camera interface failed: " << e.what();
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }
    if (!Init(param))
    {
        std::ostringstream oss;
        oss << "mdc610 camera interface failed to init";
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }
}

template <typename ProxyType>
bool_t Mdc610CameraInterface<ProxyType>::Init(const Mdc610CameraInterfaceParam& param)
{
    LOG(INFO) << "instance = " << param.instance;
    if ((DECODE_INSTANCEID_MIN <= param.instance) && (param.instance <= DECODE_INSTANCEID_MAX))
    {
        encoded_ = false;
    }
    else if ((ENCODE_INSTANCEID_MIN <= param.instance) && (param.instance <= ENCODE_INSTANCEID_MAX))
    {
        encoded_ = true;
    }
    else
    {
        std::ostringstream oss;
        oss << "mdc610 camera instance id invalid: " << param.instance;
        LOG(ERROR) << oss.str();
        throw std::runtime_error(oss.str());
    }

    instance_                = param.instance;
    use_datalayer_timestamp_ = param.use_datalayer_timestamp;

    if (!use_datalayer_timestamp_)
    {
        Timestamp   mgt_ts;
        Timestamp   data_ts;
        holo::Timer timer(10);
        while (!holo::mdc610::GetAllLevelTime(mgt_ts, data_ts))
        {
            timer.Start();
            LOG(ERROR) << "failed to get mdc610 system time, will retry...";
            timer.Stop();
        }
        timediff_ = mgt_ts - data_ts;
        LOG(INFO) << "mdc610 management-level-time - data-level-time = " << timediff_.ToSec();
    }

#if (20220228 == MDC610_VERSION_NUM)
    if (!ara::rm::RegisterHisiResource()) 
    {
        LOG(ERROR) << "register camera_receive failed!";
        return false;
    }
    
    BuffCfg cfg;
    if (memset_s(&cfg, sizeof(BuffCfg), 0x0, sizeof(BuffCfg)) != EOK) 
    {
        LOG(ERROR) << "memset_s buff cfg failed!";
        return false;
    }

    const int ret = halBuffInit(&cfg);
    if (ret != DRV_ERROR_NONE) 
    {
        if (DRV_ERROR_REPEATED_INIT != ret)
        {
            LOG(ERROR) << "halBuffInit result: " << ret;
            return false;
        }

        LOG(WARNING) << "halBuffInit repeat";
    }
#endif

    FindService();
    thread_ = std::make_shared<std::thread>(&Mdc610CameraInterface<ProxyType>::Subscribe, this);

    return true;
}

template <typename ProxyType>
void Mdc610CameraInterface<ProxyType>::ServiceAvailabilityCallback(ServiceHandleContainerType  handles,
                                                                   ara::com::FindServiceHandle handler)
{
    (void)handler;
    if (!proxy_)
    {
        for (auto handle : handles)
        {
            ara::core::StringView instanceIDSV = handle.GetInstanceId().ToString();
            int32_t               myInstanceId = (instanceIDSV.at(0) - '0') * 10 + (instanceIDSV.at(1) - '0');
            if (instance_ == myInstanceId)
            {
                proxy_ = std::make_unique<ProxyType>(handle);
                LOG(INFO) << "camera proxy initialized successfully";
                return;
            }
        }
    }
}

template <typename ProxyType>
void Mdc610CameraInterface<ProxyType>::FindService()
{
    LOG(INFO) << "start find service";
    service_handle_ = ProxyType::StartFindService(
        [this](ServiceHandleContainerType handles, ara::com::FindServiceHandle handler) {
            ServiceAvailabilityCallback(std::move(handles), handler);
        },
        ara::core::InstanceSpecifier(Mdc610CameraInterfaceBaseT<ProxyType>::string_view_));
}

template <>
void Mdc610CameraInterface<decodedProxy>::ReceiveHandler()
{
    proxy_->cameraDecodedMbufEvent.GetNewSamples(
        [this](ara::com::SamplePtr<ara::camera::CameraDecodedMbufStruct const> ptr) {
            if (callback_)
            {
                auto     sample = ptr.Get();
                Mbuf*    pMbuf  = reinterpret_cast<Mbuf*>(sample->RawData);
                uint8_t* pData  = nullptr;

#if (20220228 == MDC610_VERSION_NUM)
                uint64_t len    = 0;
#else
                uint32_t len    = 0;
#endif
                if (halMbufGetDataPtr(pMbuf, reinterpret_cast<void**>(&pData), &len) != 0)
                {
                    LOG(ERROR) << "failed to get data from hal mbuf";
                    return;
                }
                StreamBuffer buffer;

                buffer.init     = true;
                buffer.start    = static_cast<void*>(pData);
                buffer.capacity = sample->DataSize;
                buffer.size     = sample->DataSize;

                Timestamp receive_stamp;
                (void)holo::mdc610::GetDataLevelTime(receive_stamp);
                Timestamp trigger_stamp(sample->CameraHeader.Stamp.Sec, sample->CameraHeader.Stamp.Nsec);

                if (!use_datalayer_timestamp_)
                {
                    (void)holo::mdc610::GetTimeDiff(timediff_);
                    receive_stamp += timediff_;
                    trigger_stamp += timediff_;
                }
                // LOG(INFO) << std::setprecision(19) << trigger_stamp.ToSec();

                callback_(buffer, receive_stamp, trigger_stamp);
                (void)halMbufFree(reinterpret_cast<Mbuf*>(sample->RawData));
            }
        },
        LAST_SIZE);
}

template <>
void Mdc610CameraInterface<encodedProxy>::ReceiveHandler()
{
    proxy_->cameraEncodedMbufEvent.GetNewSamples(
        [this](ara::com::SamplePtr<ara::camera::CameraEncodedMbufStruct const> ptr) {
            if (callback_ || rawcallback_)
            {
                auto     sample = ptr.Get();
                Mbuf*    pMbuf  = reinterpret_cast<Mbuf*>(sample->RawData);
                uint8_t* pData  = nullptr;
#if (20220228 == MDC610_VERSION_NUM)
                uint64_t len    = 0;
#else
                uint32_t len    = 0;
#endif
                if (halMbufGetDataPtr(pMbuf, reinterpret_cast<void**>(&pData), &len) != 0)
                {
                    LOG(ERROR) << "failed to get data from hal mbuf";
                    return;
                }

                uint8_t current_frame_type = holo::sensors::camera::FrameType::UNKNOWN;
                if (Mdc610CameraFrameType::FRAME_TYPE_I == sample->FrameType)
                {
                    current_frame_type = holo::sensors::camera::FrameType::I;
                }
                else
                {
                    current_frame_type = holo::sensors::camera::FrameType::P;
                }

                Timestamp receive_stamp;
                (void)holo::mdc610::GetDataLevelTime(receive_stamp);
                Timestamp trigger_stamp(sample->CameraHeader.Stamp.Sec, sample->CameraHeader.Stamp.Nsec);

                if (!use_datalayer_timestamp_)
                {
                    (void)holo::mdc610::GetTimeDiff(timediff_);
                    receive_stamp += timediff_;
                    trigger_stamp += timediff_;
                }
                // LOG(INFO) << std::setprecision(19) << trigger_stamp.ToSec();

                if (callback_)
                {
                    StreamBuffer buffer;
                    buffer.init     = true;
                    buffer.start    = static_cast<void*>(pData);
                    buffer.capacity = sample->DataSize;
                    buffer.size     = sample->DataSize;
                    callback_(buffer, receive_stamp, trigger_stamp, current_frame_type);
                }
                if (rawcallback_)
                {
                    ImagePacket packet;
                    packet.image_type     = ImageType::H265;
                    packet.seq            = counter_++;
                    packet.data           = const_cast<uint8_t*>(pData);
                    packet.size           = sample->DataSize;
                    packet.received_stamp = receive_stamp;
                    packet.trigger_stamp  = trigger_stamp;
                    rawcallback_(packet);
                }
                // Free Mbuf
                (void)halMbufFree(reinterpret_cast<Mbuf*>(sample->RawData));
            }
        },
        LAST_SIZE);
}

template <>
void Mdc610CameraInterface<decodedProxy>::Subscribe()
{
    LOG(INFO) << "wait for camera proxy initialization";
    while (!proxy_ && running_)
    {
        holo::os::Sleep(0.1f);
    }
    if (running_)
    {
        LOG(INFO) << "start to subscribe";
        if (!proxy_->cameraDecodedMbufEvent.IsSubscribed())
        {
            proxy_->cameraDecodedMbufEvent.SetReceiveHandler([this]() { ReceiveHandler(); });
            proxy_->cameraDecodedMbufEvent.Subscribe(SUBSCRIBE_NUM);
        }
    }
}

template <>
void Mdc610CameraInterface<encodedProxy>::Subscribe()
{
    LOG(INFO) << "wait for camera proxy initialization";
    while (!proxy_ && running_)
    {
        holo::os::Sleep(0.1f);
    }
    if (running_)
    {
        LOG(INFO) << "start to subscribe";
        if (!proxy_->cameraEncodedMbufEvent.IsSubscribed())
        {
            proxy_->cameraEncodedMbufEvent.SetReceiveHandler([this]() { ReceiveHandler(); });
            proxy_->cameraEncodedMbufEvent.Subscribe(SUBSCRIBE_NUM);
        }
    }
}

template <typename ProxyType>
void Mdc610CameraInterface<ProxyType>::StopFindService()
{
    if (proxy_)
    {
        LOG(INFO) << "stop service";
        proxy_->StopFindService(service_handle_);
    }
}

template <typename ProxyType>
Mdc610CameraInterface<ProxyType>::~Mdc610CameraInterface()
{
    running_ = false;
    if (thread_ && thread_->joinable())
    {
        thread_->join();
    }
    StopFindService();
}

template class Mdc610CameraInterface<encodedProxy>;
template class Mdc610CameraInterface<decodedProxy>;

}  // namespace interface
}  // namespace sensors
}  // namespace holo