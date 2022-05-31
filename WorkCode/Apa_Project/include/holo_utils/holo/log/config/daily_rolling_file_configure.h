/* Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file daily_rolling_file_configure.h
 * @brief This header defines a daily rolling file as an output device.
 * @author moxiao@holomatic.com
 * @date 2021-09-07
 */

#ifndef HOLO_LOG_CONFIG_DAILY_ROLLING_FILE_CONFIGURE_H_
#define HOLO_LOG_CONFIG_DAILY_ROLLING_FILE_CONFIGURE_H_

#include <holo/log/config/configure.h>

namespace holo
{
namespace log
{
/**
 * @brief
 */
class DailyRollingFileConfigure : public Configure
{
public:
    static constexpr holo::uint32_t DEFAULT_MAX_BACKUP_INDEX = 10U;

    enum class DailyRollingFileSchedule : holo::uint32_t
    {
        MONTHLY = 0U,
        WEEKLY,
        DAILY,
        TWICE_DAILY,
        HOURLY,
        MINUTELY,
    };

    DailyRollingFileConfigure(std::string const& name, std::string const& filename)
      : Configure(name), filename_(filename)
    {
    }

    DailyRollingFileConfigure(YAML::Node const& config_node);
    DailyRollingFileConfigure(YAML::Node const& root_node, YAML::Node const& config_node);

    virtual ~DailyRollingFileConfigure() noexcept
    {
    }

    void SetFilename(std::string const& filename)
    {
        filename_ = filename;
    }

    std::string GetFilename() const
    {
        return filename_;
    }

    void SetDailyRollingFileSchedule(DailyRollingFileSchedule schedule)
    {
        schedule_ = schedule;
    }

    DailyRollingFileSchedule GetDailyRollingFileSchedule() const
    {
        return schedule_;
    }

    void SetFilenamePattern(std::string const& pattern)
    {
        filename_pattern_ = pattern;
    }

    std::string GetFilenamePattern() const
    {
        return filename_pattern_;
    }

    void SetMaxBackupIndex(holo::uint32_t index)
    {
        max_backup_index_ = index;
    }

    holo::uint32_t GetMaxBackupIndex() const
    {
        return max_backup_index_;
    }

    void SetImmediateFlush(holo::bool_t value)
    {
        immediate_flush_ = value;
    }

    holo::bool_t GetImmediateFlush() const
    {
        return immediate_flush_;
    }

    void SetCreateDirs(holo::bool_t value)
    {
        create_dirs_ = value;
    }

    holo::bool_t GetCreateDirs() const
    {
        return create_dirs_;
    }

    void SetRollOnClose(holo::bool_t value)
    {
        roll_on_close_ = value;
    }

    holo::bool_t GetRollOnClose() const
    {
        return roll_on_close_;
    }

private:
    /**
     * @brief parse configure form yaml node
     *
     * @param node YAML::Node
     */
    void parse(YAML::Node const& node);

private:
    std::string              filename_;
    std::string              filename_pattern_{"%Y-%m-%d-%H-%M-%S.%q"};
    DailyRollingFileSchedule schedule_{DailyRollingFileSchedule::DAILY};
    holo::uint32_t           max_backup_index_{DEFAULT_MAX_BACKUP_INDEX};
    holo::bool_t             immediate_flush_{true};
    holo::bool_t             create_dirs_{true};
    holo::bool_t             roll_on_close_{true};

    std::unordered_map<std::string, DailyRollingFileSchedule> schedule_map_{
        {"MONTHLY", DailyRollingFileSchedule::MONTHLY}, {"WEEKLY", DailyRollingFileSchedule::WEEKLY},
        {"DAILY", DailyRollingFileSchedule::DAILY},     {"TWICE_DAILY", DailyRollingFileSchedule::TWICE_DAILY},
        {"HOURLY", DailyRollingFileSchedule::HOURLY},   {"MINUTELY", DailyRollingFileSchedule::MINUTELY}};
};

}  // namespace log

}  // namespace holo

#endif
