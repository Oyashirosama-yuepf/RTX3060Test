/**
 * @file main.cpp
 * @author housixiu (housiixu1@holomatic.com)
 * @brief holobag_gui start file
 * @version 0.1
 * @date 2020-12-22
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */
#include <QApplication>
#include <iostream>
#include <glog/logging.h>
#include <holo_cmw/utils/cxxopts.hpp>
#include <include/widget.h>
#include <include/control_play.h>
#include <include/signal_and_slot.h>
#include <include/holo_replay.h>

int main(int argc, char *argv[])
{
    cxxopts::Options options(argv[0], "holobag gui");
    options.add_options()
        ("h,help", "show this message")
        ("c,config_file", "configuration file path", cxxopts::value<std::string>()->default_value(""))
        ("v,verbose", "if also outputs glog to console")
        ("n,node_name", "node name for this app", cxxopts::value<std::string>()->default_value("HoloReplay"))
        ("m,min_log_level", "minimum log level, INFO(0), WARNING(1), ERROR(2), FATAL(3)",cxxopts::value<holo::uint8_t>()->default_value("2"))
        ;
    options.parse(argc, argv);

    if ( options.count("help") )
    {
        std::cout << options.help();
        return 0;
    }

    holo::CreateHoloLogSubdirectory("holobag");
    std::string log_file = holo::GetLogFileAbsolutePath("holobag/" + std::string(argv[0]) + ".log");
    google::InitGoogleLogging(argv[0]);
    google::SetLogDestination(google::FATAL, "");
    google::SetLogDestination(google::ERROR, "");
    google::SetLogDestination(google::WARNING, "");
    google::SetLogDestination(google::INFO, log_file.c_str());
    FLAGS_alsologtostderr = bool(options.count("verbose") > 0);
    FLAGS_minloglevel     = options["min_log_level"].as<holo::uint8_t>();

    QApplication a(argc, argv);
    Widget w;
    w.show();

    ControlPlay* replay = ControlPlay::Instance();
    replay->play_data_.node_name_ = options["node_name"].as<std::string>();
    replay->play_data_.argc = argc;
    replay->play_data_.argv = argv;

    return a.exec();
}
