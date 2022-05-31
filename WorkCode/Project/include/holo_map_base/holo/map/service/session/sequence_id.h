/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file sequence_id.h
 * @brief sequence_id.h
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-12"
 */

#ifndef HOLO_MAP_SERVICE_SESSION_SEQUENCE_ID_H_
#define HOLO_MAP_SERVICE_SESSION_SEQUENCE_ID_H_

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

/**
 * @brief A proxy for operating Sequence Id. A session data package must with an individual,
 *        clients receive packages by requesting and subscribing, so we have to identify
 *        the package where it from by sequence id.
 */
class SequenceIdProxy
{
public:
    /// Redefine FixDataPackageType type for inner member.
    using DataPackageType       = holo::map::service::io::FixDataPackageType;
    /// Redefine sequence id type from DataPackageType.
    using SequenceIdType        = DataPackageType::SequenceIdType;
    /// Redefine token id type from DataPackageType.
    using TokenIdType           = DataPackageType::TokenIdType;

    /**
     * @brief Constructor.
     * 
     * @param[in] Token id, should apply from MapLocalService.
     */
    explicit SequenceIdProxy(TokenIdType const token);

    /**
     * @brief Destructor.
     */
    virtual ~SequenceIdProxy() noexcept;

    /**
     * @brief Add server mask to sequence id.
     * 
     * @detail It will set the first bit of sequence id to 1.
     * @param[in] id Sequence id.
     * @return A new sequence id with server mask.
     */
    SequenceIdType ManifestServerSequenceId(SequenceIdType const id) const;

    /**
     * @brief Remove server mask from sequence id.
     * 
     * @detail It will set the first bit of sequence id to 0.
     * @param[in] id Sequence id.
     * @return A new sequence if without server mask.
     */
    SequenceIdType ConcealServerSequenceId(SequenceIdType const id) const;

    /**
     * @brief Whether or not a sequence id with server mask.
     * 
     * @param[in] id Sequence id.
     * @return true: If the sequence id with server mask;
     *         false: otherwise.
     */
    holo::bool_t IsServerSequenceId(SequenceIdType const id) const;

    /**
     * @brief Whether or not a sequence id with client mask.
     * 
     * @param[in] id Sequence id.
     * @return true: If the sequence id with client mask;
     *         false: otherwise.
     */
    holo::bool_t IsClientSequenceId(SequenceIdType const id) const;

    /**
     * @brief Access current sequence id.
     * 
     * @return If initialized with server token, return sequence id with server mask.
     *         If initialized with client token, return sequence id with client mask. 
     */
    SequenceIdType GetCurrentSequenceId() const;
    
    /**
     * @brief Generate a new sequence id.
     * 
     * @return If initialized with server token, return sequence id with server mask.
     *         If initialized with client token, return sequence id with client mask.
     */
    SequenceIdType GenerateSequenceId();

private:
    /// Inner sequence id, range: [0, 0X00FFFFFFFFFFFFFF]. It is increased by GenerateSequenceId(),
    /// if it out of range, it will be reset to 0.
    SequenceIdType  sequence_id_    = 0;
    /// Token id, caller should initialize it by their token id applied from MapLocalService.
    TokenIdType     token_id_       = 0;
    /// Every token has an independent type, range: [0, 127], token type will be mask on
    /// the output sequence id at the first byte, type with 0 for server token and type with
    /// [1, 127] for clients token. So we can support only 127 clients and only one server.
    TokenIdType     token_type_     = 0;
}; ///< End of class SequenceIdProxy

/**
 * @}
 *
 */

} ///< namespace session
} ///< namespace service
} ///< namespace map
} ///< namesapce holo

#endif /* HOLO_MAP_SERVICE_SESSION_SEQUENCE_ID_H_ */
