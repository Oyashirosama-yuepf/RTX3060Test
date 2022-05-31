/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 *
 * @file hpa_event_response.h
 * @brief This header file defines hpa event response
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021-05-29
 */

#ifndef HOLO_PARKING_BASE_SYSTEM_HPA_EVENT_RESPONSE_H_
#define HOLO_PARKING_BASE_SYSTEM_HPA_EVENT_RESPONSE_H_

#include <holo/common/timestamp.h>
#include <holo/core/types.h>

namespace holo {
namespace parking {
namespace system {
/**
 * @brief This class defines hpa event response
 */
class HpaEventResponse
{
public:
    enum class ResponseResultType : uint8_t
    {
        SUCCESS     = 0U,
        FAILED      = 1U,
        NO_RESPONSE = 2U,
    };

    enum class PathStateType : uint8_t
    {
        LEARNING_FINISHED = 0U,
        LEARNING_ACTIVE   = 1U,
        LEARNING_FAILED   = 2U,
        PATH_SAVING       = 3U,
        NOT_USED          = 4U,
    };

    struct HpaPathDetail
    {
        uint8_t path_index;  // 1 ~ 10
        uint8_t park_mode;   // 0: parkin; 1: parkinout
        uint8_t path_slot;   // 0: fixed; 1: passingby
        PathStateType path_state;
        uint8_t save_progress;     // 0 ~ 100
        uint8_t path_length;       // unit: m
        std::string picture_path;  // the file path which saves the picture taken in path start point or end point
    };

    struct HpaPathInfo
    {
        HpaPathDetail path[10];
    };

    /**
     * @brief default constructor
     */
    HpaEventResponse() noexcept
        : timestamp_()
        , response_result_(ResponseResultType::NO_RESPONSE)
        , is_used_(0)
        , is_park_(0)
        , is_selectline_(0)
        , hpa_path_info_{}
    {
    }

    /* timestamp_ */
    Timestamp GetTimestamp() const noexcept
    {
        return timestamp_;
    }

    void SetTimestamp(Timestamp const timestamp)
    {
        timestamp_ = timestamp;
    }

    /* response_result_ */
    ResponseResultType GetResponseResult() const noexcept
    {
        return response_result_;
    }

    void SetResponseResult(ResponseResultType const response_result)
    {
        response_result_ = response_result;
    }

    /* is_used_ */
    uint8_t GetIsUsed() const noexcept
    {
        return is_used_;
    }

    void SetIsUsed(uint8_t const is_used)
    {
        is_used_ = is_used;
    }

    /* is_park_ */
    uint8_t GetIsPark() const noexcept
    {
        return is_park_;
    }

    void SetIsPark(uint8_t const is_park)
    {
        is_park_ = is_park;
    }

    /* is_selectline_ */
    uint8_t GetIsSelectline() const noexcept
    {
        return is_selectline_;
    }

    void SetIsSelectline(uint8_t const is_selectline)
    {
        is_selectline_ = is_selectline;
    }

    /* hpa_path_info_ */
    HpaPathInfo GetHpaPathInfo() const noexcept
    {
        return hpa_path_info_;
    }

    void SetHpaPathInfo(HpaPathInfo const hpa_path_info)
    {
        hpa_path_info_ = hpa_path_info;
    }

    /* path_index */
    uint8_t GetPathIndex(uint8_t const array_number) const noexcept
    {
        return hpa_path_info_.path[array_number].path_index;
    }

    void SetPathIndex(uint8_t const path_index, uint8_t const array_number)
    {
        hpa_path_info_.path[array_number].path_index = path_index;
    }

    /* park_mode */
    uint8_t GetParkMode(uint8_t const array_number) const noexcept
    {
        return hpa_path_info_.path[array_number].park_mode;
    }

    void SetParkMode(uint8_t const park_mode, uint8_t const array_number)
    {
        hpa_path_info_.path[array_number].park_mode = park_mode;
    }

    /* path_slot */
    uint8_t GetParkSlot(uint8_t const array_number) const noexcept
    {
        return hpa_path_info_.path[array_number].path_slot;
    }

    void SetPathSlot(uint8_t const path_slot, uint8_t const array_number)
    {
        hpa_path_info_.path[array_number].path_slot = path_slot;
    }

    /* path_state */
    PathStateType GetParkState(uint8_t const array_number) const noexcept
    {
        return hpa_path_info_.path[array_number].path_state;
    }

