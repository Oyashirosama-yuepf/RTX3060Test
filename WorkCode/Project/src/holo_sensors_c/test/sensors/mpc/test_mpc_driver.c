/*!
 * @brief Unit test for mpc driver.
 * @author liuya@holomaitc.com
 * @date 2019-9-25
 * @attention Copyright@Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <holo_c/sensors/mpc/mpc_driver.h>
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

struct CanMessage mpc_line_partA_msg[4];
struct CanMessage mpc_line_partB_msg[4];
struct CanMessage mpc_object_partA_msg[16];
struct CanMessage mpc_object_partB_msg[16];
struct CanMessage mpc_object_partC_msg[16];
struct CanMessage mpc_object_partD_msg[16];
struct CanMessage mpc_object_partE_msg[16];

static struct MpcDriver driver;

static void init_line_can_msg(void)
{
    uint8_t i;

    mpc_line_partA_msg[0].id = ID_BV1_Lin_01_A;
    mpc_line_partB_msg[0].id = ID_BV1_Lin_01_B;

    mpc_line_partA_msg[1].id = ID_BV1_Lin_02_A;
    mpc_line_partB_msg[1].id = ID_BV1_Lin_02_B;

    mpc_line_partA_msg[2].id = ID_BV1_Lin_03_A;
    mpc_line_partB_msg[2].id = ID_BV1_Lin_03_B;

    mpc_line_partA_msg[3].id = ID_BV1_Lin_04_A;
    mpc_line_partB_msg[3].id = ID_BV1_Lin_04_B;

    for (i = 0; i < MPC_LINE_NUM; i++)
    {
        mpc_line_partA_msg[i].len     = 8;
        mpc_line_partA_msg[i].data[0] = 0x00;
        mpc_line_partA_msg[i].data[1] = 0x00;
        mpc_line_partA_msg[i].data[2] = 0x06;
        mpc_line_partA_msg[i].data[3] = 0x01;
        mpc_line_partA_msg[i].data[4] = 0x00;
        mpc_line_partA_msg[i].data[5] = 0xDE;
        mpc_line_partA_msg[i].data[6] = 0xFF;
        mpc_line_partA_msg[i].data[7] = 0xFF;

        mpc_line_partB_msg[i].len     = 8;
        mpc_line_partB_msg[i].data[0] = 0x00;
        mpc_line_partB_msg[i].data[1] = 0x00;
        mpc_line_partB_msg[i].data[2] = 0x00;
        mpc_line_partB_msg[i].data[3] = 0x20;
        mpc_line_partB_msg[i].data[4] = 0x80;
        mpc_line_partB_msg[i].data[5] = 0x9C;
        mpc_line_partB_msg[i].data[6] = 0x00;
        mpc_line_partB_msg[i].data[7] = 0x00;
    }
}

static void init_object_can_msg(void)
{
    uint8_t i;

    for (i = 0; i < 4; i++)
    {
        mpc_object_partA_msg[i].id = ID_BV_Obj_01_A + 4 * i;
        mpc_object_partB_msg[i].id = ID_BV_Obj_01_B + 4 * i;
        mpc_object_partC_msg[i].id = ID_BV_Obj_01_C + 4 * i;
        mpc_object_partD_msg[i].id = ID_BV_Obj_01_D + 4 * i;
    }

    for (i = 4; i < MPC_OBJECT_NUM; i++)
    {
        mpc_object_partA_msg[i].id = ID_BV_Obj_05_A + 4 * (i - 4);
        mpc_object_partB_msg[i].id = ID_BV_Obj_05_B + 4 * (i - 4);
        mpc_object_partC_msg[i].id = ID_BV_Obj_05_C + 4 * (i - 4);
        mpc_object_partD_msg[i].id = ID_BV_Obj_05_D + 4 * (i - 4);
    }

    for (i = 0; i < 8; i++)
    {
        mpc_object_partE_msg[i].id = ID_BV_Obj_01_E + 1 * i;
    }

    for (i = 8; i < MPC_OBJECT_NUM; i++)
    {
        mpc_object_partE_msg[i].id = ID_BV_Obj_09_E + 1 * (i - 8);
    }

    for (i = 0; i < MPC_OBJECT_NUM; i++)
    {
        mpc_object_partA_msg[i].len = 8;
        mpc_object_partB_msg[i].len = 8;
        mpc_object_partC_msg[i].len = 8;
        mpc_object_partD_msg[i].len = 8;
        mpc_object_partE_msg[i].len = 8;

        mpc_object_partA_msg[i].data[0] = 0x00;
        mpc_object_partA_msg[i].data[1] = 0x00;
        mpc_object_partA_msg[i].data[2] = 0xC0;
        mpc_object_partA_msg[i].data[3] = 0x00;
        mpc_object_partA_msg[i].data[4] = 0x70;
        mpc_object_partA_msg[i].data[5] = 0x2D;
        mpc_object_partA_msg[i].data[6] = 0x00;
        mpc_object_partA_msg[i].data[7] = 0x06;

        mpc_object_partB_msg[i].data[0] = 0x00;
        mpc_object_partB_msg[i].data[1] = 0x00;
        mpc_object_partB_msg[i].data[2] = 0x00;
        mpc_object_partB_msg[i].data[3] = 0xFF;
        mpc_object_partB_msg[i].data[4] = 0xFB;
        mpc_object_partB_msg[i].data[5] = 0x01;
        mpc_object_partB_msg[i].data[6] = 0xFF;
        mpc_object_partB_msg[i].data[7] = 0x00;

        mpc_object_partC_msg[i].data[0] = 0x00;
        mpc_object_partC_msg[i].data[1] = 0x00;
        mpc_object_partC_msg[i].data[2] = 0xFE;
        mpc_object_partC_msg[i].data[3] = 0x03;
        mpc_object_partC_msg[i].data[4] = 0xFC;
        mpc_object_partC_msg[i].data[5] = 0xFB;
        mpc_object_partC_msg[i].data[6] = 0x07;
        mpc_object_partC_msg[i].data[7] = 0x00;

        mpc_object_partD_msg[i].data[0] = 0x00;
        mpc_object_partD_msg[i].data[1] = 0x00;
        mpc_object_partD_msg[i].data[2] = 0xFF;
        mpc_object_partD_msg[i].data[3] = 0xFF;
        mpc_object_partD_msg[i].data[4] = 0x3F;
        mpc_object_partD_msg[i].data[5] = 0x00;
        mpc_object_partD_msg[i].data[6] = 0x00;
        mpc_object_partD_msg[i].data[7] = 0x01;

        mpc_object_partE_msg[i].data[0] = 0x00;
        mpc_object_partE_msg[i].data[1] = 0x00;
        mpc_object_partE_msg[i].data[2] = 0xC0;
        mpc_object_partE_msg[i].data[3] = 0x06;
        mpc_object_partE_msg[i].data[4] = 0x00;
        mpc_object_partE_msg[i].data[5] = 0x00;
        mpc_object_partE_msg[i].data[6] = 0x00;
        mpc_object_partE_msg[i].data[7] = 0x00;
    }
}

static void test_mpc_driver_init(void)
{
    uint8_t          i;
    struct Timestamp sys_time;

    TEST_ASSERT_EQUAL(RC_SUCCESS, mpc_driver_init(&driver));

    timestamp_init_from_timestamp(&sys_time, mpc_line_raw_data_get_timestamp(&driver.lines.left_left_line));
    TEST_ASSERT_EQUAL_INT64(0, timestamp_get_sec(&sys_time));

    timestamp_init_from_timestamp(&sys_time, mpc_line_raw_data_get_timestamp(&driver.lines.left_line));
    TEST_ASSERT_EQUAL_INT64(0, timestamp_get_sec(&sys_time));

    timestamp_init_from_timestamp(&sys_time, mpc_line_raw_data_get_timestamp(&driver.lines.right_line));
    TEST_ASSERT_EQUAL_INT64(0, timestamp_get_sec(&sys_time));

    timestamp_init_from_timestamp(&sys_time, mpc_line_raw_data_get_timestamp(&driver.lines.right_right_line));
    TEST_ASSERT_EQUAL_INT64(0, timestamp_get_sec(&sys_time));

    for (i = 0; i < MPC_OBJECT_NUM; i++)
    {
        timestamp_init_from_timestamp(&sys_time, mpc_object_raw_data_get_timestamp(&driver.objects.object[i]));
        TEST_ASSERT_EQUAL_INT64(0, timestamp_get_sec(&sys_time));
    }
}

static void test_mpc_driver_process_line_data(void)
{
    uint8_t  i;
    uint16_t raw_data = 0;

    time_t                utc_seconds;
    struct Timestamp      sys_time;
    struct Timestamp      raw_data_timestamp;
    struct MpcLineRawData line;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    for (i = 0; i < MPC_LINE_NUM; i++)
    {
        TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_LINE_CONTINUE,
                                mpc_driver_process_data(&driver, &sys_time, mpc_line_partA_msg[i].id,
                                                        mpc_line_partA_msg[i].data, mpc_line_partA_msg[i].len));

        switch (i)
        {
            case 0:
                line = driver.lines.left_left_line;
                break;

            case 1:
                line = driver.lines.left_line;
                break;

            case 2:
                line = driver.lines.right_line;
                break;

            case 3:
                line = driver.lines.right_right_line;
                break;

            default:
                break;
        }

        timestamp_init_from_timestamp(&raw_data_timestamp, mpc_line_raw_data_get_timestamp(&line));
        TEST_ASSERT_EQUAL_HEX64(sys_time.nsec, raw_data_timestamp.nsec);

        raw_data = mpc_line_raw_data_get_dx_begin(&line);
        TEST_ASSERT_EQUAL_HEX16(0x06, raw_data);

        raw_data = mpc_line_raw_data_get_dx_end(&line);
        TEST_ASSERT_EQUAL_HEX16(0x01, raw_data);

        raw_data = mpc_line_raw_data_get_dy(&line);
        TEST_ASSERT_EQUAL_HEX16(0x780, raw_data);

        raw_data = mpc_line_raw_data_get_confidence(&line);
        TEST_ASSERT_EQUAL_HEX16(0x3F, raw_data);

        raw_data = mpc_line_raw_data_get_angle_diff(&line);
        TEST_ASSERT_EQUAL_HEX16(0xFFF, raw_data);

        if (i == (MPC_LINE_NUM - 1))
        {
            TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_LINE_COMPLETE,
                                    mpc_driver_process_data(&driver, &sys_time, mpc_line_partB_msg[i].id,
                                                            mpc_line_partB_msg[i].data, mpc_line_partB_msg[i].len));
        }
        else
        {
            TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_LINE_CONTINUE,
                                    mpc_driver_process_data(&driver, &sys_time, mpc_line_partB_msg[i].id,
                                                            mpc_line_partB_msg[i].data, mpc_line_partB_msg[i].len));
        }

        switch (i)
        {
            case 0:
                line = driver.lines.left_left_line;
                break;

            case 1:
                line = driver.lines.left_line;
                break;

            case 2:
                line = driver.lines.right_line;
                break;

            case 3:
                line = driver.lines.right_right_line;
                break;

            default:
                break;
        }

        raw_data = mpc_line_raw_data_get_horizon_curve(&line);
        TEST_ASSERT_EQUAL_HEX16(0x802, raw_data);

        raw_data = mpc_line_raw_data_get_width(&line);
        TEST_ASSERT_EQUAL_HEX16(0x9C, raw_data);

        raw_data = mpc_line_raw_data_get_id(&line);
        TEST_ASSERT_EQUAL_HEX16(0x0, raw_data);

        raw_data = mpc_line_raw_data_get_type(&line);
        TEST_ASSERT_EQUAL_HEX16(0x0, raw_data);

        raw_data = mpc_line_raw_data_get_color(&line);
        TEST_ASSERT_EQUAL_HEX16(0x0, raw_data);
    }
}

static void test_mpc_driver_process_object_data(void)
{
    uint8_t  i;
    uint16_t raw_data = 0;

    time_t           utc_seconds;
    struct Timestamp sys_time;
    struct Timestamp raw_data_timestamp;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    for (i = 0; i < MPC_OBJECT_NUM; i++)
    {
        TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_OBJ_CONTINUE,
                                mpc_driver_process_data(&driver, &sys_time, mpc_object_partA_msg[i].id,
                                                        mpc_object_partA_msg[i].data, mpc_object_partA_msg[i].len));

        timestamp_init_from_timestamp(&raw_data_timestamp,
                                      mpc_object_raw_data_get_timestamp(&driver.objects.object[i]));
        TEST_ASSERT_EQUAL_HEX64(sys_time.nsec, raw_data_timestamp.nsec);

        raw_data = mpc_object_raw_data_get_lon_dist(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0xC0, raw_data);

        raw_data = mpc_object_raw_data_get_angle_center(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x5AE, raw_data);

        raw_data = mpc_object_raw_data_get_classification(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x06, raw_data);

        TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_OBJ_CONTINUE,
                                mpc_driver_process_data(&driver, &sys_time, mpc_object_partB_msg[i].id,
                                                        mpc_object_partB_msg[i].data, mpc_object_partB_msg[i].len));

        raw_data = mpc_object_raw_data_get_angle_width(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x7FE, raw_data);

        raw_data = mpc_object_raw_data_get_confidence(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x7E, raw_data);

        raw_data = mpc_object_raw_data_get_angle_speed(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x1FE, raw_data);

        TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_OBJ_CONTINUE,
                                mpc_driver_process_data(&driver, &sys_time, mpc_object_partC_msg[i].id,
                                                        mpc_object_partC_msg[i].data, mpc_object_partC_msg[i].len));

        raw_data = mpc_object_raw_data_get_inv_ttc(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x3FE, raw_data);

        raw_data = mpc_object_raw_data_get_angle_overlap_egolane_right(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x1FE, raw_data);

        raw_data = mpc_object_raw_data_get_angle_overlap_egolane_left(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x1FE, raw_data);

        raw_data = mpc_object_raw_data_get_age(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x00, raw_data);

        TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_OBJ_CONTINUE,
                                mpc_driver_process_data(&driver, &sys_time, mpc_object_partD_msg[i].id,
                                                        mpc_object_partD_msg[i].data, mpc_object_partD_msg[i].len));

        raw_data = mpc_object_raw_data_get_angle_edge_right(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x7FF, raw_data);

        raw_data = mpc_object_raw_data_get_angle_edge_left(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x7FF, raw_data);

        raw_data = mpc_object_raw_data_get_id(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x01, raw_data);

        if (i == (MPC_OBJECT_NUM - 1))
        {
            TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_OBJ_COMPLETE,
                                    mpc_driver_process_data(&driver, &sys_time, mpc_object_partE_msg[i].id,
                                                            mpc_object_partE_msg[i].data, mpc_object_partE_msg[i].len));
        }
        else
        {
            TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_OBJ_CONTINUE,
                                    mpc_driver_process_data(&driver, &sys_time, mpc_object_partE_msg[i].id,
                                                            mpc_object_partE_msg[i].data, mpc_object_partE_msg[i].len));
        }

        raw_data = mpc_object_raw_data_get_lon_velocity(&driver.objects.object[i]);
        TEST_ASSERT_EQUAL_HEX16(0x6C0, raw_data);
    }
}

static void test_mpc_line_raw_data_serialize_and_deserialize_4byte_aligned(void)
{
    const uint8_t          buf_size       = 112;
    const uint8_t          error_buf_size = 100;
    uint8_t                i;
    uint8_t                buffer[120];
    struct MpcLinesRawData lines_raw_data;
    struct MpcLineRawData  driver_line_raw_data;
    struct MpcLineRawData  deserialized_line_raw_data;

    TEST_ASSERT_EQUAL_INT(buf_size, mpc_lines_raw_data_get_serialized_size_4byte_aligned(&driver.lines));

    TEST_ASSERT_EQUAL_INT(RC_SERIALIZATION_BUFFER_OVERFLOW,
                          mpc_lines_raw_data_serialize_4byte_aligned(&driver.lines, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, mpc_lines_raw_data_serialize_4byte_aligned(&driver.lines, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                          mpc_lines_raw_data_deserialize_4byte_aligned(&lines_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, mpc_lines_raw_data_deserialize_4byte_aligned(&lines_raw_data, buffer, buf_size));

    for (i = 0; i < MPC_LINE_NUM; i++)
    {
        switch (i)
        {
            case 0:
                driver_line_raw_data       = driver.lines.left_left_line;
                deserialized_line_raw_data = lines_raw_data.left_left_line;
                break;

            case 1:
                driver_line_raw_data       = driver.lines.left_line;
                deserialized_line_raw_data = lines_raw_data.left_line;
                break;

            case 2:
                driver_line_raw_data       = driver.lines.right_line;
                deserialized_line_raw_data = lines_raw_data.right_line;
                break;

            case 3:
                driver_line_raw_data       = driver.lines.right_right_line;
                deserialized_line_raw_data = lines_raw_data.right_right_line;
                break;

            default:
                break;
        }

        TEST_ASSERT_EQUAL_HEX64(driver_line_raw_data.timestamp.sec, deserialized_line_raw_data.timestamp.sec);
        TEST_ASSERT_EQUAL_HEX64(driver_line_raw_data.timestamp.nsec, deserialized_line_raw_data.timestamp.nsec);

        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_confidence(&driver_line_raw_data),
                                mpc_line_raw_data_get_confidence(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_id(&driver_line_raw_data),
                                mpc_line_raw_data_get_id(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_type(&driver_line_raw_data),
                                mpc_line_raw_data_get_type(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_width(&driver_line_raw_data),
                                mpc_line_raw_data_get_width(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_color(&driver_line_raw_data),
                                mpc_line_raw_data_get_color(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_dx_begin(&driver_line_raw_data),
                                mpc_line_raw_data_get_dx_begin(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_dx_end(&driver_line_raw_data),
                                mpc_line_raw_data_get_dx_end(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_dy(&driver_line_raw_data),
                                mpc_line_raw_data_get_dy(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_angle_diff(&driver_line_raw_data),
                                mpc_line_raw_data_get_angle_diff(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_horizon_curve(&driver_line_raw_data),
                                mpc_line_raw_data_get_horizon_curve(&deserialized_line_raw_data));
    }
}

static void test_mpc_line_raw_data_serialize_and_deserialize_8byte_aligned(void)
{
    const uint8_t          buf_size       = 128;
    const uint8_t          error_buf_size = 100;
    uint8_t                i;
    uint8_t                buffer[128];
    struct MpcLinesRawData lines_raw_data;
    struct MpcLineRawData  driver_line_raw_data;
    struct MpcLineRawData  deserialized_line_raw_data;

    TEST_ASSERT_EQUAL_INT(buf_size, mpc_lines_raw_data_get_serialized_size_8byte_aligned(&driver.lines));

    TEST_ASSERT_EQUAL_INT(RC_SERIALIZATION_BUFFER_OVERFLOW,
                          mpc_lines_raw_data_serialize_8byte_aligned(&driver.lines, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, mpc_lines_raw_data_serialize_8byte_aligned(&driver.lines, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                          mpc_lines_raw_data_deserialize_8byte_aligned(&lines_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, mpc_lines_raw_data_deserialize_8byte_aligned(&lines_raw_data, buffer, buf_size));

    for (i = 0; i < MPC_LINE_NUM; i++)
    {
        switch (i)
        {
            case 0:
                driver_line_raw_data       = driver.lines.left_left_line;
                deserialized_line_raw_data = lines_raw_data.left_left_line;
                break;

            case 1:
                driver_line_raw_data       = driver.lines.left_line;
                deserialized_line_raw_data = lines_raw_data.left_line;
                break;

            case 2:
                driver_line_raw_data       = driver.lines.right_line;
                deserialized_line_raw_data = lines_raw_data.right_line;
                break;

            case 3:
                driver_line_raw_data       = driver.lines.right_right_line;
                deserialized_line_raw_data = lines_raw_data.right_right_line;
                break;

            default:
                break;
        }

        TEST_ASSERT_EQUAL_HEX64(driver_line_raw_data.timestamp.sec, deserialized_line_raw_data.timestamp.sec);
        TEST_ASSERT_EQUAL_HEX64(driver_line_raw_data.timestamp.nsec, deserialized_line_raw_data.timestamp.nsec);

        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_confidence(&driver_line_raw_data),
                                mpc_line_raw_data_get_confidence(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_id(&driver_line_raw_data),
                                mpc_line_raw_data_get_id(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_type(&driver_line_raw_data),
                                mpc_line_raw_data_get_type(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_width(&driver_line_raw_data),
                                mpc_line_raw_data_get_width(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_color(&driver_line_raw_data),
                                mpc_line_raw_data_get_color(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_dx_begin(&driver_line_raw_data),
                                mpc_line_raw_data_get_dx_begin(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_dx_end(&driver_line_raw_data),
                                mpc_line_raw_data_get_dx_end(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_dy(&driver_line_raw_data),
                                mpc_line_raw_data_get_dy(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_angle_diff(&driver_line_raw_data),
                                mpc_line_raw_data_get_angle_diff(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_horizon_curve(&driver_line_raw_data),
                                mpc_line_raw_data_get_horizon_curve(&deserialized_line_raw_data));
    }
}

static void test_mpc_line_raw_data_serialize_and_deserialize_default(void)
{
    const uint8_t          buf_size       = 112;
    const uint8_t          error_buf_size = 100;
    uint8_t                i;
    uint8_t                buffer[128];
    struct MpcLinesRawData lines_raw_data;
    struct MpcLineRawData  driver_line_raw_data;
    struct MpcLineRawData  deserialized_line_raw_data;

    TEST_ASSERT_EQUAL_INT(buf_size, mpc_lines_raw_data_get_serialized_size(&driver.lines));

    TEST_ASSERT_EQUAL_INT(RC_SERIALIZATION_BUFFER_OVERFLOW,
                          mpc_lines_raw_data_serialize(&driver.lines, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, mpc_lines_raw_data_serialize(&driver.lines, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                          mpc_lines_raw_data_deserialize(&lines_raw_data, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, mpc_lines_raw_data_deserialize(&lines_raw_data, buffer, buf_size));

    for (i = 0; i < MPC_LINE_NUM; i++)
    {
        switch (i)
        {
            case 0:
                driver_line_raw_data       = driver.lines.left_left_line;
                deserialized_line_raw_data = lines_raw_data.left_left_line;
                break;

            case 1:
                driver_line_raw_data       = driver.lines.left_line;
                deserialized_line_raw_data = lines_raw_data.left_line;
                break;

            case 2:
                driver_line_raw_data       = driver.lines.right_line;
                deserialized_line_raw_data = lines_raw_data.right_line;
                break;

            case 3:
                driver_line_raw_data       = driver.lines.right_right_line;
                deserialized_line_raw_data = lines_raw_data.right_right_line;
                break;

            default:
                break;
        }

        TEST_ASSERT_EQUAL_HEX64(driver_line_raw_data.timestamp.sec, deserialized_line_raw_data.timestamp.sec);
        TEST_ASSERT_EQUAL_HEX64(driver_line_raw_data.timestamp.nsec, deserialized_line_raw_data.timestamp.nsec);

        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_confidence(&driver_line_raw_data),
                                mpc_line_raw_data_get_confidence(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_id(&driver_line_raw_data),
                                mpc_line_raw_data_get_id(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_type(&driver_line_raw_data),
                                mpc_line_raw_data_get_type(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_width(&driver_line_raw_data),
                                mpc_line_raw_data_get_width(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_color(&driver_line_raw_data),
                                mpc_line_raw_data_get_color(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_dx_begin(&driver_line_raw_data),
                                mpc_line_raw_data_get_dx_begin(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_dx_end(&driver_line_raw_data),
                                mpc_line_raw_data_get_dx_end(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_dy(&driver_line_raw_data),
                                mpc_line_raw_data_get_dy(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_angle_diff(&driver_line_raw_data),
                                mpc_line_raw_data_get_angle_diff(&deserialized_line_raw_data));
        TEST_ASSERT_EQUAL_HEX16(mpc_line_raw_data_get_horizon_curve(&driver_line_raw_data),
                                mpc_line_raw_data_get_horizon_curve(&deserialized_line_raw_data));
    }
}

static void test_mpc_object_list_raw_data_serialize_and_deserialize_4byte_aligned(void)
{
    const uint16_t              buf_size       = 580;
    const uint16_t              error_buf_size = 500;
    uint8_t                     i;
    uint8_t                     buffer[600];
    struct MpcObjectListRawData object_list_raw_data;

    memset(buffer, 0, 600);

    TEST_ASSERT_EQUAL_INT(buf_size, mpc_object_list_raw_data_get_serialized_size_4byte_aligned(&driver.objects));

    TEST_ASSERT_EQUAL_INT(RC_SERIALIZATION_BUFFER_OVERFLOW,
                          mpc_object_list_raw_data_serialize_4byte_aligned(&driver.objects, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size,
                          mpc_object_list_raw_data_serialize_4byte_aligned(&driver.objects, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                          mpc_object_list_raw_data_deserialize_4byte_aligned(&driver.objects, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size,
                          mpc_object_list_raw_data_deserialize_4byte_aligned(&object_list_raw_data, buffer, buf_size));

    for (i = 0; i < MPC_OBJECT_NUM; i++)
    {
        TEST_ASSERT_EQUAL_HEX64(driver.objects.object[i].timestamp.sec, object_list_raw_data.object[i].timestamp.sec);
        TEST_ASSERT_EQUAL_HEX64(driver.objects.object[i].timestamp.nsec, object_list_raw_data.object[i].timestamp.nsec);

        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_confidence(&driver.objects.object[i]),
                                mpc_object_raw_data_get_confidence(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_id(&driver.objects.object[i]),
                                mpc_object_raw_data_get_id(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_classification(&driver.objects.object[i]),
                                mpc_object_raw_data_get_classification(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_age(&driver.objects.object[i]),
                                mpc_object_raw_data_get_age(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_inv_ttc(&driver.objects.object[i]),
                                mpc_object_raw_data_get_inv_ttc(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_lon_dist(&driver.objects.object[i]),
                                mpc_object_raw_data_get_lon_dist(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_lon_velocity(&driver.objects.object[i]),
                                mpc_object_raw_data_get_lon_velocity(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_center(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_center(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_width(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_width(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_speed(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_speed(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_edge_left(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_edge_left(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_edge_right(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_edge_right(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_overlap_egolane_left(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_overlap_egolane_left(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_overlap_egolane_right(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_overlap_egolane_right(&object_list_raw_data.object[i]));
    }
}

static void test_mpc_object_list_raw_data_serialize_and_deserialize_8byte_aligned(void)
{
    const uint16_t              buf_size       = 584;
    const uint16_t              error_buf_size = 500;
    uint8_t                     i;
    uint8_t                     buffer[600];
    struct MpcObjectListRawData object_list_raw_data;

    memset(buffer, 0, 600);

    TEST_ASSERT_EQUAL_INT(buf_size, mpc_object_list_raw_data_get_serialized_size_8byte_aligned(&driver.objects));

    TEST_ASSERT_EQUAL_INT(RC_SERIALIZATION_BUFFER_OVERFLOW,
                          mpc_object_list_raw_data_serialize_8byte_aligned(&driver.objects, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size,
                          mpc_object_list_raw_data_serialize_8byte_aligned(&driver.objects, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                          mpc_object_list_raw_data_deserialize_8byte_aligned(&driver.objects, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size,
                          mpc_object_list_raw_data_deserialize_8byte_aligned(&object_list_raw_data, buffer, buf_size));

    for (i = 0; i < MPC_OBJECT_NUM; i++)
    {
        TEST_ASSERT_EQUAL_HEX64(driver.objects.object[i].timestamp.sec, object_list_raw_data.object[i].timestamp.sec);
        TEST_ASSERT_EQUAL_HEX64(driver.objects.object[i].timestamp.nsec, object_list_raw_data.object[i].timestamp.nsec);

        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_confidence(&driver.objects.object[i]),
                                mpc_object_raw_data_get_confidence(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_id(&driver.objects.object[i]),
                                mpc_object_raw_data_get_id(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_classification(&driver.objects.object[i]),
                                mpc_object_raw_data_get_classification(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_age(&driver.objects.object[i]),
                                mpc_object_raw_data_get_age(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_inv_ttc(&driver.objects.object[i]),
                                mpc_object_raw_data_get_inv_ttc(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_lon_dist(&driver.objects.object[i]),
                                mpc_object_raw_data_get_lon_dist(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_lon_velocity(&driver.objects.object[i]),
                                mpc_object_raw_data_get_lon_velocity(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_center(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_center(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_width(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_width(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_speed(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_speed(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_edge_left(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_edge_left(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_edge_right(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_edge_right(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_overlap_egolane_left(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_overlap_egolane_left(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_overlap_egolane_right(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_overlap_egolane_right(&object_list_raw_data.object[i]));
    }
}

static void test_mpc_object_list_raw_data_serialize_and_deserialize_default(void)
{
    const uint16_t              buf_size       = 580;
    const uint16_t              error_buf_size = 500;
    uint8_t                     i;
    uint8_t                     buffer[600];
    struct MpcObjectListRawData object_list_raw_data;

    memset(buffer, 0, 600);

    TEST_ASSERT_EQUAL_INT(buf_size, mpc_object_list_raw_data_get_serialized_size(&driver.objects));

    TEST_ASSERT_EQUAL_INT(RC_SERIALIZATION_BUFFER_OVERFLOW,
                          mpc_object_list_raw_data_serialize(&driver.objects, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, mpc_object_list_raw_data_serialize(&driver.objects, buffer, buf_size));

    TEST_ASSERT_EQUAL_INT(RC_DESERIALIZATION_BUFFER_UNDERFLOW,
                          mpc_object_list_raw_data_deserialize(&driver.objects, buffer, error_buf_size));
    TEST_ASSERT_EQUAL_INT(buf_size, mpc_object_list_raw_data_deserialize(&object_list_raw_data, buffer, buf_size));

    for (i = 0; i < MPC_OBJECT_NUM; i++)
    {
        TEST_ASSERT_EQUAL_HEX64(driver.objects.object[i].timestamp.sec, object_list_raw_data.object[i].timestamp.sec);
        TEST_ASSERT_EQUAL_HEX64(driver.objects.object[i].timestamp.nsec, object_list_raw_data.object[i].timestamp.nsec);

        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_confidence(&driver.objects.object[i]),
                                mpc_object_raw_data_get_confidence(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_id(&driver.objects.object[i]),
                                mpc_object_raw_data_get_id(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_classification(&driver.objects.object[i]),
                                mpc_object_raw_data_get_classification(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_age(&driver.objects.object[i]),
                                mpc_object_raw_data_get_age(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_inv_ttc(&driver.objects.object[i]),
                                mpc_object_raw_data_get_inv_ttc(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_lon_dist(&driver.objects.object[i]),
                                mpc_object_raw_data_get_lon_dist(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_lon_velocity(&driver.objects.object[i]),
                                mpc_object_raw_data_get_lon_velocity(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_center(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_center(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_width(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_width(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_speed(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_speed(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_edge_left(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_edge_left(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_edge_right(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_edge_right(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_overlap_egolane_left(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_overlap_egolane_left(&object_list_raw_data.object[i]));
        TEST_ASSERT_EQUAL_HEX16(mpc_object_raw_data_get_angle_overlap_egolane_right(&driver.objects.object[i]),
                                mpc_object_raw_data_get_angle_overlap_egolane_right(&object_list_raw_data.object[i]));
    }
}

void test_mpc_failure_case(void)
{
    time_t           utc_seconds;
    struct Timestamp sys_time;

    utc_seconds = time((time_t*)NULL);
    timestamp_init_from_sec(&sys_time, utc_seconds);

    TEST_ASSERT_EQUAL_INT(RC_SUCCESS, mpc_msg_id_is_valid(ID_BV1_Lin_01_A));
    TEST_ASSERT_EQUAL_INT(RC_FAIL, mpc_msg_id_is_valid(0xFF));

    driver.parse_state = MPC_PARSE_IDLE;
    TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_DATA_ERROR,
                            mpc_driver_process_data(&driver, &sys_time, mpc_object_partA_msg[0].id,
                                                    mpc_object_partA_msg[0].data, mpc_object_partA_msg[0].len));

    driver.parse_state = MPC_PARSE_LINE;
    TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_DATA_ERROR,
                            mpc_driver_process_data(&driver, &sys_time, mpc_object_partA_msg[0].id,
                                                    mpc_object_partA_msg[0].data, mpc_object_partA_msg[0].len));

    driver.parse_state = MPC_PARSE_OBJECT;
    TEST_ASSERT_EQUAL_INT64(RC_MPC_PARSE_DATA_ERROR,
                            mpc_driver_process_data(&driver, &sys_time, mpc_line_partA_msg[0].id,
                                                    mpc_line_partA_msg[0].data, mpc_line_partA_msg[0].len));
}

int main(void)
{
    UNITY_BEGIN();

    init_line_can_msg();
    init_object_can_msg();
    RUN_TEST(test_mpc_driver_init);
    RUN_TEST(test_mpc_driver_process_line_data);
    RUN_TEST(test_mpc_driver_process_object_data);
    RUN_TEST(test_mpc_line_raw_data_serialize_and_deserialize_4byte_aligned);
    RUN_TEST(test_mpc_line_raw_data_serialize_and_deserialize_8byte_aligned);
    RUN_TEST(test_mpc_line_raw_data_serialize_and_deserialize_default);
    RUN_TEST(test_mpc_object_list_raw_data_serialize_and_deserialize_4byte_aligned);
    RUN_TEST(test_mpc_object_list_raw_data_serialize_and_deserialize_8byte_aligned);
    RUN_TEST(test_mpc_object_list_raw_data_serialize_and_deserialize_default);
    RUN_TEST(test_mpc_failure_case);

    return UNITY_END();
}
