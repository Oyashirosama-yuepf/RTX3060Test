/**
 * @file holo_export.h
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief the header of the holo export class
 * @version 0.1
 * @date 2020-08-04
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd. Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_CMW_APPS_HOLO_EXPORT_H_
#define _HOLO_CMW_APPS_HOLO_EXPORT_H_

#include <holo/core/types.h>
#include <holo/bag/base/storage_interfaces/base_io_interface.h>
#include <holo/bag/base/storage_interfaces/read_only_interface.h>
#include <holo/bag/storage/sqlite_storage.h>

#include <memory>
#include <string>
#include <vector>

namespace holo_cmw
{
class HoloExport
{
public:
    HoloExport() =default;
    ~HoloExport() = default;
    void ExportParam(const std::string& bag_name ,const std::string& output_path);
    void ExportMsg(const std::string& bag_name ,const std::string& topic_name, const std::string& output_file);
};
}  // namespace holo_cmw

#endif  //_HOLO_CMW_APPS_HOLO_EXPORT_H_
