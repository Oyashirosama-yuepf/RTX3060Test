/*!
 *  \brief This header file defines basic data types for holo projects.
 *  \author zhangjiannan(zhangjiannan@holomaitc.com)
 *  \date 2019-1-2
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#ifndef HOLO_C_CORE_STATIC_ASSERT_H_
#define HOLO_C_CORE_STATIC_ASSERT_H_

#ifdef __cplusplus
extern "C" {
#endif

#ifndef __cplusplus
#define HOLO_STATIC_ASSERT(EXPR)                                                                                       \
    extern int32_t(*build_assert(void))[sizeof(struct { uint32_t build_assert_failed : (EXPR) ? 1 : -1; })]
#else /* __cplusplus */
#define HOLO_STATIC_ASSERT(_EXPR) typedef int build_assert_failed[(_EXPR) ? 1 : -1]
#endif /* __cplusplus */

#ifdef __cplusplus
}
#endif

#endif
