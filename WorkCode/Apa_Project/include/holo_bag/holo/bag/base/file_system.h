
/**
 * @file file_system.hpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief this file define the base file system api
 * @version 0.1
 * @date 2020-04-27
 *
 * @copyright Copyright © Holomatic Technology (Beijing) Co.Ltd  Please refer to COPYRIGHT.txt for complete terms of
 * copyright notice.
 *
 */

#ifndef _HOLOBAG_BASE_FILESYSTEM_HPP_
#define _HOLOBAG_BASE_FILESYSTEM_HPP_

#include <sys/stat.h>

#include <algorithm>
#include <sstream>
#include <string>
#include <vector>

#include <sys/types.h>
#include <unistd.h>

#define OS_DIRSEP '/'

namespace holo
{
namespace bag
{
namespace fs
{
/// Split a specified input into tokens using a delimiter and a type erased insert iterator.
/**
 * @brief The returned vector will contain the tokens split from the input
 *
 * @param[in] input the input string to be split
 * @param[in] delim the delimiter used to split the input string
 * @param[in] insert iterator pointing to a storage container
 */
template <
    class InsertIterator,
    typename std::enable_if<std::is_same<InsertIterator&, decltype(std::declval<InsertIterator>().operator=(
                                                              std::declval<std::string>()))>::value>::type* = nullptr>
void Split(const std::string& input, char delim, InsertIterator& it, bool skip_empty = false)
{
    std::stringstream ss;
    ss.str(input);
    std::string item;
    while (std::getline(ss, item, delim))
    {
        if (skip_empty && item == "")
        {
            continue;
        }
        it = item;
    }
}

/// Split a specified input into tokens using a delimiter.
/**
 * @brief The returned vector will contain the tokens split from the input
 *
 * @param[in] input the input string to be split
 * @param[in] delim the delimiter used to split the input string
 * @return std::vector<std::string>， A vector of tokens.
 */
inline std::vector<std::string> Split(const std::string& input, char delim, bool skip_empty = false)
{
    std::vector<std::string> result;
    auto                     it = std::back_inserter(result);
    Split(input, delim, it, skip_empty);
    return result;
}

static constexpr char const K_PREFERRED_SEPARATOR = OS_DIRSEP;

class path
{
public:
    /**
     * @brief Constructs an empty path.
     */
    path() : path("")
    {
    }

    /**
     * @brief Conversion constructor from a std::string path.
     *
     * @param p A string path split by the platform's string path separator.
     */
    path(const std::string& p)  // NOLINT(runtime/explicit): this is a conversion constructor
      : path_(p), path_as_vector_(Split(p, K_PREFERRED_SEPARATOR))
    {
        std::replace(path_.begin(), path_.end(), '\\', K_PREFERRED_SEPARATOR);
        std::replace(path_.begin(), path_.end(), '/', K_PREFERRED_SEPARATOR);
    }

    /**
     * @brief Copy constructor.
     */
    path(const path& p) = default;

    /**
     * @brief Get the path delimited using this system's path separator.
     *
     * @return std::string, The path as a string
     */
    std::string GetPath() const
    {
        return path_;
    }

    /**
     * @brief Check if this path exists.
     *
     * @return bool, True if the path exists, false otherwise.
     */
    bool Exists() const
    {
        return access(path_.c_str(), 0) == 0;
    }

    /**
     * @brief Check if the path exists and it is a directory.
     *
     * @return bool, True if the path is an existing directory, false otherwise.
     */
    bool IsDirectory() const noexcept
    {
        struct stat stat_buffer;
        auto const rc = stat(path_.c_str(), &stat_buffer);

        if (rc != 0)
        {
            return false;
        }

        return S_ISDIR(stat_buffer.st_mode);
    }

    /**
     * @brief Check if the path is a regular file.
     *
     * @return bool, True if the file is an existing regular file, false otherwise.
     */
    bool IsRegularFile() const noexcept
    {
        struct stat stat_buffer;
        auto const rc = stat(path_.c_str(), &stat_buffer);

        if (rc != 0)
        {
            return false;
        }

        return S_ISREG(stat_buffer.st_mode);
    }

    /**
     * @brief Return the size of the file in bytes.
     *
     * @return uint64_t, size of file in bytes
     * 
     * @throw std::system_error
     */
    uint64_t FileSize() const
    {
        if (IsDirectory())
        {
            auto ec = std::make_error_code(std::errc::is_a_directory);
            throw std::system_error{ec, "cannot get file size"};
        }

        struct stat stat_buffer;
        auto const rc = stat(path_.c_str(), &stat_buffer);

        if (rc != 0)
        {
            std::error_code ec{errno, std::system_category()};
            errno = 0;
            throw std::system_error{ec, "cannot get file size"};
        }
        else
        {
            return static_cast<uint64_t>(stat_buffer.st_size);
        }
    }

    /**
     * @brief Check if the path is empty.
     *
     * @return bool, True if the path is empty, false otherwise.
     */
    bool Empty() const
    {
        return path_.empty();
    }

    /**
     * @brief Check if the path is an absolute path.
     *
     * @return bool, True if the path is absolute, false otherwise.
     */
    bool IsAbsolute() const
    {
        return path_.compare(0, 1, "/") == 0 || path_.compare(1, 2, ":\\") == 0;
    }

    /**
     * @brief Const iterator to first element of this path.
     *
     * @return std::vector<std::string>, A const iterator to the first element.
     */
    std::vector<std::string>::const_iterator CBegin() const
    {
        return path_as_vector_.cbegin();
    }

