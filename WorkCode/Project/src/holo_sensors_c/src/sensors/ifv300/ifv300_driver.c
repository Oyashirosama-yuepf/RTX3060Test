/*!
 * @file ifv300_driver.c
 * @brief This source file implements ifv driver operation functions
 * @author liuya@holomatic.com
 * @date 2020-04-15
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <holo_c/sensors/ifv300/ifv300_driver.h>
#include <holo_c/sensors/dbc/ifv300_output_dbc.h>
#include <holo_c/sensors/dbc/ifv300_input_dbc.h>
#include <stdio.h>
#include <string.h>

/**
 * @brief only the can msg id in this table is useful for ifv300 driver
 *
 */
static const uint32_t ifv_msg_id_table[] = {ID_VIS_LANE_INFORMATION,
                                            ID_VIS_LANE_NEAR_LEFT_INDIVIDUAL,
                                            ID_VIS_LANE_NEAR_RIGHT_INDIVIDUAL,
                                            ID_VIS_LANE_NEIGHBOR_LEFT,
                                            ID_VIS_LANE_NEIGHBOR_RIGHT,
                                            ID_VIS_OBS_MSG_1,
                                            ID_VIS_OBS_MSG_2,
                                            ID_VIS_OBS_MSG_3};

retcode_t ifv_msg_id_is_valid(uint32_t id)
{
    retcode_t rc = RC_FAIL;
    uint16_t  i;

    for (i = 0; i < (sizeof(ifv_msg_id_table) / sizeof(uint32_t)); i++)
    {
        if (id == ifv_msg_id_table[i])
        {
            rc = RC_SUCCESS;
            break;
        }
    }

    return rc;
}

retcode_t ifv_driver_init(struct IfvDriver* driver)
{
    assert(driver != NULL);

    driver->parse_state = IFV_PARSE_IDLE;

    memset(&driver->lines, 0, sizeof(struct IfvLinesRawData));

    driver->objects.num = 0;
    memset(&driver->objects, 0, sizeof(struct IfvObjectRawData) * IFV_OBJECT_NUM);

    return RC_SUCCESS;
}


