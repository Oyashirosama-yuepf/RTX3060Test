/*!
 * @file conti_radar_object.h
 * @brief This header file defines conti radar objcet raw data structure and api functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_CONTI_RADAR_STRUCTURE_CONTI_RADAR_OBJECT_H_
#define HOLO_C_SENSORS_CONTI_RADAR_STRUCTURE_CONTI_RADAR_OBJECT_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup sensors
 * @{
 *
 */

struct ContiRadarObjectRawData
{
    struct Timestamp timestamp;

    uint16_t id;
    uint16_t classification;
    uint16_t meas_state;
    uint16_t prob_of_exist;
    uint16_t rcs;

    uint16_t length;
    uint16_t width;

    uint16_t dyn_prop;
    uint16_t dist_lon;
    uint16_t dist_lat;
    uint16_t vrel_lon;
    uint16_t vrel_lat;
    uint16_t arel_lon;
    uint16_t arel_lat;
    uint16_t orientation_angle;
    uint16_t dist_lon_rms;
    uint16_t dist_lat_rms;
    uint16_t vrel_lon_rms;
    uint16_t vrel_lat_rms;
    uint16_t arel_lon_rms;
    uint16_t arel_lat_rms;
    uint16_t orientation_angle_rms;
};
HOLO_STATIC_ASSERT(sizeof(struct ContiRadarObjectRawData) == 52);

struct ContiRadarObjectListRawData
{
    uint32_t                       num;
    struct ContiRadarObjectRawData objects[100];
};

/**
 * @{
 * Begin Setter API group
 *
 */

/**
 * @brief set conti radar object list num
 *
 * @param obj_list conti radar object raw data
 * @param num object num
 */
static inline void conti_radar_object_list_raw_data_set_num(struct ContiRadarObjectListRawData* obj_list,
                                                            const uint32_t                      num)
{
    obj_list->num = num;
}

/**
 * @brief set conti radar object raw data timestamp
 *
 * @param raw_data conti radar object raw data pointer
 * @param timestamp system timestamp
 */
static inline void conti_radar_object_raw_data_set_timestamp(struct ContiRadarObjectRawData* raw_data,
                                                             const struct Timestamp          timestamp)
{
    raw_data->timestamp = timestamp;
}

/**
 * @brief set conti radar object id raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param id object id
 */
static inline void conti_radar_object_raw_data_set_id(struct ContiRadarObjectRawData* raw_data, uint16_t id)
{
    raw_data->id = id;
}

/**
 * @brief set conti radar object classification raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param classification object classification
 */
static inline void conti_radar_object_raw_data_set_classification(struct ContiRadarObjectRawData* raw_data,
                                                                  uint16_t                        classification)
{
    raw_data->classification = classification;
}

/**
 * @brief set conti radar object meas state raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param meas_state object meas state
 */
static inline void conti_radar_object_raw_data_set_meas_state(struct ContiRadarObjectRawData* raw_data,
                                                              uint16_t                        meas_state)
{
    raw_data->meas_state = meas_state;
}

/**
 * @brief set conti radar object exist prob raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param prob_of_exist object exist prob
 */
static inline void conti_radar_object_raw_data_set_prob_of_exist(struct ContiRadarObjectRawData* raw_data,
                                                                 uint16_t                        prob_of_exist)
{
    raw_data->prob_of_exist = prob_of_exist;
}

/**
 * @brief set conti radar object rcs raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param rcs object rcs
 */
static inline void conti_radar_object_raw_data_set_rcs(struct ContiRadarObjectRawData* raw_data, uint16_t rcs)
{
    raw_data->rcs = rcs;
}

/**
 * @brief set conti radar object length raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param length object length
 */
static inline void conti_radar_object_raw_data_set_length(struct ContiRadarObjectRawData* raw_data, uint16_t length)
{
    raw_data->length = length;
}

/**
 * @brief set conti radar object width raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param width object width
 */
static inline void conti_radar_object_raw_data_set_width(struct ContiRadarObjectRawData* raw_data, uint16_t width)
{
    raw_data->width = width;
}

/**
 * @brief set conti radar object dyn prop raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param dyn_prop object dyn prop
 */
