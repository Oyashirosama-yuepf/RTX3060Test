/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file response_session.h
 * @brief Response session serialization
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_SERVICE_SESSION_RESPONSE_SESSION_H_
#define HOLO_MAP_SERVICE_SESSION_RESPONSE_SESSION_H_

#include <vector>
#include <memory>

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
 * @brief Concrete response session serialization, serialize and deserialize
 *        response session.
 * 
 * @detail In general, default response data contains map object data with same type,
 *         like tile data, road data, lane data, lane group data, lane boundary data
 *         and object data.
 */
class DefaultResponseSession : public Serialization
{
public:
    /// Redefine inner type for inner members.
    using ResponseDataType = holo::uint8_t const*;
    using ResponseDataValueType = holo::uint8_t;
    using ResponseDataPtrType = ResponseDataValueType*;
    using ResponseDataCPtrType = ResponseDataValueType const*;

    /**
     * @brief Constructor.
     */
    DefaultResponseSession();

    /**
     * @brief Desconstructor.
     */
    virtual ~DefaultResponseSession() noexcept;

    /**
     * @brief Access required session count, caller should prepare those sessions for
     *        transforming response data.
     * 
     * @return Required session count;
     */
    std::size_t GetSessionCount() const override;

    /**
     * @brief Access the max response data size.
     * 
     * @return The max response data size.
     */
    std::size_t GetResponseDataCapacity() const;

    /**
     * @brief Clear inner response data buffer and inner byte stream cache.
     */
    virtual void Clear() override;

    /**
     * @brief Access concreate response data size.
     * 
     * @return Response data size, if response data is empty, this value will be 0.
     */
    std::size_t GetResponseDataSize() const noexcept;

    /**
     * @brief Assign concreate response data size.
     * 
     * @param[in] s Data size.
     */
    void SetResponseDataSize(std::size_t const s) noexcept;

    /**
     * @brief Access concreate response data.
     * 
     * @return Response data.
     */
    ResponseDataCPtrType GetResponseData() const noexcept;

    /**
     * @brief Access concreate response data.
     * 
     * @return Response data.
     */
    ResponseDataPtrType GetResponseData() noexcept;

    /**
     * @brief Assign response data.
     * 
     * @param[in] d Response data, a pointer refer to a map object buffer,
     *             this object only refer to the pointer, don't copy the data
     *             or release the pointer.
     * @param[in] s Data size of response data.
     */
    void SetResponseData(ResponseDataCPtrType d, std::size_t const s);

protected:
    /**
     * @brief Serialize response data to base byte stream cache.
     */
    virtual holo::bool_t serialize(Header const& header, SessionPtrType ptr) override;

    /**
     * @brief Deserialize base byte stream buffer to response data.
     */
    virtual holo::bool_t deserialize(SessionPtrType ptr, Header& header) override;

private:
    /// Max response buffer size, the max data transportation package should less than
    /// this value, otherwise DefaultResponseSession will throw an exception.
    static std::size_t const DEFAULT_REQUEST_BUFFER_SIZE;

    /// Serialized buffer of map object.
    ResponseDataPtrType    data_       = nullptr; 
    /// Size of serialized buffer.
    std::size_t            size_       = 0;
    /// Current data offset with data buffer.
    std::size_t            offset_      = 0;
}; ///< End of class DefaultResponseSession

/**
 * @}
 *
 */

} ///< namespace serialization
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_SESSION_RESPONSE_SESSION_H_ */
