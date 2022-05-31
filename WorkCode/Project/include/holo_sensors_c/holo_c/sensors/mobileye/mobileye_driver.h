/*!
 * @file mpc_driver.h
 * @brief This header file defines bosch mpc sensor driver functions
 * @author liuya@holomatic.com
 * @date 2019-09-25
 * @attention Copyright @ Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#ifndef HOLO_C_SENSORS_MOBILEYE_DRIVER_H_
#define HOLO_C_SENSORS_MOBILEYE_DRIVER_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/types.h>
#include <holo_c/sensors/mobileye/mobileye_dbc_output.h>
#include <holo_c/sensors/mobileye/structure/mobileye_lane.h>
#include <holo_c/sensors/mobileye/structure/mobileye_object.h>


/**
 * @addtogroup sensors
 * @{
 */

/**
 * @brief only the can msg id in this table is useful for mobileye driver
 *
 */
static const uint32_t mobileye_msg_id_table[] = { 
	ID_Lane0_Signals_Message_Part0, 
	ID_Lane0_Signals_Message_Part1,
    ID_Lane0_Signals_Message_Part2, 
    ID_Lane1_Signals_Message_Part0, 
    ID_Lane1_Signals_Message_Part1,
    ID_Lane1_Signals_Message_Part2, 
    ID_Lane2_Signals_Message_Part0, 
	ID_Lane2_Signals_Message_Part1,
    ID_Lane2_Signals_Message_Part2, 
    ID_Lane3_Signals_Message_Part0, 
    ID_Lane3_Signals_Message_Part1,
    ID_Lane3_Signals_Message_Part2, 
    ID_Objects_Signals_Header,
    ID_Objects0_Signals_Message_Part0,  
    ID_Objects0_Signals_Message_Part1,
	ID_Objects0_Signals_Message_Part2,
	ID_Objects0_Signals_Message_Part3,
	ID_Objects1_Signals_Message_Part0,  
    ID_Objects1_Signals_Message_Part1,
	ID_Objects1_Signals_Message_Part2,
	ID_Objects1_Signals_Message_Part3,
	ID_Objects2_Signals_Message_Part0,  
    ID_Objects2_Signals_Message_Part1,
	ID_Objects2_Signals_Message_Part2,
	ID_Objects2_Signals_Message_Part3,
	ID_Objects3_Signals_Message_Part0,  
    ID_Objects3_Signals_Message_Part1,
	ID_Objects3_Signals_Message_Part2,
	ID_Objects3_Signals_Message_Part3,
	ID_Objects4_Signals_Message_Part0,  
    ID_Objects4_Signals_Message_Part1,
	ID_Objects4_Signals_Message_Part2,
	ID_Objects4_Signals_Message_Part3,
	ID_Objects5_Signals_Message_Part0,  
    ID_Objects5_Signals_Message_Part1,
	ID_Objects5_Signals_Message_Part2,
	ID_Objects5_Signals_Message_Part3,
	ID_Objects6_Signals_Message_Part0,  
    ID_Objects6_Signals_Message_Part1,
	ID_Objects6_Signals_Message_Part2,
	ID_Objects6_Signals_Message_Part3,
	ID_Objects7_Signals_Message_Part0,  
    ID_Objects7_Signals_Message_Part1,
	ID_Objects7_Signals_Message_Part2,
	ID_Objects7_Signals_Message_Part3};

/**
 * @brief mobileye can data process state
 *
 */
enum MobileyeParseState
{
    MOBILEYE_PARSE_IDLE = 0,
    MOBILEYE_PARSE_LINE,
    MOBILEYE_PARSE_OBJECT,
    MOBILEYE_PARSE_ERROR,
};

/**
 * @brief mobileye driver struct
 *
 */
struct MobileyeDriver
{
    enum MobileyeParseState          parse_state;
    struct MobileyeLanesRawData      lanes;
    struct MobileyeObjectListRawData objects;
};

/**
 * @brief whether the can msg id received in the valide table
 *
 * @param id can msg id
 * @return retcode_t RC_SUCCESS(valid), RC_FAIL(invalide)
 */
retcode_t mobileye_msg_id_is_valid(uint32_t id);

/**
 * @brief Init mpc driver
 *
 * @param driver Mpc driver pointer
 * @return retcode_t RC_SUCCESS
 */
retcode_t mobileye_driver_init(struct MobileyeDriver* driver);

/**
 * @brief Process mcp CAN bus data
 *
 * @param driver Mpc driver pointer
 * @param timestamp CAN data received timestamp
 * @param id CAN msg id
 * @param msg CAN msg content
 * @param len CAN msg length
 *
 * @return retcode_t RC_MPC_PARSE_LINE_CONTINUE Parse lane boundaries not complete yet.
 * @return retcode_t RC_MPC_PARSE_LINE_COMPLETE Parse lane boundaries complete.
 * @return retcode_t RC_MPC_PARSE_OBJ_CONTINUE Parse object not complete yet.
 * @return retcode_t RC_MPC_PARSE_OBJ_COMPLETE Parse object complete.
 * @return retcode_t RC_MPC_PARSE_ID_ERROR CAN id is not correct.
 * @return retcode_t RC_MPC_PARSE_DATA_ERROR CAN data is error.
 */
retcode_t mobileye_driver_process_data(void);

/**
 * @}
 *
 */

#endif
