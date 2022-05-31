/* Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file hololog.h

 * @brief This header defines the HoloLogger class
 * This file contains #include information about logging-related stuff.
 * Pretty much everybody needs to #include this file so that they can log various happenings.

 * @author moxiao@holomatic.com
 * @date 2021-09-06
 */

#ifndef HOLO_LOG_HOLOLOG_H_
#define HOLO_LOG_HOLOLOG_H_

#include <holo/core/types.h>
#include <yaml-cpp/yaml.h>

#include <holo/log/common.h>
#include <holo/log/configure.h>
#include <holo/log/loglevel.h>
#include <holo/log/writer.h>

namespace holo
{
namespace log
{
/**
 * @brief This class is a wrapper for all log module.
 */
class HoloLogger final
{
public:
    HoloLogger(HoloLogger const&) = delete;
    HoloLogger(HoloLogger&&)      = delete;
    HoloLogger& operator=(HoloLogger const&) = delete;
    HoloLogger& operator=(HoloLogger&&) = delete;

    /**
     * @brief default constructor
     */
    HoloLogger() = default;

    /**
     * @brief Initialize HoloLogger with yaml, and app_name
     *
     * @param node Yaml node
     * @param app_name std::string
     */
    static void Initialize(YAML::Node const& node, std::string const& app_name = "");

    /**
     * @brief Initialize HoloLogger with app_name
     *
     * @param app_name std::string
     */
    static void Initialize(std::string const& app_name = "");

    /**
     * @brief Calling this method will safely close HoloLogger
     * and release all resources.
     */
    static void Shutdown();

    /**
     * @brief Add a console output device.
     * write log to std::cout or std::cerr. The default target is std::cout.
     *
     * @param configure ConsoleConfigure
     */
    static void Add(ConsoleConfigure const& configure);

    /**
     * @brief Add a file as a output device.
     * write log to a file
     *
     * @param configure SingleFileConfigure
     */
    static void Add(SingleFileConfigure const& configure);

    /**
     * @brief Add a file as a output device.
     * write log to a file, and backup the file when reach a certain size.
     *
     * @param configure RollingFileConfigure
     */
    static void Add(RollingFileConfigure const& configure);

    /**
     * @brief Add a file as a output device.
     * The log is written to a file,
     * and the file is rolled over at a user chosen frequency.
     *
     * @param configure DailyRollingFileConfigure
     */
    static void Add(DailyRollingFileConfigure const& configure);

    /**
     * @brief Add a file as a output device.
     * The file is rolled over at a user chosen frequency while also
     * keeping in check a total maximum number of produced files.
     *
     * @param configure TimeBasedRollingFileConfigure
     */
    static void Add(TimeBasedRollingFileConfigure const& configure);

    /**
     * @brief Sends log to a remote log server.
     * Remote logging uses the TCP protocol.
     *
     * @param configure SocketConfigure
     */
    static void Add(SocketConfigure const& configure);

    /**
     * @brief Set loglevel to HoloLogger
     *
     * @param level LogLevel
     */
    static void SetLogLevel(LogLevel level);

    /**
     * @brief Set loglevel to output device using a name specified by the user.
     *
     * @param name The output device name
     * @param level LogLevel
     */
    static void SetLogLevel(std::string const& name, LogLevel level);

    static void SetMaxLogLevel(LogLevel max_level);

    static void SetMaxLogLevel(std::string const& name, LogLevel max_level);
};

#if defined(HOLO_LOG_TYPE) && (HOLO_LOG_TYPE == HOLO_LOG_TYPE_GLOG)

/*******************************************************************************
*************************          GLOG            *****************************
*******************************************************************************/
#if GOOGLE_STRIP_LOG == 0
#define COMPACT_GOOGLE_LOG_TRACE ::holo::log::StreamWriter(__FILE__, __LINE__)
#define LOG_TO_STRING_TRACE(message) ::holo::log::StreamWriter(__FILE__, __LINE__, ::holo::log::LogLevel::INFO, message)
#else
#define COMPACT_GOOGLE_LOG_TRACE ::holo::log::NullWriter()
#define LOG_TO_STRING_TRACE(message) ::holo::log::NullWriter()
#endif

#if GOOGLE_STRIP_LOG == 0
#define COMPACT_GOOGLE_LOG_DEBUG ::holo::log::StreamWriter(__FILE__, __LINE__)
#define LOG_TO_STRING_DEBUG(message) ::holo::log::StreamWriter(__FILE__, __LINE__, ::holo::log::LogLevel::INFO, message)
#else
#define COMPACT_GOOGLE_LOG_DEBUG ::holo::log::NullWriter()
#define LOG_TO_STRING_DEBUG(message) ::holo::log::NullWriter()
#endif
/*******************************************************************************
*************************         END GLOG         *****************************
*******************************************************************************/

#else

/*******************************************************************************
*************************        HOLO LOG          *****************************
*******************************************************************************/
#ifndef HOLO_LOG_ENABLE_LEVEL
#define HOLO_LOG_ENABLE_LEVEL 0U
#endif

#if HOLO_LOG_ENABLE_LEVEL == 0U
#define COMPACT_HOLO_LOG_TRACE ::holo::log::StreamWriter(__FILE__, __FUNCTION__, __LINE__, ::holo::log::LogLevel::TRACE)
#else
#define COMPACT_HOLO_LOG_TRACE ::holo::log::NullWriter()
#endif

#if HOLO_LOG_ENABLE_LEVEL <= 10000U
#define COMPACT_HOLO_LOG_DEBUG ::holo::log::StreamWriter(__FILE__, __FUNCTION__, __LINE__, ::holo::log::LogLevel::DEBUG)
#else
#define COMPACT_HOLO_LOG_DEBUG ::holo::log::NullWriter()
#endif

#if HOLO_LOG_ENABLE_LEVEL <= 20000U
#define COMPACT_HOLO_LOG_INFO ::holo::log::StreamWriter(__FILE__, __FUNCTION__, __LINE__, ::holo::log::LogLevel::INFO)
#else
#define COMPACT_HOLO_LOG_INFO ::holo::log::NullWriter()
#endif

#if HOLO_LOG_ENABLE_LEVEL <= 30000U
#define COMPACT_HOLO_LOG_WARNING                                                                                       \
    ::holo::log::StreamWriter(__FILE__, __FUNCTION__, __LINE__, ::holo::log::LogLevel::WARNING)
#else
#define COMPACT_HOLO_LOG_WARNING ::holo::log::NullWriter()
#endif

#if HOLO_LOG_ENABLE_LEVEL <= 40000U
#define COMPACT_HOLO_LOG_ERROR ::holo::log::StreamWriter(__FILE__, __FUNCTION__, __LINE__, ::holo::log::LogLevel::ERROR)
#else
#define COMPACT_HOLO_LOG_ERROR ::holo::log::NullWriter()
#endif

#if HOLO_LOG_ENABLE_LEVEL <= 50000U
#define COMPACT_HOLO_LOG_FATAL ::holo::log::StreamWriter(__FILE__, __FUNCTION__, __LINE__, ::holo::log::LogLevel::FATAL)
#else
#define COMPACT_HOLO_LOG_FATAL ::holo::log::NullWriter()
#endif

#define LOG(severity) COMPACT_HOLO_LOG_##severity.stream()

/*******************************************************************************
*************************         LOG_IF           *****************************
*******************************************************************************/
class LogMessageVoidify
{
public:
    LogMessageVoidify()
    {
    }

