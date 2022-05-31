/**
 * @file holobag.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief the app main
 * @version 0.1
 * @date 2020-05-12
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#include <glog/logging.h>
#include <holo/utils/holo_root.h>
#include <holo_export.h>
#include <holo_filter.h>
#include <holo_info.h>
#include <holo_record.h>
#include <holo_replay.h>

#include <cmw_wrapper/utils/cxxopts.hpp>

void print_usage(void);

int main(int argc, char** argv)
{
    if (argc <= 1)
    {
        print_usage();
        return 0;
    }

    if (std::string(argv[1]) == "play")
    {
        cxxopts::Options options(argv[1], "holobag play");
        options.add_options()
            ("h,help", "show this message")
            ("v,verbose", "if also outputs glog to console")
            ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("HoloReplay"))
            ("m,min_log_level", "minimum log level, INFO(2), WARNING(3), ERROR(4), FATAL(5)， OFF(6)",cxxopts::value<holo::uint8_t>()->default_value("3"))
            ("i,input_file", "input file name", cxxopts::value<std::string>()->default_value(""))
            ("s,skip_time", "skip some time when start play", cxxopts::value<holo::float64_t>()->default_value("0.0"))
            ("d,duration", "set the time to end play", cxxopts::value<holo::float64_t>()->default_value("0.0"))
            ("r,rate", "the rate when play the input bag", cxxopts::value<holo::float32_t>()->default_value("1.0"))
            ("t,topic_names","the unique topic names you input.",cxxopts::value<std::vector<std::string>>()->default_value(""))
            ("accept", "the topic you want to play flag")
            ("domain_id", "set the domain id, this option must be set", cxxopts::value<holo::uint64_t>()->default_value("0"))
            ("decode", "  set the flag to decode the image in bag")
            ("encode_type", "set image encode type to encoder", cxxopts::value<std::string>()->default_value("RGB"))
            ("image_type", "set image type to encoder", cxxopts::value<std::string>()->default_value("H264"));

        options.parse(argc, argv);

        if (options.count("help"))
        {
            std::cout << options.help();
            return 0;
        }
        if (!options.count("domain_id"))
        {
            std::cout << "No domain id input, holobag terminate, more information please input --help!" << std::endl;
            return -1;
        }

        holo::CreateHoloLogSubdirectory("holobag");
        std::string log_file_base = holo::GetLogFileAbsolutePath("holobag/" + std::string(argv[1]));
        holo::log::HoloLogger::Initialize();
        ::holo::log::TimeBasedRollingFileConfigure log_file("file_output_device1", log_file_base + ".log");
        log_file.SetFilenamePattern(log_file_base + ".%d-%H-%M-%S.%q" + ".log");
        log_file.SetMaxHistory(50);
        ::holo::log::HoloLogger::Add(log_file);
        ::holo::uint32_t                 min_log_level = options["min_log_level"].as<holo::uint8_t>() * 10000;
        ::holo::log::log4cplus::LogLevel log_level     = ::holo::log::log4cplus::LogLevel(min_log_level);
        ::holo::log::HoloLogger::SetLogLevel(log_level);

        holo_cmw::HoloReplay replay(argc, argv, options["node_name"].as<std::string>(),
                                    options["domain_id"].as<holo::uint64_t>(), bool(options.count("decode") > 0), 
                                    options["encode_type"].as<std::string>(), options["image_type"].as<std::string>());
        if (replay.SetUp(options["input_file"].as<std::string>()))
        {
            replay.SetUserOptions(options["skip_time"].as<holo::float64_t>(), options["duration"].as<holo::float64_t>(),
                                  options["rate"].as<holo::float32_t>(), options.count("accept"));
            if (options.count("topic_names"))
            {
                replay.SetIgnoredTopics(options["topic_names"].as<std::vector<std::string>>(),
                                        options.count("topic_names"));
            }
            replay.Play();
        }

        ::holo::log::HoloLogger::Shutdown();
        return 0;
    }
    if (std::string(argv[1]) == "record")
    {
        cxxopts::Options options(argv[1], "holobag record");
        options.add_options()
            ("h,help", "show this message")
            ("v,verbose", "if also outputs glog to console")
            ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("HoloRecord"))
            ("m,min_log_level", "minimum log level, INFO(2), WARNING(3), ERROR(4), FATAL(5)， OFF(6)",cxxopts::value<holo::uint8_t>()->default_value("3"))
            ("O,output_name", "output name", cxxopts::value<std::string>()->default_value(""))
            ("domain_id", "set the domain id, this option must be set", cxxopts::value<holo::uint64_t>()->default_value("0"))
            ("encode", "choose to encode the image from the ipc with the extracting frame frequency",cxxopts::value<holo::uint16_t>()->default_value("3"))
            ("split_size", "split holobag by size, unit: GB", cxxopts::value<holo::uint64_t>()->default_value("0"))
            ("split_time", "split holobag by time, unit: seconds", cxxopts::value<holo::uint64_t>()->default_value("0"))
            ("encode_type", "set image encode type to encoder", cxxopts::value<std::string>()->default_value("RGB"))
            ("image_type", "set image type to encoder", cxxopts::value<std::string>()->default_value("H264"));

        options.parse(argc, argv);

        if (options.count("help"))
        {
            std::cout << options.help();
            return 0;
        }
        if (!options.count("domain_id"))
        {
            std::cout << "No domain id input, holobag terminate, more information please input --help!" << std::endl;
            return -1;
        }

        holo::CreateHoloLogSubdirectory("holobag");
        std::string log_file_base = holo::GetLogFileAbsolutePath("holobag/" + std::string(argv[1]));
        holo::log::HoloLogger::Initialize();
        ::holo::log::TimeBasedRollingFileConfigure log_file("file_output_device1", log_file_base + ".log");
        log_file.SetFilenamePattern(log_file_base + ".%d-%H-%M-%S.%q" + ".log");
        log_file.SetMaxHistory(50);
        ::holo::log::HoloLogger::Add(log_file);
        ::holo::uint32_t                 min_log_level = options["min_log_level"].as<holo::uint8_t>() * 10000;
        ::holo::log::log4cplus::LogLevel log_level     = ::holo::log::log4cplus::LogLevel(min_log_level);
        ::holo::log::HoloLogger::SetLogLevel(log_level);

        holo_cmw::HoloRecord record(argc, argv, options["node_name"].as<std::string>(),
                                    options["domain_id"].as<holo::uint64_t>(), bool(options.count("encode") > 0),
                                    options["encode"].as<holo::uint16_t>(), options["encode_type"].as<std::string>(),
                                    options["image_type"].as<std::string>());
        if (record.SetUp(options["split_size"].as<holo::uint64_t>(), options["split_time"].as<holo::uint64_t>(), options["output_name"].as<std::string>()))
        {
            record.Record();
        }

        ::holo::log::HoloLogger::Shutdown();
        return 0;
    }
    else if (std::string(argv[1]) == "info")
    {
        cxxopts::Options options(argv[1], "holobag info");
        options.add_options()
            ("h,help", "show this message")
            ("v,verbose", "if also outputs glog to console")
            ("m,min_log_level", "minimum log level, INFO(2), WARNING(3), ERROR(4), FATAL(5)， OFF(6)",cxxopts::value<holo::uint8_t>()->default_value("3"))
            ("d,details","if also show the details info, such as version data.");
        options.parse(argc, argv);

        if (options.count("help"))
        {
            std::cout << options.help();
            return 0;
        }
        if (std::string(argv[2]).empty())
        {
            std::cout << "The file name should not be empty!";
            return 0;
        }

        holo::CreateHoloLogSubdirectory("holobag");
        std::string log_file_base = holo::GetLogFileAbsolutePath("holobag/" + std::string(argv[1]));
        holo::log::HoloLogger::Initialize();
        ::holo::log::TimeBasedRollingFileConfigure log_file("file_output_device1", log_file_base + ".log");
        log_file.SetFilenamePattern(log_file_base + ".%d-%H-%M-%S.%q" + ".log");
        log_file.SetMaxHistory(50);
        ::holo::log::HoloLogger::Add(log_file);
        ::holo::uint32_t                 min_log_level = options["min_log_level"].as<holo::uint8_t>() * 10000;
        ::holo::log::log4cplus::LogLevel log_level     = ::holo::log::log4cplus::LogLevel(min_log_level);
        ::holo::log::HoloLogger::SetLogLevel(log_level);

        holo_cmw::HoloInfo info;
        info.Info(std::string(argv[2]), bool(options.count("details") > 0));

        ::holo::log::HoloLogger::Shutdown();
        return 0;
    }
    else if (std::string(argv[1]) == "filter")
    {
        cxxopts::Options options(argv[1], "holobag filter");
        options.add_options()
            ("h,help", "show this message")
            ("v,verbose", "if also outputs glog to console")
            ("m,min_log_level", "minimum log level, INFO(2), WARNING(3), ERROR(4), FATAL(5)， OFF(6)",cxxopts::value<holo::uint8_t>()->default_value("3"))
            ("i,input_file","the input holobag name to be filterd",cxxopts::value<std::string>()->default_value(""))
            ("o,output_file","the output holobag name",cxxopts::value<std::string>()->default_value(""))
            ("s,start_time","the (relative) start time (in seconds). ",cxxopts::value<holo::float64_t>()->default_value("0.0"))
            ("e,end_time","the (relative) end time. -1 means the end of bag time",cxxopts::value<holo::float64_t>()->default_value("-1.0"))
            ("t,topic_names","the topic names you want to filter.",cxxopts::value<std::vector<std::string>>()->default_value(""));
        options.parse(argc, argv);
        if (options.count("help"))
        {
            std::cout << options.help();
            return 0;
        }

        holo::CreateHoloLogSubdirectory("holobag");
        std::string log_file_base = holo::GetLogFileAbsolutePath("holobag/" + std::string(argv[1]));
        holo::log::HoloLogger::Initialize();
        ::holo::log::TimeBasedRollingFileConfigure log_file("file_output_device1", log_file_base + ".log");
        log_file.SetFilenamePattern(log_file_base + ".%d-%H-%M-%S.%q" + ".log");
        log_file.SetMaxHistory(50);
        ::holo::log::HoloLogger::Add(log_file);
        ::holo::uint32_t                 min_log_level = options["min_log_level"].as<holo::uint8_t>() * 10000;
        ::holo::log::log4cplus::LogLevel log_level     = ::holo::log::log4cplus::LogLevel(min_log_level);
        ::holo::log::HoloLogger::SetLogLevel(log_level);

        holo_cmw::HoloFilter filter;
        filter.Filter(options["input_file"].as<std::string>(), options["output_file"].as<std::string>(),
                      options["start_time"].as<holo::float64_t>(), options["end_time"].as<holo::float64_t>(),
                      options["topic_names"].as<std::vector<std::string>>());

        ::holo::log::HoloLogger::Shutdown();
        return 0;
    }
    else if (std::string(argv[1]) == "export")
    {
        cxxopts::Options options(argv[1], "holobag export");
        options.add_options()
            ("h,help", "show this message")
            ("v,verbose", "if also outputs glog to console")
            ("m,min_log_level", "minimum log level, INFO(2), WARNING(3), ERROR(4), FATAL(5)， OFF(6)",cxxopts::value<holo::uint8_t>()->default_value("3"))
            ("i,input_file","the input holobag name to be filterd",cxxopts::value<std::string>()->default_value(""))
            ("p,params_export","export params from bag")
            ("e,export_path","the params path to save them.",cxxopts::value<std::string>()->default_value(""));
        options.parse(argc, argv);
        if (options.count("help"))
        {
            std::cout << options.help();
            return 0;
        }

        holo::CreateHoloLogSubdirectory("holobag");
        std::string log_file_base = holo::GetLogFileAbsolutePath("holobag/" + std::string(argv[1]));
        holo::log::HoloLogger::Initialize();
        ::holo::log::TimeBasedRollingFileConfigure log_file("file_output_device1", log_file_base + ".log");
        log_file.SetFilenamePattern(log_file_base + ".%d-%H-%M-%S.%q" + ".log");
        log_file.SetMaxHistory(50);
        ::holo::log::HoloLogger::Add(log_file);
        ::holo::uint32_t                 min_log_level = options["min_log_level"].as<holo::uint8_t>() * 10000;
        ::holo::log::log4cplus::LogLevel log_level     = ::holo::log::log4cplus::LogLevel(min_log_level);
        ::holo::log::HoloLogger::SetLogLevel(log_level);

        holo_cmw::HoloExport expo;
        if (options.count("params_export") > 0)
        {
            expo.ExportParam(options["input_file"].as<std::string>(), options["export_path"].as<std::string>());
        }
        ::holo::log::HoloLogger::Shutdown();
        return 0;
    }
    return -1;
}

void print_usage(void)
{
    printf("usage:\n");
    printf("\tholobag play    -- play the given holobag file .\n");
    printf("\tholobag record  -- record messsages to holobag file.\n");
    printf("\tholobag info    -- print the information of holobag file.\n");
    printf("\tholobag filter  -- filter given topics data from source holobag file and save to the destionation "
           "holobag.\n");
    printf("\tholobag export  -- export params from given holobag file.\n");
}
