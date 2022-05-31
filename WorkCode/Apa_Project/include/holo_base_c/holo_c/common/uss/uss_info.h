/**
 * @file chassis_state.h
 * @brief This header file defines ChassisState Object.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-8-12
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef _USS_INFO_H_
#define _USS_INFO_H_

#include <holo_c/common/timestamp.h>
#include <holo_c/core/config.h>
#include <holo_c/core/retcode.h>
#include <holo_c/core/static_assert.h>
#include <holo_c/core/types.h>
#include<stdio.h>
#ifdef __cplusplus
extern "C" {
#endif

#define PSLOT_NUM     (7u)
#define MAPOBJ_NUM    (20u)

/**
 * @brief This structure describes information from uss detection.
 */
struct UssInfo_ApaState
{
    struct Timestamp stamp;

    /* APA_01 */
    float32_t    Someip_AbsltPinionAgReq;
    uint8_t      Someip_AbsltPinionAgReqValid;
    uint8_t      Someip_APA_EPSReqTyp;
    uint8_t      Someip_ApaAbortReason;
    uint8_t      Someip_ApaInstruction;
    uint16_t     Someip_ApaManeuverDst;
    float32_t    Someip_ApaMaxVelocity;
    uint8_t      Someip_ApaOperatingMode;
    uint8_t      Someip_APASts;
    uint8_t      Someip_FrntLeMidRegnDst;
    uint8_t      Someip_FrntLeRegnDst;
    uint8_t      Someip_FrntMidRegnDst;
    uint8_t      Someip_FrntRiMidRegnDst;
    uint8_t      Someip_FrntRiRegnDst;
    uint8_t      Someip_FrntSnsrDegSt;
    uint8_t      Someip_FrntSysSts;
    uint8_t      Someip_ReLeMidRegnDst;
    uint8_t      Someip_ReLeRegnDst;
    uint8_t      Someip_ReMidRegnDst;
    uint8_t      Someip_ReRiMidRegnDst;
    uint8_t      Someip_ReRiRegnDst;
    uint8_t      Someip_ReSnsrDegSt;
    uint8_t      Someip_ReSysSts;
    uint8_t      Someip_UpaSysDi;
    uint8_t      Someip_UpaSysSrv;
    uint8_t      Someip_UpaSysSts;
    uint8_t      Someip_VmmYawAngle;
    int32_t      Someip_VmmSPos;
    int32_t      Someip_VmmXPos;
    int32_t      Someip_VmmYPos;
};
// HOLO_STATIC_ASSERT(sizeof(struct UssInfo_ApaState) == 88);

struct UssInfo_ParkingSlot_Attr
{
    /* APA_04  -  APA_07 */
    uint8_t      Someip_ApaSlotID;
    uint8_t      Someip_ApaSlotSts;
    int8_t       Someip_ApaSlotObj1Alpha;
    int8_t       Someip_ApaSlotObj2Alpha;
    int16_t      Someip_ApaSlotObj1X;
    int16_t      Someip_ApaSlotObj1Y;
    int16_t      Someip_ApaSlotObj2X;
    int16_t      Someip_ApaSlotObj2Y;
    uint16_t     Someip_ApaSlotSizeX;
    uint16_t     Someip_ApaSlotSizeY;
    //float64_t    Someip_ApaSlotVehPsi;
    int16_t      Someip_ApaSlotVehX;
    int16_t      Someip_ApaSlotVehY;
    float32_t    Someip_ApaSlotVehPsi;
};

struct UssInfo_ParkingSlot
{
    struct Timestamp stamp;
    struct UssInfo_ParkingSlot_Attr ParkingSlot[PSLOT_NUM];
};
// HOLO_STATIC_ASSERT(sizeof(struct UssInfo_ParkingSlot) == 88);

struct UssInfo_MapObj_Attr
{
    /* APA_ADC_01 */
    uint8_t      Someip_MapObjTyp;
    uint8_t      Someip_MapObjHei;
    int16_t      Someip_MapObjP1X;
    int16_t      Someip_MapObjP1Y;
    int16_t      Someip_MapObjP2X;
    int16_t      Someip_MapObjP2Y;
    float32_t    Someip_MapObjHeiProblty;
    float32_t    Someip_MapObjProblty;
};

