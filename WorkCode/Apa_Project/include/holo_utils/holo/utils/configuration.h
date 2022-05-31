
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file configuration.h
 * @brief This header file defines method of accessing configuration files
 * @author Zhou Huishuang(zhouhuishuang@holomatic.com)
 * @date 2022-01-20
 */

#ifndef HOLO_CONFIGURATION_CONFIGURATION_H_
#define HOLO_CONFIGURATION_CONFIGURATION_H_

#include <holo/core/exception.h>
#include <holo/log/hololog.h>
#include <holo/os/filesystem.h>
#include <yaml-cpp/yaml.h>
#include <fstream>
#include <mutex>

namespace holo
{
namespace utils
{
/**
 * @addtogroup configuration
 * {
 */

/**
 * @brief This class defines the process methods of configuration file
 */
class Configuration
{
public:
    using FileSystem = holo::os::FileSystem;

    /**
     * @brief load configuration from environment variable
     * @details load from HOLO_CONFIG_ROOT environment variable if HOLO_CONFIG_ROOT exist, else load from
     * HOLO_ROOT/config environment variable
     *
     * @throw holo::exception::RuntimeErrorException when neither HOLO_CONFIG_ROOT nor HOLO_ROOT are set
     */
    static void LoadConfiguration()
    {
        std::call_once(instance_flag_, []()
        {
            std::string              config_path = getConfigPathFromEnv();
            FileSystem               fs;
            std::vector<std::string> file_list;
            fs.ListFiles(config_path, true, file_list);
            for (std::string const& file : file_list)
            {
                loadFileToNode(file);
            }
        });
    }

    /**
     * @brief load configuration
     *
     * @param path config path
     *
     * @throw holo::exception::RuntimeErrorException when path is not exist
     */
    static void LoadConfiguration(std::string const& path)
    {
        std::call_once(instance_flag_, [&]()
        {
            std::string const        absolute_path = getAbsolutePath(path);
            FileSystem               fs;
            std::vector<std::string> file_list;
            if (fs.IsDirectory(absolute_path))
            {
                fs.ListFiles(absolute_path, true, file_list);
            }
            else
            {
                file_list.push_back(absolute_path);
            }

            for (std::string const& file : file_list)
            {
                loadFileToNode(file);
            }
        });
    }

    /**
     * @brief load configuration
     *
     * @param paths config paths
     *
     * @throw holo::exception::RuntimeErrorException when path is not exist
     */
    static void LoadConfiguration(std::vector<std::string> const& paths)
    {
        std::call_once(instance_flag_, [&]()
        {
            FileSystem               fs;
            std::vector<std::string> file_list;
            for (std::string const& path : paths)
            {
                std::string const absolute_path = getAbsolutePath(path);
                if (fs.IsDirectory(absolute_path))
                {
                    fs.ListFiles(absolute_path, true, file_list);
                }
                else
                {
                    file_list.push_back(absolute_path);
                }
            }
            for (std::string const& file : file_list)
            {
                loadFileToNode(file);
            }
        });
    }

    /**
     * @brief get configuration
     *
     * @param config_path node path
     *
     * @return config node
     */
    static YAML::Node const GetConfig(std::string const& config_path)
    {
        return getSubNodeFromConfig(config_path);
    }

    /**
     * @brief get configuration
     *
     * @param config_path node path
     *
     * @return config node
     * @throw YAML::InvalidNode when node cannot be converted to type T
     */
    template <typename T>
    static T GetConfig(std::string const& config_path)
    {
        YAML::Node node = getSubNodeFromConfig(config_path);
        return node.as<T>();
    }

    /**
     * @brief get configuration
     *
     * @param config_path node path
     * @param default_value default value
     *
     * @return node value
     */
    template <typename T>
    static T GetConfig(std::string const& config_path, T const& default_value)
    {
        try
        {
            YAML::Node node = getSubNodeFromConfig(config_path);
            return node.as<T>();
        }
        catch (YAML::Exception const& e)
        {
            YAML::Node node;
            return node.as<T>(default_value);
        }
    }

    /**
     * @brief set configuration
     *
     * @param config_path node path
     * @param value set value
     */
    template <typename T>
    static void SetConfig(std::string const& config_path, T value)
    {
        YAML::Node node;
        YAML::Node sub_node = getSubNodeFromConfig(config_path);

        node = value;
        mergeNode(node, sub_node);
    }

    /**
     * @brief save configuration
     *
     * @param config_path node path
     * @param file_path file path
     */
    static void SaveConfig(std::string const& config_path, std::string const& file_path)
    {
        std::string const absolute_path = getAbsolutePath(file_path);
        FileSystem        fs;
        if (!fs.IsFile(absolute_path))
        {
            fs.CreateFile(absolute_path);
        }

        YAML::Node file_node = YAML::LoadFile(absolute_path);
        YAML::Node sub_node  = createNodeFromConfig(config_path);

        mergeNode(sub_node, file_node);
        if (!file_node["version"] || file_node["version"].as<uint16_t>() < 1)
        {
            file_node["version"] = 1;
        }

        std::ofstream fout(absolute_path);
        fout << file_node;
        fout.close();
    }

