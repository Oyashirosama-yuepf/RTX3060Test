/**
 * @file chassis_state.c
 * @brief This file implements ChassisState Object related functions.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date 2019-11-1
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <assert.h>
#include <holo_c/common/uss/uss_info.h>
#include <holo_c/utils/serialization.h>
#include <string.h>
#include <stdio.h>
retcode_t ussInfo_init_default(void* p2ussInfo, uint16_t len)
{
    memset((uint8_t*)p2ussInfo, 0x00, len);
    return RC_SUCCESS;
}

static retcode_t serialize_data_ApaState(const struct UssInfo_ApaState* state, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;

    serialized_size += timestamp_serialize(&state->stamp, buffer, buffer_size);
    serialized_size += serialize_float32(&state->Someip_AbsltPinionAgReq,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_AbsltPinionAgReqValid,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_APA_EPSReqTyp,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_ApaAbortReason,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_ApaInstruction,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint16((uint16_t*)&state->Someip_ApaManeuverDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_float32(&state->Someip_ApaMaxVelocity,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_ApaOperatingMode,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_APASts,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_FrntLeMidRegnDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_FrntLeRegnDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_FrntMidRegnDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_FrntRiMidRegnDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_FrntRiRegnDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_FrntSnsrDegSt,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_FrntSysSts,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_ReLeMidRegnDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_ReLeRegnDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_ReMidRegnDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_ReRiMidRegnDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_ReRiRegnDst,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_ReSnsrDegSt,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_ReSysSts,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_UpaSysDi,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_UpaSysSrv,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_UpaSysSts,
                                        buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_uint8((uint8_t*)&state->Someip_VmmYawAngle,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_int32((int32_t*)&state->Someip_VmmSPos,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_int32((int32_t*)&state->Someip_VmmXPos,
                                         buffer + serialized_size, buffer_size - serialized_size);
    serialized_size += serialize_int32((int32_t*)&state->Someip_VmmYPos,
                                         buffer + serialized_size, buffer_size - serialized_size);
    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data_ApaState(struct UssInfo_ApaState* state, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;

    deserialized_size += timestamp_deserialize(&state->stamp, buffer, buffer_size);
    deserialized_size += deserialize_float32(&state->Someip_AbsltPinionAgReq,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_AbsltPinionAgReqValid,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_APA_EPSReqTyp,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_ApaAbortReason,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_ApaInstruction,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint16((uint16_t*)&state->Someip_ApaManeuverDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_float32(&state->Someip_ApaMaxVelocity,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_ApaOperatingMode,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_APASts,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_FrntLeMidRegnDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_FrntLeRegnDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_FrntMidRegnDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_FrntRiMidRegnDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_FrntRiRegnDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_FrntSnsrDegSt,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_FrntSysSts,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_ReLeMidRegnDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_ReLeRegnDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_ReMidRegnDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_ReRiMidRegnDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_ReRiRegnDst,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_ReSnsrDegSt,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_ReSysSts,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_UpaSysDi,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_UpaSysSrv,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_UpaSysSts,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_uint8((uint8_t*)&state->Someip_VmmYawAngle,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_int32((int32_t*)&state->Someip_VmmSPos,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_int32((int32_t*)&state->Someip_VmmXPos,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    deserialized_size += deserialize_int32((int32_t*)&state->Someip_VmmYPos,
                                         buffer + deserialized_size, buffer_size - deserialized_size);
    return (retcode_t)deserialized_size;
}
uint32_t s_size[10] ={0};
static retcode_t serialize_data_ParkingSlot(const struct UssInfo_ParkingSlot* PSlot, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;
    uint8_t idx_slot = 0;

    serialized_size += timestamp_serialize(&PSlot->stamp, buffer, buffer_size);
    for(idx_slot = 0; idx_slot < PSLOT_NUM; idx_slot++)
    {
        serialized_size += serialize_uint8((uint8_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotID,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_uint8((uint8_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotSts,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int8((int8_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj1Alpha,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int8((int8_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj2Alpha,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj1X,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj1Y,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj2X,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj2Y,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_uint16((uint16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotSizeX,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_uint16((uint16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotSizeY,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotVehX,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotVehY,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_float32((float32_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotVehPsi,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
    }

    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data_ParkingSlot(struct UssInfo_ParkingSlot* PSlot, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;
    uint8_t idx_slot = 0;

    deserialized_size += timestamp_deserialize(&PSlot->stamp, buffer, buffer_size);
    for(idx_slot = 0; idx_slot < PSLOT_NUM; idx_slot++)
    {
        deserialized_size += deserialize_uint8((uint8_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotID,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_uint8((uint8_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotSts,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int8((int8_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj1Alpha,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int8((int8_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj2Alpha,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj1X,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj1Y,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj2X,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotObj2Y,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_uint16((uint16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotSizeX,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_uint16((uint16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotSizeY,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotVehX,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int16((int16_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotVehY,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_float32((float32_t*)&PSlot->ParkingSlot[idx_slot].Someip_ApaSlotVehPsi,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding(deserialized_size, buffer + deserialized_size, buffer_size - deserialized_size);
        

    }

    return (retcode_t)deserialized_size;
}
uint32_t s_size_map[10] ={0};
static retcode_t serialize_data_MapObj(const struct UssInfo_MapObj* MapObj, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t serialized_size = 0;
    uint8_t idx_MapObj = 0;

    serialized_size += timestamp_serialize(&MapObj->stamp, buffer, buffer_size);

    for(idx_MapObj = 0; idx_MapObj < MAPOBJ_NUM; idx_MapObj++)
    {
        serialized_size += serialize_uint8((uint8_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjTyp,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_uint8((uint8_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjHei,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int16((int16_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjP1X,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int16((int16_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjP1Y,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int16((int16_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjP2X,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_int16((int16_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjP2Y,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_float32((float32_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjHeiProblty,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_float32((float32_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjProblty,
                                            buffer + serialized_size, buffer_size - serialized_size);
        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

    }
    s_size_map[4] = serialized_size;
    return (retcode_t)serialized_size;
}

static retcode_t deserialize_data_MapObj(struct UssInfo_MapObj* MapObj, uint8_t* buffer, uint32_t buffer_size)
{
    uint32_t deserialized_size = 0;
    uint8_t idx_MapObj = 0;

    deserialized_size += timestamp_deserialize(&MapObj->stamp, buffer, buffer_size);

    for(idx_MapObj = 0; idx_MapObj < MAPOBJ_NUM; idx_MapObj++)
    {
        deserialized_size += deserialize_uint8((uint8_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjTyp,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_uint8((uint8_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjHei,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int16((int16_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjP1X,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int16((int16_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjP1Y,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int16((int16_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjP2X,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_int16((int16_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjP2Y,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_float32((float32_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjHeiProblty,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_float32((float32_t*)&MapObj->Mapobj[idx_MapObj].Someip_MapObjProblty,
                                            buffer + deserialized_size, buffer_size - deserialized_size);
        deserialized_size += deserialize_padding(deserialized_size, buffer + deserialized_size, buffer_size - deserialized_size);
    }
    return (retcode_t)deserialized_size;
}
uint32_t g_expect = 0;
retcode_t UssInfo_ApaState_serialize(const struct UssInfo_ApaState* state, uint8_t* buffer, uint32_t buffer_size)
{
    assert(state != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = serialization_aligned_size(sizeof(struct UssInfo_ApaState));
    g_expect = expected_size;
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data_ApaState(state, buffer, buffer_size);

        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);

        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t UssInfo_ApaState_deserialize(struct UssInfo_ApaState* state,  uint8_t* buffer, uint32_t buffer_size)
{
    assert(state != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = serialization_aligned_size(sizeof(struct UssInfo_ApaState));

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data_ApaState(state, buffer, buffer_size);

        deserialized_size +=
            deserialize_padding(deserialized_size, buffer + deserialized_size, buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

retcode_t UssInfo_ParkingSlot_serialize(const struct UssInfo_ParkingSlot* PSlot, uint8_t* buffer, uint32_t buffer_size)
{
    assert(PSlot != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = serialization_aligned_size(sizeof(struct UssInfo_ParkingSlot));

    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data_ParkingSlot(PSlot, buffer, buffer_size);
        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t UssInfo_ParkingSlot_deserialize(struct UssInfo_ParkingSlot* PSlot,  uint8_t* buffer, uint32_t buffer_size)
{
    assert(PSlot != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = serialization_aligned_size(sizeof(struct UssInfo_ParkingSlot));
    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data_ParkingSlot(PSlot, buffer, buffer_size);

        deserialized_size +=
            deserialize_padding(deserialized_size, buffer + deserialized_size, buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}

retcode_t UssInfo_MapObj_serialize(const struct UssInfo_MapObj* MapObj, uint8_t* buffer, uint32_t buffer_size)
{
    assert(MapObj != NULL);
    assert(buffer != NULL);

    retcode_t rc              = RC_SUCCESS;
    uint32_t  serialized_size = 0;
    uint32_t  expected_size   = serialization_aligned_size(sizeof(struct UssInfo_MapObj));
    s_size_map[0] = buffer_size;
    s_size_map[1] = expected_size;
    if (buffer_size < expected_size)
    {
        rc = RC_SERIALIZATION_BUFFER_OVERFLOW;
    }
    else
    {
        serialized_size += serialize_data_MapObj(MapObj, buffer, buffer_size);
        s_size_map[2] = serialized_size;
        serialized_size += serialize_padding(serialized_size, buffer + serialized_size, buffer_size - serialized_size);
        s_size_map[3] = serialized_size;
        assert(expected_size == serialized_size);
        rc = (retcode_t)serialized_size;
    }

    return rc;
}

retcode_t UssInfo_MapObj_deserialize(struct UssInfo_MapObj* MapObj,  uint8_t* buffer, uint32_t buffer_size)
{
    assert(MapObj != NULL);
    assert(buffer != NULL);

    retcode_t rc                = RC_SUCCESS;
    uint32_t  deserialized_size = 0;
    uint32_t  expected_size     = serialization_aligned_size(sizeof(struct UssInfo_MapObj));

    if (buffer_size < expected_size)
    {
        rc = RC_DESERIALIZATION_BUFFER_UNDERFLOW;
    }
    else
    {
        deserialized_size += deserialize_data_MapObj(MapObj, buffer, buffer_size);

        deserialized_size +=
            deserialize_padding(deserialized_size, buffer + deserialized_size, buffer_size - deserialized_size);

        assert(deserialized_size == expected_size);
        rc = (retcode_t)deserialized_size;
    }
    return rc;
}
