
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file filesystem.cpp
 * @brief This header file define methods of accessing file
 * @author Zhou Huishuang(zhouhuishuang@holomatic.com)
 * @date 2022-02-15
 */

#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#include <holo/core/exception.h>
#include <holo/os/filesystem.h>

namespace holo
{
namespace os
{
static void list_files(std::string dirpath, bool recursive, std::vector<std::string>& result,
                       std::vector<std::string>& dirs)
{
    DIR*           dir = nullptr;
    struct dirent* ptr = nullptr;

    if ((dir = opendir(dirpath.c_str())) == NULL)
    {
        throw std::runtime_error((std::string("Open directory failed ") + dirpath).c_str());
    }

    while ((ptr = readdir(dir)) != NULL)
    {
        std::string d_name = ptr->d_name;
        if (d_name == "." || d_name == "..")  /// current dir OR parrent dir
            continue;

        std::string current_file = dirpath + "/" + d_name;
        struct stat statbuf;
        if (stat(current_file.c_str(), &statbuf) != 0)
        {
            throw std::runtime_error((std::string("Unable to read file ") + current_file).c_str());
        }

        if (S_ISDIR(statbuf.st_mode))  /// dir
        {
            if (recursive)
            {
                dirs.push_back(current_file);
            }
        }
        else if (S_ISREG(statbuf.st_mode))  /// file
        {
            result.push_back(current_file);
        }
        else
        {
            throw std::runtime_error((std::string("Unsupported file type ") + current_file).c_str());
        }
    }
    closedir(dir);
}

void FileSystem::ListFiles(std::string const& dirpath, bool recursive, std::vector<std::string>& result)
{
    std::vector<std::string> dirs          = {dirpath};
    size_t                   end_condition = 1U;
    size_t                   i             = 0;
    while (i < end_condition)
    {
        list_files(dirs[i], recursive, result, dirs);
        end_condition = dirs.size();
        ++i;
    }
}

bool FileSystem::IsFile(std::string const& path) noexcept
{
    struct stat buf;
    if (lstat(path.c_str(), &buf) < 0)
    {
        return false;
    }
    if (S_ISREG(buf.st_mode))
    {
        return true;
    }
    return false;
}

bool FileSystem::IsDirectory(std::string const& path) noexcept
{
    struct stat buf;
    if (lstat(path.c_str(), &buf) < 0)
    {
        return false;
    }
    if (S_ISDIR(buf.st_mode))
    {
        return true;
    }
    return false;
}

bool FileSystem::IsSymbolLink(std::string const& path) noexcept
{
    struct stat buf;
    if (lstat(path.c_str(), &buf) < 0)
    {
        return false;
    }
    if (S_ISLNK(buf.st_mode))
    {
        return true;
    }
    return false;
}

bool FileSystem::CreateFile(std::string const& path) noexcept
{
    FILE* fp = fopen(path.c_str(), "a+");
    if (fp == NULL)
    {
        return false;
    }
    fclose(fp);
    return true;
}

bool FileSystem::CreateFolder(std::string const& path, uint32_t mode) noexcept
{
    return (mkdir(path.c_str(), mode) != -1);
}

bool FileSystem::RemoveFile(std::string path) noexcept
{
    return (remove(path.c_str()) != -1);
}

bool FileSystem::RemoveFolder(std::string path) noexcept
{
    return (rmdir(path.c_str()) != -1);
}
}  // namespace os
}  // namespace holo
