/*!
 * @file holo_root.h
 * @brief holo_root utils used to get HOLO_XXX_ROOT directories.
 * @author zhangjiannan(zhangjiannan@holomaitc.com) zhaofx(zhaofuxing@holomatic.com)
 * @date Jan 21, 2019
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 *
 */

#ifndef HOLO_UTILS_HOLO_ROOT_H_
#define HOLO_UTILS_HOLO_ROOT_H_

#include <string>

namespace holo
{

/**
 * @brief Check if a string is an absolute path.
 *
 * @param path path
 *
 * @return true if path is an absolute path, otherwise false.
 */
bool IsAbsolutePath(const std::string& path);

/**
 * @brief Get holo_root directory.
 *
 * @details If HOLO_ROOT environment variable is set, holo_root will be set to $HOLO_ROOT. Otherwise holo_root will be set to default "/opt/holo"
 *
 * @return holo_root path
 */
std::string GetHoloRootDirectory();

/**
 * @brief Get holo_config_root directory.
 *
 * @details If HOLO_CONFIG_ROOT environment variable is set, holo_config_root will be set to $HOLO_CONFIG_ROOT. Otherwise holo_config_root will be set to default "$HOLO_ROOT/config"
 *
 * @return holo_config_root path
 */
std::string GetHoloConfigRootDirectory();

/**
 * @brief Get holo_log_root directory.
 *
 * @details If HOLO_LOG_ROOT environment variable is set, holo_log_root will be set to $HOLO_LOG_ROOT. Otherwise holo_log_root will be set to default "$HOLO_ROOT/log"
 *
 * @return holo_log_root path
 */
std::string GetHoloLogRootDirectory();


/**
 * @brief Get absolute path from relative path and root path.
 *
 * @param path relative path to file.
 * @param root root of reletive path.
 *
 * @return if path is an absolute path, return path. Otherwise return root + path.
 */
std::string GetFileAbsolutePath(const std::string& path, const std::string root = "");

/**
 * @brief Get absolute path of a holo config file.
 *
 * @param path relative path to config file.
 *
 * @return If path is an absolute path, return path. Otherwise return $HOLO_CONFIG_ROOT/path.
 */
std::string GetConfigFileAbsolutePath(const std::string& path);

/**
 * @brief Get absolute path of a holo log file.
 *
 * @param path relative path to log file.
 *
 * @return If path is an absolute path, return path. Otherwise return $HOLO_LOG_ROOT/path.
 */
std::string GetLogFileAbsolutePath(const std::string& path);

/**
 * @brief Get parent directory name of a path
 *
 * @param path path
 *
 * @return parent directory
 */
std::string GetParentDirectory(const std::string& path);

/**
 * @brief Create log subdirectory relative to holo_log_root.
 *
 * @param rel_path relative path to holo_log_root.
 *
 * @return true if create directory successfully. otherwise false.
 */
bool CreateHoloLogSubdirectory(const std::string& rel_path);

/**
 * @brief Get current executable file path.
 *
 * @return absolute path to current executable.
 */
std::string GetCurrentExecPath();

/**
 * @brief Get current executable file direcotry.
 *
 * @return absolute directory to current executable.
 */
std::string GetCurrentExecDirectory();

}

#endif
