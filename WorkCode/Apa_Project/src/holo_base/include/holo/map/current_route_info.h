/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file current_route_info.h
 * @brief current_route_info: provide road infos in front of the car .
 * @author zhaofx(zhaofuxing@holomaitc.com)
 * @date "2019-11-26"
 */

#ifndef HOLO_BASE_INCLUDE_HOLO_MAP_ROUTE_INFO_H_
#define HOLO_BASE_INCLUDE_HOLO_MAP_ROUTE_INFO_H_

#include <memory>
#include <vector>

#include <holo/core/types.h>

#include <holo/common/odometry.h>
#include <holo/map/common_def.h>
#include <holo/map/common_object.h>
#include <holo/map/link_info.h>
#include <holo/serialization/serialization.h>

namespace holo
{
namespace map
{
/**
 * @addtogroup map
 * @{
 *
 */
class CurrentRouteInfo final
{
public:
    using PtrCurrentRouteInfo      = ::std::shared_ptr<CurrentRouteInfo>;
    using ConstPtrCurrentRouteInfo = ::std::shared_ptr<CurrentRouteInfo const>;

public:
    /**
     * @brief Get left and right road line by given odometry, if the given odometry is out of the
     * CurrentRouteInfo,return false.
     * @param[in] info current route info
     * @param[in] lane_seq lane sequence of current road. Maybe some special lane sequence is -1.
     * @param[out] left_route_lines Left road line.
     * @param[out] right_route_lines Right road line.
     * @param[in] distance Distance of road line.
     * @param[in] forward Direction(only support true now).
     * @return true Success;
     *         false Failure.
     */
    static bool GetCurrentRouteLine(const CurrentRouteInfo& info, const SeqValue lane_seq,
                                    ::std::vector<::std::vector<::holo::geometry::Point3d>>& left_route_lines,
                                    ::std::vector<::std::vector<::holo::geometry::Point3d>>& right_route_lines,
                                    const ::holo::float32_t distance = 50.0f, const bool forward = true);

    /**
     * @brief Get left and right road line by given odometry, if the given odometry is out of the
     * CurrentRouteInfo,return false.
     *
     * @param[in] info               Current route info
     * @param[in] link_id            Id for link after map matching
     * @param[in] lane_id            Id for lane after map matching
     * @param[out] left_route_lines  Left road lines are sorted from near to far.
     * @param[out] right_route_lines Right road line are sorted from near to far.
     * @param[in] forward            true for looking up succeeding links, false for preceeding links.
     *
     * @return true Operate Successfully;
     *         false Otherwise.
     */
    static bool GetCurrentRouteLineV2(CurrentRouteInfo const& info, KeyValue const link_id, KeyValue const lane_id,
                                      ::std::vector<::std::vector<::holo::geometry::Point3d>>& left_route_lines,
                                      ::std::vector<::std::vector<::holo::geometry::Point3d>>& right_route_lines,
                                      bool const                                               forward = true);

public:
    /**
     * @brief Set Links
     *
     * @param[in] links
     */
    void SetLinks(const ::std::vector<LinkInfo>& links) noexcept
    {
        this->vec_links_ = links;
    }

    /**
     * @brief Set Links as rvalue
     *
     * @param[in] links
     */
    void SetLinks(::std::vector<LinkInfo>&& links) noexcept
    {
        this->vec_links_ = std::move(links);
    }

    /**
     * @brief Get road infos,xx m in front of the car, the length of the road will be greater than user expect.
     *
     * @return const ::std::vector<LinkInfo>&
     */
    const ::std::vector<LinkInfo>& GetLinks() const noexcept
    {
        return this->vec_links_;
    }

    /**
     * @brief Set the Rear Links
     *
     * @param[in] links
     */
    void SetRearLinks(const ::std::vector<LinkInfo>& links) noexcept
    {
        this->vec_rear_links_ = links;
    }

    /**
     * @brief Set the Rear Links as rvalue
     *
     * @param[in] links
     */
    void SetRearLinks(::std::vector<LinkInfo>&& links) noexcept
    {
        this->vec_rear_links_ = std::move(links);
    }

    /**
     * @brief Get road infos,xx m rear of the car
     *
     * @return const ::std::vector<LinkInfo>&
     */
    const ::std::vector<LinkInfo>& GetRearLinks() const noexcept
    {
        return this->vec_rear_links_;
    }

    /**
     * @brief Set the objects
     *
     * @param[in] links
     */
    void SetObjects(const ::std::vector<CommonObject>& objects) noexcept
    {
        this->vec_objects_ = objects;
    }

    /**
     * @brief Set the objects as rvalue
     *
     * @param[in] links
     */
    void SetObjects(::std::vector<CommonObject>&& objects) noexcept
    {
        this->vec_objects_ = std::move(objects);
    }

    /**
     * @brief Get road objects
     *
     * @return const ::std::vector<LinkInfo>&
     */
    const ::std::vector<CommonObject>& GetObjects() const noexcept
    {
        return this->vec_objects_;
    }

