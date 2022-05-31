/**
 * @file holo_export.cpp
 * @author your name (you@domain.com)
 * @brief the implementation of the holo export
 * @version 0.1
 * @date 2020-08-05
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd. Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 */

#include <glog/logging.h>
#include <holo/bag/base/param_metadata.h>
#include <holo/utils/holo_root.h>
#include <holo_export.h>
#include <sys/stat.h>
#include <unistd.h>

#include <fstream>

#define MAX_PATH_LEN 256

namespace holo_cmw
{
holo::int32_t CreateDirectory(const std::string &directory_path)
{
    holo::uint32_t dir_path_len = directory_path.length();
    if (dir_path_len > MAX_PATH_LEN)
    {
        return -1;
    }
    char tmp_dir_path[MAX_PATH_LEN] = { 0 };
    for (uint32_t i = 0; i < dir_path_len; ++i)
    {
        tmp_dir_path[i] = directory_path[i];
        if (tmp_dir_path[i] == '\\' || tmp_dir_path[i] == '/')
        {
            if (access(tmp_dir_path, 0) != 0)
            {
                int32_t ret = mkdir(tmp_dir_path,S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
                if (ret != 0)
                {
                    return ret;
                }
            }
        }
    }
    return 0;
}

void HoloExport::ExportParam(const std::string& bag_name, const std::string& output_path)
{
    if (bag_name.empty())
    {
        LOG(ERROR) << "file name is empty!";
        return;
    }
    std::shared_ptr<holo::bag::storage_interfaces::ReadOnlyInterface> storage_;
    storage_ = std::make_shared<holo::bag::SqliteStorage>();
    storage_->Open(bag_name, holo::bag::storage_interfaces::IOFlag::READ_ONLY);
    std::vector<holo::bag::ParamMetadata> params = storage_->GetAllParamsFile();
    LOG(INFO) << "Param size " << params.size();
    if (params.size() == 0)
    {
        LOG(WARNING) << "No params contained in the holobagg.";
        return;
    }
    std::string real_path = output_path;
    if (output_path.empty())
    {
        real_path = holo::GetHoloConfigRootDirectory();
    }
    LOG(INFO) << real_path;
    for (auto param : params)
    {
        std::string full_path = real_path + "/" + param.path + "/";
        CreateDirectory(full_path);
        LOG(INFO) << full_path;
        std::ofstream out(full_path + param.name);
        out << param.file;
        out.close();
    }
}

}  // namespace holo_cmw