#ifndef HOLO_LOG_CONFIG_TIME_BASED_ROLLING_FILE_CONFIGURE_H_
#define HOLO_LOG_CONFIG_TIME_BASED_ROLLING_FILE_CONFIGURE_H_

#include <holo/log/config/configure.h>

namespace holo
{
namespace log
{
class TimeBasedRollingFileConfigure : public Configure
{
public:
    static constexpr holo::uint32_t DEFAULT_MAX_HISTORY = 100U;

    TimeBasedRollingFileConfigure(std::string const& name, std::string const& filename)
      : Configure(name), filename_(filename)
    {
    }

    virtual ~TimeBasedRollingFileConfigure() noexcept
    {
    }

    TimeBasedRollingFileConfigure(YAML::Node const& config_node);
    TimeBasedRollingFileConfigure(YAML::Node const& root_node, YAML::Node const& config_node);

    void SetFilename(std::string const& filename)
    {
        filename_ = filename;
    }

    std::string GetFilename() const
    {
        return filename_;
    }

    void SetFilenamePattern(std::string const& pattern)
    {
        filename_pattern_ = pattern;
    }

    std::string GetFilenamePattern() const
    {
        return filename_pattern_;
    }

    void SetMaxHistory(holo::uint32_t value)
    {
        max_history_ = value;
    }

    holo::uint32_t GetMaxHistory() const
    {
        return max_history_;
    }

    void SetCleanHistoryOnStart(holo::bool_t value)
    {
        clean_history_on_start_ = value;
    }

    holo::bool_t GetCleanHistoryOnStart() const
    {
        return clean_history_on_start_;
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
    std::string    filename_;
    std::string    filename_pattern_{"%d.log"};
    holo::uint32_t max_history_{DEFAULT_MAX_HISTORY};
    holo::bool_t   clean_history_on_start_{false};
    holo::bool_t   immediate_flush_{true};
    holo::bool_t   create_dirs_{true};
    holo::bool_t   roll_on_close_{true};
};

}  // namespace log

}  // namespace holo

#endif
