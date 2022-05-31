/*!
 * @file predefine.h
 * @brief Redefine system macro to holo macro.
 * @author Zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-09-12"
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_OS_PREDEFINE_H_
#define HOLO_OS_PREDEFINE_H_

namespace holo
{
namespace os
{
/**
 * @def HOLO_PLATFORM_LINUX
 * @brief Redefine LINUX system indicator macro to holo macro, it will be used when we use system function
 *
 * @def HOLO_PLATFORM_QNX
 * @brief Redefine QNX system indicator macro to holo macro, it will be used when we use system function
 */
#ifdef __linux__
#define HOLO_PLATFORM_LINUX
#elif __QNX__
#define HOLO_PLATFORM_QNX
#else
error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif
}  // namespace os
}  // namespace holo

#endif  // HOLO_OS_PREDEFINE_H_
