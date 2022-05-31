/*!
 * @file holo_root.h
 * @brief holo_root utils used to get HOLO_XXX_ROOT directories.
 * @author zhangjiannan(zhangjiannan@holomaitc.com) zhaofx(zhaofuxing@holomaitc.com)
 * @date Jan 21, 2019
 * @attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 *
 */
#include <holo/utils/holo_root.h>

#include <holo/os/predefine.h>

#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <cstdlib>

namespace holo
{
bool IsAbsolutePath(const std::string& path)
{
    if (path == "")
    {
        return false;
    }
    if (path[0] == '/')
    {
        return true;
    }
    return false;
}

std::string GetHoloRootDirectory()
{
    char* p = std::getenv("HOLO_ROOT");
    if (p != nullptr)
    {
        return std::string(p);
    }
    else
    {
        return "/opt/holo";
    }
}

std::string GetHoloConfigRootDirectory()
{
    char* p = std::getenv("HOLO_CONFIG_ROOT");
    if (p != nullptr)
    {
        return std::string(p);
    }
    else
    {
        return GetHoloRootDirectory() + "/config";
    }
}

std::string GetHoloLogRootDirectory()
{
    char* p = std::getenv("HOLO_LOG_ROOT");
    if (p != nullptr)
    {
        return std::string(p);
    }
    else
    {
        return GetHoloRootDirectory() + "/log";
    }
}

std::string GetFileAbsolutePath(const std::string& path, const std::string root)
{
    if (IsAbsolutePath(path))
    {
        return path;
    }
    return root + "/" + path;
}

std::string GetConfigFileAbsolutePath(const std::string& path)
{
    return GetFileAbsolutePath(path, GetHoloConfigRootDirectory());
}

std::string GetLogFileAbsolutePath(const std::string& path)
{
    return GetFileAbsolutePath(path, GetHoloLogRootDirectory());
}
std::string GetParentDirectory(const std::string& path)
{
    std::string parent;
    size_t      idx = path.find_last_of("/");
    if (std::string::npos == idx)
    {
        return "";
    }
    parent = path.substr(0, idx);
    return parent;
}

static bool _mkdirs(const std::string& abs_path)
{
    struct stat statbuf;
    /* Check if abs_path already exists */
    if (stat(abs_path.c_str(), &statbuf) != -1)
    {
        if (S_ISDIR(statbuf.st_mode))
        {
            return true;
        }
    }

    /* abs_path not exists or it is not a directory */
    for (std::string::const_iterator p = abs_path.begin(); p != abs_path.end(); ++p)
    {
        /* iterate from root most path */
        if (*p == '/')
        {
            std::string tmp_path = abs_path.substr(0, p - abs_path.begin() + 1);

            /* tmp_path exists */
            if (stat(tmp_path.c_str(), &statbuf) != -1)
            {
                if (S_ISDIR(statbuf.st_mode))
                {
                    /* tmp_path is a directory */
                    continue;
                }
                else
                {
                    /* Entity is not a directory(file or symbol link) */
                    if (mkdir(tmp_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != -1)
                    {
                        continue;
                    }
                    else
                    {
                        return false; /* Failed to create directory. */
                    }
                }
            }
            else
            {
                if (errno == ENOENT)
                {
                    /* No such entity, create directory. */
                    if (mkdir(tmp_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != -1)
                    {
                        continue;
                    }
                    else
                    {
                        return false; /* Failed to create directory. */
                    }
                }
                else
                {
                    return false; /* Other error. */
                }
            }
        }
    }
    /* Create abs_path directory */
    if (*abs_path.rbegin() != '/') /* In case input parameter ends with "/". eg. /input/path/like/this/ */
    {
        if (mkdir(abs_path.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH) != -1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    return true;
}

bool CreateHoloLogSubdirectory(const std::string& rel_path)
{
    if (IsAbsolutePath(rel_path))
    {
        return false;
    }
    return _mkdirs(GetHoloLogRootDirectory() + "/" + rel_path);
}

std::string GetCurrentExecPath()
{
    char buf[4096 + 256] = {0};
    if (readlink("/proc/self/exe", buf, 4096 + 256) < 0)
    {
        return "";
    }
    return std::string(buf);
}

std::string GetCurrentExecDirectory()
{
    std::string full_path = GetCurrentExecPath();
    full_path             = full_path.substr(0, full_path.find_last_of("/"));
    return full_path;
}

}  // namespace holo