struct UssInfo_MapObj
{
    struct Timestamp stamp;
    struct UssInfo_MapObj_Attr Mapobj[MAPOBJ_NUM];
};
// HOLO_STATIC_ASSERT(sizeof(struct UssInfo_MapObj) == 88);
////////////////////////////////////////////////////////////////////
//////////////////////UssInfo_MapObj_Attr ///////////////////////////
////////////////////////////get///////////////////////////////////////
static inline bool is_map_satisfy(const struct UssInfo_MapObj* state,	const  uint8_t offse)
{
	if(NULL == state)
	{
		return false;
	}
	if(offse > (MAPOBJ_NUM -1))
	{
		return false;
	}
	return true;
}
static inline	uint8_t get_someip_MapObjTyp(const struct UssInfo_MapObj* state,	const  uint8_t offset) 
{
		if(!is_map_satisfy(state,  offset))
	   {
		   return 0;
	   }
		return state->Mapobj[offset].Someip_MapObjTyp;
}
static inline	uint8_t get_someip_MapObjHei(const struct UssInfo_MapObj* state,	const  uint8_t offset) 
{
	if(!is_map_satisfy(state,  offset))
	{
		return 0;
	}
	return state->Mapobj[offset].Someip_MapObjHei;
}

static inline	int16_t get_someip_MapObjP1X(const struct UssInfo_MapObj* state,	const  uint8_t offset) 
{
	if(!is_map_satisfy(state,  offset))
	{
		return 0;
	}
	return state->Mapobj[offset].Someip_MapObjP1X;
}
static inline	int16_t get_someip_MapObjP1Y(const struct UssInfo_MapObj* state,	const  uint8_t offset) 
{
	if(!is_map_satisfy(state,  offset))
	{
		return 0;
	}
	return state->Mapobj[offset].Someip_MapObjP1Y;
}
static inline	int16_t get_someip_MapObjP2X(const struct UssInfo_MapObj* state,	const  uint8_t offset) 
{
	if(!is_map_satisfy(state,  offset))
	{
		return 0;
	}
	return state->Mapobj[offset].Someip_MapObjP2X;
}
static inline	int16_t get_someip_MapObjP2Y(const struct UssInfo_MapObj* state,	const  uint8_t offset) 
{
	if(!is_map_satisfy(state,  offset))
	{
	   return 0 ;
	}
	return state->Mapobj[offset].Someip_MapObjP2Y;
}
static inline	float32_t get_someip_MapObjHeiProblty(const struct UssInfo_MapObj* state,	const  uint8_t offset) 
{
	if(!is_map_satisfy(state,  offset))
	{
		return 0;
	}
	return state->Mapobj[offset].Someip_MapObjHeiProblty; 
}
static inline	float32_t  get_someip_MapObjProblty(const struct UssInfo_MapObj* state,	const  uint8_t offset) 
{
		if(!is_map_satisfy(state,  offset))
	   {
		   return 0;
	   }
		return state->Mapobj[offset].Someip_MapObjProblty;
}

/////////////////////////////////////////////////////////////////////////////////////
///////////////////////////UssInfo_ParkingSlot_Attr//////////////////////////////////////
////////////////////////////////////////get////////////////////////////////////////////////////
//fmh add USSApaSlot start
static bool is_satisfy(const struct UssInfo_ParkingSlot* state,  const  uint8_t offset)
{
    if (NULL == state)
    {
        printf("is_satisfy\n");
        return false;
    }     
    if(offset > (PSLOT_NUM -1))
    {
         return false;
    }
    return true;
}
static inline	uint8_t  get_someip_ApaSlotID(const struct UssInfo_ParkingSlot* state,  const  uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset].Someip_ApaSlotID;
}
static inline	uint8_t  get_someip_ApaSlotSts(const struct UssInfo_ParkingSlot* state,const  uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset].Someip_ApaSlotSts  ;
}
static inline	int8_t  get_someip_ApaSlotObj1Alpha(const struct UssInfo_ParkingSlot* state,uint8_t offset) 
{
     if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset].Someip_ApaSlotObj1Alpha  ;
}
static inline	int8_t  get_someip_ApaSlotObj2Alpha(const struct UssInfo_ParkingSlot* state,const  uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset]. Someip_ApaSlotObj2Alpha  ;
}
static inline	int16_t  get_someip_ApaSlotObj1X(const struct UssInfo_ParkingSlot* state,const  uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset].Someip_ApaSlotObj1X  ;
}
static inline	int16_t  get_someip_ApaSlotObj1Y(const struct UssInfo_ParkingSlot* state,uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset].Someip_ApaSlotObj1Y ;
}

static inline	int16_t  get_someip_ApaSlotObj2X(const struct UssInfo_ParkingSlot* state,const  uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
     return state-> ParkingSlot[offset].Someip_ApaSlotObj2X  ;
}
static inline	int16_t  get_someip_ApaSlotObj2Y(const struct UssInfo_ParkingSlot* state,const  uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset].Someip_ApaSlotObj2Y  ;
}
static inline	uint16_t  get_someip_ApaSlotSizeX(const struct UssInfo_ParkingSlot* state,uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
   return  state-> ParkingSlot[offset].Someip_ApaSlotSizeX  ;
}
static inline	uint16_t  get_someip_ApaSlotSizeY(const struct UssInfo_ParkingSlot* state, const  uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset].Someip_ApaSlotSizeY  ;
}

