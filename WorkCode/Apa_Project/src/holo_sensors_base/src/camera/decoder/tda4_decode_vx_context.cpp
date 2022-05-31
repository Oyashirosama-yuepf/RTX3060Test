/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tda4_decode_vx_context.cpp
 * @brief TDA4 Decode VX Context
 * @author zhangruiqiang(zhangruiqiang@holomatic.com).
 * @date 2021-11-12
 */

#include <holo/sensors/camera/decoder/tda4_decode_vx_context.h>

namespace holo
{
namespace sensors
{
namespace camera
{
std::mutex Tda4DecodeVxContext::mutex_;
int32_t    Tda4DecodeVxContext::refnum_;
vx_context Tda4DecodeVxContext::context_;

Tda4DecodeVxContext::Tda4DecodeVxContext(uint16_t refnum)
{
    std::lock_guard<std::mutex> guard(mutex_);
    if (refnum_ == 0)
    {
        if (appCommonInit() != 0)
        {
            std::string info = "tda4 vx context: app common init failed";
            LOG(ERROR) << info;
            throw std::runtime_error(info);
        }
        tivxInit();
        tivxHostInit();
        context_ = vxCreateContext();
        tivxHwaLoadKernels(context_);
        refnum_ += refnum;
        return;
    }
    if (refnum_ + refnum >= 4)
    {
        std::string info = "tda4 vx context: refnum = " + std::to_string(refnum_);
        LOG(ERROR) << info;
        throw std::runtime_error(info);
    }
    refnum_ += refnum;
}

vx_context Tda4DecodeVxContext::GetContext() const noexcept
{
    return context_;
}

Tda4DecodeVxContext::~Tda4DecodeVxContext()
{
    std::lock_guard<std::mutex> guard(mutex_);
    if (--refnum_ == 0)
    {
        tivxHwaUnLoadKernels(context_);
        vxReleaseContext(&context_);
        context_ = nullptr;
        tivxHostDeInit();
        tivxDeInit();
        appCommonDeInit();
    }
}

}  // namespace camera
}  // namespace sensors
}  // namespace holo