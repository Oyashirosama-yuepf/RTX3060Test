/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file parking_structure.h
 * @brief This header file defines parking structure
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#ifndef HOLO_PARKING_PARKING_STRUCTURES_H
#define HOLO_PARKING_PARKING_STRUCTURES_H

#include <map>
#include <string>
#include <vector>

#include <holo/common/chassis_state.h>
#include <holo/core/types.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

// define macro to pack structures correctly with both GCC and MSVC compilers
#ifdef _MSC_VER
#define PACK( __Declaration__ ) __pragma( pack(push, 1) ) __Declaration__ __pragma( pack(pop) )
#else
#define PACK( __Declaration__ ) __Declaration__ __attribute__((__packed__))
#endif


static const uint16_t    PARKING_TCP_HEADER    = 0xAA55;
static const uint16_t    PARKING_UDP_HEADER    = 0xAA55;
// a complete msg is
// 0xAA55 + msg_id(uint16_t) + data_len(uint32_t) + data
// therefore sizeof(0xAA55) + sizeof(uint16_t) + sizeof(uint32_t)
// =  2 + 2 + 4 = 8
static const uint8_t    MSG_INFO_LEN          = 8;
static const uint8_t    HEADER_OFFSET         = 0;
static const uint8_t    MSG_ID_OFFSET         = 2;
static const uint8_t    MSG_LEN_OFFSET        = 4;
static const uint8_t    DATA_OFFSET           = 8;

typedef std::vector<uint8_t> InputMsg;

enum ComStatus: uint8_t
{
	SUCCESS      = 0x00,
	FAILURE      = 0x01
};

enum EntranceStatus: uint8_t
{
	ES_SUCCESS        = 0x00,
	ES_WRONG_POSITION = 0x01,
	ES_WRONG_ROTATION = 0x02,
	ES_NOCAR          = 0xFF,
};

enum ParkingMsgId: uint16_t
{
	// 0x03xx: root server to cloud
	R2CParkingCommand    = 0x0300,
	R2CCallbackCommand   = 0x0301,
	R2CCarState          = 0x0302,
	R2CPath              = 0x0303,
	R2CPlanningState     = 0x0304,
	R2CEntrance          = 0x0305,
	R2CParkingFinished   = 0x0306,
	R2CAbnormalTakeOver  = 0x0307,
	R2CAlive             = 0x0310,
	
	// 0x04xx: cloud to root server
	C2RParkingCommand    = 0x0400,
	C2RCallbackCommand   = 0x0401,
	C2RCarState          = 0x0402,
	C2RPath              = 0x0403,
	C2REtrance			 = 0x0404
};

// struct R2VInfo
// {
// 	bool_t new_command = false;
// 	holo::planning::ParkCmd command;
// 	// bool_t new_spaces = false;
// 	// holo::map::ParkingSpacesMsg spaces;
// 	// bool_t new_obs = false;
// 	// holo::ObstaclePtrListT<holo::ObstacleGeneralT<holo::float32_t>> obs;
// 	// bool_t new_sectors = false;
// 	// std::vector<holo::ParkingUidObstacle::Sector> scts;
// 	TimeStamp obs_st;
// 	bool_t new_odo = false;
// 	Odometry odo;
// 	bool_t new_path = false;
// 	Pathf path;
// }; 

PACK(
struct C2RCommand
{
	uint64_t  vehicle_id;
	uint64_t  entry_id;
	uint64_t  slot_id;
	float32_t car_length;
	float32_t car_width;
	float32_t car_height;
	float32_t rear_axis_y;
	float32_t rear_axis_z;
}
);

PACK(
struct R2CCarState
{
	uint64_t  vehicle_id;
	uint16_t  main_state_;
	uint16_t  sub_state_;
	float32_t x;
	float32_t y;
	float32_t theta;
}
);

PACK(
struct R2CParkingFnished
{
	uint64_t vehicle_id;
	uint8_t  is_auto; //1  or 0
}
);

PACK(
struct R2CAbnormalTake
{
	uint64_t vehicle_id;
	uint32_t abnormal;
}
);

PACK(
struct R2CPathPoint
{
	float32_t x;
	float32_t y;
}
);

/////////
///  HPP
/////////

static const uint16_t    HPP_PARKING_TCP_HEADER    = 0xAA00;
static const uint8_t     IDLE_HPP = 0;
static const uint8_t     PATH_FOLLOW_HPP = 30;

enum PathFollowHPP: uint8_t
{
	PF_NORMAL = 0,
	PF_WAIT,
	PF_ROUTE_PROBLEM,
};

// sizeof(HPPC2VMsg) = 25+8
PACK(
struct HPPC2VMsg
{
	uint16_t head;//2
	uint16_t msg_id;//2
	uint32_t len;//4
	uint64_t car_id;//
	uint64_t route_id;
	uint8_t  confirm;
	uint64_t take_id;
}
);

// sizeof(HPPV2CParkingMsg) = 19
PACK(
struct HPPV2CParkingMsg
{
	uint16_t head;
	uint16_t msg_id;
	uint32_t len;
	uint64_t car_id;
	uint8_t  parking_status;
	uint8_t  error_code;
	uint8_t  progress;
}
);

// sizeof(HPPV2CLearningMsg) = 19
PACK(
struct HPPV2CLearningMsg
{
	uint16_t head;
	uint16_t msg_id;
	uint32_t len;
	uint64_t car_id;
	uint8_t  learning_status;
	uint8_t  is_learn_success;
	uint8_t  error_code;
}
);

// sizeof(HPPV2CResponseMsg) = 17
PACK(
struct HPPV2CResponseMsg
{
	uint16_t head;
	uint16_t msg_id;
	uint32_t len;
	uint64_t car_id;
	uint8_t  reply;
}
); 

enum HPPParkingMsgId: uint16_t
{
	// 0x01xx: cloud to vehicle server
	C2VParkingCmd    		 = 0x0100,
	C2VLearningReqCmd   	 = 0x0101,
	C2VFinishLearningCmd     = 0x0102,
	C2VConfirmLearingPathCmd = 0x0103,
	C2VTakeRecoveryCmd 	     = 0x0104,
	C2VInOutPathCmd 	     = 0x0105,
	C2VStartStopMappingCmd 	 = 0x0106,

	// 0x02xx: vehicle server to cloude
	V2CParkingProgress    	 = 0x0200,
	V2CLearningProgress   	 = 0x0201,
	V2CVehicleProgress   	 = 0x0202,
	V2CMappingProgress   	 = 0x0203,

	V2CParkingRsp    		 = 0x0220,
	V2CLearnRsp   			 = 0x0221,
	V2CFinsihLearnRsp    	 = 0x0222,
	V2CConfirmLearRsp   	 = 0x0223,

	// heartbeat
	HeartbeatCmd 		     = 0x0210,
};

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo

#endif //HOLO_PARKING_PARKING_STRUCTURES_H