    /**
     * @brief Const iterator to one past the last element of this path.
     *
     * @return std::vector<std::string>, A const iterator to one past the last element of the path.
     */
    std::vector<std::string>::const_iterator CEnd() const
    {
        return path_as_vector_.cend();
    }

    /**
     * @brief Get the parent directory of this path.
     *
     * @return path, A path to the parent directory.
     */
    path ParentPath() const
    {
        path parent;
        for (auto it = this->CBegin(); it != --this->CEnd(); ++it)
        {
            if (!parent.Empty() || it->empty())
            {
                parent /= *it;
            }
            else
            {
                parent = *it;
            }
        }
        return parent;
    }

    /**
     * @brief Get the last element in this path.
     *
     * @attention If this path points to a directory, it will return the directory name.
     *
     * @return path, The last element in this path
     */
    path FileName() const
    {
        return path_.empty() ? path() : *--this->CEnd();
    }

    /**
     * @brief Get a relative path to the component including and following the last '.'.
     *
     * @return path, The string extension
     */
    path Extension() const
    {
        const char*  delimiter   = ".";
        auto        split_fname = Split(this->GetPath(), *delimiter);
        return split_fname.size() == 1 ? path("") : path("." + split_fname.back());
    }

    /**
     * @brief Concatenate a path and a string into a single path.
     *
     * @param other the string compnoent to concatenate
     * @return path, The combined path of this and other.
     */
    path operator/(const std::string& other)
    {
        return this->operator/(path(other));
    }

    /**
     * @brief Append a string component to this path.
     *
     * @param other the string component to append
     * @return path, *this
     */
    path& operator/=(const std::string& other)
    {
        this->operator /= (path(other));
        return *this;
    }

    /**
     * @brief Concatenate two paths together.
     *
     * @param other the path to append
     * @return path, The combined path.
     */
    path operator/(const path& other)
    {
        return path(*this).operator /= (other);
    }

    /**
     * @brief Append a string component to this path.
     *
     * @param other the string component to append
     * @return path, *this
     */
    path& operator/=(const path& other)
    {
        this->path_ += K_PREFERRED_SEPARATOR + other.GetPath();
        this->path_as_vector_.insert(std::end(this->path_as_vector_), std::begin(other.path_as_vector_),
                                     std::end(other.path_as_vector_));
        return *this;
    }

private:
    std::string              path_;
    std::vector<std::string> path_as_vector_;
};

/**
 * @brief Check if the path is a regular file.
 *
 * @param p The path to check
 * @return bool, True if the path exists, false otherwise.
 */
inline bool IsRegularFile(const path& p) noexcept
{
    return p.IsRegularFile();
}

/**
 * @brief Check if the path is a directory.
 *
 * @param p The path to check
 * @return path, True if the path is an existing directory, false otherwise.
 */
inline bool IsDirectory(const path& p) noexcept
{
    return p.IsDirectory();
}

/**
 * @brief Get the file size of the path.
 *
 * @param p The path to get the file size of.
 * @return uint64_t， The file size in bytes.
 *
 * @throw std::sytem_error
 */
inline uint64_t FileSize(const path& p)
{
    return p.FileSize();
}

/**
 * @brief Check if a path exists.
 *
 * @param path_to_check The path to check.
 * @return bool, True if the path exists, false otherwise.
 */
inline bool Exists(const path& path_to_check)
{
    return path_to_check.Exists();
}

/**
 * @brief Get a path to a location in the temporary directory, if it's available.
 *
 * @return path, A path to a randomly generated file location in the temporary directory.
 */
inline path TempDirectoryPath()
{
    const char* temp_path = getenv("TMPDIR");
    if (!temp_path)
    {
        temp_path = "/tmp";
    }

    return path(temp_path);
}

/**
 * @brief Create a directory with the given path p.
 * 
 * @attention This builds directories recursively and will skip directories if they are already created.
 * 
 * @param p The path to create.
 * @return bool, Return true if the directory is created, false otherwise.
 */
inline bool CreateDirectories(const path& p)
{
    path p_built;
    int  status = 0;

    for (auto it = p.CBegin(); it != p.CEnd() && status == 0; ++it)
    {
        if (!p_built.Empty() || it->empty())
        {
            p_built /= *it;
        }
        else
        {
            p_built = *it;
        }
        if (!p_built.Exists())
        {

            status = mkdir(p_built.GetPath().c_str(), S_IRWXU | S_IRWXG | S_IRWXO);
        }
    }
    return status == 0;
}

/**
 * @brief Remove the file or directory at the path p.
 *
 * @param p, The path of the object to remove.
 * @return bool, true if the file exists and it was successfully removed, false otherwise.
 */
inline bool Remove(const path& p)
{

    return ::remove(p.GetPath().c_str()) == 0;
}

/**
 * @brief Remove extension(s) from a path.
 *
 * @attention An extension is defined as text starting from the end of a path to the first period (.) character.
 *
 * @param file_path The file path string.
 * @param n_times The number of extensions to remove if there are multiple extensions.
 * @return path, The path object.
 */
inline path RemoveExtension(const path& file_path, int n_times = 1)
{
    path new_path(file_path);
    for (int i = 0; i < n_times; i++)
    {
        const auto new_path_str = new_path.GetPath();
        const auto last_dot     = new_path_str.find_last_of('.');
        if (last_dot == std::string::npos)
        {
            return new_path;
        }
        new_path = path(new_path_str.substr(0, last_dot));
    }
    return new_path;
}

#undef OS_DIRSEP

}  // namespace fs
}  // namespace bag
}  // namespace holo

#endif  // _HOLOBAG_BASE_FILESYSTEM_HPP_
