/* Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file configure.h
 * @brief configure base class
 * @author moxiao@holomatic.com
 * @date 2021-09-07
 */

#ifndef HOLO_LOG_CONFIG_CONFIGURE_H_
#define HOLO_LOG_CONFIG_CONFIGURE_H_

#include <holo/core/types.h>
#include <holo/log/exception.h>
#include <holo/log/loglevel.h>
#include <yaml-cpp/yaml.h>
#include <stdexcept>
#include <string>
#include <unordered_map>

namespace holo
{
namespace log
{
/**
 * @brief define common properties of configures
 */
class Configure
{
public:
    using PatternCallback = std::function<std::string const&(std::string const& file, holo::int32_t line,
                                                             LogLevel level, holo::int32_t pid, holo::int32_t tid)>;

    static constexpr holo::char_t const* HOLO_LOG_DEFAULT_PATTERN{"%d %b %L %p %m%n"};
    static constexpr holo::uint32_t      DEFAULT_ASYNC_QUEUE_LEN{1000U};

    /**
     * @brief Constructs a Configure object with a name
     *
     * @param name Configure object name, should be unique
     */
    Configure(std::string const& name);

    /**
     * @brief Constructs a Configure object with a yaml node
     *
     * @param node YAML::Node
     */
    Configure(YAML::Node const& node);

    /**
     * @brief Get Configure object name
     *
     * @return std::string
     */
    std::string GetName() const noexcept
    {
        return name_;
    }

    /**
     * @brief Set Log Level
     *
     * @param level ::holo::log::LogLevel
     */
    void SetLevel(LogLevel const level) noexcept
    {
        level_ = level;
    }

    /**
     * @brief Get Log Level
     *
     * @return LogLevel
     */
    LogLevel GetLevel() const noexcept
    {
        return level_;
    }

    void SetMaxLevel(LogLevel const max_level) noexcept
    {
        max_level_ = max_level;
    }

    LogLevel GetMaxLevel() const noexcept
    {
        return max_level_;
    }

    /**
     * @brief Set log pattern
     *
     * @param pattern std::string
     */
    void SetPattern(std::string const& pattern) noexcept
    {
        pattern_ = pattern;
    }

    /**
     * @brief Get log pattern
     *
     * @return std::string
     */
    std::string GetPattern() const noexcept
    {
        return pattern_;
    }

    void SetPatternFunction(PatternCallback const& function) noexcept
    {
        function_ = function;
    }

    PatternCallback GetPatternFunction() const noexcept
    {
        return function_;
    }

    /**
     * @brief Set async flag
     *
     * @param async holo::bool_t
     */
    void SetAsync(holo::bool_t const async) noexcept
    {
        async_ = async;
    }

    /**
     * @brief Get async flag
     *
     * @return holo::bool_t
     */
    holo::bool_t GetAsync() const noexcept
    {
        return async_;
    }

    /**
     * @brief Set async cache queue len
     *
     * @param async_queue_len holo::uint32_t
     */
    void SetAsyncQueueLen(holo::uint32_t const async_queue_len) noexcept
    {
        async_queue_len_ = async_queue_len;
    }

    /**
     * @brief Get async cache queue len
     *
     * @return holo::uint32_t
     */
    holo::uint32_t GetAsyncQueueLen() const noexcept
    {
        return async_queue_len_;
    }

protected:
    /**
     * @brief Extract the value specified by the key in the yaml file
     *
     * @tparam T
     * @param node
     * @param key
     *
     * @return T
     */
    template <typename T>
    T extractValue(YAML::Node const& node, std::string const& key)
    {
        if (node[key].IsDefined())
        {
            if (node[key].IsScalar())
            {
                return node[key].as<T>();
            }
            else
            {
                NodeTypeException e{node[key].Mark(), key};
                throw e;
            }
        }

        NodeMissingException e{node.Mark(), key};
        throw e;
    }

    /**
     * @brief extract the value specified by the key in the yaml file.
     * If fails, the default value is returned.
     *
     * @tparam T
     * @param node
     * @param key
     * @param default_value
     *
     * @return T
     */
    template <typename T>
    T extractValue(YAML::Node const& node, std::string const& key, T const& default_value)
    {
        if (node[key].IsDefined())
        {
            if (node[key].IsScalar())
            {
                return node[key].as<T>();
            }
            else
            {
                NodeTypeException e{node[key].Mark(), key};
                throw e;
            }
        }

        return default_value;
    }

    /**
     * @brief Set Configure object name
     *
     * @param name std::string
     */
    void setName(std::string const& name) noexcept
    {
        name_ = name;
    }

    /**
     * @brief parse configure form yaml node
     *
     * @param node YAML::Node
     */
    void parse(YAML::Node const& node);

private:
    Configure() = delete;
    std::string                               name_;
    std::string                               pattern_;
    LogLevel                                  level_;
    LogLevel                                  max_level_;
    holo::bool_t                              async_;
    holo::uint32_t                            async_queue_len_;
    PatternCallback                           function_;
    std::unordered_map<std::string, LogLevel> level_map_;
};

}  // namespace log

}  // namespace holo

#endif
