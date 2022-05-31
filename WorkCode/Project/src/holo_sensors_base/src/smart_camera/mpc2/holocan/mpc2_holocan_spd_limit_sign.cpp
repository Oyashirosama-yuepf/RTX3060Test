/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mpc2_holocan_spd_limit_sign.cpp
 * @brief To receive and construct bosch mpc outputs
 * @author zhangtongyang<zhangtongyang@holomatic.com>
 * @date 2021/12/30
 */

#include <holo/log/hololog.h>
#include <holo/sensors/smart_camera/mpc2/mpc2_holocan.h>
#include <holo_c/sensors/dbc/mpc_recv_dbc.h>
#include <exception>

namespace holo
{
namespace sensors
{
namespace bosch_mpc
{
void BoschMpcDriverT<HoloCanPacket>::ConstructSpdLimitSign1PartA(const HoloCanPacket& msg, SpdSignType& spd_sign)
{
    uint32_t  u32val;
    float32_t f32val;
    uint8_t   u8val;
    bool_t    bval;
    u32val = GET_RSR_Objects01_A_RsrObj01_A_PositionX(msg.GetData());
    f32val = CALC_RSR_Objects01_A_RsrObj01_A_PositionX(u32val, 1.0f);
    spd_sign.SetPosX(f32val);
    u32val = GET_RSR_Objects01_A_RsrObj01_A_PositionY(msg.GetData());
    f32val = CALC_RSR_Objects01_A_RsrObj01_A_PositionY(u32val, 1.0f);
    spd_sign.SetPosY(f32val);
    u32val = GET_RSR_Objects01_A_RsrObj01_A_PositionZ(msg.GetData());
    f32val = CALC_RSR_Objects01_A_RsrObj01_A_PositionZ(u32val, 1.0f);
    spd_sign.SetPosZ(f32val);
    u32val = GET_RSR_Objects01_A_RsrObj01_A_Stable(msg.GetData());
    bval   = CALC_RSR_Objects01_A_RsrObj01_A_Stable(u32val, 1);
    spd_sign.SetStable(bval);
    u32val = GET_RSR_Objects01_A_RsrObj01_A_Embedded(msg.GetData());
    u8val  = CALC_RSR_Objects01_A_RsrObj01_A_Embedded(u32val, 1);
    spd_sign.SetEmbedded(u8val);
    u32val = GET_RSR_Objects01_A_RsrObj01_A_Goodness(msg.GetData());
    u8val  = CALC_RSR_Objects01_A_RsrObj01_A_Goodness(u32val, 1);
    spd_sign.SetGoodness(u8val);
    u32val = GET_RSR_Objects01_A_RsrObj01_A_Quality(msg.GetData());
    bval   = CALC_RSR_Objects01_A_RsrObj01_A_Quality(u32val, 1);
    spd_sign.SetQuality(bval);
    u32val = GET_RSR_Objects01_A_RsrObj01_A_Vms(msg.GetData());
    bval   = CALC_RSR_Objects01_A_RsrObj01_A_Vms(u32val, 1);
    spd_sign.SetVms(bval);
    u32val = GET_RSR_Objects01_A_RsrObj01_A_Class(msg.GetData());
    u8val  = CALC_RSR_Objects01_A_RsrObj01_A_Class(u32val, 1);
    spd_sign.SetClassfication(u8val);
    u32val = GET_RSR_Objects01_A_RsrObj01_A_Id(msg.GetData());
    u8val  = CALC_RSR_Objects01_A_RsrObj01_A_Id(u32val, 1);
    spd_sign.SetId(u8val);
    spd_sign.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
}

void BoschMpcDriverT<HoloCanPacket>::ConstructSpdLimitSign2PartA(const HoloCanPacket& msg, SpdSignType& spd_sign)
{
    uint32_t  u32val;
    float32_t f32val;
    uint8_t   u8val;
    bool_t    bval;
    u32val = GET_RSR_Objects02_A_RsrObj02_A_PositionX(msg.GetData());
    f32val = CALC_RSR_Objects02_A_RsrObj02_A_PositionX(u32val, 1.0f);
    spd_sign.SetPosX(f32val);
    u32val = GET_RSR_Objects02_A_RsrObj02_A_PositionY(msg.GetData());
    f32val = CALC_RSR_Objects02_A_RsrObj02_A_PositionY(u32val, 1.0f);
    spd_sign.SetPosY(f32val);
    u32val = GET_RSR_Objects02_A_RsrObj02_A_PositionZ(msg.GetData());
    f32val = CALC_RSR_Objects02_A_RsrObj02_A_PositionZ(u32val, 1.0f);
    spd_sign.SetPosZ(f32val);
    u32val = GET_RSR_Objects02_A_RsrObj02_A_Stable(msg.GetData());
    bval   = CALC_RSR_Objects02_A_RsrObj02_A_Stable(u32val, 1);
    spd_sign.SetStable(bval);
    u32val = GET_RSR_Objects02_A_RsrObj02_A_Embedded(msg.GetData());
    u8val  = CALC_RSR_Objects02_A_RsrObj02_A_Embedded(u32val, 1);
    spd_sign.SetEmbedded(u8val);
    u32val = GET_RSR_Objects02_A_RsrObj02_A_Goodness(msg.GetData());
    u8val  = CALC_RSR_Objects02_A_RsrObj02_A_Goodness(u32val, 1);
    spd_sign.SetGoodness(u8val);
    u32val = GET_RSR_Objects02_A_RsrObj02_A_Quality(msg.GetData());
    bval   = CALC_RSR_Objects02_A_RsrObj02_A_Quality(u32val, 1);
    spd_sign.SetQuality(bval);
    u32val = GET_RSR_Objects02_A_RsrObj02_A_Vms(msg.GetData());
    bval   = CALC_RSR_Objects02_A_RsrObj02_A_Vms(u32val, 1);
    spd_sign.SetVms(bval);
    u32val = GET_RSR_Objects02_A_RsrObj02_A_Class(msg.GetData());
    u8val  = CALC_RSR_Objects02_A_RsrObj02_A_Class(u32val, 1);
    spd_sign.SetClassfication(u8val);
    u32val = GET_RSR_Objects02_A_RsrObj02_A_Id(msg.GetData());
    u8val  = CALC_RSR_Objects02_A_RsrObj02_A_Id(u32val, 1);
    spd_sign.SetId(u8val);
    spd_sign.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
}

void BoschMpcDriverT<HoloCanPacket>::ConstructSpdLimitSign3PartA(const HoloCanPacket& msg, SpdSignType& spd_sign)
{
    uint32_t  u32val;
    float32_t f32val;
    uint8_t   u8val;
    bool_t    bval;
    u32val = GET_RSR_Objects03_A_RsrObj03_A_PositionX(msg.GetData());
    f32val = CALC_RSR_Objects03_A_RsrObj03_A_PositionX(u32val, 1.0f);
    spd_sign.SetPosX(f32val);
    u32val = GET_RSR_Objects03_A_RsrObj03_A_PositionY(msg.GetData());
    f32val = CALC_RSR_Objects03_A_RsrObj03_A_PositionY(u32val, 1.0f);
    spd_sign.SetPosY(f32val);
    u32val = GET_RSR_Objects03_A_RsrObj03_A_PositionZ(msg.GetData());
    f32val = CALC_RSR_Objects03_A_RsrObj03_A_PositionZ(u32val, 1.0f);
    spd_sign.SetPosZ(f32val);
    u32val = GET_RSR_Objects03_A_RsrObj03_A_Stable(msg.GetData());
    bval   = CALC_RSR_Objects03_A_RsrObj03_A_Stable(u32val, 1);
    spd_sign.SetStable(bval);
    u32val = GET_RSR_Objects03_A_RsrObj03_A_Embedded(msg.GetData());
    u8val  = CALC_RSR_Objects03_A_RsrObj03_A_Embedded(u32val, 1);
    spd_sign.SetEmbedded(u8val);
    u32val = GET_RSR_Objects03_A_RsrObj03_A_Goodness(msg.GetData());
    u8val  = CALC_RSR_Objects03_A_RsrObj03_A_Goodness(u32val, 1);
    spd_sign.SetGoodness(u8val);
    u32val = GET_RSR_Objects03_A_RsrObj03_A_Quality(msg.GetData());
    bval   = CALC_RSR_Objects03_A_RsrObj03_A_Quality(u32val, 1);
    spd_sign.SetQuality(bval);
    u32val = GET_RSR_Objects03_A_RsrObj03_A_Vms(msg.GetData());
    bval   = CALC_RSR_Objects03_A_RsrObj03_A_Vms(u32val, 1);
    spd_sign.SetVms(bval);
    u32val = GET_RSR_Objects03_A_RsrObj03_A_Class(msg.GetData());
    u8val  = CALC_RSR_Objects03_A_RsrObj03_A_Class(u32val, 1);
    spd_sign.SetClassfication(u8val);
    u32val = GET_RSR_Objects03_A_RsrObj03_A_Id(msg.GetData());
    u8val  = CALC_RSR_Objects03_A_RsrObj03_A_Id(u32val, 1);
    spd_sign.SetId(u8val);
    spd_sign.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
}

void BoschMpcDriverT<HoloCanPacket>::ConstructSpdLimitSign4PartA(const HoloCanPacket& msg, SpdSignType& spd_sign)
{
    uint32_t  u32val;
    float32_t f32val;
    uint8_t   u8val;
    bool_t    bval;
    u32val = GET_RSR_Objects04_A_RsrObj04_A_PositionX(msg.GetData());
    f32val = CALC_RSR_Objects04_A_RsrObj04_A_PositionX(u32val, 1.0f);
    spd_sign.SetPosX(f32val);
    u32val = GET_RSR_Objects04_A_RsrObj04_A_PositionY(msg.GetData());
    f32val = CALC_RSR_Objects04_A_RsrObj04_A_PositionY(u32val, 1.0f);
    spd_sign.SetPosY(f32val);
    u32val = GET_RSR_Objects04_A_RsrObj04_A_PositionZ(msg.GetData());
    f32val = CALC_RSR_Objects04_A_RsrObj04_A_PositionZ(u32val, 1.0f);
    spd_sign.SetPosZ(f32val);
    u32val = GET_RSR_Objects04_A_RsrObj04_A_Stable(msg.GetData());
    bval   = CALC_RSR_Objects04_A_RsrObj04_A_Stable(u32val, 1);
    spd_sign.SetStable(bval);
    u32val = GET_RSR_Objects04_A_RsrObj04_A_Embedded(msg.GetData());
    u8val  = CALC_RSR_Objects04_A_RsrObj04_A_Embedded(u32val, 1);
    spd_sign.SetEmbedded(u8val);
    u32val = GET_RSR_Objects04_A_RsrObj04_A_Goodness(msg.GetData());
    u8val  = CALC_RSR_Objects04_A_RsrObj04_A_Goodness(u32val, 1);
    spd_sign.SetGoodness(u8val);
    u32val = GET_RSR_Objects04_A_RsrObj04_A_Quality(msg.GetData());
    bval   = CALC_RSR_Objects04_A_RsrObj04_A_Quality(u32val, 1);
    spd_sign.SetQuality(bval);
    u32val = GET_RSR_Objects04_A_RsrObj04_A_Vms(msg.GetData());
    bval   = CALC_RSR_Objects04_A_RsrObj04_A_Vms(u32val, 1);
    spd_sign.SetVms(bval);
    u32val = GET_RSR_Objects04_A_RsrObj04_A_Class(msg.GetData());
    u8val  = CALC_RSR_Objects04_A_RsrObj04_A_Class(u32val, 1);
    spd_sign.SetClassfication(u8val);
    u32val = GET_RSR_Objects04_A_RsrObj04_A_Id(msg.GetData());
    u8val  = CALC_RSR_Objects04_A_RsrObj04_A_Id(u32val, 1);
    spd_sign.SetId(u8val);
    spd_sign.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
}

void BoschMpcDriverT<HoloCanPacket>::ConstructSpdLimitSign5PartA(const HoloCanPacket& msg, SpdSignType& spd_sign)
{
    uint32_t  u32val;
    float32_t f32val;
    uint8_t   u8val;
    bool_t    bval;
    u32val = GET_RSR_Objects05_A_RsrObj05_A_PositionX(msg.GetData());
    f32val = CALC_RSR_Objects05_A_RsrObj05_A_PositionX(u32val, 1.0f);
    spd_sign.SetPosX(f32val);
    u32val = GET_RSR_Objects05_A_RsrObj05_A_PositionY(msg.GetData());
    f32val = CALC_RSR_Objects05_A_RsrObj05_A_PositionY(u32val, 1.0f);
    spd_sign.SetPosY(f32val);
    u32val = GET_RSR_Objects05_A_RsrObj05_A_PositionZ(msg.GetData());
    f32val = CALC_RSR_Objects05_A_RsrObj05_A_PositionZ(u32val, 1.0f);
    spd_sign.SetPosZ(f32val);
    u32val = GET_RSR_Objects05_A_RsrObj05_A_Stable(msg.GetData());
    bval   = CALC_RSR_Objects05_A_RsrObj05_A_Stable(u32val, 1);
    spd_sign.SetStable(bval);
    u32val = GET_RSR_Objects05_A_RsrObj05_A_Embedded(msg.GetData());
    u8val  = CALC_RSR_Objects05_A_RsrObj05_A_Embedded(u32val, 1);
    spd_sign.SetEmbedded(u8val);
    u32val = GET_RSR_Objects05_A_RsrObj05_A_Goodness(msg.GetData());
    u8val  = CALC_RSR_Objects05_A_RsrObj05_A_Goodness(u32val, 1);
    spd_sign.SetGoodness(u8val);
    u32val = GET_RSR_Objects05_A_RsrObj05_A_Quality(msg.GetData());
    bval   = CALC_RSR_Objects05_A_RsrObj05_A_Quality(u32val, 1);
    spd_sign.SetQuality(bval);
    u32val = GET_RSR_Objects05_A_RsrObj05_A_Vms(msg.GetData());
    bval   = CALC_RSR_Objects05_A_RsrObj05_A_Vms(u32val, 1);
    spd_sign.SetVms(bval);
    u32val = GET_RSR_Objects05_A_RsrObj05_A_Class(msg.GetData());
    u8val  = CALC_RSR_Objects05_A_RsrObj05_A_Class(u32val, 1);
    spd_sign.SetClassfication(u8val);
    u32val = GET_RSR_Objects05_A_RsrObj05_A_Id(msg.GetData());
    u8val  = CALC_RSR_Objects05_A_RsrObj05_A_Id(u32val, 1);
    spd_sign.SetId(u8val);
    spd_sign.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
}

void BoschMpcDriverT<HoloCanPacket>::ConstructSpdLimitSign7PartA(const HoloCanPacket& msg, SpdSignType& spd_sign)
{
    uint32_t  u32val;
    float32_t f32val;
    uint8_t   u8val;
    bool_t    bval;
    u32val = GET_RSR_Objects07_A_RsrObj07_A_PositionX(msg.GetData());
    f32val = CALC_RSR_Objects07_A_RsrObj07_A_PositionX(u32val, 1.0f);
    spd_sign.SetPosX(f32val);
    u32val = GET_RSR_Objects07_A_RsrObj07_A_PositionY(msg.GetData());
    f32val = CALC_RSR_Objects07_A_RsrObj07_A_PositionY(u32val, 1.0f);
    spd_sign.SetPosY(f32val);
    u32val = GET_RSR_Objects07_A_RsrObj07_A_PositionZ(msg.GetData());
    f32val = CALC_RSR_Objects07_A_RsrObj07_A_PositionZ(u32val, 1.0f);
    spd_sign.SetPosZ(f32val);
    u32val = GET_RSR_Objects07_A_RsrObj07_A_Stable(msg.GetData());
    bval   = CALC_RSR_Objects07_A_RsrObj07_A_Stable(u32val, 1);
    spd_sign.SetStable(bval);
    u32val = GET_RSR_Objects07_A_RsrObj07_A_Embedded(msg.GetData());
    u8val  = CALC_RSR_Objects07_A_RsrObj07_A_Embedded(u32val, 1);
    spd_sign.SetEmbedded(u8val);
    u32val = GET_RSR_Objects07_A_RsrObj07_A_Goodness(msg.GetData());
    u8val  = CALC_RSR_Objects07_A_RsrObj07_A_Goodness(u32val, 1);
    spd_sign.SetGoodness(u8val);
    u32val = GET_RSR_Objects07_A_RsrObj07_A_Quality(msg.GetData());
    bval   = CALC_RSR_Objects07_A_RsrObj07_A_Quality(u32val, 1);
    spd_sign.SetQuality(bval);
    u32val = GET_RSR_Objects07_A_RsrObj07_A_Vms(msg.GetData());
    bval   = CALC_RSR_Objects07_A_RsrObj07_A_Vms(u32val, 1);
    spd_sign.SetVms(bval);
    u32val = GET_RSR_Objects07_A_RsrObj07_A_Class(msg.GetData());
    u8val  = CALC_RSR_Objects07_A_RsrObj07_A_Class(u32val, 1);
    spd_sign.SetClassfication(u8val);
    u32val = GET_RSR_Objects07_A_RsrObj07_A_Id(msg.GetData());
    u8val  = CALC_RSR_Objects07_A_RsrObj07_A_Id(u32val, 1);
    spd_sign.SetId(u8val);
    spd_sign.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
}

void BoschMpcDriverT<HoloCanPacket>::ConstructSpdLimitSign8PartA(const HoloCanPacket& msg, SpdSignType& spd_sign)
{
    uint32_t  u32val;
    float32_t f32val;
    uint8_t   u8val;
    bool_t    bval;
    u32val = GET_RSR_Objects08_A_RsrObj08_A_PositionX(msg.GetData());
    f32val = CALC_RSR_Objects08_A_RsrObj08_A_PositionX(u32val, 1.0f);
    spd_sign.SetPosX(f32val);
    u32val = GET_RSR_Objects08_A_RsrObj08_A_PositionY(msg.GetData());
    f32val = CALC_RSR_Objects08_A_RsrObj08_A_PositionY(u32val, 1.0f);
    spd_sign.SetPosY(f32val);
    u32val = GET_RSR_Objects08_A_RsrObj08_A_PositionZ(msg.GetData());
    f32val = CALC_RSR_Objects08_A_RsrObj08_A_PositionZ(u32val, 1.0f);
    spd_sign.SetPosZ(f32val);
    u32val = GET_RSR_Objects08_A_RsrObj08_A_Stable(msg.GetData());
    bval   = CALC_RSR_Objects08_A_RsrObj08_A_Stable(u32val, 1);
    spd_sign.SetStable(bval);
    u32val = GET_RSR_Objects08_A_RsrObj08_A_Embedded(msg.GetData());
    u8val  = CALC_RSR_Objects08_A_RsrObj08_A_Embedded(u32val, 1);
    spd_sign.SetEmbedded(u8val);
    u32val = GET_RSR_Objects08_A_RsrObj08_A_Goodness(msg.GetData());
    u8val  = CALC_RSR_Objects08_A_RsrObj08_A_Goodness(u32val, 1);
    spd_sign.SetGoodness(u8val);
    u32val = GET_RSR_Objects08_A_RsrObj08_A_Quality(msg.GetData());
    bval   = CALC_RSR_Objects08_A_RsrObj08_A_Quality(u32val, 1);
    spd_sign.SetQuality(bval);
    u32val = GET_RSR_Objects08_A_RsrObj08_A_Vms(msg.GetData());
    bval   = CALC_RSR_Objects08_A_RsrObj08_A_Vms(u32val, 1);
    spd_sign.SetVms(bval);
    u32val = GET_RSR_Objects08_A_RsrObj08_A_Class(msg.GetData());
    u8val  = CALC_RSR_Objects08_A_RsrObj08_A_Class(u32val, 1);
    spd_sign.SetClassfication(u8val);
    u32val = GET_RSR_Objects08_A_RsrObj08_A_Id(msg.GetData());
    u8val  = CALC_RSR_Objects08_A_RsrObj08_A_Id(u32val, 1);
    spd_sign.SetId(u8val);
    spd_sign.SetTimestamp(holo::common::Timestamp(msg.GetSec(), msg.GetNsec()));
}

}  // namespace bosch_mpc
}  // namespace sensors
}  // namespace holo