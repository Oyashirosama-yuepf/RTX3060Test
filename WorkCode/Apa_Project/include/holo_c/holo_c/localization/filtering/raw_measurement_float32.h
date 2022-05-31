/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file raw_measurement_float32.h
 * @brief This header file defines float32 raw measurement struct of the integrated navigation. The raw measurement
 * includes the ChassisState and Gnss Pvt.
 *
 * @author Lei Gehang (leigehang@holomatic.com)
 * @date Mar 14, 2020
 */

#ifndef HOLO_C_LOCALIZATION_FILTERING_RAW_MEASUREMENT_FLOAT32_H_
#define HOLO_C_LOCALIZATION_FILTERING_RAW_MEASUREMENT_FLOAT32_H_

#include <assert.h>

#include <holo_c/common/chassis_state.h>
#include <holo_c/common/gnss_pvt.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup localization
 * @{
 *
 */

/**
 * @brief This struct defines float32 raw measurement structure of the integrated navigation algorithm
 * @details The struct RawMeasurementf is defined for saving the raw measurements of the integrated navigation
 * algorithm, including the Gnss measurements and ChassisState measurements(Imu measurements). It can be expanded if
 * needed.
 * @attention The data buffer of raw measurement struct must be in time order from early to late.
 */
struct RawMeasurementf
{
    struct ChassisState* chassis_state_data;  ///< The ChassisState measurement buffer
    uint16_t             chassis_state_size;  ///< The size of ChassisState measurement buffer
    struct GnssPvt*      gnss_pvt_data;       ///< The GNSS measurement buffer
    uint16_t             gnss_pvt_size;       ///< The size of GNSS measurement buffer
};

/// check the size of RawMeasurementf with static assert
HOLO_STATIC_ASSERT(sizeof(struct RawMeasurementf) == 32u);

/**
 * @brief Initialize a RawMeasurement struct to empty.
 * @details It means the pointer of the buffers of the RawMeasurements are all NULL and corresponding size are all zero.
 *
 * @param[in, out] self The initialized RawMeasurements struct
 * @return The return code
 */
retcode_t raw_measurementf_init_to_empty(struct RawMeasurementf* self);

/**
 * @brief Initialize a RawMeasurement struct from the GnssPvt array and chassistate array
 *
 * @param[in, out] self The initialized RawMeasurements struct
 * @param[in] gnss_pvt_buffer The GNSSPvt buffer
 * @param[in] gnss_pvt_buffer_size The size of GNSSPvt buffer
 * @param[in] chassisstate_buffer The ChassiState buffer
 * @param[in] chassisstate_buffer_size The size of ChassisState buffer
 * @return The return code
 */
retcode_t raw_measurementf_init(struct RawMeasurementf* self, struct GnssPvt* gnss_pvt_buffer,
                                uint16_t gnss_pvt_buffer_size, struct ChassisState* chassisstate_buffer,
                                uint16_t chassisstate_buffer_size);

/**
 * @brief Initialize a RawMeasurement struct only from the GnssPvt array. The ChassiState may be empty.
 *
 * @param[in, out] self The initialized RawMeasurement struct
 * @param[in] gnss_pvt_buffer The GnssPvt buffer
 * @param[in] gnss_pvt_buffer_size The size of GnssPvt buffer
 * @return The return code
 */
retcode_t raw_measurementf_init_from_gnss_pvt_data(struct RawMeasurementf* self, struct GnssPvt* gnss_pvt_buffer,
                                                   uint16_t gnss_pvt_buffer_size);

/**
 * @brief Initialize a RawMeasurement struct only from the chassistate array. The GnssPvt may be empty.
 *
 * @param[in, out] self The initialized RawMeasurement struct
 * @param[in] chassisstate_buffer The ChassiState buffer
 * @param[in] chassisstate_buffer_size The size of ChassisState buffer
 * @return The return code
 */
retcode_t raw_measurementf_init_from_chassistate_data(struct RawMeasurementf* self,
                                                      struct ChassisState*    chassisstate_buffer,
                                                      uint16_t                chassisstate_buffer_size);

/**
 * @brief Judge if all raw measurements including Gnss and ChassisState is empty
 *
 * @param[in] self The RawMeasurement struct
 * @return It returns true if all raw measurements is empty. Othersize, it returns false
 */
bool_t raw_measurementf_is_all_empty(struct RawMeasurementf const* self);

/**
 * @brief Judge if Gnss measurement is empty
 *
 * @param[in] self The RawMeasurement struct
 * @return It returns true if Gnss measurement is empty. Othersize, it returns false
 */
bool_t raw_measurementf_is_gnss_measurement_empty(struct RawMeasurementf const* self);

/**
 * @brief Judge if ChassisState measurement is empty
 *
 * @param[in] self The RawMeasurement struct
 * @return It returns true if ChassisState measurement is empty. Othersize, it returns false
 */
bool_t raw_measurementf_is_chassis_state_measurement_empty(struct RawMeasurementf const* self);

/**
 * @brief Get number of the Gnss measurement
 *
 * @param[in] self The RawMeasurement struct
 * @return Number of the Gnss measurement
 */
uint16_t raw_measurementf_get_gnss_measurement_size(struct RawMeasurementf const* self);

/**
 * @brief Get number of the ChassisState measurement
 *
 * @param[in] self The RawMeasurement struct
 * @return Number of the ChassisState measurement
 */
uint16_t raw_measurementf_get_chassis_state_measurement_size(struct RawMeasurementf const* self);

/**
 * @brief Get Gnss measurement from raw measurements by index
 *
 * @param[in] self The RawMeasurement struct
 * @param[in] index Data index. The initial index is 0
 * @param[out] gnss_measurement Output Gnss measurement
 * @return The return code
 */
retcode_t raw_measurementf_get_gnss_measurement_by_index(struct RawMeasurementf const* self, uint16_t index,
                                                         struct GnssPvt* gnss_measurement);

/**
 * @brief Get ChassisState measurement from raw measurements by index
 *
 * @param[in] self The RawMeasurement struct
 * @param[in] index Data index. The initial index is 0
 * @param[out] chassis_state_measurement Output ChassisState measurement
 * @return The return code
 */
retcode_t raw_measurementf_get_chassis_state_measurement_by_index(struct RawMeasurementf const* self, uint16_t index,
                                                                  struct ChassisState* chassis_state_measurement);

/**
 * @brief Get the earliest measurement from the raw measurement struct. It may be either Gnss or ChassisState.
 *
 * @param[in] self The RawMeasurement struct
 * @param[out] earliest_measurement The earliest measurement. It may be either Gnss or ChassisState.
 * @return The return code
 */
retcode_t raw_measurementf_get_earliest_measurement(struct RawMeasurementf const* self,
                                                    struct RawMeasurementf*       earliest_measurement);

/**
 * @brief Get the last measurement from the raw measurement struct. It may be either Gnss or ChassisState.
 *
 * @param[in] self The RawMeasurement struct
 * @param[out] last_measurement The last measurement. It may be either Gnss or ChassisState.
 * @return The return code
 */
retcode_t raw_measurementf_get_last_measurement(struct RawMeasurementf const* self,
                                                struct RawMeasurementf*       last_measurement);

/**
 * @brief Get the next measurement from the raw measurement struct after the input timestamp
 *
 * @param[in] self The RawMeasurement struct
 * @param[in] timestamp The given timestamp
 * @param[out] next_measurement The next measurement after input timestamp. It may be either Gnss or ChassisState.
 * @return The return code
 */
retcode_t raw_measurementf_get_next_measurement(struct RawMeasurementf const* self, struct Timestamp const* timestamp,
                                                struct RawMeasurementf* next_measurement);

/**
 * @brief Sort the data of raw measurement by timestamp
 *
 * @param[in] self The raw measurement struct
 * @return The return code
 */
retcode_t raw_measurementf_sort_by_timestamp(struct RawMeasurementf* self);

/**
 * @brief Delete GNSS measurement of a certain index from the raw measurements
 *
 * @param[in] index The target index
 * @param[in, out] self The processed raw measurements
 * @return The return code
 */
retcode_t raw_measurementf_delete_gnss_measurement_by_index(uint16_t index, struct RawMeasurementf* self);

/**
 * @brief Delete ChassisState measurement of a certain index from the raw measurements
 *
 * @param[in] index The target index
 * @param[in, out] self The processed raw measurements
 * @return The return code
 */
retcode_t raw_measurementf_delete_chassis_state_measurement_by_index(uint16_t index, struct RawMeasurementf* self);

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif  // HOLO_C_LOCALIZATION_FILTERING_RAW_MEASUREMENT_FLOAT32_H_
