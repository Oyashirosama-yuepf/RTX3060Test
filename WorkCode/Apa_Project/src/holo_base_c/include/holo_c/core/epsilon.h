/*!
 *  \brief This header file defines epsilon values for float and double.
 *  \author zhangjiannan(zhangjiannan@holomaitc.com)
 *  \date 2018-1-7
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_C_CORE_EPSILON_H_
#define HOLO_C_CORE_EPSILON_H_

#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

static const float32_t holo_float32_epsilon = 1e-6f;
static const float64_t holo_float64_epsilon = 1e-6;

#ifdef __cplusplus
}
#endif

#endif
