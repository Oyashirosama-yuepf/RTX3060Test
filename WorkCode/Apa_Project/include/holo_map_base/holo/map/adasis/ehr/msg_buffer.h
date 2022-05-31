/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file msg_buffer.h
 * @brief This header file defines the ehr msg buffer,include split buffer to
 * header and payload.
 * @author zhengshulei@holomatic.com
 * @date 2021-10-25
 */
#ifndef HOLO_MAP_ADASIS_EHR_MSG_BUFFER_H_
#define HOLO_MAP_ADASIS_EHR_MSG_BUFFER_H_

#include <holo/map/adasis/baidu_v3/msg_types.h>

namespace holo
{
namespace map
{
namespace adasis
{
namespace ehr
{
using namespace baidu_v3;

/**
 * @addtogroup ehr
 * @{
 *
 */


/**
 * @brief EHP message package buffer implete header and entire parse.
 */
class MessageBuffer
{
public:
    const holo::uint16_t E2E_HEADER_LENGTH     = 14;
    const holo::uint16_t PAYLOAD_HEADER_LENGTH = 28;
    const holo::uint16_t ADASV3_HEADER_LENGTH  = 3;

public:
    /**
     * @brief Constructor of MessageBuffer.
     * 
     * @param[in] buffer message buffer pointer.
     * @param[in] size message buffer size.
     */
    MessageBuffer(const holo::uint8_t* buffer, holo::uint16_t size);
    ~MessageBuffer();

public:
    /**
     * @brief Get real paload size of EHP package.
     */
    holo::uint16_t GetPayloadLength();
    /**
     * @brief Parse EHP package header.
     * @param[out] header EHP package header.
     */
    holo::bool_t GetE2EHeader(E2EHeader& header);
    /**
     * @brief Parse EHP package paload header(include timestap and mapdata).
     * @param[out] header EHP package paload header.
     */
    holo::bool_t GetPayloadHeader(PayloadHeader& header);
    /**
     * @brief Parse ADASIS V3 header.
     * @param[out] header ADASIS V3 header.
     */
    holo::bool_t GetAdasisV3Header(AdasisHeader& header);
    /**
     * @brief Calculate package checksum.
     * @return package checksum.
     */
    holo::uint32_t CalculateCheckSum();
    /**
     * @brief Parse Baidu-EHP tx message.
     * @tparam T is Baidu-EHP tx message, e.g. MLM_LOC, MLM_PFLM.
     * @param[out] pdu_msg Baidu-EHP tx message
     */
    template <typename T>
    holo::bool_t Parse(T& pdu_msg)
    {
        msg_.Reset();
        msg_.Buffer().resize(msg_length_);
        memcpy(msg_.BufferAddress(), msg_data_, msg_length_);
        msg_ >> pdu_msg;
        return true;
    }

    void SetVerbose(holo::bool_t const v) noexcept
    {
        this->verbose_ = v;
    }

private:
    holo::bool_t verbose_ = false;
    const holo::uint8_t* msg_data_ = nullptr;
    holo::uint16_t msg_length_     = 0;
    BDDeserializer msg_;
};

/**
 * @}
 */

} // namespace ehr
} // namespace adasis
} // namespace map
} // namespace holo

#endif /* HOLO_MAP_ADASIS_EHR_MSG_BUFFER_H_ */