    // This has to be an operator with a precedence lower than << but
    // // higher than ?:
    void operator&(std::ostream&)
    {
    }
};

#define LOG_IF(severity, condition) !(condition) ? (void)0 : ::holo::log::LogMessageVoidify() & LOG(severity)

/*******************************************************************************
*************************           DLOG           *****************************
*******************************************************************************/
#ifndef NDEBUG
#define DLOG(severity) ::holo::log::NullWriter()
#define DLOG_IF(severity, condition) ::holo::log::NullWriter()
#else
#define DLOG(severity) LOG(severity)
#define DLOG_IF(severity, condition) LOG_IF(severity, condition)
#endif

/*******************************************************************************
*************************       LOG_EVERY_N        *****************************
*******************************************************************************/
#define LOG_EVERY_N_VARNAME(base, line) LOG_EVERY_N_VARNAME_CONCAT(base, line)
#define LOG_EVERY_N_VARNAME_CONCAT(base, line) base##line

#define LOG_OCCURRENCES LOG_EVERY_N_VARNAME(occurrences_, __LINE__)
#define LOG_OCCURRENCES_MOD_N LOG_EVERY_N_VARNAME(occurrences_mod_n_, __LINE__)

#define SOME_KIND_OF_LOG_EVERY_N(severity, n)                                                                          \
    static unsigned LOG_OCCURRENCES = 0, LOG_OCCURRENCES_MOD_N = 0;                                                    \
    __sync_add_and_fetch(&LOG_OCCURRENCES, 1);                                                                         \
    if (__sync_add_and_fetch(&LOG_OCCURRENCES_MOD_N, 1) > n)                                                           \
        __sync_sub_and_fetch(&LOG_OCCURRENCES_MOD_N, n);                                                               \
    if (LOG_OCCURRENCES_MOD_N == 1)                                                                                    \
    LOG(severity)

#define LOG_EVERY_N(severity, n) SOME_KIND_OF_LOG_EVERY_N(severity, (n))

/*******************************************************************************
*************************      LOG_IF_EVERY_N      *****************************
*******************************************************************************/
#define SOME_KIND_OF_LOG_IF_EVERY_N(severity, condition, n)                                                            \
    static unsigned LOG_OCCURRENCES = 0, LOG_OCCURRENCES_MOD_N = 0;                                                    \
    __sync_add_and_fetch(&LOG_OCCURRENCES, 1);                                                                         \
    if ((condition) && (__sync_add_and_fetch(&LOG_OCCURRENCES_MOD_N, 1) || true) &&                                    \
        ((LOG_OCCURRENCES_MOD_N >= n && __sync_sub_and_fetch(&LOG_OCCURRENCES_MOD_N, n)) || true) &&                   \
        LOG_OCCURRENCES_MOD_N == (1 % n))                                                                              \
    LOG(severity)

#define LOG_IF_EVERY_N(severity, condition, n) SOME_KIND_OF_LOG_IF_EVERY_N(severity, (condition), (n))

/*******************************************************************************
*************************       LOG_FIRST_N        *****************************
*******************************************************************************/
#define SOME_KIND_OF_LOG_FIRST_N(severity, n)                                                                          \
    static unsigned LOG_OCCURRENCES = 0;                                                                               \
    if (LOG_OCCURRENCES <= n)                                                                                          \
        __sync_add_and_fetch(&LOG_OCCURRENCES, 1);                                                                     \
    if (LOG_OCCURRENCES <= n)                                                                                          \
    LOG(severity)

#define LOG_FIRST_N(severity, n) SOME_KIND_OF_LOG_FIRST_N(severity, (n))

/*******************************************************************************
*************************       END HOLO LOG       *****************************
*******************************************************************************/

#endif

}  // namespace log

}  // namespace holo

#endif
