/*!
 * @brief Unit test for control_command.
 * @author lijiawen(lijiawen@holomaitc.com)
 * @date 2019-10-25
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 *             notice.
 */

#include <holo_c/common/control_command.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/types.h>
#include <unity.h>

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test void control_command_init_default(struct ControlCommand* command);
 */
static void test_control_command_init_default(void)
{
    struct ControlCommand command;
    control_command_init_default(&command);

    TEST_ASSERT_EQUAL_UINT32(0u, timestamp_get_sec(control_command_get_timestamp(&command)));
    TEST_ASSERT_EQUAL_UINT32(0u, timestamp_get_nsec(control_command_get_timestamp(&command)));

    TEST_ASSERT_EQUAL_FLOAT(LATERAL_CONTROL_MODEL_DISABLE, control_command_get_lateral_control_model(&command));
    TEST_ASSERT_EQUAL_FLOAT(LONGITUDINAL_CONTROL_MODEL_DISABLE,
                            control_command_get_longitudinal_control_model(&command));
    TEST_ASSERT_EQUAL_FLOAT(GEAR_CONTROL_MODEL_DISABLE, control_command_get_gear_control_model(&command));

    TEST_ASSERT_EQUAL_FLOAT(0.0f, control_command_get_lateral_control_value(&command));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, control_command_get_longitudinal_control_value1(&command));
    TEST_ASSERT_EQUAL_FLOAT(0.0f, control_command_get_longitudinal_control_value2(&command));

    TEST_ASSERT_EQUAL_UINT8(0u, control_command_get_gear_command(&command));
    TEST_ASSERT_EQUAL_INT32(GEAR_POSITION_UNKNOWN, control_command_get_gear_position(&command));
    TEST_ASSERT_EQUAL_INT32(0, control_command_get_gear_level(&command));
    TEST_ASSERT_FALSE(control_command_get_handbrake(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test
 */
static void test_control_command_timestamp(void)
{
    struct ControlCommand command;
    struct Timestamp      stamp;
    control_command_init_default(&command);
    timestamp_init_from_sec_nsec(&stamp, 1, 2);

    const struct Timestamp* stamp1 = control_command_get_timestamp(&command);
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_sec(stamp1));
    TEST_ASSERT_EQUAL_UINT32(0, timestamp_get_nsec(stamp1));
    control_command_set_timestamp(&command, &stamp);
    TEST_ASSERT_EQUAL_UINT32(1, timestamp_get_sec(stamp1));
    TEST_ASSERT_EQUAL_UINT32(2, timestamp_get_nsec(stamp1));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_lateral_control_model(void)
{
    struct ControlCommand command;
    control_command_set_lateral_control_model(&command, LATERAL_CONTROL_MODEL_STEERING_ANGLE);
    TEST_ASSERT_EQUAL_FLOAT(LATERAL_CONTROL_MODEL_STEERING_ANGLE, control_command_get_lateral_control_model(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_longitudinal_control_model(void)
{
    struct ControlCommand command;
    control_command_set_longitudinal_control_model(&command, LONGITUDINAL_CONTROL_MODEL_TORQUE);
    TEST_ASSERT_EQUAL_FLOAT(LONGITUDINAL_CONTROL_MODEL_TORQUE,
                            control_command_get_longitudinal_control_model(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_gear_control_model(void)
{
    struct ControlCommand command;
    control_command_set_gear_control_model(&command, GEAR_CONTROL_MODEL_GEAR_CONTROL);
    TEST_ASSERT_EQUAL_FLOAT(GEAR_CONTROL_MODEL_GEAR_CONTROL, control_command_get_gear_control_model(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_lateral_torque(void)
{
    struct ControlCommand command;
    control_command_set_lateral_torque(&command, 18.5);
    TEST_ASSERT_EQUAL_FLOAT(18.5, control_command_get_lateral_torque(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_lateral_front_wheel_angle(void)
{
    struct ControlCommand command;
    control_command_set_lateral_front_wheel_angle(&command, 19.5);
    TEST_ASSERT_EQUAL_FLOAT(19.5, control_command_get_lateral_front_wheel_angle(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_lateral_steering_angle(void)
{
    struct ControlCommand command;
    control_command_set_lateral_steering_angle(&command, 17.5);
    TEST_ASSERT_EQUAL_FLOAT(17.5, control_command_get_lateral_steering_angle(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_lateral_control_value(void)
{
    struct ControlCommand command;
    control_command_set_lateral_control_value(&command, 8.5);
    TEST_ASSERT_EQUAL_FLOAT(8.5, control_command_get_lateral_control_value(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_longitudinal_control_value(void)
{
    struct ControlCommand command;
    control_command_set_longitudinal_control_value1(&command, 2.5);
    TEST_ASSERT_EQUAL_FLOAT(2.5, control_command_get_longitudinal_control_value1(&command));

    control_command_set_longitudinal_control_value2(&command, 3.5);
    TEST_ASSERT_EQUAL_FLOAT(3.5, control_command_get_longitudinal_control_value2(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_longitudinal_acceleration(void)
{
    struct ControlCommand command;
    control_command_set_longitudinal_acceleration(&command, 8.5);
    TEST_ASSERT_EQUAL_FLOAT(8.5, control_command_get_longitudinal_acceleration(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_longitudinal_deceleration(void)
{
    struct ControlCommand command;
    control_command_set_longitudinal_deceleration(&command, 2.5);
    TEST_ASSERT_EQUAL_FLOAT(2.5, control_command_get_longitudinal_deceleration(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_longitudinal_torque(void)
{
    struct ControlCommand command;
    control_command_set_longitudinal_torque(&command, 3.5);
    TEST_ASSERT_EQUAL_FLOAT(3.5, control_command_get_longitudinal_torque(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_longitudinal_torque_deceleration(void)
{
    struct ControlCommand command;
    control_command_set_longitudinal_torque_deceleration(&command, 4.5);
    TEST_ASSERT_EQUAL_FLOAT(4.5, control_command_get_longitudinal_torque_deceleration(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_longitudinal_speed_limit(void)
{
    struct ControlCommand command;
    control_command_set_longitudinal_speed_limit(&command, 4.5);
    TEST_ASSERT_EQUAL_FLOAT(4.5, control_command_get_longitudinal_speed_limit(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 */
static void test_control_command_longitudinal_stop_distance(void)
{
    struct ControlCommand command;
    control_command_set_longitudinal_stop_distance(&command, 5.5);
    TEST_ASSERT_EQUAL_FLOAT(5.5, control_command_get_longitudinal_stop_distance(&command));
}

/**
 * @brief Test:
 */
static void test_control_command_gear(void)
{
    struct ControlCommand command;
    control_command_init_default(&command);
    TEST_ASSERT_EQUAL_UINT8(0x00, control_command_get_gear_command(&command));

    control_command_set_gear_position(&command, GEAR_POSITION_P);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_P, control_command_get_gear_position(&command));
    TEST_ASSERT_EQUAL_UINT8(0x20, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x20);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_P, control_command_get_gear_position(&command));

    control_command_set_gear_position(&command, GEAR_POSITION_R);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_R, control_command_get_gear_position(&command));
    TEST_ASSERT_EQUAL_UINT8(0x40, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x40);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_R, control_command_get_gear_position(&command));

    control_command_set_gear_position(&command, GEAR_POSITION_N);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_N, control_command_get_gear_position(&command));
    TEST_ASSERT_EQUAL_UINT8(0x60, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x60);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_N, control_command_get_gear_position(&command));

    control_command_set_gear_position(&command, GEAR_POSITION_D);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_D, control_command_get_gear_position(&command));
    TEST_ASSERT_EQUAL_UINT8(0x80, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x80);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_D, control_command_get_gear_position(&command));

    control_command_set_gear_position(&command, GEAR_POSITION_S);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_S, control_command_get_gear_position(&command));
    TEST_ASSERT_EQUAL_UINT8(0xa0, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0xa0);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_S, control_command_get_gear_position(&command));

    control_command_set_gear_position(&command, GEAR_POSITION_UNKNOWN);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_UNKNOWN, control_command_get_gear_position(&command));
    TEST_ASSERT_EQUAL_UINT8(0x00, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x00);
    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_UNKNOWN, control_command_get_gear_position(&command));

    control_command_set_gear_level(&command, 1);
    TEST_ASSERT_EQUAL_UINT8(1u, control_command_get_gear_level(&command));
    TEST_ASSERT_EQUAL_UINT8(0x02, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x02);
    TEST_ASSERT_EQUAL_UINT8(1u, control_command_get_gear_level(&command));

    control_command_set_gear_level(&command, 15);
    TEST_ASSERT_EQUAL_UINT8(15u, control_command_get_gear_level(&command));
    TEST_ASSERT_EQUAL_UINT8(0x1e, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x1e);
    TEST_ASSERT_EQUAL_UINT8(15u, control_command_get_gear_level(&command));

    control_command_set_gear_level(&command, 16);
    TEST_ASSERT_EQUAL_UINT8(15u, control_command_get_gear_level(&command));
    TEST_ASSERT_EQUAL_UINT8(0x1e, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x1e);
    TEST_ASSERT_EQUAL_UINT8(15u, control_command_get_gear_level(&command));

    control_command_set_gear_level(&command, 255);
    TEST_ASSERT_EQUAL_UINT8(15u, control_command_get_gear_level(&command));
    TEST_ASSERT_EQUAL_UINT8(0x1e, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x1e);
    TEST_ASSERT_EQUAL_UINT8(15u, control_command_get_gear_level(&command));

    control_command_set_gear_level(&command, 0);
    TEST_ASSERT_EQUAL_UINT8(0u, control_command_get_gear_level(&command));
    TEST_ASSERT_EQUAL_UINT8(0x00, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x00);
    TEST_ASSERT_EQUAL_UINT8(0u, control_command_get_gear_level(&command));

    control_command_set_handbrake(&command, true);
    TEST_ASSERT_TRUE(control_command_get_handbrake(&command));
    TEST_ASSERT_EQUAL_UINT8(0x01, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x01);
    TEST_ASSERT_TRUE(control_command_get_handbrake(&command));

    control_command_set_handbrake(&command, false);
    TEST_ASSERT_FALSE(control_command_get_handbrake(&command));
    TEST_ASSERT_EQUAL_UINT8(0x00, control_command_get_gear_command(&command));
    control_command_set_gear_command(&command, 0x00);
    TEST_ASSERT_FALSE(control_command_get_handbrake(&command));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 *          1. uint32_t control_command_get_serialized_size(const struct ControlCommand* command)
 */
static void test_control_command_get_serialized_size(void)
{
    struct ControlCommand cmd;

    TEST_ASSERT_EQUAL_UINT32(36, control_command_get_serialized_size(&cmd));
}

/* -------------------------------------------------------------------------------------------------------------------*/
/**
 * @brief Test:
 *          1. retcode_t control_command_serialize(const struct ControlCommand* command, uint8_t* buffer, uint32_t
 * buffer_size)
 */
static void test_control_command_serialize_deserialize(void)
{
    struct ControlCommand command1;
    struct ControlCommand command2;
    uint8_t               buffer[1024];
    retcode_t             retcode;

    control_command_init_default(&command1);

    control_command_set_lateral_control_model(&command1, LATERAL_CONTROL_MODEL_TORQUE);
    control_command_set_longitudinal_control_model(&command1, LONGITUDINAL_CONTROL_MODEL_ACCELERATE);
    control_command_set_gear_control_model(&command1, GEAR_CONTROL_MODEL_GEAR_CONTROL);
    control_command_set_lateral_control_value(&command1, 1.0f);
    control_command_set_longitudinal_control_value1(&command1, 2.0f);
    control_command_set_longitudinal_control_value2(&command1, 3.0f);
    control_command_set_gear_position(&command1, GEAR_POSITION_R);

    retcode = control_command_serialize(&command1, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_SERIALIZATION_BUFFER_OVERFLOW, retcode);
    retcode = control_command_deserialize(&command2, buffer, 0);
    TEST_ASSERT_EQUAL_INT32(RC_DESERIALIZATION_BUFFER_UNDERFLOW, retcode);

    retcode = control_command_serialize(&command1, buffer, sizeof(buffer));
    TEST_ASSERT_GREATER_THAN_INT32(0, retcode);
    retcode = control_command_deserialize(&command2, buffer, sizeof(buffer));
    TEST_ASSERT_GREATER_THAN_INT32(0, retcode);

    TEST_ASSERT_EQUAL_FLOAT(LATERAL_CONTROL_MODEL_TORQUE, control_command_get_lateral_control_model(&command2));
    TEST_ASSERT_EQUAL_FLOAT(LONGITUDINAL_CONTROL_MODEL_ACCELERATE,
                            control_command_get_longitudinal_control_model(&command2));
    TEST_ASSERT_EQUAL_FLOAT(GEAR_CONTROL_MODEL_GEAR_CONTROL, control_command_get_gear_control_model(&command2));

    TEST_ASSERT_EQUAL_FLOAT(1.0, control_command_get_lateral_control_value(&command2));
    TEST_ASSERT_EQUAL_FLOAT(2.0, control_command_get_longitudinal_control_value1(&command2));
    TEST_ASSERT_EQUAL_FLOAT(3.0, control_command_get_longitudinal_control_value2(&command2));

    TEST_ASSERT_EQUAL_UINT8(GEAR_POSITION_R, control_command_get_gear_position(&command2));
    TEST_ASSERT_EQUAL_UINT8(0x40, control_command_get_gear_command(&command2));
}

int main()
{
    UNITY_BEGIN();
    RUN_TEST(test_control_command_init_default);
    RUN_TEST(test_control_command_timestamp);
    RUN_TEST(test_control_command_lateral_control_model);
    RUN_TEST(test_control_command_longitudinal_control_model);
    RUN_TEST(test_control_command_gear_control_model);
    RUN_TEST(test_control_command_lateral_control_value);
    RUN_TEST(test_control_command_lateral_torque);
    RUN_TEST(test_control_command_lateral_front_wheel_angle);
    RUN_TEST(test_control_command_lateral_steering_angle);
    RUN_TEST(test_control_command_longitudinal_control_value);
    RUN_TEST(test_control_command_longitudinal_acceleration);
    RUN_TEST(test_control_command_longitudinal_deceleration);
    RUN_TEST(test_control_command_longitudinal_torque);
    RUN_TEST(test_control_command_longitudinal_torque_deceleration);
    RUN_TEST(test_control_command_longitudinal_speed_limit);
    RUN_TEST(test_control_command_longitudinal_stop_distance);
    RUN_TEST(test_control_command_gear);
    RUN_TEST(test_control_command_get_serialized_size);
    RUN_TEST(test_control_command_serialize_deserialize);
    return UNITY_END();
}
