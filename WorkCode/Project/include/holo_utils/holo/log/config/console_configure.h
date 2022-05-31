/* Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file console_configure.h
 * @brief This header is used to describe a console output device.
 * @author moxiao@holomatic.com
 * @date 2021-09-07
 */

#ifndef HOLO_LOG_CONFIG_CONSOLE_CONFIGURE_H_
#define HOLO_LOG_CONFIG_CONSOLE_CONFIGURE_H_

#include <holo/log/color.h>
#include <holo/log/config/configure.h>
#include <yaml-cpp/yaml.h>
#include <unordered_map>

namespace holo
{
namespace log
{
/**
 * @brief The log will be written to a console output device.
 * The default output stream is std::cout.
 * When log_to_stderr_ is set true, the output stream will be
 * std::cerr instead of std::cout.
 * When immediate_flush_ is set true, the output stream will be
 * flushed immediately
 */
class ConsoleConfigure : public Configure
{
public:
    static constexpr holo::char_t const* DEFAULT_CONSOLE_CONFIG_NAME = "sys_default_console_configure_name";

    /**
     * @brief Constructs a ConsoleConfigure object with a name
     *
     * @param name ConsoleConfigure object name, should be unique
     */
    ConsoleConfigure(std::string const& name) : Configure(name)
    {
    }

    /**
     * @brief Constructs a ConsoleConfigure object with a yaml node
     *
     * @param node YAML::Node
     */
    ConsoleConfigure(YAML::Node const& config_node);

    /**
     * @brief Constructs a ConsoleConfigure object with two yaml nodes
     *
     * @param root_node YAML::Node
     * @param config_node YAML::Node
     */
    ConsoleConfigure(YAML::Node const& root_node, YAML::Node const& config_node);

    /**
     * @brief Destroys the ConsoleConfigure object
     */
    virtual ~ConsoleConfigure() noexcept
    {
    }

    /**
     * @brief Set log to std::cerr
     *
     * @param value holo::bool_t
     */
    void SetLogToStderr(holo::bool_t value)
    {
        log_to_stderr_ = value;
    }

    /**
     * @brief Get log to std::cerr flag(true or false)
     *
     * @return holo::bool_t
     */
    holo::bool_t GetLogToStderr() const
    {
        return log_to_stderr_;
    }

    /**
     * @brief Set immediate flush
     *
     * @param value holo::bool_t
     */
    void SetImmediateFlush(holo::bool_t value)
    {
        immediate_flush_ = value;
    }

    /**
     * @brief Get immediate flush flag(true or false)
     *
     * @return holo::bool_t
     */
    holo::bool_t GetImmediateFlush() const
    {
        return immediate_flush_;
    }

    void SetColor(LogLevel level, Color color)
    {
        if (color > Color::NONE)
        {
            BadLogParameterException e{"ConsoleConfigure::SetColor", static_cast<holo::uint32_t>(color),
                                       "color Must be between 0 and Color::NONE"};
            throw e;
        }

        color_map_[level] = color;
    }

    Color GetColor(LogLevel level) const
    {
        auto const& got = color_map_.find(level);
        if (got == color_map_.end())
        {
            BadLogParameterException e{"ConsoleConfigure::GetColor", static_cast<holo::uint32_t>(level),
                                       error_msg::INVALID_LEVEL};
            throw e;
        }
        else
        {
            return got->second;
        }
    }

private:
    /**
     * @brief parse configure form yaml node
     *
     * @param node YAML::Node
     */
    void parse(YAML::Node const& node);

private:
    holo::bool_t log_to_stderr_{false};
    holo::bool_t immediate_flush_{false};

    std::unordered_map<LogLevel, Color> color_map_{
        {LogLevel::TRACE, Color::NONE},      {LogLevel::DEBUG, Color::NONE},
        {LogLevel::INFO, Color::NONE},       {LogLevel::WARNING, Color::LIGHT_YELLOW},
        {LogLevel::ERROR, Color::LIGHT_RED}, {LogLevel::FATAL, Color::LIGHT_PINK},
        {LogLevel::OFF, Color::NONE}};
};

}  // namespace log

}  // namespace holo

#endif
