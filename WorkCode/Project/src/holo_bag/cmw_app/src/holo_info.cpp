/**
 * @file holo_info.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief
 * @version 0.1
 * @date 2020-05-14
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd. Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#include <holo/log/hololog.h>
#include <holo_info.h>

#include <chrono>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

namespace holo_cmw
{
HoloInfo::HoloInfo() : info_ptr_(std::make_shared<holo::bag::Info>()), show_details_(false)
{
}

void HoloInfo::Info(const std::string& file_name, holo::bool_t show_details)
{
    holo::bag::BagMetadata metadata;
    try
    {
        metadata = info_ptr_->ReadMetadata(file_name);
    }
    catch (std::runtime_error& e)
    {
        (void)e;
        LOG(ERROR) << "Could not read metadata for " << file_name;
        return;
    }
    show_details_ = show_details;
    HoloInfo::formatBagMetadata(metadata);
}

void HoloInfo::formatBagMetadata(const holo::bag::BagMetadata& metadata)
{
    auto              start_time = metadata.starting_time.time_since_epoch();
    auto              end_time   = start_time + metadata.duration;
    std::stringstream info_stream;
    int               indentation_spaces = 19;  // The longest info field (Topics with Type:) plus one space.

    info_stream << std::endl;
    info_stream << "Files:             ";
    formatFilePaths(metadata.relative_file_paths, info_stream, indentation_spaces);
    info_stream << "Bag size:          " << formatFileSize(metadata.bag_size) << std::endl;
    info_stream << "Duration:          " << formatDuration(metadata.duration)["time_in_sec"] << "s" << std::endl;
    info_stream << "Start:             " << formatTimePoint(start_time) << std::endl;
    info_stream << "End:               " << formatTimePoint(end_time) << std::endl;
    info_stream << "Messages:          " << metadata.message_count << std::endl;
    info_stream << "Topic information: ";
    formatTopicsWithType(metadata.topics_with_message_count, info_stream, indentation_spaces);

    if (show_details_)
    {
        info_stream << "Version information: " << std::endl;
        for (auto ver : metadata.version_data)
        {
            info_stream << ver.category << "| " << ver.type << "| " << ver.version << std::endl;
        }
    }
    // print to console
    std::cout << info_stream.str() << std::endl;
}

std::unordered_map<std::string, std::string>
HoloInfo::formatDuration(std::chrono::high_resolution_clock::duration duration)
{
    std::unordered_map<std::string, std::string> formatted_duration;
    auto        m_seconds          = std::chrono::duration_cast<std::chrono::milliseconds>(duration);
    auto        seconds            = std::chrono::duration_cast<std::chrono::seconds>(m_seconds);
    std::string fractional_seconds = std::to_string(m_seconds.count() % 1000);
    std::time_t std_time_point     = seconds.count();
    tm          time;

    localtime_r(&std_time_point, &time);

    std::stringstream formatted_date;
    std::stringstream formatted_time;
    formatted_date << std::put_time(&time, "%b %e %Y");
    formatted_time << std::put_time(&time, "%H:%M:%S") << "." << fractional_seconds;
    formatted_duration["date"]        = formatted_date.str();
    formatted_duration["time"]        = formatted_time.str();
    formatted_duration["time_in_sec"] = std::to_string(seconds.count()) + "." + fractional_seconds;

    return formatted_duration;
}

std::string HoloInfo::formatTimePoint(std::chrono::high_resolution_clock::duration duration)
{
    auto formatted_duration = formatDuration(duration);
    return formatted_duration["date"] + " " + formatted_duration["time"] + " (" + formatted_duration["time_in_sec"] +
           ")";
}

std::string HoloInfo::formatFileSize(uint64_t file_size)
{
    double             size                   = static_cast<double>(file_size);
    static const char* units[]                = {"B", "KiB", "MiB", "GiB", "TiB"};
    double             reference_number_bytes = 1024;
    int                index                  = 0;
    while (size >= reference_number_bytes && index < 4)
    {
        size /= reference_number_bytes;
        index++;
    }

    std::stringstream rounded_size;
    int               size_format_precision = index == 0 ? 0 : 1;
    rounded_size << std::setprecision(size_format_precision) << std::fixed << size;
    return rounded_size.str() + " " + units[index];
}

void HoloInfo::formatFilePaths(const std::vector<std::string>& paths, std::stringstream& info_stream,
                               int indentation_spaces)
{
    if (paths.empty())
    {
        info_stream << std::endl;
        return;
    }

    info_stream << paths[0] << std::endl;
    size_t number_of_files = paths.size();
    for (size_t i = 1; i < number_of_files; i++)
    {
        indent(info_stream, indentation_spaces);
        info_stream << paths[i] << std::endl;
    }
}

void HoloInfo::formatTopicsWithType(const std::vector<holo::bag::TopicInformation>& topics,
                                    std::stringstream& info_stream, int indentation_spaces)
{
    if (topics.empty())
    {
        info_stream << std::endl;
        return;
    }

    auto print_topic_info = [&info_stream](const holo::bag::TopicInformation& ti) -> void {
        info_stream << "Topic: " << ti.topic_metadata.name << " | ";
        info_stream << "Type: " << ti.topic_metadata.type << " | ";
        info_stream << "Count: " << ti.message_count << " | ";
        info_stream << "Serialization Format: " << ti.topic_metadata.serialization_format;
        info_stream << std::endl;
    };

    print_topic_info(topics[0]);
    size_t number_of_topics = topics.size();
    for (size_t j = 1; j < number_of_topics; ++j)
    {
        indent(info_stream, indentation_spaces);
        print_topic_info(topics[j]);
    }
}

void HoloInfo::indent(std::stringstream& info_stream, int number_of_spaces)
{
    info_stream << std::string(number_of_spaces, ' ');
}

}  // namespace holo_cmw