static inline	float32_t  get_someip_ApaSlotVehPsi(const struct UssInfo_ParkingSlot* state,const  uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset]. Someip_ApaSlotVehPsi  ;
}
static inline	int16_t  get_someip_ApaSlotVehX(const struct UssInfo_ParkingSlot* state,const  uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset].Someip_ApaSlotVehX  ;
}
static inline	int16_t  get_someip_ApaSlotVehY(const struct UssInfo_ParkingSlot* state,const  uint8_t offset) 
{
    if(!is_satisfy(state, offset))
    {
        return 0;
    }
    return state-> ParkingSlot[offset]. Someip_ApaSlotVehY;
}
//////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////UssInfo_ApaState/////////////////////////////////////////////////
//////////////////// get//////////////////////////////////////////////////////////////////////////////

static inline float32_t  ussapa01_get_someip_AbsltPinionAgReq(const struct UssInfo_ApaState* state)
{     
    if(NULL== state)
    {
        return  0;
    }
    return state->Someip_AbsltPinionAgReq;
}
static inline uint8_t  ussapa01_get_someip_AbsltPinionAgReqValid(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_AbsltPinionAgReqValid;
}
////this string have _ , do not move
static inline uint8_t  ussapa01_get_someip_APA_EPSReqTyp(const struct UssInfo_ApaState* state)
{   
      if(NULL== state)
    {
        return  0;
    }
    //this string have _ , do not move
    return state->Someip_APA_EPSReqTyp;
}
static inline uint8_t  ussapa01_get_someip_ApaAbortReason(const struct UssInfo_ApaState* state)
{  
    if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ApaAbortReason;
}
static inline uint8_t  ussapa01_someip_ApaInstruction(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ApaInstruction;
}
static inline 	uint16_t    ussapa01_get_someip_ApaManeuverDst(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ApaManeuverDst;
}
static inline float32_t  ussapa01_get_someip_ApaMaxVelocity(const struct UssInfo_ApaState* state)
{
    if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ApaMaxVelocity;
}
static inline uint8_t ussapa01_get_someip_ApaOperatingMode(const struct UssInfo_ApaState* state)
{
    if(NULL== state)
    {
        return 0;
    }
    return state->Someip_ApaOperatingMode;
}
static inline	uint8_t     ussapa01_get_someip_APASts(const struct UssInfo_ApaState* state)
{   
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_APASts;
}
static inline	uint8_t     ussapa01_get_someip_FrntLeMidRegnDst(const struct UssInfo_ApaState* state)
{   
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_FrntLeMidRegnDst;
}
static inline	uint8_t     ussapa01_get_someip_FrntLeRegnDst(const struct UssInfo_ApaState* state)
{   
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_FrntLeRegnDst;
}
static inline	uint8_t      ussapa01_get_someip_FrntMidRegnDst(const struct UssInfo_ApaState* state)
{   
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_FrntMidRegnDst;
}
static inline	uint8_t     ussapa01_get_someip_FrntRiMidRegnDst(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_FrntRiMidRegnDst;
}
static inline	uint8_t     ussapa01_get_someip_FrntRiRegnDst(const struct UssInfo_ApaState* state)
{   
    if(NULL== state)
    {
        return  0;
    }
    return state->Someip_FrntRiRegnDst;
}
static inline	uint8_t     ussapa01_get_someip_FrntSnsrDegSt(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_FrntSnsrDegSt;
}
static inline	uint8_t    ussapa01_get_someip_FrntSysSts(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_FrntSysSts;
}
static inline	uint8_t     ussapa01_get_someip_ReLeMidRegnDst(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ReLeMidRegnDst;
 }
static inline	uint8_t    ussapa01_get_someip_ReLeRegnDst(const struct UssInfo_ApaState* state)
{   
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ReLeRegnDst;
}
static inline	uint8_t    ussapa01_get_someip_ReMidRegnDst(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ReMidRegnDst;
 }
static inline	uint8_t    ussapa01_get_someip_ReRiMidRegnDst(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ReRiMidRegnDst;
 }
static inline	uint8_t     ussapa01_get_someip_ReRiRegnDst(const struct UssInfo_ApaState* state)
{     
    if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ReRiRegnDst;
 }