static inline void conti_radar_object_raw_data_set_dyn_prop(struct ContiRadarObjectRawData* raw_data, uint16_t dyn_prop)
{
    raw_data->dyn_prop = dyn_prop;
}

/**
 * @brief set conti radar object lon dist raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param dist_lon object lon dist
 */
static inline void conti_radar_object_raw_data_set_dist_lon(struct ContiRadarObjectRawData* raw_data, uint16_t dist_lon)
{
    raw_data->dist_lon = dist_lon;
}

/**
 * @brief set conti radar object lat dist raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param dist_lat object lat dist
 */
static inline void conti_radar_object_raw_data_set_dist_lat(struct ContiRadarObjectRawData* raw_data, uint16_t dist_lat)
{
    raw_data->dist_lat = dist_lat;
}

/**
 * @brief set conti radar object lon vrel raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param vrel_lon object lon vrel
 */
static inline void conti_radar_object_raw_data_set_vrel_lon(struct ContiRadarObjectRawData* raw_data, uint16_t vrel_lon)
{
    raw_data->vrel_lon = vrel_lon;
}

/**
 * @brief set conti radar object lat vrel raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param vrel_lat object lat vrel
 */
static inline void conti_radar_object_raw_data_set_vrel_lat(struct ContiRadarObjectRawData* raw_data, uint16_t vrel_lat)
{
    raw_data->vrel_lat = vrel_lat;
}

/**
 * @brief set conti radar object lon arel raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param arel_lon object lon arel
 */
static inline void conti_radar_object_raw_data_set_arel_lon(struct ContiRadarObjectRawData* raw_data, uint16_t arel_lon)
{
    raw_data->arel_lon = arel_lon;
}

/**
 * @brief set conti radar object lat arel raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param arel_lat object lat arel
 */
static inline void conti_radar_object_raw_data_set_arel_lat(struct ContiRadarObjectRawData* raw_data, uint16_t arel_lat)
{
    raw_data->arel_lat = arel_lat;
}

/**
 * @brief set conti radar object orientation angle raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param orientation_angle object orientation angle
 */
static inline void conti_radar_object_raw_data_set_orientation_angle(struct ContiRadarObjectRawData* raw_data,
                                                                     uint16_t                        orientation_angle)
{
    raw_data->orientation_angle = orientation_angle;
}

/**
 * @brief set conti radar object lon dist rms raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param dist_lon_rms object lon dist rms
 */
static inline void conti_radar_object_raw_data_set_dist_lon_rms(struct ContiRadarObjectRawData* raw_data,
                                                                uint16_t                        dist_lon_rms)
{
    raw_data->dist_lon_rms = dist_lon_rms;
}

/**
 * @brief set conti radar object lat dist rms raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param dist_lat_rms object lat dist rms
 */
static inline void conti_radar_object_raw_data_set_dist_lat_rms(struct ContiRadarObjectRawData* raw_data,
                                                                uint16_t                        dist_lat_rms)
{
    raw_data->dist_lat_rms = dist_lat_rms;
}

/**
 * @brief set conti radar object lon vrel rms raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param vrel_lon_rms object lon vrel rms
 */
static inline void conti_radar_object_raw_data_set_vrel_lon_rms(struct ContiRadarObjectRawData* raw_data,
                                                                uint16_t                        vrel_lon_rms)
{
    raw_data->vrel_lon_rms = vrel_lon_rms;
}

/**
 * @brief set conti radar object lat vrel rms raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param vrel_lat_rms object lat vrel rms
 */
static inline void conti_radar_object_raw_data_set_vrel_lat_rms(struct ContiRadarObjectRawData* raw_data,
                                                                uint16_t                        vrel_lat_rms)
{
    raw_data->vrel_lat_rms = vrel_lat_rms;
}

/**
 * @brief set conti radar object lon arel rms raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param arel_lon_rms object lat arel rms
 */
static inline void conti_radar_object_raw_data_set_arel_lon_rms(struct ContiRadarObjectRawData* raw_data,
                                                                uint16_t                        arel_lon_rms)
{
    raw_data->arel_lon_rms = arel_lon_rms;
}

/**
 * @brief set conti radar object lat arel rms raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param arel_lat_rms object lat arel rms
 */
static inline void conti_radar_object_raw_data_set_arel_lat_rms(struct ContiRadarObjectRawData* raw_data,
                                                                uint16_t                        arel_lat_rms)
{
    raw_data->arel_lat_rms = arel_lat_rms;
}