void IfvParseIdle(struct IfvDriver* driver, const struct Timestamp* timestamp, uint32_t id)
{
    if (id == ID_VIS_LANE_INFORMATION)
    {
        ifv_lines_raw_data_set_timestamp(&driver->lines, timestamp);
        driver->parse_state = IFV_PARSE_LINE_HEAD;
    }
    else
    {
        driver->parse_state = IFV_PARSE_ERROR;
    }
}
void IfvParseLineHead(struct IfvDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, retcode_t* rc)
{
    if (id == ID_VIS_LANE_INFORMATION)
    {
        ifv_lines_raw_data_construct_info_head(&driver->lines.line_head, msg);
        driver->parse_state = IFV_PARSE_LINE_NEAR_LEFT;
        *len -= *len;

        *rc = RC_IFV_PARSE_LINE_CONTINUE;
    }
    else
    {
        driver->parse_state = IFV_PARSE_ERROR;
    }
}
void IfvParseLineNearOrNeighbor(struct IfvDriver* driver, uint32_t id, const uint8_t* msg, uint8_t* len, 
                                uint8_t* obj_index, retcode_t* rc)
{
    switch (driver->parse_state)
    {
        case IFV_PARSE_LINE_NEAR_LEFT:
            if (id == ID_VIS_LANE_NEAR_LEFT_INDIVIDUAL)
            {
                ifv_lines_raw_data_construct_info_curve(&driver->lines.left, msg);
                driver->parse_state = IFV_PARSE_LINE_NEAR_RIGHT;
                *len -= *len;

                *rc = RC_IFV_PARSE_LINE_CONTINUE;
            }
            else
            {
                driver->parse_state = IFV_PARSE_ERROR;
            }
            break;
        case IFV_PARSE_LINE_NEAR_RIGHT:
            if (id == ID_VIS_LANE_NEAR_RIGHT_INDIVIDUAL)
            {
                ifv_lines_raw_data_construct_info_curve(&driver->lines.right, msg);
                driver->parse_state = IFV_PARSE_LINE_NEIGHBOR_RIGHT;
                *len -= *len;

                *rc = RC_IFV_PARSE_LINE_CONTINUE;
            }
            else
            {
                driver->parse_state = IFV_PARSE_ERROR;
            }
            break;
        case IFV_PARSE_LINE_NEIGHBOR_RIGHT:
            if (id == ID_VIS_LANE_NEIGHBOR_RIGHT)
            {
                ifv_lines_raw_data_construct_info_curve(&driver->lines.right_right, msg);
                driver->parse_state = IFV_PARSE_LINE_NEIGHBOR_LEFT;
                *len -= *len;

                *rc = RC_IFV_PARSE_LINE_CONTINUE;
            }
            else
            {
                driver->parse_state = IFV_PARSE_ERROR;
            }
            break;
        case IFV_PARSE_LINE_NEIGHBOR_LEFT:
            if (id == ID_VIS_LANE_NEIGHBOR_LEFT)
            {
                ifv_lines_raw_data_construct_info_curve(&driver->lines.left_left, msg);
                driver->parse_state = IFV_PARSE_OBJECT_PART1;
                *len -= *len;
                *obj_index = 0;

                *rc = RC_IFV_PARSE_LINE_COMPLETE;
            }
            else
            {
                driver->parse_state = IFV_PARSE_ERROR;
            }
            break;
        default:break;
    }
}
void IfvParseObjectPart(struct IfvDriver* driver, const struct Timestamp* timestamp, uint32_t id, 
                        const uint8_t* msg, uint8_t* len, uint8_t* obj_index, retcode_t* rc)
{
    switch (driver->parse_state)
    {
        case IFV_PARSE_OBJECT_PART1:
            if (id == ID_VIS_OBS_MSG_1)
            {
                ifv_object_raw_data_set_timestamp(&driver->objects.object[*obj_index], timestamp);
                ifv_object_raw_data_construct_partA(&driver->objects.object[*obj_index], msg);
                driver->parse_state = IFV_PARSE_OBJECT_PART2;
                *len -= *len;

                *rc = RC_IFV_PARSE_OBJ_CONTINUE;
            }
            else
            {
                driver->parse_state = IFV_PARSE_ERROR;
            }
            break;
        case IFV_PARSE_OBJECT_PART2:
            if (id == ID_VIS_OBS_MSG_2)
            {
                ifv_object_raw_data_construct_partB(&driver->objects.object[*obj_index], msg);
                driver->parse_state = IFV_PARSE_OBJECT_PART3;
                *len -= *len;

                *rc = RC_IFV_PARSE_OBJ_CONTINUE;
            }
            else
            {
                driver->parse_state = IFV_PARSE_ERROR;
            }
            break;
        case IFV_PARSE_OBJECT_PART3:
            if (id == ID_VIS_OBS_MSG_3)
            {
                ifv_object_raw_data_construct_partC(&driver->objects.object[*obj_index], msg);

                if (*obj_index == IFV_OBJECT_NUM - 1)
                {
                    ifv_object_list_raw_data_set_obj_num(&driver->objects, IFV_OBJECT_NUM);
                    driver->parse_state = IFV_PARSE_IDLE;

                    *rc = RC_IFV_PARSE_OBJ_COMPLETE;
                }
                else
                {
                    driver->parse_state = IFV_PARSE_OBJECT_PART1;

                    *rc = RC_IFV_PARSE_OBJ_CONTINUE;
                }

                (*obj_index)++;
                *len -= *len;
            }
            else
            {
                driver->parse_state = IFV_PARSE_ERROR;
            }
            break;
        default:break;
    }
}
retcode_t ifv_driver_process_data(struct IfvDriver* driver, const struct Timestamp* timestamp, uint32_t id,
                                  const uint8_t* msg, uint8_t len)
{
    assert(driver != NULL);
    assert(msg != NULL);

    static uint8_t obj_index = 0;
    retcode_t      rc        = RC_FAIL;

    while (len)
    {
        switch (driver->parse_state)
        {
            case IFV_PARSE_IDLE:
                IfvParseIdle(driver, timestamp, id);
                break;
            case IFV_PARSE_LINE_HEAD:
                IfvParseLineHead(driver, id, msg, &len, &rc);
                break;
            case IFV_PARSE_LINE_NEAR_LEFT:
            case IFV_PARSE_LINE_NEAR_RIGHT:
            case IFV_PARSE_LINE_NEIGHBOR_RIGHT:
            case IFV_PARSE_LINE_NEIGHBOR_LEFT:
                IfvParseLineNearOrNeighbor(driver, id, msg, &len, &obj_index, &rc);
                break;

            case IFV_PARSE_OBJECT_PART1:
            case IFV_PARSE_OBJECT_PART2:
            case IFV_PARSE_OBJECT_PART3:
                IfvParseObjectPart(driver, timestamp, id, msg, &len, &obj_index, &rc);
                break;

            case IFV_PARSE_ERROR:
            default:
                rc = RC_IFV_PARSE_DATA_ERROR;
                len -= len;
                driver->parse_state = IFV_PARSE_IDLE;
                break;
        }
    }
    return rc;
}