    /**
     * @brief Set the status
     *
     * @details the meanings of status could be viewed at the field status_,
     * and the status is mainly used to represent the relibility of the current
     * route info.
     *
     * @param[in] status
     */
    void SetStatus(uint8_t status) noexcept
    {
        status_ = status;
    }

    /**
     * @brief Get status
     *
     * @details When you decide to use the current route info, you need
     * to judge whether the status is 0. If not, you'd better discard it.
     *
     * @return uint8_t
     */
    uint8_t GetStatus() const noexcept
    {
        return status_;
    }

    /**
     * @brief Output link info content as string
     *
     * @return ::std::string
     */
    ::std::string ToString() const noexcept
    {
        ::std::ostringstream oss;

        for (const auto& iter : GetLinks())
        {
            oss << " \n link:" << iter.ToString() << "; ";
        }

        return oss.str();
    }

    /**
     * @brief Get serialized size at give byte alignment value
     *
     * @tparam ALIGN Byte alignment value
     *
     * @return Serialized size
     */
    template <size_t ALIGN = 4U>
    size_t GetSerializedSize() const noexcept
    {
        size_t aligned_size = holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(vec_links_.size()));
        if (vec_links_.size() > 0U)
        {
            for (size_t i = 0U; i < vec_links_.size(); i++)
            {
                aligned_size += vec_links_[i].GetSerializedSize<ALIGN>();
            }
        }
        aligned_size += holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(vec_rear_links_.size()));
        if (vec_rear_links_.size() > 0U)
        {
            for (size_t i = 0U; i < vec_rear_links_.size(); i++)
            {
                aligned_size += vec_rear_links_[i].GetSerializedSize<ALIGN>();
            }
        }
        aligned_size += holo::serialization::SerializedSize<ALIGN>(static_cast<uint32_t>(vec_objects_.size()));
        if (vec_objects_.size() > 0U)
        {
            for (size_t i = 0U; i < vec_objects_.size(); i++)
            {
                aligned_size += vec_objects_[i].GetSerializedSize<ALIGN>();
            }
        }
        aligned_size += holo::serialization::SerializedSize<ALIGN>(status_);
        return aligned_size;
    }

    /**
     * @brief Serialize this object into buffer through serializer.
     *
     * @param serializer The buffer to serializer.
     *
     * @return none.
     *
     * @throws holo::exception::SerializationBufferOvecflowException if buffer size < serialized size.
     *
     * @exceptsafe Basic
     */
    template <typename S>
    void Serialize(S& serializer) const
    {
        uint32_t i = 0, vec_size = static_cast<uint32_t>(vec_links_.size());
        serializer << vec_size;
        for (i = 0; i < vec_size; ++i)
        {
            serializer << vec_links_[i];
        }
        vec_size = static_cast<uint32_t>(vec_rear_links_.size());
        serializer << vec_size;
        for (i = 0; i < vec_size; ++i)
        {
            serializer << vec_rear_links_[i];
        }
        vec_size = static_cast<uint32_t>(vec_objects_.size());
        serializer << vec_size;
        for (i = 0; i < vec_size; ++i)
        {
            serializer << vec_objects_[i];
        }
        serializer << status_;
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
    template <typename D>
    void Deserialize(D& deserializer)
    {
        uint32_t                    i = 0, vec_size = 0;
        ::std::vector<LinkInfo>     vec_links;
        ::std::vector<LinkInfo>     vec_rear_links;
        ::std::vector<CommonObject> vec_objects;

        deserializer >> holo::serialization::align >> vec_size;
        vec_links.resize(vec_size);
        for (i = 0; i < vec_size; ++i)
        {
            deserializer >> vec_links[i];
        }

        deserializer >> vec_size;
        vec_rear_links.resize(vec_size);
        for (i = 0; i < vec_size; ++i)
        {
            deserializer >> vec_rear_links[i];
        }

        deserializer >> vec_size;
        vec_objects.resize(vec_size);
        for (i = 0; i < vec_size; ++i)
        {
            deserializer >> vec_objects[i];
        }
        deserializer >> status_ >> holo::serialization::align;

        vec_links_      = std::move(vec_links);
        vec_rear_links_ = std::move(vec_rear_links);
        vec_objects_    = std::move(vec_objects);
    }

private:
    /**
     * @brief links info
     **/
    ::std::vector<LinkInfo> vec_links_;
    /**
     * @brief rear links info
     */
    ::std::vector<LinkInfo> vec_rear_links_;
    /**
     * @brief common objects
     */
    ::std::vector<CommonObject> vec_objects_;
    /**
     * @brief the status is used to store state for route info after map matching
     *
     * @details The status is used to store state for route info. The meanings are as followed:
     *  - 0：success
     *  - 1：conventional failure
     *  - 2：retry fails
     *  - 3：network error
     *  - 4：serialize error
     *  - 5：map match result unreliable
     */
    uint8_t status_ = 1U;
};

/**
 * @}
 *
 */
}  // namespace map
}  // namespace holo
#endif  // HOLO_BASE_INCLUDE_HOLO_MAP_ROUTE_INFO_H_
