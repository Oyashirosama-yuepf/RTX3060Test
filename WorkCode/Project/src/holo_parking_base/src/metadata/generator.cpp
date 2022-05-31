#include <holo/parking/vision/point_feature.h>
#include <holo/parking/vision/point_feature_list.h>

#include <holo/metadata/type_description.h>
#include <holo/parking/metadata/vision/point_feature_list_type_description.h>
#include <holo/parking/metadata/vision/point_feature_type_description.h>

#include <sys/stat.h>
#include <fstream>
#include <map>

static std::string version = "v0_0";

using ScalarType = holo::float32_t;

static std::map<std::string, holo::metadata::TypeDescription::PtrType> td_map = {
    {version + "/vision/PointFeatureT",
     holo::metadata::TypeDescriptionResolver<holo::parking::vision::PointFeatureT<ScalarType>>::Get()},
    {version + "/vision/PointFeaturePtrListT",
     holo::metadata::TypeDescriptionResolver<
         holo::parking::vision::PointFeaturePtrListT<holo::parking::vision::PointFeatureT<ScalarType>>>::Get()},
};

int createDirectory(std::string const& relpath)
{
    size_t end = 0;
    while (end != std::string::npos)
    {
        end     = relpath.find_first_of("/", end + 1);
        int ret = mkdir(relpath.substr(0, end).c_str(), 0755);
        if (ret != 0)
        {
            if (errno != EEXIST)
            {
                return -1;
            }
            else
            {
                struct stat s;
                if (stat(relpath.substr(0, end).c_str(), &s) == 0)
                {
                    if (s.st_mode & S_IFDIR)
                    {
                        continue;
                    }
                    else
                    {
                        return -2;
                    }
                }
                else
                {
                    return -3;
                }
            }
        }
    }
    return 0;
}

int main()
{
    for (auto const& value : td_map)
    {
        std::string relpath = "metadata/" + value.first + ".yaml";
        if (relpath.find_last_of("/") != std::string::npos)
        {
            if (createDirectory(relpath.substr(0, relpath.find_last_of("/"))) != 0)
            {
                continue;
            }
        }
        std::ofstream of;
        of.open(relpath);
        of << value.second->ToYaml() << std::endl;
        of.close();
    }
    return 0;
}
