/*!
 * @brief Unit test for conti radar driver.
 * @author liuya@holomaitc.com
 * @date 2019-9-25
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/sensors/dbc/conti_radar_dbc.h>
#include <holo_c/sensors/conti_radar/conti_radar_driver.h>
#include <holo_c/utils/serialization.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unity.h>

struct CanMessage
{
    uint32_t id;
    uint8_t  len;
    uint8_t  data[8];
};

struct CanMessage conti_radar_error_msg;
struct CanMessage conti_radar_part0_msg;
struct CanMessage conti_radar_part1_msg[CONTI_RADAR_OBJECT_NUM];
struct CanMessage conti_radar_part2_msg[CONTI_RADAR_OBJECT_NUM];
struct CanMessage conti_radar_part3_msg[CONTI_RADAR_OBJECT_NUM];

static struct ContiRadarDriver driver;

static void init_radar_can_msg(void)
{
    uint8_t i;

    conti_radar_error_msg.id  = 0xFF;
    conti_radar_error_msg.len = 8;

    conti_radar_part0_msg.id      = ID_Object_0_Status;
    conti_radar_part0_msg.len     = 8;
    conti_radar_part0_msg.data[0] = 0x64;
    conti_radar_part0_msg.data[1] = 0x00;
    conti_radar_part0_msg.data[2] = 0x00;
    conti_radar_part0_msg.data[3] = 0x00;
    conti_radar_part0_msg.data[4] = 0x00;
    conti_radar_part0_msg.data[5] = 0x00;
    conti_radar_part0_msg.data[6] = 0x00;
    conti_radar_part0_msg.data[7] = 0x00;

    for (i = 0; i < CONTI_RADAR_OBJECT_NUM; i++)
    {
        conti_radar_part1_msg[i].id      = ID_Object_1_General;
        conti_radar_part1_msg[i].len     = 8;
        conti_radar_part1_msg[i].data[0] = i;
        conti_radar_part1_msg[i].data[1] = 0x4F;
        conti_radar_part1_msg[i].data[2] = 0x63;
        conti_radar_part1_msg[i].data[3] = 0xF0;
        conti_radar_part1_msg[i].data[4] = 0x94;
        conti_radar_part1_msg[i].data[5] = 0x21;
        conti_radar_part1_msg[i].data[6] = 0xC7;
        conti_radar_part1_msg[i].data[7] = 0x7F;

        conti_radar_part2_msg[i].id      = ID_Object_2_Quality;
        conti_radar_part2_msg[i].len     = 8;
        conti_radar_part2_msg[i].data[0] = i;
        conti_radar_part2_msg[i].data[1] = 0x3A;
        conti_radar_part2_msg[i].data[2] = 0x02;
        conti_radar_part2_msg[i].data[3] = 0x24;
        conti_radar_part2_msg[i].data[4] = 0x84;
        conti_radar_part2_msg[i].data[5] = 0x80;
        conti_radar_part2_msg[i].data[6] = 0x74;
        conti_radar_part2_msg[i].data[7] = 0x00;

        conti_radar_part3_msg[i].id      = ID_Object_3_Extended;
        conti_radar_part3_msg[i].len     = 8;
        conti_radar_part3_msg[i].data[0] = i;
        conti_radar_part3_msg[i].data[1] = 0xAA;
        conti_radar_part3_msg[i].data[2] = 0x14;
        conti_radar_part3_msg[i].data[3] = 0xA3;
        conti_radar_part3_msg[i].data[4] = 0x76;
        conti_radar_part3_msg[i].data[5] = 0x80;
        conti_radar_part3_msg[i].data[6] = 0x0F;
        conti_radar_part3_msg[i].data[7] = 0x07;
    }
}

static void test_conti_radar_driver_init(void)
{
    TEST_ASSERT_EQUAL(RC_SUCCESS, conti_radar_driver_init(&driver));
    TEST_ASSERT_EQUAL_INT64(0, driver.object_list.num);

    conti_radar_object_list_raw_data_set_num(&driver.object_list, 20);
    TEST_ASSERT_EQUAL_INT(20, conti_radar_object_list_raw_data_get_num(&driver.object_list));
}

static void test_conti_radar_process_data(void)
{
    uint8_t  i;
    uint16_t raw_data = 0;

    time_t           utc_seconds;
    struct Timestamp sys_time;
    struct Timestamp raw_data_timestamp;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    for (i = 0; i < 100; i++)
    {
        TEST_ASSERT_EQUAL_INT64(RC_PARSE_CONTI_RADAR_CONTINUE,
                                conti_radar_driver_process_data(&driver, sys_time, 0, conti_radar_part1_msg[i].id,
                                                                conti_radar_part1_msg[i].data,
                                                                conti_radar_part1_msg[i].len));

        TEST_ASSERT_EQUAL_INT64(RC_PARSE_CONTI_RADAR_CONTINUE,
                                conti_radar_driver_process_data(&driver, sys_time, 0, conti_radar_part2_msg[i].id,
                                                                conti_radar_part2_msg[i].data,
                                                                conti_radar_part2_msg[i].len));

        TEST_ASSERT_EQUAL_INT64(RC_PARSE_CONTI_RADAR_CONTINUE,
                                conti_radar_driver_process_data(&driver, sys_time, 0, conti_radar_part3_msg[i].id,
                                                                conti_radar_part3_msg[i].data,
                                                                conti_radar_part3_msg[i].len));
    }

    TEST_ASSERT_EQUAL_INT64(RC_SUCCESS,
                            conti_radar_driver_process_data(&driver, sys_time, 0, conti_radar_part0_msg.id,
                                                            conti_radar_part0_msg.data, conti_radar_part0_msg.len));

    TEST_ASSERT_EQUAL_HEX16(100, driver.object_list.num);

    for (i = 0; i < 100; i++)
    {
        timestamp_init_from_timestamp(&raw_data_timestamp,
                                      conti_radar_object_raw_data_get_timestamp(&driver.object_list.objects[i]));
        TEST_ASSERT_EQUAL_HEX64(sys_time.nsec, raw_data_timestamp.nsec);

        raw_data = conti_radar_object_raw_data_get_id(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(i, raw_data);

        raw_data = conti_radar_object_raw_data_get_dist_lon(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x9EC, raw_data);

        raw_data = conti_radar_object_raw_data_get_dist_lat(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x3F0, raw_data);

        raw_data = conti_radar_object_raw_data_get_vrel_lon(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x250, raw_data);

        raw_data = conti_radar_object_raw_data_get_vrel_lat(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x10E, raw_data);

        raw_data = conti_radar_object_raw_data_get_dyn_prop(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x07, raw_data);

        raw_data = conti_radar_object_raw_data_get_rcs(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x7F, raw_data);

        raw_data = conti_radar_object_raw_data_get_dist_lon_rms(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x07, raw_data);

        raw_data = conti_radar_object_raw_data_get_dist_lat_rms(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x08, raw_data);

        raw_data = conti_radar_object_raw_data_get_vrel_lon_rms(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x01, raw_data);

        raw_data = conti_radar_object_raw_data_get_vrel_lat_rms(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x02, raw_data);

        raw_data = conti_radar_object_raw_data_get_arel_lon_rms(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x09, raw_data);

        raw_data = conti_radar_object_raw_data_get_arel_lat_rms(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x01, raw_data);

        raw_data = conti_radar_object_raw_data_get_orientation_angle_rms(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x04, raw_data);

        raw_data = conti_radar_object_raw_data_get_meas_state(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x05, raw_data);

        raw_data = conti_radar_object_raw_data_get_prob_of_exist(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x03, raw_data);

        raw_data = conti_radar_object_raw_data_get_arel_lon(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x550, raw_data);

        raw_data = conti_radar_object_raw_data_get_arel_lat(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x14A, raw_data);

        raw_data = conti_radar_object_raw_data_get_classification(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x03, raw_data);

        raw_data = conti_radar_object_raw_data_get_orientation_angle(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x1DA, raw_data);

        raw_data = conti_radar_object_raw_data_get_length(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x0F, raw_data);

        raw_data = conti_radar_object_raw_data_get_width(&driver.object_list.objects[i]);
        TEST_ASSERT_EQUAL_HEX16(0x07, raw_data);
    }
}

static void test_conti_radar_object_raw_data_serialize_and_deserialize_4byte_aligned(void)
{
    const uint16_t                     buf_size       = 5204;
    const uint16_t                     error_buf_size = 5200;
    uint8_t                            i;
    uint8_t                            buffer[5204];
    struct ContiRadarObjectListRawData obj_list_raw_data;

    memset(buffer, 0, buf_size);

    TEST_ASSERT_EQUAL_UINT64(buf_size,
                             conti_radar_object_list_raw_data_get_serialized_size_4byte_aligned(&driver.object_list));

    TEST_ASSERT_EQUAL_INT64(RC_SERIALIZATION_BUFFER_OVERFLOW, conti_radar_object_list_raw_data_serialize_4byte_aligned(
                                                                  &driver.object_list, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT64(
        buf_size, conti_radar_object_list_raw_data_serialize_4byte_aligned(&driver.object_list, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT64(
        RC_DESERIALIZATION_BUFFER_UNDERFLOW,
        conti_radar_object_list_raw_data_deserialize_4byte_aligned(&obj_list_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT64(
        buf_size, conti_radar_object_list_raw_data_deserialize_4byte_aligned(&obj_list_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_HEX16(driver.object_list.num, obj_list_raw_data.num);

    for (i = 0; i < driver.object_list.num; i++)
    {
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_id(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_id(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_classification(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_classification(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_meas_state(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_meas_state(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_prob_of_exist(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_prob_of_exist(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_length(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_length(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_width(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_width(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dyn_prop(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dyn_prop(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dist_lon(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dist_lon(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_vrel_lat(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_vrel_lat(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lon(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lon(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lat(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lat(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_orientation_angle(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_orientation_angle(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dist_lon_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dist_lon_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dist_lat_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dist_lat_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_vrel_lon_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_vrel_lon_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_vrel_lat_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_vrel_lat_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lon_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lon_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lat_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lat_rms(&obj_list_raw_data.objects[i]));
    }
}

static void test_conti_radar_object_raw_data_serialize_and_deserialize_8byte_aligned(void)
{
    const uint16_t                     buf_size       = 5208;
    const uint16_t                     error_buf_size = 5200;
    uint8_t                            i;
    uint8_t                            buffer[5208];
    struct ContiRadarObjectListRawData obj_list_raw_data;

    memset(buffer, 0, buf_size);

    TEST_ASSERT_EQUAL_UINT64(buf_size,
                             conti_radar_object_list_raw_data_get_serialized_size_8byte_aligned(&driver.object_list));

    TEST_ASSERT_EQUAL_INT64(RC_SERIALIZATION_BUFFER_OVERFLOW, conti_radar_object_list_raw_data_serialize_8byte_aligned(
                                                                  &driver.object_list, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT64(
        buf_size, conti_radar_object_list_raw_data_serialize_8byte_aligned(&driver.object_list, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT64(
        RC_DESERIALIZATION_BUFFER_UNDERFLOW,
        conti_radar_object_list_raw_data_deserialize_8byte_aligned(&obj_list_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT64(
        buf_size, conti_radar_object_list_raw_data_deserialize_8byte_aligned(&obj_list_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_HEX16(driver.object_list.num, obj_list_raw_data.num);

    for (i = 0; i < driver.object_list.num; i++)
    {
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_id(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_id(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_classification(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_classification(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_meas_state(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_meas_state(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_prob_of_exist(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_prob_of_exist(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_length(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_length(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_width(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_width(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dyn_prop(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dyn_prop(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dist_lon(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dist_lon(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_vrel_lat(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_vrel_lat(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lon(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lon(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lat(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lat(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_orientation_angle(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_orientation_angle(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dist_lon_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dist_lon_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dist_lat_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dist_lat_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_vrel_lon_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_vrel_lon_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_vrel_lat_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_vrel_lat_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lon_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lon_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lat_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lat_rms(&obj_list_raw_data.objects[i]));
    }
}

static void test_conti_radar_failure_case(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    TEST_ASSERT_EQUAL_INT64(RC_PARSE_CONTI_RADAR_ID_ERROR,
                            conti_radar_driver_process_data(&driver, sys_time, 0, conti_radar_error_msg.id,
                                                            conti_radar_error_msg.data, conti_radar_error_msg.len));
}

void test_conti_radar_object_raw_data_serialize_and_deserialize_default(void)
{
    const uint16_t                     buf_size       = 5204;
    const uint16_t                     error_buf_size = 5200;
    uint8_t                            i;
    uint8_t                            buffer[5204];
    struct ContiRadarObjectListRawData obj_list_raw_data;

    memset(buffer, 0, buf_size);

    TEST_ASSERT_EQUAL_UINT64(buf_size, conti_radar_object_list_raw_data_get_serialized_size(&driver.object_list));

    TEST_ASSERT_EQUAL_INT64(RC_SERIALIZATION_BUFFER_OVERFLOW,
                            conti_radar_object_list_raw_data_serialize(&driver.object_list, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT64(buf_size,
                            conti_radar_object_list_raw_data_serialize(&driver.object_list, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT64(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                            conti_radar_object_list_raw_data_deserialize(&obj_list_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT64(buf_size,
                            conti_radar_object_list_raw_data_deserialize(&obj_list_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_HEX16(driver.object_list.num, obj_list_raw_data.num);

    for (i = 0; i < driver.object_list.num; i++)
    {
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_id(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_id(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_classification(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_classification(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_meas_state(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_meas_state(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_prob_of_exist(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_prob_of_exist(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_length(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_length(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_width(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_width(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dyn_prop(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dyn_prop(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dist_lon(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dist_lon(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_vrel_lat(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_vrel_lat(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lon(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lon(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lat(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lat(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_orientation_angle(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_orientation_angle(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dist_lon_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dist_lon_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_dist_lat_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_dist_lat_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_vrel_lon_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_vrel_lon_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_vrel_lat_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_vrel_lat_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lon_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lon_rms(&obj_list_raw_data.objects[i]));
        TEST_ASSERT_EQUAL_HEX16(conti_radar_object_raw_data_get_arel_lat_rms(&driver.object_list.objects[i]),
                                conti_radar_object_raw_data_get_arel_lat_rms(&obj_list_raw_data.objects[i]));
    }
}

int main(void)
{
    UNITY_BEGIN();

    init_radar_can_msg();
    RUN_TEST(test_conti_radar_driver_init);
    RUN_TEST(test_conti_radar_process_data);
    RUN_TEST(test_conti_radar_object_raw_data_serialize_and_deserialize_4byte_aligned);
    RUN_TEST(test_conti_radar_object_raw_data_serialize_and_deserialize_8byte_aligned);
    RUN_TEST(test_conti_radar_object_raw_data_serialize_and_deserialize_default);
    RUN_TEST(test_conti_radar_failure_case);

    return UNITY_END();
}
