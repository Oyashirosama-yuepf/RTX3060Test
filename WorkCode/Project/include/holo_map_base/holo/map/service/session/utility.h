/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file utility.h
 * @brief Utilities for service session.
 * @author wanghaiyang@holomatic.com
 * @date "2020-12-24"
 */

#ifndef HOLO_MAP_SERVICE_SESSION_COMMON_H_
#define HOLO_MAP_SERVICE_SESSION_COMMON_H_

#include <string>

#include <holo/map/common/types.h>
#include <holo/map/service/io/types.h>

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

/// Redefine session type for task manager.
using SessionType            = holo::map::service::io::FixDataPackageType;
using SessionPtrType         = SessionType*;
using SessionCPtrType        = SessionType const*;
using SessionPtrVectorType   = std::vector<SessionPtrType>;
using SessionCPtrVectorType  = std::vector<SessionCPtrType>;

namespace utility
{
/**
 * @addtogroup utility
 * @{
 *
 */

/**
 * @brief Format Session sequence id to a JSON string.
 * 
 * @param[in] item A session sequence id value.
 * @return A JSON format string.
 */
std::string FormatToString(SessionType::SequenceIdType const& id);

/**
 * @brief Format Session item to a JSON string.
 * 
 * @param[in] item A session item.
 * @return A JSON format string.
 */
std::string FormatToString(SessionType::ItemType const& item);

/**
 * @brief Format session items to a JSON string.
 * 
 * @param[in] items Session items.
 * @return A JSON format string.
 */
std::string FormatToString(SessionType::ItemVectorType const& items);

/**
 * @brief Format session object to a JSON string.
 * 
 * @param[in] session A session object.
 * @return A JSON format string.
 */
std::string FormatToString(SessionType const& session);

/**
 * @brief Format session pointer to a JSON string.
 * 
 * @param[in] session A session pointer.
 * @return A JSON format string.
 */
std::string FormatToString(SessionPtrType  session);

/**
 * @brief Format session pointer to a JSON string.
 * 
 * @param[in] session A session pointer.
 * @return A JSON format string.
 */
std::string FormatToString(SessionCPtrType  session);

/**
 * @brief Format session pointers to a JSON string.
 * 
 * @param[in] session A vector of session pointers.
 * @return A JSON format string.
 */
std::string FormatToString(SessionPtrVectorType const& sessions);

/**
 * @brief Format session pointers to a JSON string.
 * 
 * @param[in] session A vector of session pointers.
 * @return A JSON format string.
 */
std::string FormatToString(SessionCPtrVectorType const& sessions);

/**
 * @}
 *
 */
} ///< namespace utility

/**
 * @}
 *
 */
} ///< namespace session
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_SESSION_COMMON_H_ */
