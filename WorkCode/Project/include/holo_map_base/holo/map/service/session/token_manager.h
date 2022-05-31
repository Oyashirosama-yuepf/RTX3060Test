/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file token.h
 * @brief Token.
 * @author wanghaiyang@holomatic.com
 * @date "2020-11-23"
 */

#ifndef HOLO_MAP_SERVICE_SESSION_TOKEN_MANAGER_H_
#define HOLO_MAP_SERVICE_SESSION_TOKEN_MANAGER_H_

#include <map>
#include <string>

#include <holo/map/common/types.h>
#include <holo/map/service/io/types.h>
#include <holo/map/service/session/utility.h>

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
 * @brief Token manager.
 */
class TokenManager
{
public:
    /// Redefine inner types for inner members.
    using SessionType = holo::map::service::session::SessionType;
    
    /// Redefine pattern types for inner members.
    using PatternType       = SessionType::PatternType;
    using PatternVectorType = std::vector<PatternType>;

    /// Redefine token types for inner members.
    using TokenIdType       = SessionType::TokenIdType;
    using TokenIdVectorType = std::vector<TokenIdType>;

    /// Redefine string vector type for topics.
    using TopicVectorType   = std::vector<std::string>;

    /// Redefine value type for privilege.
    using PrivilegeValueType    = holo::uint64_t;
    using ChannelModeValueType  = holo::uint8_t;

    /**
     * @brief Authority for accessing map data.
     */
    enum class Privilege : PrivilegeValueType
    {
        PRIVILEGE_UNKNOWN       = 0X00,
        PRIVILEGE_TILE          = 0X01 << 0,
        PRIVILEGE_RESERVE_1     = 0X01 << 1,
        PRIVILEGE_RESERVE_2     = 0X01 << 2,
        PRIVILEGE_RESERVE_3     = 0X01 << 3,
        PRIVILEGE_RESERVE_4     = 0X01 << 4,
        PRIVILEGE_RESERVE_5     = 0X01 << 5,
        PRIVILEGE_RESERVE_6     = 0X01 << 6,
        PRIVILEGE_RESERVE_7     = 0X01 << 7,
        PRIVILEGE_ROAD          = 0X01 << 8,
        PRIVILEGE_LANE          = 0X01 << 9,
        PRIVILEGE_LANE_GROUP    = 0X01 << 10,
        PRIVILEGE_LANE_BOUNDARY = 0X01 << 11,
        PRIVILEGE_OBJECT        = 0X01 << 12,
    };

    /**
     * @brief Different channels need to use different message topics.
     */
    enum class ChannelMode : ChannelModeValueType
    {
        /// All nodes related to LMS(Local map servcie) transport map data by a
        /// single data channel.
        CHANNEL_MODE_SINGLE     = 0,
        /// Every node has an independent data channel for transporting map data.
        CHANNEL_MODE_MULTIPLE,
        /// Nodes with MLC use REGION data channel, and other nodes use ROUTING data
        /// channel.
        CHANNEL_MODE_MIXTURE,
    };

    /// Redefine value type for ChannelMode.
    using ChannelModeType = ChannelMode;

    /**
     * @brief Token info.
     */
    struct TokenInfo
    {
        /// Token id, global unique id for Application.
        TokenIdType         token_id        = 0;
        /// Pattern type.
        PatternType         pattern         = PatternType::PATTERN_REGION;
        /// Authority collections.
        PrivilegeValueType  privileges      = static_cast<PrivilegeValueType>(Privilege::PRIVILEGE_UNKNOWN);

        /// Reader topic.
        std::string         reader_topic;
        /// Writer topic.
        std::string         writer_topic;
        /// Reader topic works with CHANNEL_MODE_MIXTURE.
        std::string         mixture_reader_topic;
        /// Writer topic works with CHANNEL_MODE_MIXTURE.
        std::string         mixture_writer_topic;

        /**
         * @brief Default constructor.
         */
        TokenInfo();

        /**
         * @brief Constructor with multiple parameters.
         * 
         * @param[in] id Token id.
         * @param[in] value Privilege value, like: Privilege::PRIVILEGE_TILE|Privilege::PRIVILEGE_ROAD.
         * @param[in] rt Reader topic name.
         * @param[in] wt Writer topic name.
         */
        TokenInfo(TokenIdType const id, PatternType const p, PrivilegeValueType const value,
            std::string const& rt, std::string const& wt, std::string const& mrt, std::string const& mwt);
    };

    /// Define token info container.
    using TokenContainerType = std::map<TokenIdType, TokenInfo>;

    /**
     * @brief Default constructor.
     */
    TokenManager() = delete;

    /**
     * @brief Default desconstructor.
     */
    virtual ~TokenManager() noexcept = delete;

