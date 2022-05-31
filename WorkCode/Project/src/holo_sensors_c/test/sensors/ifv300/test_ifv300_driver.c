/*!
 * @brief Unit test for ifv300 driver.
 * @author liuya@holomaitc.com
 * @date 2020-04-15
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/sensors/ifv300/ifv300_driver.h>
#include <holo_c/sensors/dbc/ifv300_output_dbc.h>
#include <holo_c/sensors/dbc/ifv300_input_dbc.h>
#include <holo_c/utils/serialization.h>
#include <string.h>
#include <time.h>
#include <unity.h>

struct CanMessage
{
    uint32_t id;
    uint8_t  len;
    uint8_t  data[8];
};

static struct CanMessage ifv_line_info_head_msg;
static struct CanMessage ifv_line_info_curve_msg[IFV_LINE_NUM];
static struct CanMessage ifv_object_part1_msg[IFV_OBJECT_NUM];
static struct CanMessage ifv_object_part2_msg[IFV_OBJECT_NUM];
static struct CanMessage ifv_object_part3_msg[IFV_OBJECT_NUM];

static struct IfvDriver driver;

static void init_line_can_msg(void)
{
    uint8_t i;

    ifv_line_info_head_msg.id      = 0x6A4;
    ifv_line_info_head_msg.len     = 8;
    ifv_line_info_head_msg.data[0] = 0x01;
    ifv_line_info_head_msg.data[1] = 0x01;
    ifv_line_info_head_msg.data[2] = 0x02;
    ifv_line_info_head_msg.data[3] = 0x10;
    ifv_line_info_head_msg.data[4] = 0x03;
    ifv_line_info_head_msg.data[5] = 0x00;
    ifv_line_info_head_msg.data[6] = 0x42;
    ifv_line_info_head_msg.data[7] = 0x01;

    ifv_line_info_curve_msg[0].id = ID_VIS_LANE_NEAR_LEFT_INDIVIDUAL;
    ifv_line_info_curve_msg[1].id = ID_VIS_LANE_NEAR_RIGHT_INDIVIDUAL;
    ifv_line_info_curve_msg[2].id = ID_VIS_LANE_NEIGHBOR_RIGHT;
    ifv_line_info_curve_msg[3].id = ID_VIS_LANE_NEIGHBOR_LEFT;

    for (i = 0; i < IFV_LINE_NUM; i++)
    {
        ifv_line_info_curve_msg[i].len     = 8;
        ifv_line_info_curve_msg[i].data[0] = 0x9A;
        ifv_line_info_curve_msg[i].data[1] = 0xD1;
        ifv_line_info_curve_msg[i].data[2] = 0x0C;
        ifv_line_info_curve_msg[i].data[3] = 0x32;
        ifv_line_info_curve_msg[i].data[4] = 0x83;
        ifv_line_info_curve_msg[i].data[5] = 0x86;
        ifv_line_info_curve_msg[i].data[6] = 0x66;
        ifv_line_info_curve_msg[i].data[7] = 0x06;
    }
}

static void init_object_can_msg(void)
{
    uint8_t i;

    for (i = 0; i < IFV_OBJECT_NUM; i++)
    {
        ifv_object_part1_msg[i].id      = ID_VIS_OBS_MSG_1;
        ifv_object_part1_msg[i].len     = 8;
        ifv_object_part1_msg[i].data[0] = 0x10;
        ifv_object_part1_msg[i].data[1] = 0x31;
        ifv_object_part1_msg[i].data[2] = 0x68;
        ifv_object_part1_msg[i].data[3] = 0x00;
        ifv_object_part1_msg[i].data[4] = 0x00;
        ifv_object_part1_msg[i].data[5] = 0x00;
        ifv_object_part1_msg[i].data[6] = 0x00;
        ifv_object_part1_msg[i].data[7] = 0x42;

        ifv_object_part2_msg[i].id      = ID_VIS_OBS_MSG_2;
        ifv_object_part2_msg[i].len     = 5;
        ifv_object_part2_msg[i].data[0] = 0x0A;
        ifv_object_part2_msg[i].data[1] = 0x80;
        ifv_object_part2_msg[i].data[2] = 0xCA;
        ifv_object_part2_msg[i].data[3] = 0x04;
        ifv_object_part2_msg[i].data[4] = 0x04;

        ifv_object_part3_msg[i].id      = ID_VIS_OBS_MSG_3;
        ifv_object_part3_msg[i].len     = 8;
        ifv_object_part3_msg[i].data[0] = 0x0F;
        ifv_object_part3_msg[i].data[1] = 0x43;
        ifv_object_part3_msg[i].data[2] = 0x33;
        ifv_object_part3_msg[i].data[3] = 0x00;
        ifv_object_part3_msg[i].data[4] = 0xE0;
        ifv_object_part3_msg[i].data[5] = 0xCC;
        ifv_object_part3_msg[i].data[6] = 0x99;
        ifv_object_part3_msg[i].data[7] = 0x19;
    }
}

static void test_ifv_driver_init(void)
{
    uint8_t          i;
    struct Timestamp sys_time;

    TEST_ASSERT_EQUAL(RC_SUCCESS, ifv_driver_init(&driver));

    timestamp_init_from_timestamp(&sys_time, ifv_lines_raw_data_get_timestamp(&driver.lines));
    TEST_ASSERT_EQUAL_INT64(0, timestamp_get_sec(&sys_time));

    TEST_ASSERT_EQUAL_INT64(0, ifv_object_list_raw_data_get_vehicle_speed(&driver.objects));
    TEST_ASSERT_EQUAL_INT64(0, ifv_object_list_raw_data_get_obj_num(&driver.objects));
    for (i = 0; i < IFV_OBJECT_NUM; i++)
    {
        timestamp_init_from_timestamp(&sys_time, ifv_object_raw_data_get_timestamp(&driver.objects.object[i]));
        TEST_ASSERT_EQUAL_INT64(0, timestamp_get_sec(&sys_time));
    }
}

static void test_ifv_driver_process_line_data(void)
{
    uint8_t  i;
    uint16_t raw_data = 0;

    time_t           utc_seconds;
    struct Timestamp sys_time;
    struct Timestamp raw_data_timestamp;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_LINE_CONTINUE,
                            ifv_driver_process_data(&driver, &sys_time, ifv_line_info_head_msg.id,
                                                    ifv_line_info_head_msg.data, ifv_line_info_head_msg.len));

    for (i = 0; i < IFV_LINE_NUM - 1; i++)
    {
        TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_LINE_CONTINUE,
                                ifv_driver_process_data(&driver, &sys_time, ifv_line_info_curve_msg[i].id,
                                                        ifv_line_info_curve_msg[i].data,
                                                        ifv_line_info_curve_msg[i].len));
    }

    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_LINE_COMPLETE,
                            ifv_driver_process_data(&driver, &sys_time, ifv_line_info_curve_msg[i].id,
                                                    ifv_line_info_curve_msg[i].data, ifv_line_info_curve_msg[i].len));

    raw_data = ifv_line_info_head_raw_data_get_lane_change(&driver.lines.line_head);
    TEST_ASSERT_EQUAL_HEX16(0x01, raw_data);

    raw_data = ifv_line_info_head_raw_data_get_left_left_type(&driver.lines.line_head);
    TEST_ASSERT_EQUAL_HEX16(0x02, raw_data);

    raw_data = ifv_line_info_head_raw_data_get_left_type(&driver.lines.line_head);
    TEST_ASSERT_EQUAL_HEX16(0x01, raw_data);

    raw_data = ifv_line_info_head_raw_data_get_right_right_type(&driver.lines.line_head);
    TEST_ASSERT_EQUAL_HEX16(0x04, raw_data);

    raw_data = ifv_line_info_head_raw_data_get_right_type(&driver.lines.line_head);
    TEST_ASSERT_EQUAL_HEX16(0x01, raw_data);

    raw_data = ifv_line_info_head_raw_data_get_left_left_lkaconf(&driver.lines.line_head);
    TEST_ASSERT_EQUAL_HEX16(0x02, raw_data);

    raw_data = ifv_line_info_head_raw_data_get_left_lkaconf(&driver.lines.line_head);
    TEST_ASSERT_EQUAL_HEX16(0x01, raw_data);

    raw_data = ifv_line_info_head_raw_data_get_right_right_lkaconf(&driver.lines.line_head);
    TEST_ASSERT_EQUAL_HEX16(0x03, raw_data);

    raw_data = ifv_line_info_head_raw_data_get_right_lkaconf(&driver.lines.line_head);
    TEST_ASSERT_EQUAL_HEX16(0x00, raw_data);

    timestamp_init_from_timestamp(&raw_data_timestamp, ifv_lines_raw_data_get_timestamp(&driver.lines));
    TEST_ASSERT_EQUAL_HEX64(sys_time.nsec, raw_data_timestamp.nsec);

    raw_data = ifv_line_info_curve_raw_data_get_mark_color(&driver.lines.left_left);
    TEST_ASSERT_EQUAL_HEX16(0x02, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a0(&driver.lines.left_left);
    TEST_ASSERT_EQUAL_HEX16(0x19A, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a1(&driver.lines.left_left);
    TEST_ASSERT_EQUAL_HEX16(0xCC, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a2(&driver.lines.left_left);
    TEST_ASSERT_EQUAL_HEX16(0xCD, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a3(&driver.lines.left_left);
    TEST_ASSERT_EQUAL_HEX16(0x199A, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_range(&driver.lines.left_left);
    TEST_ASSERT_EQUAL_HEX16(0x34, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_mark_color(&driver.lines.left);
    TEST_ASSERT_EQUAL_HEX16(0x02, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a0(&driver.lines.left);
    TEST_ASSERT_EQUAL_HEX16(0x19A, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a1(&driver.lines.left);
    TEST_ASSERT_EQUAL_HEX16(0xCC, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a2(&driver.lines.left);
    TEST_ASSERT_EQUAL_HEX16(0xCD, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a3(&driver.lines.left);
    TEST_ASSERT_EQUAL_HEX16(0x199A, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_range(&driver.lines.left);
    TEST_ASSERT_EQUAL_HEX16(0x34, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_mark_color(&driver.lines.right);
    TEST_ASSERT_EQUAL_HEX16(0x02, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a0(&driver.lines.right);
    TEST_ASSERT_EQUAL_HEX16(0x19A, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a1(&driver.lines.right);
    TEST_ASSERT_EQUAL_HEX16(0xCC, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a2(&driver.lines.right);
    TEST_ASSERT_EQUAL_HEX16(0xCD, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a3(&driver.lines.right);
    TEST_ASSERT_EQUAL_HEX16(0x199A, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_range(&driver.lines.right);
    TEST_ASSERT_EQUAL_HEX16(0x34, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_mark_color(&driver.lines.right_right);
    TEST_ASSERT_EQUAL_HEX16(0x02, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a0(&driver.lines.right_right);
    TEST_ASSERT_EQUAL_HEX16(0x19A, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a1(&driver.lines.right_right);
    TEST_ASSERT_EQUAL_HEX16(0xCC, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a2(&driver.lines.right_right);
    TEST_ASSERT_EQUAL_HEX16(0xCD, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_a3(&driver.lines.right_right);
    TEST_ASSERT_EQUAL_HEX16(0x199A, raw_data);

    raw_data = ifv_line_info_curve_raw_data_get_range(&driver.lines.right_right);
    TEST_ASSERT_EQUAL_HEX16(0x34, raw_data);
}

static void test_ifv_driver_process_object_data(void)
{
    uint8_t  i;
    uint16_t raw_data = 0;

    time_t           utc_seconds;
    struct Timestamp sys_time;
    struct Timestamp raw_data_timestamp;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    for (i = 0; i < IFV_OBJECT_NUM; i++)
    {
        TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_OBJ_CONTINUE,
                                ifv_driver_process_data(&driver, &sys_time, ifv_object_part1_msg[i].id,
                                                        ifv_object_part1_msg[i].data, ifv_object_part1_msg[i].len));

        TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_OBJ_CONTINUE,
                                ifv_driver_process_data(&driver, &sys_time, ifv_object_part2_msg[i].id,
                                                        ifv_object_part2_msg[i].data, ifv_object_part2_msg[i].len));

        if (i == (IFV_OBJECT_NUM - 1))
        {
            TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_OBJ_COMPLETE,
                                    ifv_driver_process_data(&driver, &sys_time, ifv_object_part3_msg[i].id,
                                                            ifv_object_part3_msg[i].data, ifv_object_part3_msg[i].len));
        }
        else
        {
            TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_OBJ_CONTINUE,
                                    ifv_driver_process_data(&driver, &sys_time, ifv_object_part3_msg[i].id,
                                                            ifv_object_part3_msg[i].data, ifv_object_part3_msg[i].len));
        }
    }

    for (i = 0; i < IFV_OBJECT_NUM; i++)
    {
        timestamp_init_from_timestamp(&raw_data_timestamp,
                                      ifv_object_raw_data_get_timestamp(&driver.objects.object[i]));
        TEST_ASSERT_EQUAL_HEX64(sys_time.sec, raw_data_timestamp.sec);
        TEST_ASSERT_EQUAL_HEX64(sys_time.nsec, raw_data_timestamp.nsec);

        raw_data = ifv_object_raw_data_get_message_counter_msg1(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x2, raw_data);

        raw_data = ifv_object_raw_data_get_count_msg1(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x1, raw_data);

        raw_data = ifv_object_raw_data_get_id(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x1, raw_data);

        raw_data = ifv_object_raw_data_get_classification(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x3, raw_data);

        raw_data = ifv_object_raw_data_get_ped_waise_up(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x1, raw_data);

        raw_data = ifv_object_raw_data_get_turn_indicator(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x1, raw_data);

        raw_data = ifv_object_raw_data_get_brake_light_indicator(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x2, raw_data);

        raw_data = ifv_object_raw_data_get_height(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x10, raw_data);

        raw_data = ifv_object_raw_data_get_message_counter_msg2(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x2, raw_data);

        raw_data = ifv_object_raw_data_get_count_msg2(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x2, raw_data);

        raw_data = ifv_object_raw_data_get_long_accel(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0xA00, raw_data);

        raw_data = ifv_object_raw_data_get_ttc_const_acc_model(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x99, raw_data);

        raw_data = ifv_object_raw_data_get_cut_in_cut_out(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x2, raw_data);

        raw_data = ifv_object_raw_data_get_message_counter_msg3(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x3, raw_data);

        raw_data = ifv_object_raw_data_get_count_msg3(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x3, raw_data);

        raw_data = ifv_object_raw_data_get_lat_pos(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x733, raw_data);

        raw_data = ifv_object_raw_data_get_lat_vel(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x666, raw_data);

        raw_data = ifv_object_raw_data_get_long_pos(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x19A, raw_data);

        raw_data = ifv_object_raw_data_get_long_vel(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x800, raw_data);

        raw_data = ifv_object_raw_data_get_width(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0xC, raw_data);
    }
}

static void test_ifv_lines_raw_data_serialize_and_deserialize(void)
{
    const uint8_t          buf_size       = 74;
    const uint8_t          error_buf_size = 60;
    uint8_t                buffer[74];
    struct IfvLinesRawData lines_raw_data;

    TEST_ASSERT_EQUAL_INT(buf_size, ifv_lines_raw_data_get_serialized_size(&driver.lines));

    TEST_ASSERT_EQUAL_INT(RC_SERIALIZATION_BUFFER_OVERFLOW,
                          ifv_lines_raw_data_serialize(&driver.lines, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, ifv_lines_raw_data_serialize(&driver.lines, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                          ifv_lines_raw_data_deserialize(&lines_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, ifv_lines_raw_data_deserialize(&lines_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_HEX64(driver.lines.timestamp.sec, lines_raw_data.timestamp.sec);
    TEST_ASSERT_EQUAL_HEX64(driver.lines.timestamp.nsec, lines_raw_data.timestamp.nsec);

    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_head_raw_data_get_lane_change(&driver.lines.line_head),
                            ifv_line_info_head_raw_data_get_lane_change(&lines_raw_data.line_head));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_head_raw_data_get_left_left_type(&driver.lines.line_head),
                            ifv_line_info_head_raw_data_get_left_left_type(&lines_raw_data.line_head));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_head_raw_data_get_left_type(&driver.lines.line_head),
                            ifv_line_info_head_raw_data_get_left_type(&lines_raw_data.line_head));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_head_raw_data_get_right_right_type(&driver.lines.line_head),
                            ifv_line_info_head_raw_data_get_right_right_type(&lines_raw_data.line_head));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_head_raw_data_get_right_type(&driver.lines.line_head),
                            ifv_line_info_head_raw_data_get_right_type(&lines_raw_data.line_head));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_head_raw_data_get_left_left_lkaconf(&driver.lines.line_head),
                            ifv_line_info_head_raw_data_get_left_left_lkaconf(&lines_raw_data.line_head));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_head_raw_data_get_left_lkaconf(&driver.lines.line_head),
                            ifv_line_info_head_raw_data_get_left_lkaconf(&lines_raw_data.line_head));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_head_raw_data_get_right_right_lkaconf(&driver.lines.line_head),
                            ifv_line_info_head_raw_data_get_right_right_lkaconf(&lines_raw_data.line_head));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_head_raw_data_get_right_lkaconf(&driver.lines.line_head),
                            ifv_line_info_head_raw_data_get_right_lkaconf(&lines_raw_data.line_head));

    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_mark_color(&driver.lines.left_left),
                            ifv_line_info_curve_raw_data_get_mark_color(&lines_raw_data.left_left));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a0(&driver.lines.left_left),
                            ifv_line_info_curve_raw_data_get_a0(&lines_raw_data.left_left));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a1(&driver.lines.left_left),
                            ifv_line_info_curve_raw_data_get_a1(&lines_raw_data.left_left));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a2(&driver.lines.left_left),
                            ifv_line_info_curve_raw_data_get_a2(&lines_raw_data.left_left));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a3(&driver.lines.left_left),
                            ifv_line_info_curve_raw_data_get_a3(&lines_raw_data.left_left));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_range(&driver.lines.left_left),
                            ifv_line_info_curve_raw_data_get_range(&lines_raw_data.left_left));

    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_mark_color(&driver.lines.left),
                            ifv_line_info_curve_raw_data_get_mark_color(&lines_raw_data.left));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a0(&driver.lines.left),
                            ifv_line_info_curve_raw_data_get_a0(&lines_raw_data.left));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a1(&driver.lines.left),
                            ifv_line_info_curve_raw_data_get_a1(&lines_raw_data.left));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a2(&driver.lines.left),
                            ifv_line_info_curve_raw_data_get_a2(&lines_raw_data.left));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a3(&driver.lines.left),
                            ifv_line_info_curve_raw_data_get_a3(&lines_raw_data.left));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_range(&driver.lines.left),
                            ifv_line_info_curve_raw_data_get_range(&lines_raw_data.left));

    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_mark_color(&driver.lines.right),
                            ifv_line_info_curve_raw_data_get_mark_color(&lines_raw_data.right));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a0(&driver.lines.right),
                            ifv_line_info_curve_raw_data_get_a0(&lines_raw_data.right));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a1(&driver.lines.right),
                            ifv_line_info_curve_raw_data_get_a1(&lines_raw_data.right));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a2(&driver.lines.right),
                            ifv_line_info_curve_raw_data_get_a2(&lines_raw_data.right));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a3(&driver.lines.right),
                            ifv_line_info_curve_raw_data_get_a3(&lines_raw_data.right));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_range(&driver.lines.right),
                            ifv_line_info_curve_raw_data_get_range(&lines_raw_data.right));

    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_mark_color(&driver.lines.right_right),
                            ifv_line_info_curve_raw_data_get_mark_color(&lines_raw_data.right_right));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a0(&driver.lines.right_right),
                            ifv_line_info_curve_raw_data_get_a0(&lines_raw_data.right_right));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a1(&driver.lines.right_right),
                            ifv_line_info_curve_raw_data_get_a1(&lines_raw_data.right_right));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a2(&driver.lines.right_right),
                            ifv_line_info_curve_raw_data_get_a2(&lines_raw_data.right_right));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_a3(&driver.lines.right_right),
                            ifv_line_info_curve_raw_data_get_a3(&lines_raw_data.right_right));
    TEST_ASSERT_EQUAL_HEX16(ifv_line_info_curve_raw_data_get_range(&driver.lines.right_right),
                            ifv_line_info_curve_raw_data_get_range(&lines_raw_data.right_right));
}

static void test_ifv_object_list_raw_data_serialize_and_deserialize(void)
{
    const uint16_t              buf_size       = 728;
    const uint16_t              error_buf_size = 700;
    uint8_t                     i;
    uint8_t                     buffer[728];
    struct IfvObjectListRawData object_list_raw_data;

    TEST_ASSERT_EQUAL_INT(buf_size, ifv_object_list_raw_data_get_serialized_size(&driver.objects));

    TEST_ASSERT_EQUAL_INT(RC_SERIALIZATION_BUFFER_OVERFLOW,
                          ifv_object_list_raw_data_serialize(&driver.objects, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, ifv_object_list_raw_data_serialize(&driver.objects, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                          ifv_object_list_raw_data_deserialize(&driver.objects, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, ifv_object_list_raw_data_deserialize(&object_list_raw_data, buffer, buf_size));

    TEST_ASSERT_EQUAL_HEX64(ifv_object_list_raw_data_get_vehicle_speed(&driver.objects),
                            ifv_object_list_raw_data_get_vehicle_speed(&object_list_raw_data));

    TEST_ASSERT_EQUAL_HEX64(ifv_object_list_raw_data_get_obj_num(&driver.objects),
                            ifv_object_list_raw_data_get_obj_num(&object_list_raw_data));

    for (i = 0; i < IFV_OBJECT_NUM; i++)
    {
        TEST_ASSERT_EQUAL_HEX64(driver.objects.object[i].timestamp.sec, object_list_raw_data.object[i].timestamp.sec);
        TEST_ASSERT_EQUAL_HEX64(driver.objects.object[i].timestamp.nsec, object_list_raw_data.object[i].timestamp.nsec);

        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_message_counter_msg1(&driver.objects.object[i]),
                                ifv_object_raw_data_get_message_counter_msg1(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_count_msg1(&driver.objects.object[i]),
                                ifv_object_raw_data_get_count_msg1(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_id(&driver.objects.object[i]),
                                ifv_object_raw_data_get_id(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_classification(&driver.objects.object[i]),
                                ifv_object_raw_data_get_classification(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_ped_waise_up(&driver.objects.object[i]),
                                ifv_object_raw_data_get_ped_waise_up(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_turn_indicator(&driver.objects.object[i]),
                                ifv_object_raw_data_get_turn_indicator(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_brake_light_indicator(&driver.objects.object[i]),
                                ifv_object_raw_data_get_brake_light_indicator(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_height(&driver.objects.object[i]),
                                ifv_object_raw_data_get_height(&object_list_raw_data.object[i]));

        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_message_counter_msg2(&driver.objects.object[i]),
                                ifv_object_raw_data_get_message_counter_msg2(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_count_msg2(&driver.objects.object[i]),
                                ifv_object_raw_data_get_count_msg2(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_long_accel(&driver.objects.object[i]),
                                ifv_object_raw_data_get_long_accel(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_ttc_const_acc_model(&driver.objects.object[i]),
                                ifv_object_raw_data_get_ttc_const_acc_model(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_cut_in_cut_out(&driver.objects.object[i]),
                                ifv_object_raw_data_get_cut_in_cut_out(&object_list_raw_data.object[i]));

        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_message_counter_msg3(&driver.objects.object[i]),
                                ifv_object_raw_data_get_message_counter_msg3(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_count_msg3(&driver.objects.object[i]),
                                ifv_object_raw_data_get_count_msg3(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_lat_pos(&driver.objects.object[i]),
                                ifv_object_raw_data_get_lat_pos(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_lat_vel(&driver.objects.object[i]),
                                ifv_object_raw_data_get_lat_vel(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_long_pos(&driver.objects.object[i]),
                                ifv_object_raw_data_get_long_pos(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_long_vel(&driver.objects.object[i]),
                                ifv_object_raw_data_get_long_vel(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(ifv_object_raw_data_get_width(&driver.objects.object[i]),
                                ifv_object_raw_data_get_width(&object_list_raw_data.object[i]));
    }
}

void test_ifv_failure_case(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, ifv_msg_id_is_valid(ID_VIS_LANE_NEAR_LEFT_INDIVIDUAL));
    TEST_ASSERT_EQUAL_INT(RC_FAIL, ifv_msg_id_is_valid(0xFF));

    driver.parse_state = IFV_PARSE_IDLE;
    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_DATA_ERROR,
                            ifv_driver_process_data(&driver, &sys_time, ifv_line_info_curve_msg[0].id,
                                                    ifv_line_info_curve_msg[0].data, ifv_line_info_curve_msg[0].len));

    driver.parse_state = IFV_PARSE_LINE_HEAD;
    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_DATA_ERROR,
                            ifv_driver_process_data(&driver, &sys_time, ifv_line_info_curve_msg[0].id,
                                                    ifv_line_info_curve_msg[0].data, ifv_line_info_curve_msg[0].len));

    driver.parse_state = IFV_PARSE_LINE_NEAR_LEFT;
    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_DATA_ERROR,
                            ifv_driver_process_data(&driver, &sys_time, ifv_object_part1_msg[0].id,
                                                    ifv_object_part1_msg[0].data, ifv_object_part1_msg[0].len));

    driver.parse_state = IFV_PARSE_LINE_NEAR_RIGHT;
    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_DATA_ERROR,
                            ifv_driver_process_data(&driver, &sys_time, ifv_object_part1_msg[0].id,
                                                    ifv_object_part1_msg[0].data, ifv_object_part1_msg[0].len));

    driver.parse_state = IFV_PARSE_LINE_NEIGHBOR_LEFT;
    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_DATA_ERROR,
                            ifv_driver_process_data(&driver, &sys_time, ifv_object_part1_msg[0].id,
                                                    ifv_object_part1_msg[0].data, ifv_object_part1_msg[0].len));

    driver.parse_state = IFV_PARSE_LINE_NEIGHBOR_RIGHT;
    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_DATA_ERROR,
                            ifv_driver_process_data(&driver, &sys_time, ifv_object_part1_msg[0].id,
                                                    ifv_object_part1_msg[0].data, ifv_object_part1_msg[0].len));

    driver.parse_state = IFV_PARSE_OBJECT_PART1;
    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_DATA_ERROR,
                            ifv_driver_process_data(&driver, &sys_time, ifv_line_info_head_msg.id,
                                                    ifv_line_info_head_msg.data, ifv_line_info_head_msg.len));

    driver.parse_state = IFV_PARSE_OBJECT_PART2;
    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_DATA_ERROR,
                            ifv_driver_process_data(&driver, &sys_time, ifv_line_info_head_msg.id,
                                                    ifv_line_info_head_msg.data, ifv_line_info_head_msg.len));

    driver.parse_state = IFV_PARSE_OBJECT_PART3;
    TEST_ASSERT_EQUAL_INT64(RC_IFV_PARSE_DATA_ERROR,
                            ifv_driver_process_data(&driver, &sys_time, ifv_line_info_head_msg.id,
                                                    ifv_line_info_head_msg.data, ifv_line_info_head_msg.len));
}

int main(void)
{
    UNITY_BEGIN();

    init_line_can_msg();
    init_object_can_msg();
    RUN_TEST(test_ifv_driver_init);
    RUN_TEST(test_ifv_driver_process_line_data);
    RUN_TEST(test_ifv_driver_process_object_data);
    RUN_TEST(test_ifv_lines_raw_data_serialize_and_deserialize);
    RUN_TEST(test_ifv_object_list_raw_data_serialize_and_deserialize);
    RUN_TEST(test_ifv_failure_case);

    return UNITY_END();
}