/**
 * @brief set conti radar object orientation angle rms raw data
 *
 * @param raw_data conti radar raw data pointer
 * @param orientation_angle_rms object orientation angle rms
 */
static inline void conti_radar_object_raw_data_set_orientation_angle_rms(struct ContiRadarObjectRawData* raw_data,
                                                                         uint16_t orientation_angle_rms)
{
    raw_data->orientation_angle_rms = orientation_angle_rms;
}

/**
 * @}
 * End Setter API group
 *
 */

/**
 * @{
 * Begin Getter API group
 *
 */

/**
 * @brief get conti radar object list num
 *
 * @param obj_list conti radar object raw data
 * @return uint32_t object num
 */
static inline uint32_t conti_radar_object_list_raw_data_get_num(struct ContiRadarObjectListRawData* obj_list)
{
    return obj_list->num;
}

/**
 * @brief get conti radar object raw data timestamp
 *
 * @param raw_data conti radar object raw data pointer
 * @param timestamp timestamp pointer
 * @return retcode_t RC_SUCCESS
 */
static inline struct Timestamp* conti_radar_object_raw_data_get_timestamp(struct ContiRadarObjectRawData* raw_data)
{
    return &raw_data->timestamp;
}

/**
 * @brief get conti radar id raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object id raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_id(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->id;
}

/**
 * @brief get conti radar classification raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object classification raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_classification(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->classification;
}

/**
 * @brief get conti radar meas state raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object meas state raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_meas_state(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->meas_state;
}

/**
 * @brief get conti radar exist prob raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object exist prob raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_prob_of_exist(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->prob_of_exist;
}

/**
 * @brief get conti radar rcs raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object rcs raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_rcs(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->rcs;
}

/**
 * @brief get conti radar length raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object length raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_length(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->length;
}

/**
 * @brief get conti radar width raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object width raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_width(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->width;
}

/**
 * @brief get conti radar dyn prop raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object dyn prop raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_dyn_prop(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->dyn_prop;
}

/**
 * @brief get conti radar dist lon raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object dist lon raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_dist_lon(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->dist_lon;
}

/**
 * @brief get conti radar dist lat raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object dist lat raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_dist_lat(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->dist_lat;
}

/**
 * @brief get conti radar vrel lon raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object vrel lon raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_vrel_lon(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->vrel_lon;
}

/**
 * @brief get conti radar vrel lat raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object vrel lat raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_vrel_lat(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->vrel_lat;
}

/**
 * @brief get conti radar arel lon raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object arel lon raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_arel_lon(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->arel_lon;
}

/**
 * @brief get conti radar arel lat raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object arel lat raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_arel_lat(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->arel_lat;
}

/**
 * @brief get conti radar orientation angle raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object orientation angle raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_orientation_angle(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->orientation_angle;
}

/**
 * @brief get conti radar dist lon rms raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object dist lon rms raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_dist_lon_rms(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->dist_lon_rms;
}

/**
 * @brief get conti radar dist lat rms raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object dist lat rms raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_dist_lat_rms(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->dist_lat_rms;
}

/**
 * @brief get conti radar arel lon rms raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object vrel lon rms raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_vrel_lon_rms(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->vrel_lon_rms;
}

/**
 * @brief get conti radar arel lat rms raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object vrel lat rms raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_vrel_lat_rms(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->vrel_lat_rms;
}

/**
 * @brief get conti radar arel lon rms raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object arel lon rms raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_arel_lon_rms(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->arel_lon_rms;
}

/**
 * @brief get conti radar arel lat rms raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object arel lat rms raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_arel_lat_rms(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->arel_lat_rms;
}

/**
 * @brief get conti radar orientation angle rms raw data
 *
 * @param raw_data conti radar object raw data pointer
 * @return uint16_t object orientation angle rms raw data
 */
static inline uint16_t conti_radar_object_raw_data_get_orientation_angle_rms(struct ContiRadarObjectRawData* raw_data)
{
    return raw_data->orientation_angle_rms;
}

/**
 * @}
 * End Getter API group
 *
 */