static inline	uint8_t     ussapa01_get_someip_ReSnsrDegSt(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ReSnsrDegSt;
 }
static inline	uint8_t     ussapa01_get_someip_ReSysSts(const struct UssInfo_ApaState* state)
{     
    if(NULL== state)
    {
        return  0;
    }
    return state->Someip_ReSysSts;
}
static inline	uint8_t     ussapa01_get_someip_UpaSysDi(const struct UssInfo_ApaState* state)
{     
    if(NULL== state)
    {
        return  0;
    }
    return state->Someip_UpaSysDi;
}
static inline	uint8_t     ussapa01_get_someip_UpaSysSrv(const struct UssInfo_ApaState* state)
{     
    if(NULL== state)
    {
        return  0;
    }
    return state->Someip_UpaSysSrv;
}
static inline	uint8_t     ussapa01_get_someip_UpaSysSts(const struct UssInfo_ApaState* state)
{    
    if(NULL== state)
    {
        return  0;
    }
    return state->Someip_UpaSysSts;
 }
static inline	int32_t     ussapa01_get_someip_VmmSPos(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_VmmSPos;
}
static inline	uint8_t     ussapa01_get_someip_mmYawAngle(const struct UssInfo_ApaState* state)
{     
    if(NULL== state)
    {
        return  0;
    }
    return state->Someip_VmmYawAngle;
}

static inline	int32_t     ussapa01_get_someip_VmmXPos(const struct UssInfo_ApaState* state)
{    
     if(NULL== state)
    {
        return  0;
    }
    return state->Someip_VmmXPos;
}
static inline	int32_t      ussapa01_get_someip_VmmYPos(const struct UssInfo_ApaState* state)
{     
    if(NULL== state)
    {
        return 0;
    }
    return state->Someip_VmmYPos;
}

////////////////////////////////UssInfo_MapObj_Attr/////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Default constructor
 *
 * @param state The input uss infomation.
 *
 * @return RC_SUCCESS
 */
 retcode_t ussInfo_init_default(void* p2ussInfo, uint16_t len);

/**
 * @brief Get serialized buffer size.
 *
 * @param state The ChassisState object.
 *
 * @return Serialized size.
 */
// uint32_t chassis_state_get_serialized_size(const struct ChassisState* state);

/**
 * @brief Serialize UssInfo_ApaState object to buffer.
 *
 * @param state The UssInfo_ApaState object.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return Positive interger Number of bytes serialized into buffer.
 */
extern retcode_t UssInfo_ApaState_serialize(const struct UssInfo_ApaState* state, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize UssInfo_ApaState object from buffer.
 *
 * @param state The UssInfo_ApaState object.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return Positive integer Number of bytes deserialized from buffer.
 */
extern retcode_t UssInfo_ApaState_deserialize(struct UssInfo_ApaState* state,  uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Serialize UssInfo_ParkingSlot info to buffer.
 *
 * @param PSlot The UssInfo_ParkingSlot info.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return Positive interger Number of bytes serialized into buffer.
 */
extern retcode_t UssInfo_ParkingSlot_serialize(const struct UssInfo_ParkingSlot* PSlot, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize UssInfo_ParkingSlot info from buffer.
 *
 * @param PSlot The UssInfo_ParkingSlot info.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return Positive integer Number of bytes deserialized from buffer.
 */
extern retcode_t UssInfo_ParkingSlot_deserialize(struct UssInfo_ParkingSlot* PSlot,  uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Serialize UssInfo_MapObj info to buffer.
 *
 * @param MapObj The UssInfo_MapObj info.
 * @param buffer The buffer to serialize to.
 * @param buffer_size Size of buffer.
 *
 * @return RC_SERIALIZATION_BUFFER_OVERFLOW buffer_size is smaller than needed.
 * @return Positive interger Number of bytes serialized into buffer.
 */
extern retcode_t UssInfo_MapObj_serialize(const struct UssInfo_MapObj* MapObj, uint8_t* buffer, uint32_t buffer_size);

/**
 * @brief Deserialize UssInfo_MapObj info from buffer.
 *
 * @param MapObj The UssInfo_MapObj info.
 * @param buffer The buffer to deserialize from.
 * @param buffer_size Size of buffer.
 *
 * @return RC_DESERIALIZATION_BUFFER_UNDERFLOW Input buffer size is smaller than needed.
 * @return Positive integer Number of bytes deserialized from buffer.
 */
extern retcode_t UssInfo_MapObj_deserialize(struct UssInfo_MapObj* MapObj,  uint8_t* buffer, uint32_t buffer_size);

/**
 * @}
 * End Serialization/Deserialization API group.
 */

#ifdef __cplusplus
}
#endif

#endif
