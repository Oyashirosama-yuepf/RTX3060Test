/*!
 *  \brief This header file defines basic data types for holo projects.
 *  \author zhangjiannan(zhangjiannan@holomaitc.com)
 *  \date 2018-12-23
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_C_CORE_TYPES_H_
#define HOLO_C_CORE_TYPES_H_

#include <holo_c/core/static_assert.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef float   float32_t;
typedef double  float64_t;
typedef int32_t retcode_t;
typedef bool    bool_t;
typedef char    char_t;

typedef unsigned char ubyte;
typedef unsigned int  uword;

HOLO_STATIC_ASSERT(sizeof(float32_t) == 4);
HOLO_STATIC_ASSERT(sizeof(float64_t) == 8);

#ifdef __cplusplus
}
#endif

#endif
