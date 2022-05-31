/*!
 * @file conti_radar_driver.c
 * @brief This source file implements conti radar sensor driver functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <assert.h>
#include <holo_c/sensors/dbc/conti_radar_dbc.h>
#include <holo_c/sensors/conti_radar/conti_radar_driver.h>
#include <stdio.h>
#include <string.h>

retcode_t conti_radar_driver_init(struct ContiRadarDriver* driver)
{
    assert(driver != NULL);

    driver->object_list.num = 0;
    driver->parse_state     = CONTI_RADAR_PARSE_IDLE;

    return RC_SUCCESS;
}

static uint8_t part1_msg_buf[5][100][8];
static uint8_t part2_msg_buf[5][100][8];
static uint8_t part3_msg_buf[5][100][8];

static uint8_t part1_msg_index[5];
static uint8_t part2_msg_index[5];
static uint8_t part3_msg_index[5];

static uint8_t part1_obj_id[5];
static uint8_t part2_obj_id[5];
static uint8_t part3_obj_id[5];


void ObjectId0Status(struct ContiRadarDriver* driver, const struct Timestamp timestamp, uint8_t index)
{
    uint8_t   i, j, k;
    for (i = 0; i < part1_msg_index[index]; i++)
    {
        part1_obj_id[index] = GET_Object_1_General_Object_ID(part1_msg_buf[index][i]);

        for (j = 0; j < part2_msg_index[index]; j++)
        {
            part2_obj_id[index] = GET_Object_2_Quality_Object_ID(part2_msg_buf[index][j]);

            if (part2_obj_id[index] == part1_obj_id[index])
            {
                for (k = 0; k < part3_msg_index[index]; k++)
                {
                    part3_obj_id[index] = GET_Object_3_Extended_Object_ID(part3_msg_buf[index][k]);

                    if (part3_obj_id[index] == part1_obj_id[index])
                    {
                        conti_radar_object_raw_data_set_timestamp(
                            &driver->object_list.objects[driver->object_list.num], timestamp);

                        conti_radar_object_raw_data_construct_part1(
                            &driver->object_list.objects[driver->object_list.num], part1_msg_buf[index][i]);

                        conti_radar_object_raw_data_construct_part2(
                            &driver->object_list.objects[driver->object_list.num], part2_msg_buf[index][j]);

                        conti_radar_object_raw_data_construct_part3(
                            &driver->object_list.objects[driver->object_list.num], part3_msg_buf[index][k]);

                        driver->object_list.num++;
                    }
                }
            }
        }
    }
}

retcode_t conti_radar_driver_process_data(struct ContiRadarDriver* driver, const struct Timestamp timestamp,
                                          uint8_t index, uint32_t msg_id, const uint8_t* msg, uint8_t len)
{
    assert(driver != NULL);
    assert(msg != NULL);

    retcode_t rc = RC_FAIL;

    switch (msg_id)
    {
        case ID_Object_0_Status:
            driver->object_list.num = GET_Object_0_Status_Object_NofObjects(msg);
            memset(driver->object_list.objects, 0, CONTI_RADAR_OBJECT_NUM * sizeof(struct ContiRadarObjectRawData));

            if (driver->object_list.num != 0)
            {
                driver->object_list.num = 0;
                ObjectId0Status(driver, timestamp, index);
            }

            part1_msg_index[index] = 0;
            part2_msg_index[index] = 0;
            part3_msg_index[index] = 0;

            rc = RC_SUCCESS;
            break;

        case ID_Object_1_General:
            memcpy(part1_msg_buf[index][part1_msg_index[index]++], msg, len);
            rc = RC_PARSE_CONTI_RADAR_CONTINUE;
            break;

        case ID_Object_2_Quality:
            memcpy(part2_msg_buf[index][part2_msg_index[index]++], msg, len);
            rc = RC_PARSE_CONTI_RADAR_CONTINUE;
            break;

        case ID_Object_3_Extended:
            memcpy(part3_msg_buf[index][part3_msg_index[index]++], msg, len);
            rc = RC_PARSE_CONTI_RADAR_CONTINUE;
            break;

        default:
            rc = RC_PARSE_CONTI_RADAR_ID_ERROR;
            break;
    };

    return rc;
}
