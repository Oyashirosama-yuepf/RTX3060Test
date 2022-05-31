/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mdc_camera_decoded_interface.h
 * @brief define the mdc610 camera decoded interface class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2021-05-27
 */

#ifndef HOLO_SENSORS_CMW_APP_INTERFACE_MDC_CAMERA_DECODED_INTERFACE_H
#define HOLO_SENSORS_CMW_APP_INTERFACE_MDC_CAMERA_DECODED_INTERFACE_H

#include <holo/common/timestamp.h>
#include <holo/os/time.h>
#include <holo/os/timer.h>
#include <holo/sensors/camera/image_structure.h>
#include <holo/sensors/utils/mdc610_utils.h>
#include <holo/utils/yaml.h>

#include "driver/ascend_hal.h"
#if (20220228 == MDC610_VERSION_NUM)
#include "ara/rm/rm.h"
#endif
#include "mdc/cam/camera/cameradecodedmbufserviceinterface_proxy.h"
#include "mdc/cam/camera/cameraencodedmbufserviceinterface_proxy.h"

namespace holo
{
namespace sensors
{
namespace interface
{
using holo::common::Timestamp;
using holo::sensors::camera::ImagePacket;
using holo::sensors::camera::ImageType;
using holo::sensors::camera::StreamBuffer;

using decodedProxy = ::mdc::cam::camera::proxy::CameraDecodedMbufServiceInterfaceProxy;
using encodedProxy = ::mdc::cam::camera::proxy::CameraEncodedMbufServiceInterfaceProxy;

struct Mdc610CameraInterfaceParam
{
    int32_t instance;
    bool    use_datalayer_timestamp;
};

enum Mdc610CameraFrameType : uint32_t
{
    FRAME_TYPE_I = 19,
    FRAME_TYPE_P = 2
};

template <typename ProxyType>
class Mdc610CameraInterfaceBaseT
{
public:
    Mdc610CameraInterfaceBaseT() = delete;
};

template <>
class Mdc610CameraInterfaceBaseT<decodedProxy>
{
public:
    using DecodedCallbackType = std::function<void(const StreamBuffer&, const Timestamp&, const Timestamp&)>;

    Mdc610CameraInterfaceBaseT()
      : callback_(nullptr), string_view_("HoloVSCameraExecutable/HoloVSCamera/HoloVSCameraDecodedMbufSubscriber")
    {
    }

    virtual ~Mdc610CameraInterfaceBaseT() = default;

    void InstallCallback(const DecodedCallbackType& handler) noexcept
    {
        callback_ = handler;
    }

protected:
    DecodedCallbackType         callback_;
    const ara::core::StringView string_view_;
};

template <>
class Mdc610CameraInterfaceBaseT<encodedProxy>
{
public:
    using RawCallbackType = std::function<void(const ImagePacket&)>;
    using EncodedCallbackType =
        std::function<void(const StreamBuffer&, const Timestamp&, const Timestamp&, const uint8_t)>;

    Mdc610CameraInterfaceBaseT()
      : callback_(nullptr), string_view_("HoloVSCameraExecutable/HoloVSCamera/HoloVSCameraEncodedMbufSubscriber")
    {
    }

    virtual ~Mdc610CameraInterfaceBaseT() = default;

    void InstallCallback(const RawCallbackType& handler) noexcept
    {
        rawcallback_ = handler;
    }

    void InstallCallback(const EncodedCallbackType& handler) noexcept
    {
        callback_ = handler;
    }

protected:
    RawCallbackType             rawcallback_;
    EncodedCallbackType         callback_;
    const ara::core::StringView string_view_;
};

template <typename ProxyType>
class Mdc610CameraInterface : public Mdc610CameraInterfaceBaseT<ProxyType>
{
public:
    using ServiceHandleContainerType = ara::com::ServiceHandleContainer<typename ProxyType::HandleType>;

    Mdc610CameraInterface() = delete;
    Mdc610CameraInterface(const Mdc610CameraInterfaceParam& param);
    Mdc610CameraInterface(const holo::yaml::Node& node);
    ~Mdc610CameraInterface();

private:
    bool_t Init(const Mdc610CameraInterfaceParam& param);
    void   FindService();
    void   StopFindService();
    void   Subscribe();
    void   ServiceAvailabilityCallback(ServiceHandleContainerType handles, ara::com::FindServiceHandle handler);
    void   ReceiveHandler();

private:
    holo::bool_t                 running_;
    uint32_t                     counter_;
    int32_t                      instance_;
    holo::bool_t                 use_datalayer_timestamp_;
    holo::bool_t                 encoded_;
    ara::com::FindServiceHandle  service_handle_;
    std::unique_ptr<ProxyType>   proxy_;
    holo::common::Duration       timediff_;
    std::shared_ptr<std::thread> thread_;

private:
    static constexpr int32_t SUBSCRIBE_NUM         = 100;
    static constexpr int32_t LAST_SIZE             = 15;
    static constexpr int32_t DECODE_INSTANCEID_MIN = 21;
    static constexpr int32_t DECODE_INSTANCEID_MAX = 35;
    static constexpr int32_t ENCODE_INSTANCEID_MIN = 71;
    static constexpr int32_t ENCODE_INSTANCEID_MAX = 85;
};

}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif
