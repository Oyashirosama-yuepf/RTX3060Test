/*!
 * \brief This header file define 3d point.
 * \author zhangjiannan(zhangjiannan@holomaitc.com)
 * \date 2018-1-7
 * \attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_CORE_CONFIG_H_
#define HOLO_C_CORE_CONFIG_H_

#ifdef __cplusplus
extern "C" {
#endif

/* SERIALIZATION/DESERIALIZATION */

#define HOLO_CONFIG_SERIALIZATION_ALIGNMENT 4

/*-------------------NUMERICS-------------------*/
#define HOLO_NUMERICS_MATRIX_MAX_ROWS 100u
#define HOLO_NUMERICS_MATRIX_MAX_COLS 100u
#define HOLO_NUMERICS_MATRIX_MAX_SIZE (HOLO_NUMERICS_MATRIX_MAX_ROWS * HOLO_NUMERICS_MATRIX_MAX_COLS)
#define HOLO_NUMERICS_VECTOR_MAX_ROWS HOLO_NUMERICS_MATRIX_MAX_ROWS

#ifdef __cplusplus
}
#endif

#endif
