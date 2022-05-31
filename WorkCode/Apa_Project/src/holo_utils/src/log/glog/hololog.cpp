#include <glog/logging.h>
#include <holo/log/exception.h>
#include <holo/log/glog/default_initializer.h>
#include <holo/log/hololog.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <atomic>
#include <cstring>
#include <iostream>
#include <memory>
#include <mutex>
#include <stdexcept>

/*glog config flags:
 *FLAGS_logtostderr: bool
 *FLAGS_alsologtostderr: bool
 *FLAGS_colorlogtostderr: bool
 *FLAGS_stderrthreshold: int32
 *FLAGS_log_prefix: bool
 *FLAGS_logbuflevel: int32
 *FLAGS_logbufsecs: int32
 *FLAGS_minloglevel: int32
 *FLAGS_log_dir: string
 *FLAGS_logfile_mode: int32
 *FLAGS_log_link: string
 *FLAGS_max_log_size: int32
 *FLAGS_stop_logging_if_full_disk: bool
 * */

namespace holo
{
namespace log
{
struct GlogGlobalConfig
{
    holo::int32_t log_level;
    holo::int32_t log_max_level;

    GlogGlobalConfig() : log_level{google::INFO}, log_max_level{google::FATAL}
    {
    }
};

struct GlogConsoleConfig
{
    holo::int32_t log_level;
    holo::int32_t log_max_level;
    std::string   name;

    GlogConsoleConfig() : log_level{google::INFO}, log_max_level{google::FATAL}, name{}
    {
    }
};

struct GlogFileConfig
{
    holo::int32_t log_level;
    holo::int32_t log_max_level;
    std::string   name;

