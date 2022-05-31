
/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file filesystem.h
 * @brief This header file define methods of accessing file
 * @author Zhou Huishuang(zhouhuishuang@holomatic.com)
 * @date 2022-02-15
 */
#ifndef HOLO_OS_FILESYSTEM_
#define HOLO_OS_FILESYSTEM_

#include <string>
#include <vector>

namespace holo
{
namespace os
{
/**
 * @addtogroup os
 * {
 */

/**
 * @brief This class defines methods of file processing
 */
class FileSystem
{
public:
    /**
     * @brief list files in path
     *
     * @param[in] path Folder path
     * @result[out] result File list
     * @param[in] is_recursion Whether to get files recursively
     *
     * @throw holo::exception::RuntimeErrorException when directory is not exist
     */
    void ListFiles(std::string const& path, bool is_recursion, std::vector<std::string>& result);

    /**
     * @brief check whether is a file
     *
     * @param path file path
     *
     * @return true if path is a file
     * @return false if path isn't a file
     */
    bool IsFile(std::string const& path) noexcept;

    /**
     * @brief check whether is a directory
     *
     * @param path directory path
     *
     * @return true if path is directory
     * @return false if path isn't directory
     */
    bool IsDirectory(std::string const& path) noexcept;

    /**
     * @brief check whether is a symbol link
     *
     * @param path path
     *
     * @return true if path is symbol link
     * @return false if path isn't symbol link
     */
    bool IsSymbolLink(std::string const& path) noexcept;

    /**
     * @brief create file
     *
     * @param path file path
     *
     * @return true if the file create success
     * @return false if the file isn't create success
     */
    bool CreateFile(std::string const& path) noexcept;

    /**
     * @brief create folder
     *
     * @param path folder path
     *
     * @return true if the folder create success
     * @return false if the folder isn't create success
     */
    bool CreateFolder(std::string const& path, uint32_t mode = 0755) noexcept;

    /**
     * @brief remove file
     *
     * @param path file path
     *
     * @return true if the file remove success
     * @return false if the file isn't remove success
     */
    bool RemoveFile(std::string path) noexcept;

    /**
     * @brief remove folder
     *
     * @param path folder path
     *
     * @return true if the folder remove success
     * @return false if the folder isn't remove success
     */
    bool RemoveFolder(std::string path) noexcept;
};
/**
 * @}
 */
}  // namespace os
}  // namespace holo
#endif
