/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file common.h
 * @brief This header file defines common data types used by opendds wrapper.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-08
 */

#ifndef OPENDDS_WRAPPER_DETAILS_COMMON_H_
#define OPENDDS_WRAPPER_DETAILS_COMMON_H_

#include <opendds_wrapper/builtin/BuiltinC.h>
#include <opendds_wrapper/builtin/BuiltinS.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportC.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportImpl.h>
#include <opendds_wrapper/builtin/BuiltinTypeSupportS.h>

#include "traits.h"

namespace opendds_wrapper
{
namespace details
{

struct TopicDescription
{
    std::string topic_name;
    std::string type_name;
};

struct Duration
{
    int32_t  sec;
    uint32_t nsec;
};

template <typename V, typename Traits>
class Reader;

template <typename V, typename Traits>
class Writer;

struct BuiltinMessage
{
    using Uint8          = ::opendds_wrapper::BuiltinUint8;
    using Uint16         = ::opendds_wrapper::BuiltinUint16;
    using Uint32         = ::opendds_wrapper::BuiltinUint32;
    using Uint64         = ::opendds_wrapper::BuiltinUint64;
    using Float32        = ::opendds_wrapper::BuiltinFloat32;
    using Float64        = ::opendds_wrapper::BuiltinFloat64;
    using String         = ::opendds_wrapper::BuiltinString;
    using Buffer         = ::opendds_wrapper::BuiltinBuffer;
};

}
}

#endif
