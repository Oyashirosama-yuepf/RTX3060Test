/**
 * @file holo_replay.h
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief the header of the holo_replay cmw app
 * @version 0.1
 * @date 2020-05-09
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLO_CMW_APPS__HOLO_INFO_H_
#define _HOLO_CMW_APPS__HOLO_INFO_H_

#include <holo/bag/base/bag_metadata.h>
#include <holo/bag/interface/info.h>
#include <holo/utils/yaml.h>

#include <cmw_wrapper/utils/cxxopts.hpp>
#include <unordered_map>

namespace holo_cmw
{
class HoloInfo
{
public:
    HoloInfo();
    ~HoloInfo() = default;
    void Info(const std::string& file_name, holo::bool_t show_details = false);

private:
    void formatBagMetadata(const holo::bag::BagMetadata& metadata);

    std::unordered_map<std::string, std::string> formatDuration(std::chrono::high_resolution_clock::duration duration);

    std::string formatTimePoint(std::chrono::high_resolution_clock::duration time_point);

    std::string formatFileSize(uint64_t file_size);

    void formatFilePaths(const std::vector<std::string>& paths, std::stringstream& info_stream, int indentation_spaces);

    void formatTopicsWithType(const std::vector<holo::bag::TopicInformation>& topics, std::stringstream& info_stream,
                              int indentation_spaces);

    void indent(std::stringstream& info_stream, int number_of_spaces);

private:
    std::shared_ptr<holo::bag::Info> info_ptr_;
    holo::bool_t                     show_details_;
};

}  // namespace holo_cmw

#endif  // _HOLO_CMW_APPS__HOLO_INFO_H_