    GlogFileConfig() : log_level{google::INFO}, log_max_level{google::FATAL}, name{}
    {
    }
};

static GlogGlobalConfig  g_global_config;
static GlogConsoleConfig g_console_config;
static GlogFileConfig    g_file_config;

static std::once_flag g_init_flag;
static std::once_flag g_destroy_flag;

static std::string g_app_name{};

static void mkdirs(std::string const& path, holo::uint32_t mode = 0755)
{
    size_t      pre = 0, pos;
    std::string dir;
    int         mdret;

    while ((pos = path.find_first_of('/', pre)) != std::string::npos)
    {
        dir = path.substr(0, pos++);
        pre = pos;

        if (dir.size() == 0)
            continue;

        if ((mdret = ::mkdir(dir.c_str(), mode)) && errno != EEXIST)
        {
            if ((mdret = ::mkdir(dir.c_str(), mode)) && errno != EEXIST)
            {
                CreateLogDirectoryFailedException e{"create log directory failed! " + dir};
                throw e;
            }
        }
    }
}

static holo::int32_t toGlogLevel(LogLevel level)
{
    if (LogLevel::WARNING == level)
    {
        return google::WARNING;
    }
    else if (LogLevel::ERROR == level)
    {
        return google::ERROR;
    }
    else if (LogLevel::FATAL == level)
    {
        return google::FATAL;
    }
    else if (LogLevel::OFF == level)
    {
        return google::FATAL;
    }
    else
    {
        return google::INFO;
    }
}

void HoloLogger::Add(ConsoleConfigure const& configure)
{
    static ::holo::log::glog::DefaultInitializer initializer;

    g_console_config.name          = configure.GetName();
    g_console_config.log_level     = toGlogLevel(configure.GetLevel());
    g_console_config.log_max_level = toGlogLevel(configure.GetMaxLevel());

    if (Color::NONE != configure.GetColor(LogLevel::WARNING))
    {
        FLAGS_colorlogtostderr = true;
    }
    else if (Color::NONE != configure.GetColor(LogLevel::ERROR))
    {
        FLAGS_colorlogtostderr = true;
    }
    else if (Color::NONE != configure.GetColor(LogLevel::FATAL))
    {
        FLAGS_colorlogtostderr = true;
    }
    else
    {
        FLAGS_colorlogtostderr = false;
    }

    SetLogLevel(configure.GetName(), configure.GetLevel());
}

void HoloLogger::Add(SingleFileConfigure const& configure)
{
    static ::holo::log::glog::DefaultInitializer initializer;

    g_file_config.name          = configure.GetName();
    g_file_config.log_level     = toGlogLevel(configure.GetLevel());
    g_file_config.log_max_level = toGlogLevel(configure.GetMaxLevel());

    std::string file = configure.GetFilename();
    size_t      pos  = file.find_last_of('/');

    if (pos != std::string::npos)
    {
        std::string dir = file.substr(0U, pos + 1U);
        mkdirs(dir);
        FLAGS_log_dir = dir;
    }
    else
    {
        FLAGS_log_dir = "./";
    }

    SetLogLevel(configure.GetName(), configure.GetLevel());
}

void HoloLogger::Add(RollingFileConfigure const& configure)
{
    static ::holo::log::glog::DefaultInitializer initializer;

    g_file_config.name          = configure.GetName();
    g_file_config.log_level     = toGlogLevel(configure.GetLevel());
    g_file_config.log_max_level = toGlogLevel(configure.GetMaxLevel());

    std::string file = configure.GetFilename();
    size_t      pos  = file.find_last_of('/');

    if (pos != std::string::npos)
    {
        std::string dir = file.substr(0U, pos + 1U);
        mkdirs(dir);
        FLAGS_log_dir = dir;
    }
    else
    {
        FLAGS_log_dir = "./";
    }

    SetLogLevel(configure.GetName(), configure.GetLevel());
}

void HoloLogger::Add(DailyRollingFileConfigure const& configure)
{
    static ::holo::log::glog::DefaultInitializer initializer;

    g_file_config.name          = configure.GetName();
    g_file_config.log_level     = toGlogLevel(configure.GetLevel());
    g_file_config.log_max_level = toGlogLevel(configure.GetMaxLevel());

    std::string file = configure.GetFilename();
    size_t      pos  = file.find_last_of('/');

    if (pos != std::string::npos)
    {
        std::string dir = file.substr(0U, pos + 1U);
        mkdirs(dir);
        FLAGS_log_dir = dir;
    }
    else
    {
        FLAGS_log_dir = "./";
    }

    SetLogLevel(configure.GetName(), configure.GetLevel());
}

void HoloLogger::Add(TimeBasedRollingFileConfigure const& configure)
{
    static ::holo::log::glog::DefaultInitializer initializer;

    g_file_config.name          = configure.GetName();
    g_file_config.log_level     = toGlogLevel(configure.GetLevel());
    g_file_config.log_max_level = toGlogLevel(configure.GetMaxLevel());

    std::string file = configure.GetFilename();
    size_t      pos  = file.find_last_of('/');

    if (pos != std::string::npos)
    {
        std::string dir = file.substr(0U, pos + 1U);
        mkdirs(dir);
        FLAGS_log_dir = dir;
    }
    else
    {
        FLAGS_log_dir = "./";
    }

    SetLogLevel(configure.GetName(), configure.GetLevel());
}

void HoloLogger::Add(SocketConfigure const& configure)
{
    static ::holo::log::glog::DefaultInitializer initializer;
    (void)configure;
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
}

void HoloLogger::Initialize(std::string const& app_name)
{
    std::call_once(g_init_flag, [&] {
        if (app_name.empty())
        {
            g_app_name = "NotSetAppName";
        }
        else
        {
            size_t pos = app_name.find_last_of('/');
            if (pos != std::string::npos)
            {
                g_app_name = app_name.substr(pos + 1U, std::string::npos);
            }
            else
            {
                g_app_name = app_name;
            }
        }

        google::InitGoogleLogging(g_app_name.c_str());
    });
}

void HoloLogger::Shutdown()
{
    std::call_once(g_destroy_flag, [&] { google::ShutdownGoogleLogging(); });
}

void HoloLogger::SetLogLevel(LogLevel level)
{
    g_global_config.log_level = toGlogLevel(level);
    if (g_global_config.log_level > g_file_config.log_level)
    {
        FLAGS_minloglevel = g_global_config.log_level;
    }
    else
    {
        FLAGS_minloglevel = g_file_config.log_level;
    }
}

void HoloLogger::SetLogLevel(std::string const& name, LogLevel level)
{
    if (g_console_config.name == name)
    {
        g_console_config.log_level = toGlogLevel(level);
        if (g_global_config.log_level > g_console_config.log_level)
        {
            FLAGS_stderrthreshold = g_global_config.log_level;
        }
        else
        {
            FLAGS_stderrthreshold = g_console_config.log_level;
        }
    }
    else
    {
        if (g_global_config.log_level > g_file_config.log_level)
        {
            FLAGS_minloglevel = g_global_config.log_level;
        }
        else
        {
            FLAGS_minloglevel = g_file_config.log_level;
        }
    }
}

void HoloLogger::SetMaxLogLevel(LogLevel max_level)
{
    g_global_config.log_max_level = toGlogLevel(max_level);
}

void HoloLogger::SetMaxLogLevel(std::string const& name, LogLevel max_level)
{
    if (g_console_config.name == name)
    {
        g_console_config.log_max_level = toGlogLevel(max_level);
    }
    else
    {
        g_file_config.log_max_level = toGlogLevel(max_level);
    }
}

}  // namespace log

}  // namespace holo