    void SetPathState(PathStateType const path_state, uint8_t const array_number)
    {
        hpa_path_info_.path[array_number].path_state = path_state;
    }

    /* save_progress */
    uint8_t GetSaveProgress(uint8_t const array_number) const noexcept
    {
        return hpa_path_info_.path[array_number].save_progress;
    }

    void SetSaveProgress(uint8_t const save_progress, uint8_t const array_number)
    {
        hpa_path_info_.path[array_number].save_progress = save_progress;
    }

    /* path_length */
    uint8_t GetPathLength(uint8_t const array_number) const noexcept
    {
        return hpa_path_info_.path[array_number].path_length;
    }

    void SetPathLength(uint8_t const path_length, uint8_t const array_number)
    {
        hpa_path_info_.path[array_number].path_length = path_length;
    }

    /* picture_path */
    std::string GetPicturePath(uint8_t const array_number) const noexcept
    {
        return hpa_path_info_.path[array_number].picture_path;
    }

    void SetPicturePath(std::string const picture_path, uint8_t const array_number)
    {
        hpa_path_info_.path[array_number].picture_path = picture_path;
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U> size_t GetSerializedSize() const noexcept
    {
        size_t aligned_size = timestamp_.GetSerializedSize<ALIGN>() + holo::serialization::SerializedSize<ALIGN>(static_cast<uint8_t>(response_result_), is_used_, is_park_, is_selectline_);

        for (size_t i = 0U; i < 10U; i++)
        {
            aligned_size += hpa_path_info_.path[i].park_mode;
            aligned_size += hpa_path_info_.path[i].path_slot;
            aligned_size += hpa_path_info_.path[i].path_index;
            aligned_size += static_cast<uint8_t>(hpa_path_info_.path[i].path_state);
            aligned_size += hpa_path_info_.path[i].path_length;
            aligned_size += hpa_path_info_.path[i].picture_path.length();
            aligned_size += hpa_path_info_.path[i].save_progress;
        }
        return aligned_size;
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::serialization::SerializationBufferOverflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S> void Serialize(S &serializer) const
    {
        /* serialize data */
        serializer << timestamp_ << static_cast<uint8_t>(response_result_) << is_used_ << is_park_ << is_selectline_;
        for (size_t i = 0U; i < 10U; i++)
        {
            serializer << hpa_path_info_.path[i].park_mode;
            serializer << hpa_path_info_.path[i].path_slot;
            serializer << hpa_path_info_.path[i].path_index;
            serializer << static_cast<uint8_t>(hpa_path_info_.path[i].path_state);
            serializer << hpa_path_info_.path[i].path_length;
            serializer << hpa_path_info_.path[i].picture_path;
            serializer << hpa_path_info_.path[i].save_progress;
        }
        serializer << holo::serialization::align;
    }

    /**
     * @brief Deserialize this object from buffer through deserializer.
     *
     * @param deserializer The buffer to deserialize from.
     *
     * @return none.
     *
     * @throws holo::serialization::DeserializationBufferUnderflowException if buffer size < deserialized size.
     *
     * @exceptsafe Basic
     */
    template <typename D> void Deserialize(D &deserializer)
    {
        uint8_t response_result;
        uint8_t path_state;
        /* deserialize data */
        deserializer >> timestamp_ >> response_result >> is_used_ >> is_park_ >> is_selectline_;
        for (size_t i = 0U; i < 10U; i++)
        {
            deserializer >> hpa_path_info_.path[i].park_mode;
            deserializer >> hpa_path_info_.path[i].path_slot;
            deserializer >> hpa_path_info_.path[i].path_index;
            deserializer >> path_state;
            hpa_path_info_.path[i].path_state = static_cast<PathStateType>(path_state);
            deserializer >> hpa_path_info_.path[i].path_length;
            deserializer >> hpa_path_info_.path[i].picture_path;
            deserializer >> hpa_path_info_.path[i].save_progress;
        }
        deserializer >> holo::serialization::align;
        response_result_ = static_cast<ResponseResultType>(response_result);
    }

private:
    holo::common::Timestamp timestamp_;  ///< timestamp

    ResponseResultType response_result_;
    uint8_t is_used_;        // 0: not_used; 1: used
    uint8_t is_park_;        // 0: not_park; 1: park
    uint8_t is_selectline_;  // 0: not_selected; 1: selected
    HpaPathInfo hpa_path_info_;
};

}  // namespace system
}  // namespace parking
}  // namespace holo

#endif
