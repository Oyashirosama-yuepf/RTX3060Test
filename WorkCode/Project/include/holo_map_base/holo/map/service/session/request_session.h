/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file request_session.h
 * @brief Request session serialization.
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_SERVICE_SESSION_REQUEST_SESSION_H_
#define HOLO_MAP_SERVICE_SESSION_REQUEST_SESSION_H_

#include <vector>
#include <memory>

#include <holo/log/hololog.h>

#include <holo/map/service/io/types.h>
#include <holo/map/service/session/serialization.h>

namespace holo
{
namespace map
{
namespace service
{
namespace session
{

/**
 * @addtogroup session
 * @{
 *
 */

/**
 * @brief Concrete request session serialization, serialize and deserialize request session.
 * 
 * @detail In general, default request data contains map object ids with same type, like tile
 *         ids, road ids, lane ids, lane group ids, lane boundary ids and object ids.
 */
class DefaultRequestSession : public Serialization
{
public:
    /// Redefine inner types for inner members.
    using RequestIdType            = SessionType::ItemIdType;
    using RequestIdVectorType      = std::vector<RequestIdType>;

    using RequestCountType         = SessionType::ItemCountType;
    using RequestStatusType        = SessionType::ItemStatusType;
    using RequestFeatureType       = SessionType::ItemFeatureType;

    using FixBufferType            = std::vector<holo::uint8_t>;
    using FixBufferUPtrType        = std::unique_ptr<FixBufferType>;

    /**
     * @brief Constructor.
     */
    DefaultRequestSession();

    /**
     * @brief Destructor.
     */
    virtual ~DefaultRequestSession() noexcept;

    /**
     * @brief Access required session count, caller should prepare those sessions for
     *        transforming request data.
     * 
     * @return Required session count;
     */
    virtual std::size_t GetSessionCount() const;

    /**
     * @brief Access the max request data size.
     * 
     * @return The max request data size.
     */
    std::size_t GetRequestDataCapacity() const;

    /**
     * @brief Access concreate request data.
     * 
     * @return Request dta.
     */
    RequestIdVectorType const& GetRequestData() const noexcept;

    /**
     * @brief Access concreate request data type.
     * 
     * @return Request dta.
     */
    RequestFeatureType GetRequestDataType() const noexcept;

    /**
     * @brief Assign request data.
     * 
     * @param[n] d Request data, map object ids with same feature type.
     */
    void SetRequestData(RequestFeatureType const t, RequestIdVectorType const& d);

    /**
     * @brief Clear inner request data buffer and inner byte stream cache.
     */
    virtual void Clear() override;

protected:
    /**
     * @brief Serialize request data to base byte stream cache.
     */
    virtual holo::bool_t serialize(Header const& header, SessionPtrType ptr) override;

    /**
     * @brief Deserialize base byte stream buffer to request data.
     */
    virtual holo::bool_t deserialize(SessionPtrType ptr, Header& header) override;

private:
    /// Request data type.
    RequestFeatureType              type_ = RequestFeatureType::TYPE_UNKNOWN;
    /// Request data.
    RequestIdVectorType             data_;
    /// Serialization offset, only used in Serialize(), before a serialization group, must reset
    /// this offset. 
    RequestIdVectorType::size_type  offset_ = 0;
}; ///< End of class DefaultRequestSession

/**
 * @}
 *
 */

} ///< namespace session
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_SESSION_REQUEST_SESSION_H_ */