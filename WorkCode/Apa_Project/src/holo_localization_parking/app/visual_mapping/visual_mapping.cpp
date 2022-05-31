/*!
 * \brief running visual mapping global optimization main pipeline
 * \author Peikai. Guo guopeikai@holomatic.com
 * \date Jul-6-2020
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <glog/logging.h>
#include <holo/localization/vision/vslam/mapping/global_optimizer.h>
#include <stdio.h>

#include <boost/program_options.hpp>

namespace vision = holo::localization::vision;
namespace vslam  = vision::vslam;

///////////////////////////////////////////////////////////////////////////////
int main(int argc, char** argv)
{
    // define config file
    std::string config_file;

    boost::program_options::options_description opts("console options");
    opts.add_options()("help,h", "help message")(
        "c,config_file", boost::program_options::value<std::string>(&config_file)->required()->default_value(""),
        "config file");

    boost::program_options::variables_map vm;
    boost::program_options::store(boost::program_options::parse_command_line(argc, argv, opts), vm);

    if (vm.count("help"))
    {
        LOG(INFO) << opts;
        return 1;
    }

    try
    {
        boost::program_options::notify(vm);
    }
    catch (boost::program_options::error& e)
    {
        LOG(INFO) << e.what() << "/n" << opts;
        return 1;
    }

    LOG(INFO) << "config_file: " << config_file << "\n";

    // load parameters
    LOG(INFO) << "Main --- loading parameters...\n";
    holo::yaml::Node node = holo::yaml::LoadFile(config_file);

    // map database manager parameters
    const auto mdm_node   = node["mdm_params"];
    const auto mdm_params = vslam::MapDatabaseManager::Parameters::LoadFromYaml(mdm_node);

    // global_optimizer_params
    const auto go_node   = node["go_params"];
    const auto go_params = vslam::GlobalOptimizer::Parameters::LoadFromYaml(go_node);

    LOG(INFO) << "Main --- load parameters done.\n";
    LOG(INFO) << mdm_params << "\n";
    LOG_IF(INFO, go_params.verbose) << go_params << "\n";

    // construct map database manager
    vslam::MapDatabaseManager map_database_manager(mdm_params);

    // construct global optimizer
    vslam::GlobalOptimizer optimizer(go_params);

    // run optimization
    LOG(INFO) << "Main --- start global_optimizer.Run ...\n";
    optimizer.Run(map_database_manager);
    LOG(INFO) << "Main --- global optimization done.\n";

    LOG(INFO) << "Main --- All Done.";

    return 0;
}
