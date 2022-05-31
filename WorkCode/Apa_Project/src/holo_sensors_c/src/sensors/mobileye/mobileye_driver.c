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
#include <holo_c/sensors/mobileye/mobileye_driver.h>
#include <stdio.h>
#include <string.h>

retcode_t mobileye_msg_id_is_valid(uint32_t id)
{
    retcode_t rc = RC_FAIL;
    uint16_t  i;

    for (i = 0; i < (sizeof(mobileye_msg_id_table) / sizeof(uint32_t)); i++)
    {
        if (id == mobileye_msg_id_table[i])
        {
            rc = RC_SUCCESS;
            break;
        }
    }

    return rc;
}

retcode_t mobileye_driver_init(struct MobileyeDriver* driver)
{
    assert(driver != NULL);

    driver->parse_state = MOBILEYE_PARSE_IDLE;

    memset(&driver->lanes, 0, sizeof(struct MobileyeLaneRawData) * MOBILEYE_LANE_NUM);

    driver->objects.num = 0;
    memset(&driver->objects, 0, sizeof(struct MobileyeObjectRawData) * MOBILEYE_OBJECT_NUM);

    return RC_SUCCESS;
}

retcode_t mobileye_driver_process_data(void)
{
    //@TODO there is no ME connected to TC297 now, add later 
    return 0;
}