    Configuration()                     = default;
    Configuration(Configuration const&) = default;
    Configuration& operator=(Configuration const&) = default;
    Configuration(Configuration&&)                 = default;
    Configuration& operator=(Configuration&&) = default;
    ~Configuration()                          = default;

private:
    /**
     * @brief create node from config
     *
     * @param config_path node path
     *
     * @return new node
     */
    static YAML::Node createNodeFromConfig(std::string const& config_path)
    {
        std::vector<std::string> node_path_list = splitString(config_path, "/");
        YAML::Node               final_node     = getSubNodeFromConfig(config_path);

        return createNode(node_path_list, final_node);
    }
    /**
     * @brief create node
     *
     * @param node_path_list node path list
     * @param final_node value node
     *
     * @return new node
     */
    static YAML::Node createNode(std::vector<std::string> node_path_list, YAML::Node const& final_node)
    {
        YAML::Node node;
        if (node_path_list.size() == 1)
        {
            node[node_path_list[0]] = final_node;
            return node;
        }

        std::string path = node_path_list.front();
        node_path_list.erase(node_path_list.begin());
        node[path] = createNode(node_path_list, final_node);
        return node;
    }

    /**
     * @brief get sub node from config
     *
     * @param config_path node path
     *
     * @return reference to subnode
     */
    static YAML::Node getSubNodeFromConfig(std::string const& config_path)
    {
        YAML::Node*              p              = &config_;
        std::vector<std::string> node_path_list = splitString(config_path, "/");

        for (std::string const& path : node_path_list)
        {
            YAML::Node tmp = (*p)[path];
            p              = &tmp;
        }
        return *p;
    }
    /**
     * @brief load file to node
     *
     * @param path file path
     */
    static void loadFileToNode(std::string const& path)
    {
        YAML::Node node;
        try
        {
            node = YAML::LoadFile(path);
        }
        catch (std::exception const& e)
        {
            std::string msg = "load config file error, file path : " + path;
            throw holo::exception::RuntimeErrorException("load file error");
        }

        if (node["version"] && node["version"].as<uint8_t>() >= 1)
        {
            for (YAML::const_iterator it = node.begin(); it != node.end(); ++it)
            {
                std::string key = it->first.as<std::string>();
                if (config_[key] && key != "version")
                {
                    DLOG(WARNING) << "Conflict node: " << key << "\n"
                                  << key << " node in the " << path << " overwrite the old node";
                    YAML::Node node_ref = config_[key];
                    mergeNode(it->second, node_ref);
                }
                else
                {
                    config_[key] = it->second;
                }
            }
        }
    }

    /**
     * @brief get absolute path
     *
     * @param path path
     * @return absolute path
     */
    static std::string getAbsolutePath(std::string const& path)
    {
        if (startsWith(path, "/"))
        {
            return path;
        }
        return getConfigPathFromEnv() + "/" + path;
    }

    /**
     * @brief starts with
     *
     * @param base_str base string value
     * @param sub_str sub string value

     * @return true if the base_str is starts with sub_str
     * @return false if the base_str isn't starts with sub_str
     **/
    static bool startsWith(std::string const& base_str, std::string const& sub_str)
    {
        return base_str.find(sub_str) == 0 ? true : false;
    }

    /**
     * @brief get config path from environment
     *
     * @return environment variable
     * @throw holo::exception::RuntimeErrorException when neither HOLO_CONFIG_ROOT nor HOLO_ROOT are set
     **/
    static std::string getConfigPathFromEnv()
    {
        char* env = getenv("HOLO_CONFIG_ROOT");
        if (env == nullptr)
        {
            env = getenv("HOLO_ROOT");
            if (env == nullptr)
            {
                throw holo::exception::RuntimeErrorException(
                    "HOLO_CONFIG_ROOT or HOLO_ROOT environment variables are not available");
            }
            else
            {
                return std::string(env) + "/config";
            }
        }
        return env;
    }

    /**
     * @brief Merge two map types of node
     *
     * @param src_node source node
     * @param dest_node destination node
     **/
    static void mergeMap(YAML::Node const& src_node, YAML::Node& dest_node)
    {
        for (YAML::const_iterator it = src_node.begin(); it != src_node.end(); ++it)
        {
            std::string key = it->first.as<std::string>();
            if (dest_node[key])
            {
                if (src_node[key].IsMap() && dest_node[key].IsMap())
                {
                    YAML::Node node_ref = dest_node[key];
                    mergeMap(src_node[key], node_ref);
                }
                else
                {
                    dest_node[key] = src_node[key];
                }
            }
            else
            {
                dest_node[key] = it->second;
            }
        }
    }

    /**
     * @brief Merge two nodes
     *
     * @param src_node source node
     * @param dest_node destination node
     **/
    static void mergeNode(YAML::Node const& src_node, YAML::Node& dest_node)
    {
        if (src_node.IsMap() && dest_node.IsMap())
        {
            mergeMap(src_node, dest_node);
        }
        else
        {
            dest_node = src_node;
        }
    }

    /**
     * @brief split string
     *
     * @param in input string
     * @param delimiters delimiters

     * @return substring list
     */
    static std::vector<std::string> splitString(std::string const& in, std::string const& delimiters) noexcept
    {
        std::vector<std::string> result_list;
        if (in == "")
            return result_list;
        std::string strs = in + delimiters;
        size_t      pos  = strs.find(delimiters);

        while (pos != strs.npos)
        {
            result_list.push_back(strs.substr(0, pos));
            strs = strs.substr(pos + 1, strs.size());
            pos  = strs.find(delimiters);
        }
        return result_list;
    }

    static std::once_flag instance_flag_;  ///< singleton pattern
    static YAML::Node     config_;         ///< config node
};
/**
 * @}
 */
}  // namespace utils
}  // namespace holo
#endif
