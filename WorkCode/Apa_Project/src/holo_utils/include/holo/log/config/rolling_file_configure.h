#ifndef HOLO_LOG_CONFIG_ROLLING_FILE_CONFIGURE_H_
#define HOLO_LOG_CONFIG_ROLLING_FILE_CONFIGURE_H_

#include <holo/log/config/configure.h>

namespace holo
{
namespace log
{
class RollingFileConfigure : public Configure
{
public:
    static constexpr holo::uint32_t DEFAULT_MAX_FILE_SIZE    = 20 * 1024 * 1024U;
    static constexpr holo::uint32_t MINIMUM_FILE_SIZE        = 200 * 1024U;
    static constexpr holo::uint32_t DEFAULT_MAX_BACKUP_INDEX = 10U;

    RollingFileConfigure(std::string const& name, std::string const& filename) : Configure(name), filename_(filename)
    {
    }

    RollingFileConfigure(YAML::Node const& config_node);
    RollingFileConfigure(YAML::Node const& root_node, YAML::Node const& config_node);

    virtual ~RollingFileConfigure() noexcept
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

    void SetMaxFileSize(holo::uint32_t size)
    {
        if (size < MINIMUM_FILE_SIZE)
        {
            BadLogParameterException e{"RollingFileConfigure::SetMaxFileSize", size, error_msg::INVALID_FILE_SIZE};
            throw e;
        }
        max_file_size_ = size;
    }

    holo::uint32_t GetMaxFileSize() const
    {
        return max_file_size_;
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

private:
    /**
     * @brief parse configure form yaml node
     *
     * @param node YAML::Node
     */
    void parse(YAML::Node const& node);

private:
    std::string    filename_;
    holo::uint32_t max_file_size_{DEFAULT_MAX_FILE_SIZE};
    holo::uint32_t max_backup_index_{DEFAULT_MAX_BACKUP_INDEX};
    holo::bool_t   immediate_flush_{true};
    holo::bool_t   create_dirs_{true};
};

}  // namespace log

}  // namespace holo

#endif