/**
 * @brief Construct conti radar object raw data part1.
 *
 * @param raw_data The conti radar object raw data.
 * @param msg Conti radar can message.
 */
void conti_radar_object_raw_data_construct_part1(struct ContiRadarObjectRawData* raw_data, const uint8_t* msg);

/**
 * @brief Construct conti radar object raw data part2.
 *
 * @param raw_data The conti radar object raw data.
 * @param msg Conti radar can message.
 */
void conti_radar_object_raw_data_construct_part2(struct ContiRadarObjectRawData* raw_data, const uint8_t* msg);

/**
 * @brief Construct conti radar object raw data part3.
 *
 * @param raw_data The conti radar object raw data.
 * @param msg Conti radar can message.
 */
void conti_radar_object_raw_data_construct_part3(struct ContiRadarObjectRawData* raw_data, const uint8_t* msg);

/**
 * @brief Get 4byte aligned serialized buffer size for conti radar object list raw data.
 *
 * @param position The raw_data conti radar object list raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see conti_radar_object_list_raw_data_get_serialized_size_8byte_aligned.
 */
uint32_t
conti_radar_object_list_raw_data_get_serialized_size_4byte_aligned(const struct ContiRadarObjectListRawData* raw_data);

/**
 * @brief Get 8byte aligned serialized buffer size for conti radar object list raw data.
 *
 * @param position The raw_data conti radar object list raw data.
 *
 * @return uint32_t Serialized size.
 *
 * @see conti_radar_object_list_raw_data_get_serialized_size_8byte_aligned.
 */
uint32_t
conti_radar_object_list_raw_data_get_serialized_size_8byte_aligned(const struct ContiRadarObjectListRawData* raw_data);

/**
 * @brief Default interface get conti radar object list raw data serialized buffer size.
 *
 * @param position The raw_data conti radar object list raw data.
 *
 * @return uint32_t Serialized size.
 *
 */
uint32_t conti_radar_object_list_raw_data_get_serialized_size(const struct ContiRadarObjectListRawData* raw_data);

/**
 * @brief Serialize conti radar object list raw data 4byte aligned.
 *
 * @param raw_data The conti radar object list raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see conti_radar_object_list_raw_data_serialize_8byte_aligned.
 */
int32_t conti_radar_object_list_raw_data_serialize_4byte_aligned(const struct ContiRadarObjectListRawData* raw_data,
                                                                 uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Serialize conti radar object list raw data 8byte aligned.
 *
 * @param raw_data The conti radar object list raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 * @see conti_radar_object_list_raw_data_serialize_4byte_aligned.
 */
int32_t conti_radar_object_list_raw_data_serialize_8byte_aligned(const struct ContiRadarObjectListRawData* raw_data,
                                                                 uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Default interface serialize conti radar object list raw data.
 *
 * @param raw_data The conti radar object list raw data.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return retcode_t Positive interger Number of bytes serialized into buffer.
 *
 */
int32_t conti_radar_object_list_raw_data_serialize(const struct ContiRadarObjectListRawData* raw_data, uint8_t* buffer,
                                                   uint32_t buffer_size);

/**
 * @brief Deserialize conti radar object list raw data 4byte aligned.
 *
 * @param raw_data The conti radar object list raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see gnss_position_deserialize_8byte_aligned.
 */
int32_t conti_radar_object_list_raw_data_deserialize_4byte_aligned(struct ContiRadarObjectListRawData* raw_data,
                                                                   const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize conti radar object list raw data 8byte aligned.
 *
 * @param raw_data The conti radar object list raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 * @see conti_radar_object_list_raw_data_deserialize_4byte_aligned.
 */
int32_t conti_radar_object_list_raw_data_deserialize_8byte_aligned(struct ContiRadarObjectListRawData* raw_data,
                                                                   const uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Default interface deserialize conti radar object list raw data.
 *
 * @param raw_data The conti radar object list raw data object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return retcode_t RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return retcode_t Positive integer Number of bytes deserialized from buffer.
 *
 */
int32_t conti_radar_object_list_raw_data_deserialize(struct ContiRadarObjectListRawData* raw_data,
                                                     const uint8_t* buffer, uint32_t buffer_size);

/**
 * @}
 *
 */

#ifdef __cplusplus
}
#endif

#endif
