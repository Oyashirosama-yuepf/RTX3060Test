/*
 * Copyright (c) Huawei Technologies Co., Ltd. 2020-2021. All rights reserved.
 * Generated by VRTF CM-Generator
 */

#ifndef MDC_CAM_CAMERA_CAMERADECODEDMBUFSERVICEINTERFACE_PROXY_H
#define MDC_CAM_CAMERA_CAMERADECODEDMBUFSERVICEINTERFACE_PROXY_H

#include "ara/com/internal/proxy/proxy_adapter.h"
#include "ara/com/internal/proxy/event_adapter.h"
#include "ara/com/internal/proxy/field_adapter.h"
#include "ara/com/internal/proxy/method_adapter.h"
#include "mdc/cam/camera/cameradecodedmbufserviceinterface_common.h"
#include <string>
#include <cfloat>
#include <cmath>

namespace mdc {
namespace cam {
namespace camera {
namespace proxy {
namespace events {
    using cameraDecodedMbufEvent = ara::com::internal::proxy::event::EventAdapter<::ara::camera::CameraDecodedMbufStruct>;
    static constexpr ara::com::internal::EntityId cameraDecodedMbufEventId = 3920; //cameraDecodedMbufEvent_event_hash
}

namespace fields {
}

namespace methods {

} // namespace methods

class CameraDecodedMbufServiceInterfaceProxy {
private:
	std::unique_ptr<ara::com::internal::proxy::ProxyAdapter> proxyAdapter;
public:
    using HandleType = vrtf::vcc::api::types::HandleType;
    class ConstructionToken {
    public:
        ConstructionToken(std::unique_ptr<ara::com::internal::proxy::ProxyAdapter> proxy): ptr(std::move(proxy)){}
        ConstructionToken(ConstructionToken&& other) : ptr(std::move(other.ptr)) {}
        ConstructionToken& operator=(ConstructionToken && other)
        {
            ptr = std::move(other.ptr);
            return *this;
        }
        ConstructionToken(const ConstructionToken&) = delete;
        ConstructionToken& operator = (const ConstructionToken&) = delete;
        std::unique_ptr<ara::com::internal::proxy::ProxyAdapter> GetProxyAdapter()
        {
            return std::move(ptr);
        }
    private:
        std::unique_ptr<ara::com::internal::proxy::ProxyAdapter> ptr;
    };

    virtual ~CameraDecodedMbufServiceInterfaceProxy()
    {
        cameraDecodedMbufEvent.UnsetReceiveHandler();
        cameraDecodedMbufEvent.Unsubscribe();
    }

    explicit CameraDecodedMbufServiceInterfaceProxy(const vrtf::vcc::api::types::HandleType &handle)
        : proxyAdapter(std::make_unique<ara::com::internal::proxy::ProxyAdapter>(::mdc::cam::camera::CameraDecodedMbufServiceInterface::ServiceIdentifier, handle)),
          cameraDecodedMbufEvent(proxyAdapter->GetProxy(), events::cameraDecodedMbufEventId, proxyAdapter->GetHandle(), ::mdc::cam::camera::CameraDecodedMbufServiceInterface::ServiceIdentifier){
            bool result = true;
            if (result == false) {
#ifndef NOT_SUPPORT_EXCEPTIONS
            ara::core::ErrorCode errorcode(ara::com::ComErrc::kNetworkBindingFailure);
            throw ara::com::ComException(std::move(errorcode));
#else
            std::cerr << "Error: Not support exception, create proxy failed!"<< std::endl;
#endif
            }
        }

    CameraDecodedMbufServiceInterfaceProxy(const CameraDecodedMbufServiceInterfaceProxy&) = delete;
    CameraDecodedMbufServiceInterfaceProxy& operator=(const CameraDecodedMbufServiceInterfaceProxy&) = delete;

    CameraDecodedMbufServiceInterfaceProxy(CameraDecodedMbufServiceInterfaceProxy&& other) = default;
    CameraDecodedMbufServiceInterfaceProxy& operator=(CameraDecodedMbufServiceInterfaceProxy&& other) = default;
    CameraDecodedMbufServiceInterfaceProxy(ConstructionToken&& token) noexcept
        : proxyAdapter(token.GetProxyAdapter()),
          cameraDecodedMbufEvent(proxyAdapter->GetProxy(), events::cameraDecodedMbufEventId, proxyAdapter->GetHandle(), ::mdc::cam::camera::CameraDecodedMbufServiceInterface::ServiceIdentifier){
    }

    static ara::core::Result<ConstructionToken> Preconstruct(
        const vrtf::vcc::api::types::HandleType &handle)
    {
        std::unique_ptr<ara::com::internal::proxy::ProxyAdapter> preProxyAdapter =
            std::make_unique<ara::com::internal::proxy::ProxyAdapter>(
               ::mdc::cam::camera::CameraDecodedMbufServiceInterface::ServiceIdentifier, handle);
        bool result = true;
        if (result == true) {
            ConstructionToken token(std::move(preProxyAdapter));
            return ara::core::Result<ConstructionToken>(std::move(token));	
        } else {
            ConstructionToken token(std::move(preProxyAdapter));
            ara::core::Result<ConstructionToken> result(std::move(token));
            ara::core::ErrorCode errorcode(ara::com::ComErrc::kNetworkBindingFailure);
            result.EmplaceError(errorcode);
            return result;
        }
    }


    static ara::com::FindServiceHandle StartFindService(
        ara::com::FindServiceHandler<ara::com::internal::proxy::ProxyAdapter::HandleType> handler,
        ara::com::InstanceIdentifier instance)
    {
        return ara::com::internal::proxy::ProxyAdapter::StartFindService(handler, ::mdc::cam::camera::CameraDecodedMbufServiceInterface::ServiceIdentifier, instance);
    }

    static ara::com::FindServiceHandle StartFindService(
        ara::com::FindServiceHandler<ara::com::internal::proxy::ProxyAdapter::HandleType> handler,
        ara::core::InstanceSpecifier specifier)
    {
        return ara::com::internal::proxy::ProxyAdapter::StartFindService(handler, ::mdc::cam::camera::CameraDecodedMbufServiceInterface::ServiceIdentifier, specifier);
    }

    static ara::com::ServiceHandleContainer<ara::com::internal::proxy::ProxyAdapter::HandleType> FindService(
        ara::com::InstanceIdentifier instance)
    {
        return ara::com::internal::proxy::ProxyAdapter::FindService(::mdc::cam::camera::CameraDecodedMbufServiceInterface::ServiceIdentifier, instance);
    }

    static ara::com::ServiceHandleContainer<ara::com::internal::proxy::ProxyAdapter::HandleType> FindService(
        ara::core::InstanceSpecifier specifier)
    {
        return ara::com::internal::proxy::ProxyAdapter::FindService(::mdc::cam::camera::CameraDecodedMbufServiceInterface::ServiceIdentifier, specifier);
    }

    static void StopFindService(const ara::com::FindServiceHandle& handle)
    {
        ara::com::internal::proxy::ProxyAdapter::StopFindService(handle);
    }

    HandleType GetHandle() const
    {
        return proxyAdapter->GetHandle();
    }
    events::cameraDecodedMbufEvent cameraDecodedMbufEvent;
};
} // namespace proxy
} // namespace camera
} // namespace cam
} // namespace mdc

#endif // MDC_CAM_CAMERA_CAMERADECODEDMBUFSERVICEINTERFACE_PROXY_H
