/*!
 * \brief running visual mapping global optimization main pipeline
 * \author Peikai. Guo guopeikai@holomatic.com
 * \date Jul-6-2020
 * \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * \attention Please refer to COPYRIGHT.txt for complete terms of copyright
 * notice.
 */

#include <stdio.h>

#include <glog/logging.h>
#include <boost/program_options.hpp>

#include <holo/localization/vision/vslam/mapping/avp_mapping.h>

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
    const auto avp_params = vslam::AvpMapping::Parameters::LoadFromYaml(node);

    LOG(INFO) << "Main --- load parameters done.\n";
    LOG(INFO) << avp_params << "\n";

    // construct avp mapping
    vslam::AvpMapping avp_mapping(avp_params);

    // run optimization
    LOG(INFO) << "Main --- start avp mapping. Run ...\n";
    avp_mapping.run();
    LOG(INFO) << "Main --- avp mapping done.\n";

    LOG(INFO) << "Main --- All Done.";

    return 0;
}
