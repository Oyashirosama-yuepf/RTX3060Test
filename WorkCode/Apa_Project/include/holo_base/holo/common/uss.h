/**
 * @file chassis_state.h
 * @brief This header file defines ChassisState Object.
 * @author feiminghua(feiminghua@holomaitc.com)
 * @date 2200-2-24
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */
#ifndef HOLO_COMMON_USS_STATE_H_
#define HOLO_COMMON_USS_STATE_H_
#include <holo/common/details/uss/uss_dds_apa01.h>
#include <holo/common/details/uss/uss_dds_apa_object_adc_01to09.h>
#include <holo/common/details/uss/uss_dds_apa_park_slot_04to07.h>



// #include <holo/common/details/uss/uss_dds_apa01.h>
// #include <holo/common/details/uss/uss_dds_apa_object_adc_01to09.h>
// #include <holo/common/details/uss/uss_dds_apa_park_slot_04to07.h>
namespace holo
{
namespace common
{
/**
 * @addtogroup common
 * @{
 */

using DDSUSSApaParkSlot04To07 = details::DDSUSSApaParkSlot04To07; 
using DDSUSSApaObjectAdc01to09 = details::DDSUSSApaObjectAdc01to09;
using DDSUSSApa01 = details::DDSUSSApa01;


}  // namespace common

using DDSUSSApaParkSlot04To07[[deprecated]] = common::details::DDSUSSApaParkSlot04To07;
using DDSUSSApaObjectAdc01to09[[deprecated]] = common::details::DDSUSSApaObjectAdc01to09;
using DDSUSSApa01[[deprecated]] = common::details::DDSUSSApa01;
}  // namespace holo

#endif //HOLO_COMMON_USS_STATE_H_