    /**
     * @brief Initialize privilege table, must be called before MapEngine initialzition.
     * 
     * @note It's enough to be called only once.
     * @param[in] b Benchmark flag, if true, init context for benchmark.
     * @return true: No error;
     *         false: An error occurs int this function, please refer to log for more details.
     */
    static holo::bool_t Initialize(holo::bool_t const b = false);

    /**
     * @brief Check if target token id is valid.
     * 
     * @note Initialized() before call this function.
     * @return true: Valid token id.
     *         false: Invalid token id.
     */
    static holo::bool_t IsValidTokenId(TokenIdType const id);

    /**
     * @brief Access pattern type by channel mode type. 
     * 
     * @param[in] c Channel mode type.
     * @return Pattern type.
     */
    static PatternType GetPattern(TokenIdType const id, ChannelModeType const c);

    /**
     * @brief Access reader topic by token id.
     * 
     * @note Initialized() before call this function.
     * @param[in] id Token id applied from MapLocalService.
     * @param[in] c If true, use single data transportation channel;
     *              If false, use multiple data transportation channel.
     * @return Reader topic name.
     */
    static std::string GetReaderTopicByTokenId(TokenIdType const id, holo::bool_t const c = true);

    /**
     * @brief Access reader topic by token id with different channel mode.
     * 
     * @note Initialized() before call this function.
     * @param[in] id Token id applied from MapLocalService.
     * @param[in] c Channel mode.
     * @return Topic name for reader.
     */
    static std::string GetReaderTopicByTokenIdV2(TokenIdType const id,
        ChannelMode const c = ChannelMode::CHANNEL_MODE_SINGLE);

    /**
     * @brief Access writer topic by token id.
     * 
     * @note Initialized() before call this function.
     * @param[in] c If true, use single data transportation channel;
     *              If false, use multiple data transportation channel.
     * @return Writer topic name.
     */
    static std::string GetWriterTopicByTokenId(TokenIdType const id, holo::bool_t const c = true);

    /**
     * @brief Access writer topic by token id with different channel mode.
     * 
     * @note Initialized() before call this function.
     * @param[in] id Token id applied from MapLocalService.
     * @param[in] c Channel mode.
     * @return Topic name for writer.
     */
    static std::string GetWriterTopicByTokenIdV2(TokenIdType const id,
        ChannelMode const c = ChannelMode::CHANNEL_MODE_SINGLE);

    /**
     * @brief Access server token id.
     * 
     * @note Initialized() before call this function, and this function only
     *       work for map local server.
      * @param[in] passward Passward for accessing server token id.
     * @return Sever token id.
     */
    static TokenIdType GetServerTokenId(std::string const& password);

    /**
     * @brief Access server token ids.
     * 
     * @note Initialized() before call this function, and this function only
     *       work for map local server.
     * @param[in] passward Passward for accessing server token id.
     * @param[in] c Channel mode, refer to ChannelMode for more details.
     * @return Sever token ids.
     */
    static TokenIdVectorType GetServerTokenIds(std::string const& password,
        ChannelModeType const c = ChannelModeType::CHANNEL_MODE_SINGLE);

    /**
     * @brief Access pattern types for LMS-serverr with different channel mode.
     * 
     * @note Initialized() before call this function.
     * @param[in] password Password, only LMS-server has this password.
     * @param[in] c Channel mode, refer to TokenManager::ChannelMode for details.
     * @return Pattern types.
     */
    static PatternVectorType GetServerPatterns(std::string const& password,
        ChannelModeType const c = ChannelModeType::CHANNEL_MODE_SINGLE);

    /**
     * @brief Access reader topic for LMS-server with different channel mode.
     * 
     * @note Initialized() before call this function.
     * @param[in] password Password, only LMS-server has this password.
     * @param[in] c Channel mode.
     * @return Topic name for reader.
     */
    static TopicVectorType GetServerReaderTopics(std::string const& password,
        ChannelModeType const c = ChannelModeType::CHANNEL_MODE_SINGLE);

    /**
     * @brief Access writer topic for LMS-server with different channel mode.
     * 
     * @note Initialized() before call this function.
     * @param[in] password Password, only LMS-server has this password.
     * @param[in] c Channel mode.
     * @return Topic name for writer.
     */
    static TopicVectorType GetServerWriterTopics(std::string const& password,
        ChannelModeType const c = ChannelModeType::CHANNEL_MODE_SINGLE);

private:
    /**
     * @brief Init inner token container.
     * 
     * @return true: Success.
     *         false: An error occurs in this function.
     */
    static holo::bool_t initTokenContainer();
};

/**
 * @}
 *
 */

} ///< namespace session
} ///< namespace service
} ///< namespace map
} ///< namespace holo

#endif /* HOLO_MAP_SERVICE_SESSION_TOKEN_MANAGER_H_ */