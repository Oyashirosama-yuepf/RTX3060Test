/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file app_status.h
 * @brief This header file defines AppStatus class
 * @author GuoGuangchao(guoguangchao@holomatic.com)
 * @date 2020-04-27
 */

#ifndef HOLO_COMMON_APP_STATUS_H_
#define HOLO_COMMON_APP_STATUS_H_

#include <holo/common/timestamp.h>
#include <holo/container/vector.h>
#include <holo/core/types.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace common
{
/**
 * @brief AppStatus class.
 *
 * @verbatim
 * Serialize Type:
 * 0                   1                   2                   3
 * 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 * +-------------------------------------------------------------- +
 * |                     TIMESTAMP.SECONDS                         |
 * +---------------------------------------------------------------+
 * |                   TIMESTAMP.NANOSECONDS                       |
 * +---------------+-------------------------------+---------------+
 * |    NODEID     |    SIZE       |  STATUCCODE 0 |  STATUCCODE 1 |
 * +---------------+-------------------------------+---------------+
 * |  STATUCCODE 2 |  STATUCCODE 3 |  STATUCCODE 4 |  STATUCCODE 5 |
 * +---------------------------------------------------------------+
 *
 * TIMESTAMP: Timestamp of the data object.
 *
 * NODEID: Node Identifier of the app.
 *
 * SIZE: Number of statuscode.
 *
 * STATUSCODE(N): Statuscode for the apps.
 */
static uint32_t const APP_STATUS_MAX_CODE_NUMBER = 255U;
class AppStatus : public holo::container::details::VectorBase<uint8_t, APP_STATUS_MAX_CODE_NUMBER>
{
public:
    using Base = holo::container::details::VectorBase<uint8_t, APP_STATUS_MAX_CODE_NUMBER>;
    using Base::Base;

    AppStatus() : Base{}, timestamp_{}, node_id_{0}
    {
    }

    /**
     * @brief      Construct from module and status.
     *
     * @param[in]  timestamp  The timestamp
     * @param      nodeid     the application module type.     *
     * @exceptsafe No throw.
     */
    AppStatus(const Timestamp& timestamp, uint8_t node_id) noexcept : timestamp_(timestamp), node_id_(node_id)
    {
    }

    /**
     * @brief Set time stamp
     *
     * @return timestamp_
     */
    void SetTimestamp(const Timestamp& timestamp) noexcept
    {
        timestamp_ = timestamp;
    }

    /**
     * @brief Get time stamp
     *
     * @return timestamp_
     */
    Timestamp const& GetTimestamp() const
    {
        return timestamp_;
    }

    /**
     * @brief      Set node id
     *
     * @param      node_id  The object node id
     *
     * @exceptsafe No throw.
     */
    void SetNodeId(uint8_t node_id) noexcept
    {
        node_id_ = node_id;
    }

    /**
     * @brief      Get node id
     *
     * @return     The object node id.
     *
     * @exceptsafe No throw.
     */
    uint8_t GetNodeId() const noexcept
    {
        return node_id_;
    }

    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        return timestamp_.GetSerializedSize<ALIGN>() +
               holo::serialization::AlignedSize<ALIGN>(sizeof(uint8_t) * 2U + this->size() * sizeof(uint8_t));
    }

    template <typename S>
    void Serialize(S& serializer) const
    {
        serializer << timestamp_ << node_id_ << (static_cast<uint8_t>(this->size()));
        for (auto const& status_code : (*this))
        {
            serializer << status_code;
        }
        serializer << holo::serialization::align;
    }

    template <typename D>
    void Deserialize(D& deserializer)
    {
        this->clear();
        uint8_t size;
        deserializer >> timestamp_ >> node_id_ >> size;
        this->resize(size);
        for (size_t i = 0U; i < size; ++i)
        {
            deserializer >> (*this)[i];
        }
        deserializer >> holo::serialization::align;
    }

private:
    Timestamp timestamp_{};  ///< timestamp
    uint8_t   node_id_{};    ///< application module.
};

}  // namespace common
}  // namespace holo

#endif
