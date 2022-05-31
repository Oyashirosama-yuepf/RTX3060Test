/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file msg_verification.h
 * @brief This header file defines the ehr msg receiver.
 * @author zhengshulei@holomatic.com
 * @date 2021-10-25
 */
#ifndef HOLO_MAP_ADASIS_EHR_MSG_VERIFICATION_H_
#define HOLO_MAP_ADASIS_EHR_MSG_VERIFICATION_H_

#include <holo/core/types.h>
#include <holo/map/adasis/ehr/msg_buffer.h>

#include <map>
#include <vector>

namespace holo
{
namespace map
{
namespace adasis
{
namespace ehr
{

/**
 * @addtogroup ehr
 * @{
 *
 */

/**
 * @brief EHP message verification.
 */
class MessageVerification
{
public:
    explicit MessageVerification();
    ~MessageVerification();

public:
    /**
     * @brief EHP header verification, include length/counter/checksum.
     * @param[in] buffer message buffer
     * @param[in] header message header
     */
    holo::bool_t VerifyEHPHeader(MessageBuffer& buffer, E2EHeader& header);

    void SetVerbose(holo::bool_t const v) noexcept
    {
        this->verbose_ = v;
    }

private:
    holo::bool_t VerifyPayloadHeader(MessageBuffer& buffer);
    holo::bool_t HaveAllBundlePartReceived();
    holo::bool_t VerifyMapBundle(PayloadHeader& header);
    holo::bool_t VerifyAdasCycCounter(holo::uint32_t& pdu_id, AdasisHeader& header);

private:
    holo::bool_t verbose_ = false;
    // pdu counter
    holo::uint32_t cached_counter_ = 0;
    holo::uint32_t start_counter_ = 0;
    holo::uint32_t received_counter_ = 0;
    // map bundle
    holo::uint16_t part_count_                  = 0;
    holo::uint16_t part_index_                  = 0;
    holo::uint16_t bundle_id_                   = 0;
    holo::bool_t have_all_bundle_part_received_ = false;
    // adas header cyccounter
    std::map<holo::uint32_t, holo::uint8_t> adas_cyc_counter_map_;
};

/**
 * @}
 */

} // namespace ehr
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_EHR_MSG_VERIFICATION_H_ */