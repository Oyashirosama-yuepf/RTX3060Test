/*!
 * @file mpc_driver.c
 * @brief This source file implements mpc driver operation functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <holo_c/sensors/mpc/mpc_driver.h>
#include <stdio.h>
#include <string.h>

retcode_t mpc_msg_id_is_valid(uint32_t id)
{
    retcode_t rc = RC_FAIL;
    uint16_t  i;

    for (i = 0; i < (sizeof(mpc_msg_id_table) / sizeof(uint32_t)); i++)
    {
        if (id == mpc_msg_id_table[i])
        {
            rc = RC_SUCCESS;
            break;
        }
    }

    return rc;
}

retcode_t mpc_driver_init(struct MpcDriver* driver)
{
    assert(driver != NULL);

    driver->parse_state = MPC_PARSE_IDLE;

    memset(&driver->lines, 0, sizeof(struct MpcLineRawData) * MPC_LINE_NUM);

    driver->objects.num = 0;
    memset(&driver->objects, 0, sizeof(struct MpcObjectRawData) * MPC_OBJECT_NUM);

    return RC_SUCCESS;
}

void MpcParseIdle(struct MpcDriver* driver, const struct Timestamp* timestamp, uint32_t id)
{
    if (id == ID_BV1_Lin_01_A)
    {
        mpc_line_raw_data_set_timestamp(&driver->lines.left_left_line, timestamp);
        mpc_line_raw_data_set_timestamp(&driver->lines.left_line, timestamp);
        mpc_line_raw_data_set_timestamp(&driver->lines.right_line, timestamp);
        mpc_line_raw_data_set_timestamp(&driver->lines.right_right_line, timestamp);

        driver->parse_state = MPC_PARSE_LINE;
    }
    else
    {
        driver->parse_state = MPC_PARSE_ERROR;
    }
}
void MpcParseLine(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV1_Lin_01_A:
            mpc_line_raw_data_construct_partA(&driver->lines.left_left_line, msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_LINE_CONTINUE;
            break;

        case ID_BV1_Lin_01_B:
            mpc_line_raw_data_construct_partB(&driver->lines.left_left_line, msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_LINE_CONTINUE;
            break;

        case ID_BV1_Lin_02_A:
            mpc_line_raw_data_construct_partA(&driver->lines.left_line, msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_LINE_CONTINUE;
            break;

        case ID_BV1_Lin_02_B:
            mpc_line_raw_data_construct_partB(&driver->lines.left_line, msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_LINE_CONTINUE;
            break;

        case ID_BV1_Lin_03_A:
            mpc_line_raw_data_construct_partA(&driver->lines.right_line, msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_LINE_CONTINUE;
            break;

        case ID_BV1_Lin_03_B:
            mpc_line_raw_data_construct_partB(&driver->lines.right_line, msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_LINE_CONTINUE;
            break;

        case ID_BV1_Lin_04_A:
            mpc_line_raw_data_construct_partA(&driver->lines.right_right_line, msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_LINE_CONTINUE;
            break;

        case ID_BV1_Lin_04_B:
            mpc_line_raw_data_construct_partB(&driver->lines.right_right_line, msg);
            *len -= *len;
            *rc                 = RC_MPC_PARSE_LINE_COMPLETE;
            driver->parse_state = MPC_PARSE_OBJECT;
            break;

        default:
            driver->parse_state = MPC_PARSE_ERROR;
            break;
    }
}
void MpcParseObjectPart0(struct MpcDriver* driver, const struct Timestamp* timestamp, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    uint16_t  i;

    switch (id)
    {
        case ID_BV_Obj_01_A:
            for (i = 0; i < MPC_OBJECT_NUM; i++)
            {
                mpc_object_raw_data_set_timestamp(&driver->objects.object[i], timestamp);
            }
            mpc_object_raw_data_construct_partA(&driver->objects.object[0], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_01_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[0], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_01_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[0], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_01_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[0], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_01_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[0], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart1(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_02_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[1], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_02_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[1], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_02_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[1], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_02_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[1], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_02_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[1], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_03_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[2], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_03_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[2], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart2(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_03_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[2], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_03_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[2], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_03_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[2], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_04_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[3], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_04_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[3], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_04_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[3], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_04_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[3], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_04_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[3], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart3(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_05_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[4], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_05_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[4], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_05_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[4], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_05_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[4], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_05_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[4], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_06_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[5], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_06_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[5], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart4(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_06_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[5], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_06_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[5], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_06_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[5], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_07_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[6], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_07_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[6], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_07_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[6], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_07_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[6], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart5(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_07_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[6], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_08_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[7], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_08_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[7], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_08_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[7], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_08_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[7], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_08_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[7], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_09_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[8], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart6(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_09_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[8], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_09_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[8], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_09_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[8], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_09_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[8], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_10_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[9], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_10_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[9], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_10_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[9], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart7(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_10_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[9], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_10_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[9], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_11_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[10], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_11_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[10], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_11_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[10], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_11_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[10], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_11_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[10], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart8(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_12_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[11], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_12_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[11], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_12_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[11], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_12_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[11], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_12_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[11], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_13_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[12], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_13_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[12], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart9(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_13_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[12], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_13_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[12], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_13_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[12], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_14_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[13], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_14_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[13], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_14_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[13], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_14_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[13], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart10(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_14_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[13], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_15_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[14], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_15_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[14], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_15_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[14], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_15_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[14], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_15_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[14], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_16_A:
            mpc_object_raw_data_construct_partA(&driver->objects.object[15], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        default: break;
    }
}
void MpcParseObjectPart11(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch (id)
    {
        case ID_BV_Obj_16_B:
            mpc_object_raw_data_construct_partB(&driver->objects.object[15], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_16_C:
            mpc_object_raw_data_construct_partC(&driver->objects.object[15], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_16_D:
            mpc_object_raw_data_construct_partD(&driver->objects.object[15], msg);
            *len -= *len;
            *rc = RC_MPC_PARSE_OBJ_CONTINUE;
            break;
        case ID_BV_Obj_16_E:
            mpc_object_raw_data_construct_partE(&driver->objects.object[15], msg);
            *len -= *len;
            *rc                  = RC_MPC_PARSE_OBJ_COMPLETE;
            driver->parse_state = MPC_PARSE_IDLE;
            driver->objects.num = MPC_OBJECT_NUM;
            break;
        default: break;
    }
}

bool_t MpcParseObject1(struct MpcDriver* driver, const struct Timestamp* timestamp, uint32_t id,
                        const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    switch(id)
    {
        case ID_BV_Obj_01_A:
        case ID_BV_Obj_01_B:
        case ID_BV_Obj_01_C:
        case ID_BV_Obj_01_D:
        case ID_BV_Obj_01_E:
            MpcParseObjectPart0(driver, timestamp, id, msg, len, rc);
            break;
        case ID_BV_Obj_02_A:
        case ID_BV_Obj_02_B:
        case ID_BV_Obj_02_C:
        case ID_BV_Obj_02_D:
        case ID_BV_Obj_02_E:
        case ID_BV_Obj_03_A:
        case ID_BV_Obj_03_B:
            MpcParseObjectPart1(driver, id, msg, len, rc);
            break;
        case ID_BV_Obj_03_C:
        case ID_BV_Obj_03_D:
        case ID_BV_Obj_03_E:
        case ID_BV_Obj_04_A:
        case ID_BV_Obj_04_B:
        case ID_BV_Obj_04_C:
        case ID_BV_Obj_04_D:
        case ID_BV_Obj_04_E:
            MpcParseObjectPart2(driver, id, msg, len, rc);
            break;
        case ID_BV_Obj_05_A:
        case ID_BV_Obj_05_B:
        case ID_BV_Obj_05_C:
        case ID_BV_Obj_05_D:
        case ID_BV_Obj_05_E:
        case ID_BV_Obj_06_A:
        case ID_BV_Obj_06_B:
            MpcParseObjectPart3(driver, id, msg, len, rc);
            break;
        case ID_BV_Obj_06_C:
        case ID_BV_Obj_06_D:
        case ID_BV_Obj_06_E:
        case ID_BV_Obj_07_A:
        case ID_BV_Obj_07_B:
        case ID_BV_Obj_07_C:
        case ID_BV_Obj_07_D:
            MpcParseObjectPart4(driver, id, msg, len, rc);
            break;
        case ID_BV_Obj_07_E:
        case ID_BV_Obj_08_A:
        case ID_BV_Obj_08_B:
        case ID_BV_Obj_08_C:
        case ID_BV_Obj_08_D:
        case ID_BV_Obj_08_E:
        case ID_BV_Obj_09_A:
            MpcParseObjectPart5(driver, id, msg, len, rc);
            break;
        default:
            return false;
    }
    return true;
}

bool_t MpcParseObject2(struct MpcDriver* driver, uint32_t id, const uint8_t* msg, 
                        uint8_t* len, retcode_t* rc)
{
    switch(id)
    {
        case ID_BV_Obj_09_B:
        case ID_BV_Obj_09_C:
        case ID_BV_Obj_09_D:
        case ID_BV_Obj_09_E:
        case ID_BV_Obj_10_A:
        case ID_BV_Obj_10_B:
        case ID_BV_Obj_10_C:
            MpcParseObjectPart6(driver, id, msg, len, rc);
            break;
        case ID_BV_Obj_10_D:
        case ID_BV_Obj_10_E:
        case ID_BV_Obj_11_A:
        case ID_BV_Obj_11_B:
        case ID_BV_Obj_11_C:
        case ID_BV_Obj_11_D:
        case ID_BV_Obj_11_E:
            MpcParseObjectPart7(driver, id, msg, len, rc);
            break;
        case ID_BV_Obj_12_A:
        case ID_BV_Obj_12_B:
        case ID_BV_Obj_12_C:
        case ID_BV_Obj_12_D:
        case ID_BV_Obj_12_E:
        case ID_BV_Obj_13_A:
        case ID_BV_Obj_13_B:
            MpcParseObjectPart8(driver, id, msg, len, rc);
            break;
        case ID_BV_Obj_13_C:
        case ID_BV_Obj_13_D:
        case ID_BV_Obj_13_E:
        case ID_BV_Obj_14_A:
        case ID_BV_Obj_14_B:
        case ID_BV_Obj_14_C:
        case ID_BV_Obj_14_D:
            MpcParseObjectPart9(driver, id, msg, len, rc);
            break;
        case ID_BV_Obj_14_E:
        case ID_BV_Obj_15_A:
        case ID_BV_Obj_15_B:
        case ID_BV_Obj_15_C:
        case ID_BV_Obj_15_D:
        case ID_BV_Obj_15_E:
        case ID_BV_Obj_16_A:
            MpcParseObjectPart10(driver, id, msg, len, rc);
            break;
        case ID_BV_Obj_16_B:
        case ID_BV_Obj_16_C:
        case ID_BV_Obj_16_D:
        case ID_BV_Obj_16_E:
            MpcParseObjectPart11(driver, id, msg, len, rc);
            break;
        default:
            return false;
    }
    return true;
}

retcode_t mpc_driver_process_data(struct MpcDriver* driver, const struct Timestamp* timestamp, uint32_t id,
                                  const uint8_t* msg, uint8_t len)
{
    assert(driver != NULL);
    assert(msg != NULL);

    retcode_t rc = RC_FAIL;

    while (len)
    {
        switch (driver->parse_state)
        {
            case MPC_PARSE_IDLE:
                MpcParseIdle(driver, timestamp, id);
                break;

            case MPC_PARSE_LINE:
                MpcParseLine(driver, id, msg, &len, &rc);
                break;

            case MPC_PARSE_OBJECT:
                if(MpcParseObject1(driver, timestamp, id, msg, &len, &rc) || MpcParseObject2(driver, id, msg, &len, &rc))
                {
                }
                else
                {
                    driver->parse_state = MPC_PARSE_ERROR;
                }
                break;

            case MPC_PARSE_ERROR:
            default:
                rc = RC_MPC_PARSE_DATA_ERROR;
                len -= len;
                driver->parse_state = MPC_PARSE_IDLE;
                break;
        }
    }
    return rc;
}
