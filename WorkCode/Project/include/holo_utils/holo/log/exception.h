/* Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file exception.h
 * @brief This header file defines exceptions related to log module.
 * @author moxiao@holomatic.com
 * @date 2021-09-06
 */

#ifndef HOLO_LOG_EXCEPTION_H_
#define HOLO_LOG_EXCEPTION_H_

#include <holo/core/types.h>
#include <yaml-cpp/yaml.h>
#include <sstream>
#include <stdexcept>
#include <string>

namespace holo
{
namespace log
{
namespace error_msg
{
constexpr holo::char_t const* INVALID_LEVEL{
    "invalid level; [level] must be one of these values:{ALL, TRACE, DEBUG, INFO, WARNING, ERROR, FATAL, OFF}"};
constexpr holo::char_t const* INVALID_SCHEDULE{
    "invalid schedule; [schedule] must be one of these values:{MONTHLY, WEEKLY, DAILY, TWICE_DAILY, HOURLY, MINUTELY}"};
constexpr holo::char_t const* INVALID_FILENAME{"bad filename; The [file] name is white spaces!"};
constexpr holo::char_t const* INVALID_CONF_TYPE{
    "invalid configure type; [type] must be one of these values:{console, single_file, rolling_file, "
    "daily_rolling_file, time_based_rolling_file, socket}"};
constexpr holo::char_t const* INVALID_CONF_NAME{"bad config name; The [name] is white spaces!"};
constexpr holo::char_t const* NODE_TYPE_ERROR{" type ERROR!"};
constexpr holo::char_t const* NODE_MISSING{" (required field) NOT defined!"};
constexpr holo::char_t const* INVALID_ENV_LEVEL{
    " environment value must be one of these values:{ALL, TRACE, DEBUG, INFO, WARNING, ERROR, FATAL, OFF}"};
constexpr holo::char_t const* INVALID_FILE_SIZE{
    "file size is too small. The file size must be greater than or equal to 200KB"};
constexpr holo::char_t const* INVALID_POINTER{"Pointer is NULL"};
constexpr holo::char_t const* INVALID_COLOR{"invalid color!"};
constexpr holo::char_t const* INVALID_MAX_LEVEL{
    "invalid max level; The maximum loglevel must be greater than or equal to the current loglevel"};
}  // namespace error_msg

/**
 * @brief LogLevelStringException is used to describe an exception of log level
 */
class LogLevelStringException : public YAML::RepresentationException
{
public:
    /**
     * @brief Constructs an exception with a mark.
     *
     * @param mark The location in a yaml file.
     */
    LogLevelStringException(YAML::Mark const& mark) : YAML::RepresentationException{mark, error_msg::INVALID_LEVEL}
    {
    }
};

/**
 * @brief ScheduleStringException is used to describe an exception of daily schedule
 */
class ScheduleStringException : public YAML::RepresentationException
{
public:
    /**
     * @brief Constructs an exception with a mark.
     *
     * @param mark The location in a yaml file.
     */
    ScheduleStringException(YAML::Mark const& mark) : YAML::RepresentationException{mark, error_msg::INVALID_SCHEDULE}
    {
    }
};

/**
 * @brief FileNameNotSetException is used to describe an exception of filename
 */
class FileNameNotSetException : public YAML::RepresentationException
{
public:
    /**
     * @brief Constructs an exception with a mark.
     *
     * @param mark The location in a yaml file.
     */
    FileNameNotSetException(YAML::Mark const& mark) : YAML::RepresentationException{mark, error_msg::INVALID_FILENAME}
    {
    }
};

/**
 * @brief ConfigureTypeException is used to describe an exception of configure type
 */
class ConfigureTypeException : public YAML::RepresentationException
{
public:
    /**
     * @brief Constructs an exception with a mark.
     *
     * @param mark The location in a yaml file.
     */
    ConfigureTypeException(YAML::Mark const& mark) : YAML::RepresentationException{mark, error_msg::INVALID_CONF_TYPE}
    {
    }
};

/**
 * @brief ConfigureNameException is used to describe an exception of configure name
 */
class ConfigureNameException : public YAML::RepresentationException
{
public:
    /**
     * @brief Constructs an exception with a mark.
     *
     * @param mark The location in a yaml file.
     */
    ConfigureNameException(YAML::Mark const& mark) : YAML::RepresentationException{mark, error_msg::INVALID_CONF_NAME}
    {
    }
};

/**
 * @brief NodeTypeException is used to describe an exception of yaml node type
 */
class NodeTypeException : public YAML::RepresentationException
{
public:
    /**
     * @brief Constructs an exception with a mark and a key.
     *
     * @param mark The location in a yaml file.
     * @param key A field key in a yaml file
     */
    NodeTypeException(YAML::Mark const& mark, std::string const& key)
      : YAML::RepresentationException{mark, buildMessage(key)}
    {
    }

private:
    /**
     * @brief build exception message
     *
     * @param key
     *
     * @return std::string const
     */
    std::string const buildMessage(std::string const& key)
    {
        std::ostringstream ostream;
        ostream << "[" << key << "]" << error_msg::NODE_TYPE_ERROR;
        return ostream.str();
    }
};

/**
 * @brief NodeMissingException is used to describe an exception of yaml node
 */
class NodeMissingException : public YAML::RepresentationException
{
public:
    /**
     * @brief Constructs an exception with a mark and a key.
     *
     * @param mark The location in a yaml file.
     * @param key A field key in a yaml file
     */
    NodeMissingException(YAML::Mark const& mark, std::string const& key)
      : YAML::RepresentationException{mark, buildMessage(key)}
    {
    }

private:
    /**
     * @brief build exception message
     *
     * @param key
     *
     * @return std::string const
     */
    std::string const buildMessage(std::string const& key)
    {
        std::ostringstream ostream;
        ostream << "[" << key << "]" << error_msg::NODE_MISSING;
        return ostream.str();
    }
};

class HoloLogException : public std::runtime_error
{
public:
    HoloLogException(std::string const& msg) : std::runtime_error{msg}
    {
    }

protected:
    ~HoloLogException() noexcept override              = default;
    HoloLogException(HoloLogException const&) noexcept = default;
    HoloLogException(HoloLogException&&) noexcept      = default;
    HoloLogException& operator=(HoloLogException const&) noexcept = default;
    HoloLogException& operator=(HoloLogException&&) noexcept = default;
};

/**
 * @brief BadEnvironmentVariableException is used to describe an exception of environment variable
 */
class BadEnvironmentVariableException : public HoloLogException
{
public:
    /**
     * @brief Constructs an exception
     *
     * @param env_name
     * @param env_value
     * @param msg
     */
    BadEnvironmentVariableException(std::string const& env_name, std::string const& env_value, std::string const& msg)
      : HoloLogException{buildMessage(env_name, env_value, msg)}
    {
    }

private:
    /**
     * @brief build exception message
     *
     * @param env_name
     * @param env_value
     * @param msg
     *
     * @return std::string const
     */
    std::string const buildMessage(std::string const& env_name, std::string const& env_value, std::string const& msg)
    {
        std::ostringstream ostream;
        ostream << "(" << env_name << "=" << env_value << ")" << msg;
        return ostream.str();
    }
};

class BadLogParameterException : public HoloLogException
{
public:
    /**
     * @brief Constructs an exception.
     *
     * @param function
     * @param size
     */
    template <typename T>
    BadLogParameterException(std::string const& func, T const& value, std::string const& msg)
      : HoloLogException{buildMessage(func, value, msg)}
    {
    }

private:
    /**
     * @brief build exception message
     *
     * @param function
     * @param size
     *
     * @return std::string
     */
    template <typename T>
    std::string const buildMessage(std::string const& func, T const& value, std::string const& msg)
    {
        std::ostringstream ostream;
        ostream << func << "(" << value << ")  parameter(" << value << ")" << msg;
        return ostream.str();
    }
};

class CreateLogDirectoryFailedException : public HoloLogException
{
public:
    CreateLogDirectoryFailedException(std::string const& msg) : HoloLogException{msg}
    {
    }
};

}  // namespace log

}  // namespace holo

#endif
