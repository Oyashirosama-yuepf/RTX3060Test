#pragma once
#include <holo/os/tictoc_timer.h>
#include <holo/utils/yaml.h>
#include <time.h>
#include <fstream>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
namespace holo
{
namespace perception
{
struct DebugInfo
{
    struct Timer
    {
        Timer(std::string const& key) : key_(key)
        {
            this->start_time_.Tic();
        }
        ~Timer()
        {
            std::stringstream ss;
            clock_t           end_time = clock();
            ss << key_ << "Spend : " << (double)this->start_time_.Elapsed() << "s; ";
            debug_info_list_.push_back(ss.str());
        }

        std::string key_;
        TicTocTimer start_time_;
    };

    DebugInfo(){};
    ~DebugInfo()
    {
    }
    static void WriteObsNum(std::string const& key, int num)
    {
        std::stringstream ss;
        ss << key << " number is: " << num;
        debug_info_list_.push_back(ss.str());
    }

    static void WriteFrameDelimiter()
    {
        debug_info_list_.push_back("------------------------------");
    }

    static void WriteToTile(std::string const& filename)
    {
        std::ofstream ofs(filename);
        for (auto info : debug_info_list_)
        {
            ofs << info << std::endl;
        }
        // std::ofstream fout;
        // fout.open(filename, std::ios::out | std::ios::app);
        // std::stringstream ss;
        // for (auto info : debug_info_list_)
        // {
        //     ss << info;
        //     fout << ss.str() << std::endl;
        //     ss.clear();
        // }
        // fout.close();
    }

    static std::list<std::string> debug_info_list_;
};

}  // namespace perception
}  // namespace holo
