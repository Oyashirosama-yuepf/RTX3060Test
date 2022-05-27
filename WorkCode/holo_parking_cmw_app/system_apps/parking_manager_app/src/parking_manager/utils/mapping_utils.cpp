/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file mapping_utils.cpp
 * @brief This cpp file defines some utils functions of mapping function
 * @author yangzhongtao(yangzhongtao@holomaitc.com)
 * @date 2021/05/15
 */

#include <glog/logging.h>

#include <parking_manager/parking_manager.h>

namespace holo
{
namespace parking_cmw_app
{
namespace parking_manager
{

std::string GetStrFromTerminal(const std::string& command)
{
    std::string result;
    FILE*       fp;
    if ((fp = popen(command.c_str(), "r")) == NULL)
    {
        result = "";
    }
    else
    {
        char buffer[1024];
        while (fgets(buffer, 1024, fp) != NULL)
        {
            result += buffer;
        }

        if (pclose(fp) == -1)
        {
            result = "";
        }
    }

    return result;
}

void RestartVSLAM(const uint32_t& input_id)
{
    // Kill VSLAM
    std::string     pid_cmd = "ps -ef | grep -v grep | grep  vslam_cmw";
    std::string     pid_str;
    static uint32_t progress_count = 2;
    do
    {
        pid_str = GetStrFromTerminal(pid_cmd);
        if (!pid_str.empty())
        {
            std::vector<std::string> spilt_vec;
            boost::split(spilt_vec, pid_str, boost::is_any_of(" "), boost::token_compress_on);
            std::string pid      = spilt_vec.at(1);
            std::string kill_cmd = "kill -s 9 " + pid;
            std::string kill_str = GetStrFromTerminal(kill_cmd);
            if (kill_str.size() > 0)
            {
                LOG(ERROR) << "Could not kill the vslam app ";
            }
            LOG(ERROR) << "kill the vslam app ";
        }
        progress_count--;
    } while (progress_count);
    progress_count = 2;

    // Change Route
    std::string yaml_path = GetHoloConfigRootDirectory() + "/holo_localization_parking/app_config/vslam/visual_localization_hpp.yaml";
    std::string get_route_id_cmd =
        "cat " + yaml_path + " | grep -oE 'route_.*/' | awk -F '/' '{print $1}' | head -n1 | awk -F '_' '{print $2}'";
    // LOG(ERROR)<<"get ROUTE ID= "<<get_route_id_cmd;
    std::string route_id = GetStrFromTerminal(get_route_id_cmd);
    // LOG(ERROR)<<"ROUTE ID= "<<route_id;
    if (!route_id.empty())
    {
        std::string change_id_cmd = "sed -i 's/route_" + std::to_string(std::stoi(route_id)) + "/route_" +
                                    std::to_string(input_id) + "/g' " + yaml_path;
        std::string change_id = GetStrFromTerminal(change_id_cmd);
        LOG(ERROR) << "Change ID cmd = " << change_id_cmd;
    }

    // Restart VSLAM
    std::string bin_str = GetHoloRootDirectory() + "/bin/ros/vslam_cmw  ";
    std::string config_str =
        GetHoloRootDirectory() + "/config/holo_localization_parking/app_config/vslam/visual_localization_hpp.yaml -l 0 -m 0";
    std::string run = bin_str + " -c " + config_str;
    LOG(ERROR) << run;
    if (popen(run.c_str(), "r") == NULL)
    {
        LOG(ERROR) << "Could not run the vslam app ";
    }
    LOG(ERROR) << "run the vslam app ";
    //std::this_thread::sleep_for(std::chrono::seconds(5));
}

void StartMapping(const uint32_t& path_learning_id)
{
    std::string     pid_cmd = "ps -ef | grep -v grep | grep  vslam_cmw";
    std::string     pid_str;
    static uint32_t progress_count = 2;
    do
    {
        pid_str = GetStrFromTerminal(pid_cmd);
        if (!pid_str.empty())
        {
            std::vector<std::string> spilt_vec;
            boost::split(spilt_vec, pid_str, boost::is_any_of(" "), boost::token_compress_on);
            std::string pid      = spilt_vec.at(1);
            std::string kill_cmd = "kill -s 9 " + pid;
            std::string kill_str = GetStrFromTerminal(kill_cmd);
            if (kill_str.size() > 0)
            {
                LOG(ERROR) << "Could not kill the vslam app ";
            }
            LOG(ERROR) << "kill the vslam app ";
        }
        progress_count--;
    } while (progress_count);
    progress_count = 2;
    LOG(ERROR) << "success kill localization app";

    // Change Route
    // std::string yaml_path = GetHoloConfigRootDirectory() + "/holo_localization_parking/app_config/vslam//visual_mapping_hpp.yaml";
    // std::string get_route_id_cmd =
    //     "cat " + yaml_path + " | grep -oE 'route_.*' | awk -F ' ' '{print $1}' | head -n1 | awk -F '_' '{print $2}'";
    // // LOG(ERROR)<<"get ROUTE ID= "<<get_route_id_cmd;
    // std::string route_id = GetStrFromTerminal(get_route_id_cmd);
    // // LOG(ERROR)<<"ROUTE ID= "<<route_id;
    // if (!route_id.empty())
    // {
    //     std::string change_id_cmd = "sed -i 's/route_" + std::to_string(std::stoi(route_id)) + "/route_" +
    //                                 std::to_string(input_id) + "/g' " + yaml_path;
    //     std::string change_id = GetStrFromTerminal(change_id_cmd);
    //     LOG(ERROR) << "Change mapping online ID cmd = " << change_id_cmd;
    // }
    std::string cmd = "bash " + GetHoloParkingLibConfigDirectory() + "online_mapping.sh"; // bash
    cmd = cmd + " " + std::to_string(path_learning_id);
    LOG(ERROR) << "stop mapping command: " << cmd;
    std::string result = GetStrFromTerminal(cmd);

    std::string bin_str = GetHoloRootDirectory() + "/bin/ros/vslam_cmw -l 0 -m 0";
    std::string config_str =
        GetHoloRootDirectory() + "/config/holo_localization_parking/app_config/vslam/visual_mapping_hpp.yaml";
    std::string run = bin_str + " -c " + config_str;
    LOG(ERROR) << run;
    if (popen(run.c_str(), "r") == NULL)
    {
        LOG(ERROR) << "Could not run the vslam app ";
    }
    LOG(ERROR) << "success start mapping collect app";
    //std::this_thread::sleep_for(std::chrono::seconds(8));
}

std::string StopMapping(const uint32_t& input_id)
{
    std::string cmd = "bash " + GetHoloParkingLibConfigDirectory() + "mappping_offline.sh"; // bash
    cmd = cmd + " " + std::to_string(input_id);
    LOG(ERROR) << "stop mapping command: " << cmd;
    std::string result = GetStrFromTerminal(cmd);
    LOG(ERROR) << "stop mapping result: " << result;
    return result;
}

}  // namespace parking_manager
}  // namespace parking_cmw_app
}  // namespace holo
