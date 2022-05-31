#include <holo/log/exception.h>
#include <holo/log/hololog.h>
#include <holo/log/log4cplus/appender/console_appender.h>
#include <holo/log/log4cplus/default_initializer.h>
#include <holo/log/log4cplus/filter/loglevel_filter.h>
#include <holo/log/log4cplus/layout/pattern_layout.h>
#include <log4cplus/asyncappender.h>
#include <log4cplus/configurator.h>
#include <log4cplus/consoleappender.h>
#include <log4cplus/fileappender.h>
#include <log4cplus/initializer.h>
#include <log4cplus/layout.h>
#include <log4cplus/logger.h>
#include <log4cplus/loggingmacros.h>
#include <log4cplus/socketappender.h>
#include <log4cplus/spi/loggingevent.h>
#include <atomic>
#include <cstring>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>

namespace holo
{
namespace log
{
static constexpr holo::uint32_t MAX_STREAM_BUFFER_SIZE = 20 * 1024;

thread_local std::shared_ptr<::holo::log::log4cplus::OStream> tls_ostream{nullptr};
thread_local std::shared_ptr<::holo::log::log4cplus::OStream> tls_nullostream{nullptr};

static std::once_flag g_init_flag;
static std::once_flag g_destroy_flag;

static std::atomic<holo::bool_t> g_running{false};

static ::log4cplus::Logger createDefaultGlobalLogger();
static LogLevel            stringToLogLevel(std::string const& level);

static ::log4cplus::Initializer* g_pLog4Initializer = nullptr;
static ::log4cplus::Logger       g_logger           = createDefaultGlobalLogger();

static holo::int32_t g_appender_count{0};

static std::unique_ptr<::log4cplus::Layout> createLogLayout(std::string const&                custom_layout,
                                                            Configure::PatternCallback const& func)
{
    return std::unique_ptr<::log4cplus::Layout>(new ::holo::log::log4cplus::PatternLayout(custom_layout, func));
}

static ::log4cplus::SharedAppenderPtr createAppender(ConsoleConfigure const& value)
{
    ::log4cplus::SharedAppenderPtr appender(new ::holo::log::log4cplus::ConsoleAppender(value));

    if (value.GetAsync())
    {
        ::log4cplus::SharedAppenderPtr async_appender(
            new ::log4cplus::AsyncAppender(appender, value.GetAsyncQueueLen()));
        async_appender->setName(value.GetName());
        async_appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
        async_appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

        if (value.GetMaxLevel() > LogLevel::ALL)
        {
            async_appender->setFilter(::log4cplus::spi::FilterPtr(
                new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
        }

        return async_appender;
    }

    return appender;
}

static ::log4cplus::SharedAppenderPtr createAppender(SingleFileConfigure const& value)
{
    ::log4cplus::SharedAppenderPtr appender(new ::log4cplus::FileAppender(
        value.GetFilename(), value.GetOpenMode(), value.GetImmediateFlush(), value.GetCreateDirs()));
    appender->setName(value.GetName());
    appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
    appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

    if (value.GetMaxLevel() > LogLevel::ALL)
    {
        appender->setFilter(::log4cplus::spi::FilterPtr(
            new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
    }

    if (value.GetAsync())
    {
        ::log4cplus::SharedAppenderPtr async_appender(
            new ::log4cplus::AsyncAppender(appender, value.GetAsyncQueueLen()));
        async_appender->setName(value.GetName());
        async_appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
        async_appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

        if (value.GetMaxLevel() > LogLevel::ALL)
        {
            async_appender->setFilter(::log4cplus::spi::FilterPtr(
                new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
        }

        return async_appender;
    }

    return appender;
}

static ::log4cplus::SharedAppenderPtr createAppender(RollingFileConfigure const& value)
{
    ::log4cplus::SharedAppenderPtr appender(
        new ::log4cplus::RollingFileAppender(value.GetFilename(), value.GetMaxFileSize(), value.GetMaxBackupIndex(),
                                             value.GetImmediateFlush(), value.GetCreateDirs()));
    appender->setName(value.GetName());
    appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
    appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

    if (value.GetMaxLevel() > LogLevel::ALL)
    {
        appender->setFilter(::log4cplus::spi::FilterPtr(
            new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
    }

    if (value.GetAsync())
    {
        ::log4cplus::SharedAppenderPtr async_appender(
            new ::log4cplus::AsyncAppender(appender, value.GetAsyncQueueLen()));
        async_appender->setName(value.GetName());
        async_appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
        async_appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

        if (value.GetMaxLevel() > LogLevel::ALL)
        {
            async_appender->setFilter(::log4cplus::spi::FilterPtr(
                new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
        }

        return async_appender;
    }

    return appender;
}

static ::log4cplus::SharedAppenderPtr createAppender(DailyRollingFileConfigure const& value)
{
    ::log4cplus::SharedAppenderPtr appender(new ::log4cplus::DailyRollingFileAppender(
        value.GetFilename(), static_cast<::log4cplus::DailyRollingFileSchedule>(value.GetDailyRollingFileSchedule()),
        value.GetImmediateFlush(), value.GetMaxBackupIndex(), value.GetCreateDirs(), value.GetRollOnClose(),
        value.GetFilenamePattern()));
    appender->setName(value.GetName());
    appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
    appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

    if (value.GetMaxLevel() > LogLevel::ALL)
    {
        appender->setFilter(::log4cplus::spi::FilterPtr(
            new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
    }

    if (value.GetAsync())
    {
        ::log4cplus::SharedAppenderPtr async_appender(
            new ::log4cplus::AsyncAppender(appender, value.GetAsyncQueueLen()));
        async_appender->setName(value.GetName());
        async_appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
        async_appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

        if (value.GetMaxLevel() > LogLevel::ALL)
        {
            async_appender->setFilter(::log4cplus::spi::FilterPtr(
                new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
        }

        return async_appender;
    }

    return appender;
}

static ::log4cplus::SharedAppenderPtr createAppender(TimeBasedRollingFileConfigure const& value)
{
    ::log4cplus::SharedAppenderPtr appender(new ::log4cplus::TimeBasedRollingFileAppender(
        value.GetFilename(), value.GetFilenamePattern(), value.GetMaxHistory(), value.GetCleanHistoryOnStart(),
        value.GetImmediateFlush(), value.GetCreateDirs(), value.GetRollOnClose()));
    appender->setName(value.GetName());
    appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
    appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

    if (value.GetMaxLevel() > LogLevel::ALL)
    {
        appender->setFilter(::log4cplus::spi::FilterPtr(
            new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
    }

    if (value.GetAsync())
    {
        ::log4cplus::SharedAppenderPtr async_appender(
            new ::log4cplus::AsyncAppender(appender, value.GetAsyncQueueLen()));
        async_appender->setName(value.GetName());
        async_appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
        async_appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

        if (value.GetMaxLevel() > LogLevel::ALL)
        {
            async_appender->setFilter(::log4cplus::spi::FilterPtr(
                new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
        }

        return async_appender;
    }

    return appender;
}

static ::log4cplus::SharedAppenderPtr createAppender(SocketConfigure const& value)
{
    ::log4cplus::SharedAppenderPtr appender(
        new ::log4cplus::SocketAppender(value.GetHost(), value.GetPort(), value.GetServerName(), value.GetIpv6()));
    appender->setName(value.GetName());
    appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
    appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

    if (value.GetMaxLevel() > LogLevel::ALL)
    {
        appender->setFilter(::log4cplus::spi::FilterPtr(
            new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
    }

    if (value.GetAsync())
    {
        ::log4cplus::SharedAppenderPtr async_appender(
            new ::log4cplus::AsyncAppender(appender, value.GetAsyncQueueLen()));
        async_appender->setName(value.GetName());
        async_appender->setThreshold(static_cast<::log4cplus::LogLevel>(value.GetLevel()));
        async_appender->setLayout(createLogLayout(value.GetPattern(), value.GetPatternFunction()));

        if (value.GetMaxLevel() > LogLevel::ALL)
        {
            async_appender->setFilter(::log4cplus::spi::FilterPtr(
                new ::holo::log::log4cplus::LogLevelFilter(value.GetLevel(), value.GetMaxLevel())));
        }

        return async_appender;
    }

    return appender;
}

LogLevel stringToLogLevel(std::string const& level)
{
    if (level == "ALL")
    {
        return LogLevel::ALL;
    }
    else if (level == "DEBUG")
    {
        return LogLevel::DEBUG;
    }
    else if (level == "INFO")
    {
        return LogLevel::INFO;
    }
    else if (level == "WARNING")
    {
        return LogLevel::WARNING;
    }
    else if (level == "ERROR")
    {
        return LogLevel::ERROR;
    }
    else if (level == "FATAL")
    {
        return LogLevel::FATAL;
    }
    else if (level == "OFF")
    {
        return LogLevel::OFF;
    }
    else if (level == "TRACE")
    {
        return LogLevel::TRACE;
    }
    else
    {
        BadEnvironmentVariableException e{"HOLO_LOG_LEVEL", level, error_msg::INVALID_ENV_LEVEL};
        throw e;
    }
}

::log4cplus::Logger createDefaultGlobalLogger()
{
    LogLevel level          = LogLevel::DEBUG;
    char*    holo_log_level = getenv("HOLO_LOG_LEVEL");
    if (nullptr != holo_log_level)
    {
        level = stringToLogLevel(holo_log_level);
    }

    ::log4cplus::Logger logger = ::log4cplus::Logger::getRoot();
    logger.setLogLevel(static_cast<::log4cplus::LogLevel>(level));
    if (logger.getAllAppenders().size() <= 0U)
    {
        ConsoleConfigure               console(ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME);
        ::log4cplus::SharedAppenderPtr appender = createAppender(console);
        logger.addAppender(appender);
        g_appender_count++;
    }

    return logger;
}

void HoloLogger::Add(ConsoleConfigure const& configure)
{
    static ::holo::log::log4cplus::DefaultInitializer initializer;

    if (LogLevel::OFF != configure.GetLevel())
    {
        ::log4cplus::SharedAppenderPtr appender_ptr = createAppender(configure);

        g_logger.addAppender(appender_ptr);
        g_appender_count++;
    }

    if (g_logger.getAppender(ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME))
    {
        g_logger.removeAppender(ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME);
        g_appender_count--;
    }
}

void HoloLogger::Add(SingleFileConfigure const& configure)
{
    static ::holo::log::log4cplus::DefaultInitializer initializer;

    if (LogLevel::OFF != configure.GetLevel())
    {
        ::log4cplus::SharedAppenderPtr appender_ptr = createAppender(configure);

        g_logger.addAppender(appender_ptr);
        g_appender_count++;
    }
}

void HoloLogger::Add(RollingFileConfigure const& configure)
{
    static ::holo::log::log4cplus::DefaultInitializer initializer;

    if (LogLevel::OFF != configure.GetLevel())
    {
        ::log4cplus::SharedAppenderPtr appender_ptr = createAppender(configure);

        g_logger.addAppender(appender_ptr);
        g_appender_count++;
    }
}

void HoloLogger::Add(DailyRollingFileConfigure const& configure)
{
    static ::holo::log::log4cplus::DefaultInitializer initializer;

    if (LogLevel::OFF != configure.GetLevel())
    {
        ::log4cplus::SharedAppenderPtr appender_ptr = createAppender(configure);

        g_logger.addAppender(appender_ptr);
        g_appender_count++;
    }
}

void HoloLogger::Add(TimeBasedRollingFileConfigure const& configure)
{
    static ::holo::log::log4cplus::DefaultInitializer initializer;

    if (LogLevel::OFF != configure.GetLevel())
    {
        ::log4cplus::SharedAppenderPtr appender_ptr = createAppender(configure);

        g_logger.addAppender(appender_ptr);
        g_appender_count++;
    }
}

void HoloLogger::Add(SocketConfigure const& configure)
{
    static ::holo::log::log4cplus::DefaultInitializer initializer;

    if (LogLevel::OFF != configure.GetLevel())
    {
        ::log4cplus::SharedAppenderPtr appender_ptr = createAppender(configure);

        g_logger.addAppender(appender_ptr);
        g_appender_count++;
    }
}

void HoloLogger::Initialize(YAML::Node const& node, std::string const& app_name)
{
    Initialize(app_name);

    Configure gconfig(node);
    SetLogLevel(gconfig.GetLevel());

    YAML::Node const& configs = node["config"];
    if (!configs.IsSequence())
    {
        NodeTypeException e{configs.Mark(), "config"};
        throw e;
    }

    for (std::size_t i = 0U; i < configs.size(); i++)
    {
        YAML::Node const& config = configs[i];
        if (!config.IsMap())
        {
            NodeTypeException e{config.Mark(), std::string("config[") + std::to_string(i) + "]"};
            throw e;
        }

        if (!config["type"].IsDefined())
        {
            NodeMissingException e{config.Mark(), "type"};
            throw e;
        }

        if (config["type"].IsScalar())
        {
            std::string const& type = config["type"].as<std::string>();
            if (type == "console")
            {
                ConsoleConfigure console(node, config);
                HoloLogger::Add(console);
            }
            else if (type == "single_file")
            {
                SingleFileConfigure single_file(node, config);
                HoloLogger::Add(single_file);
            }
            else if (type == "rolling_file")
            {
                RollingFileConfigure rolling_file(node, config);
                HoloLogger::Add(rolling_file);
            }
            else if (type == "daily_rolling_file")
            {
                DailyRollingFileConfigure daily_rolling_file(node, config);
                HoloLogger::Add(daily_rolling_file);
            }
            else if (type == "time_based_rolling_file")
            {
                TimeBasedRollingFileConfigure time_based_rolling_file(node, config);
                HoloLogger::Add(time_based_rolling_file);
            }
            else if (type == "socket")
            {
                SocketConfigure socket_conf(node, config);
                HoloLogger::Add(socket_conf);
            }
            else
            {
                ConfigureTypeException e{config["type"].Mark()};
                throw e;
            }
        }
        else
        {
            NodeTypeException e{config["type"].Mark(), "type"};
            throw e;
        }
    }

    if (g_logger.getAppender(ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME))
    {
        g_logger.removeAppender(ConsoleConfigure::DEFAULT_CONSOLE_CONFIG_NAME);
        g_appender_count--;
    }
}

void HoloLogger::Initialize(std::string const& app_name)
{
    (void)app_name;
    std::call_once(g_init_flag, [&] {
        if (nullptr == g_pLog4Initializer)
        {
            g_pLog4Initializer = new ::log4cplus::Initializer();
            g_running.store(true);
        }
    });
}

void HoloLogger::Shutdown()
{
    g_running.store(false);
    std::call_once(g_destroy_flag, [&] {
        if (g_pLog4Initializer)
        {
            delete g_pLog4Initializer;
            g_pLog4Initializer = nullptr;
        }
    });
}

void HoloLogger::SetLogLevel(LogLevel level)
{
    g_logger.setLogLevel(static_cast<::log4cplus::LogLevel>(level));
}

void HoloLogger::SetLogLevel(std::string const& name, LogLevel level)
{
    ::log4cplus::SharedAppenderPtr appender_ptr = g_logger.getAppender(name);
    if (appender_ptr)
    {
        appender_ptr->setThreshold(static_cast<::log4cplus::LogLevel>(level));
    }
}

void HoloLogger::SetMaxLogLevel(LogLevel max_level)
{
    ::log4cplus::SharedAppenderPtrList const& list = g_logger.getAllAppenders();
    for (auto& appender : list)
    {
        appender->setFilter(::log4cplus::spi::FilterPtr(
            new ::holo::log::log4cplus::LogLevelFilter(static_cast<LogLevel>(appender->getThreshold()), max_level)));
    }
}

void HoloLogger::SetMaxLogLevel(std::string const& name, LogLevel max_level)
{
    ::log4cplus::SharedAppenderPtr appender = g_logger.getAppender(name);
    if (appender)
    {
        appender->setFilter(::log4cplus::spi::FilterPtr(
            new ::holo::log::log4cplus::LogLevelFilter(static_cast<LogLevel>(appender->getThreshold()), max_level)));
    }
}

::holo::log::log4cplus::StreamWriter::StreamWriter(holo::char_t const* file, holo::char_t const* function,
                                                   holo::uint32_t line, LogLevel level)
  : file_(strrchr(file, '/')), function_(function), line_(line), level_(level)
{
    if (nullptr == tls_ostream || nullptr == tls_nullostream)
    {
        tls_ostream     = std::make_shared<::holo::log::log4cplus::OStream>(MAX_STREAM_BUFFER_SIZE);
        tls_nullostream = std::make_shared<::holo::log::log4cplus::OStream>(1U);
    }
    file_++;
    static ::holo::log::log4cplus::DefaultInitializer initializer;
}

::holo::log::log4cplus::StreamWriter::~StreamWriter()
{
    if (g_running.load() && g_appender_count > 0 && g_logger.isEnabledFor(static_cast<::log4cplus::LogLevel>(level_)))
    {
        tls_ostream->Trunc();
        ::log4cplus::detail::macro_forced_log(g_logger, static_cast<::log4cplus::LogLevel>(level_), tls_ostream->str(),
                                              file_, line_, function_);
        tls_ostream->Reset();
    }
}

::holo::log::log4cplus::OStream& ::holo::log::log4cplus::StreamWriter::stream()
{
    if (g_running.load() && g_appender_count > 0 && g_logger.isEnabledFor(static_cast<::log4cplus::LogLevel>(level_)))
    {
        return *tls_ostream;
    }
    else
    {
        return *tls_nullostream;
    }
}

}  // namespace log

}  // namespace holo
