/*!
 *  \brief a container of utility functions
 *  \author daizhen(daizhen@holomaitc.com)
 *  \date 2017-09-01
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_MAP_COMMON_UTILITY_H_
#define HOLO_MAP_COMMON_UTILITY_H_

#ifdef WINDOWS
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

#include <dirent.h>  // GetAllFilesFromDirectory
#include <math.h>
#include <sys/types.h>  // GetAllFilesFromDirectory
#include <time.h>

#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <queue>

#include <holo/common/odometry.h>
#include <holo/common/timestamp.h>
#include <holo/geometry/pose3.h>

#include <holo/map/common/classes/latlon.h>
#include <holo/map/common/classes/latlonxyh.h>
#include <holo/map/common/common_type_define.h>
#include <holo/map/current_route_info.h>

namespace holo
{
namespace map
{
namespace utility
{
/**
 * @brief add a value into vector if there is no duplicate already inside
 * @tparam T
 * @param _vec [in] _vec vector to be expanded
 * @param _data [in] _data the element to be pushed to the vector
 */
template <typename T>
void UniquePush(::std::vector<T>& _vec, const T& _data)
{
    // make sure the element to be added is unique in the vector
    if (::std::find(_vec.begin(), _vec.end(), _data) == _vec.end())
    {
        _vec.push_back(_data);
    }
};
/**
 * @brief append a vector at the tail of another vector and delete the
 * duplicates
 * @param[out] _vec1 vector to be expanded
 * @param[in] _vec2 vector to be appended
 */
template <typename T>
void UniqueAppend(::std::vector<T>& _vec1, const ::std::vector<T>& _vec2)
{
    for (Size i = 0; i < _vec2.size(); ++i)
    {
        if (::std::find(_vec1.begin(), _vec1.end(), _vec2[i]) == _vec1.end())
        {
            _vec1.push_back(_vec2[i]);
        }
    }
};
/**
 * @brief Convert vector to queue.
 * duplicates
 * @param[out] _vector Source data container.
 * @param[in] _queue Destination data container.
 */
template <typename T>
void VectorToQueue(const std::vector<T>& _vector, std::queue<T>& _queue)
{
    while (!_queue.empty())
    {
        _queue.pop();
    }
    std::for_each(_vector.cbegin(), _vector.cend(), [&_queue](const T& v) -> void { _queue.push(v);});
}

/**
 * @brief if a value is in the vector vec
 * @tparam T
 * @param _vec[in] vector to be used
 * @param _value[in] value to be tested
 * @return true if value is inside the vector
 * @return false if value is not inside the vector
 */
template <typename T>
bool InsideVector(const ::std::vector<T>& _vec, const T& _value)
{
    return ::std::find(_vec.begin(), _vec.end(), _value) != _vec.end();
}

/**
 * @brief Get common elements of two vectors
 * @param[in] _v1 vector 1
 * @param[in] _v2 vector 2
 * @param[out] _common vector of common elements of vector 1 and 2
 * @return
 */
template <typename T>
void GetCommonElementsOfVector(const ::std::vector<T>& _v1, const ::std::vector<T>& _v2, ::std::vector<T>& _common)
{
    _common.clear();
    _common.reserve(std::min(_v1.size(), _v2.size()));

    for (const auto& a : _v1)
    {
        if (InsideVector(_v2, a))
        {
            UniquePush(_common, a);
        }
    }
}

/**
 * @brief Get elements that do not appear in both of vectors
 * @param[in] _v1 vector 1
 * @param[in] _v2 vector 2
 * @param[out] _diff vector of diff elements of vector 1 and 2
 * @return
 */
template <typename T>
void GetDifferentElementsOfVector(const ::std::vector<T>& _v1, const ::std::vector<T>& _v2, ::std::vector<T>& _diff)
{
    ::std::vector<T> common;
    GetCommonElementsOfVector(_v1, _v2, common);
    _diff.clear();
    for (const auto& a : _v1)
    {
        if (!InsideVector(common, a))
        {
            UniquePush(_diff, a);
        }
    }
    for (const auto& a : _v2)
    {
        if (!InsideVector(common, a))
        {
            UniquePush(_diff, a);
        }
    }
}

/**
 * @brief Get different elements that in compare vector, but not in base vector.
 * @param[in] v1 vector 1, base vector
 * @param[in] v2 vector 2, compare vector
 * @param[out] diff vector of elements which diff from vector 2 to 1, the element which in vector2 but not in vector 1.
 * @return
 */
template <typename T>
void GetUnidirectionalDifferentElementsOfVector(std::vector<T> const& v1, std::vector<T> const& v2, std::vector<T>& diff)
{
    diff.clear();
    for (T const& a : v2)
    {
        if (!InsideVector(v1, a))
        {
            UniquePush(diff, a);
        }
    }
    diff.shrink_to_fit();
}

/**
 * @brief Sort and remove duplicated element for vector.
 *
 * @details First step: sort the vector by ascending order.
 *          Second step: remove the duplicated element which difference less than tolerance value.
 *
 * @param[in,out] _vec A metric variable vector.
 * @param[in] _tolerance Maximal allowed difference value between two element.
 *                       if two element difference less than _tolerance, we will
 *                       remove the big element.
 *
 * @return true Sort-And-Remove-Duplicated-Of-Vector successful.
 * @return false Otherwise.
 */
template <typename T>
holo::bool_t SortAndRemoveDuplicatedOfVector(std::vector<T>& _vec, const T _tolerance = 0)
{
    if(_vec.empty())
    {
        return true;
    }

    if(_tolerance < 0)
    {
        LOG(ERROR) << "SortAndRemoveDuplicatedOfVector failed, _tolerance < 0,"
                   << " _tolerance=" << _tolerance;
        return false;
    }

    std::sort(_vec.begin(), _vec.end());

    std::vector<T> const vec = _vec;
    _vec.clear();

    std::size_t const size = vec.size();
    _vec.emplace_back(vec.front());
    for(std::size_t i = 1; i < size; ++i)
    {
        if(vec[i] - _vec.back() > _tolerance)
        {
          _vec.emplace_back(vec[i]);
        }
    }

    _vec.shrink_to_fit();
    return true;
}

/**
 * @brief Remove element Which out or range.
 *
 * @param[in,out] _vec A metric variable vector.
 * @param[in] _range_min Min range.
 * @param[in] _range_max Max range.
 * @param[in] _equal_min If true the element can equal min range, otherwise can't equal min range.
 * @param[in] _equal_max If true the element can equal max range, otherwise can't equal max range..
 *
 * @return true Remove-Out-Range-Elements-Of-Vector successful.
 * @return false Otherwise.
 */
template <typename T>
holo::bool_t RemoveOutRangeElementsOfVector(std::vector<T>&    _vec,
                                            const T            _range_min,
                                            const T            _range_max,
                                            const holo::bool_t _equal_min,
                                            const holo::bool_t _equal_max)
{
    if(_vec.empty())
    {
        return true;
    }
    if(_range_min > _range_max)
    {
        LOG(ERROR) << "RemoveOutRangeElementsOfVector failed, _range_min large than _range_max,"
                   << " _range_min=" << _range_min << "_range_max" << _range_max;
        return false;
    }

    std::vector<T> const vec = _vec;
    _vec.clear();

    std::size_t const size = vec.size();
    for(std::size_t i = 0; i < size; ++i)
    {
        const T check_val = vec[i];
        if ((_equal_min && check_val < _range_min)   ||
            (!_equal_min && check_val <= _range_min) ||
            (_equal_max && check_val > _range_max)   ||
            (!_equal_max && check_val >= _range_max))
        {
            continue;
        }
        _vec.emplace_back(check_val);
    }

    return true;
}

#if 0
/**
 * @brief translate peking time into gps time
 * @param[in] _year
 * @param[in] _month
 * @param[in] _day
 * @param[in] _hour
 * @param[in] _minute
 * @param[in] _second
 * @return time stamp of gps time
 */
Timestamp PekingToGPSTime(const int _year, const int _month, const int _day, const int _hour, const int _minute,
                          const int _second);
#endif
/**
 * @brief Write vector(point2d) into txt, with order of all the x
 * coordinates and y coordinates in one line, each element is seperated with
 * blank space. The txt file will be stored into folder WriteIntoTxt,
 * which should be created in the same folder with current app
 * @param _name txt file name, for example "test.txt"
 * @param _vec vector(point2d)
 */
void WriteIntoText(const ::std::string& _name, const ::std::vector<MapPoint>& _vec);
void WriteIntoText(const ::std::string& _name, const ::std::vector<Distance>& _vec,
                   const bool _write_after_last_time = false);
void WriteIntoText(const std::string& _name, const std::vector<MapPoint3>& _vec,
                   const bool _write_after_last_time = false);
void WriteIntoText(const std::string& _name, const std::string& _text, const bool _write_after_last_time = false);

/**
 *@brief clean the duplicats in this vector
 */
template <typename T>
void CleanDuplicates(::std::vector<T>& _ori);

/**
 * @brief release pointer
 *
 * @tparam T pointer non array
 * @param[in,out] _pointer
 * @return Nothing
 */
template <typename T,
          typename ::std::enable_if<
              ::std::is_pointer<T>::value ? !::std::is_array<typename ::std::remove_pointer<T>::type>::value : false,
              T>::type...>
void Release(T& _pointer)
{
    if (_pointer)
    {
        delete _pointer;
        _pointer = nullptr;
    }
}
//////////////////////////////////////////////////////////////////////////

/**
 * @brief Split string into two strings by delimiter
 *
 * @param [in] _str input string
 * @param [in] _delim delimiter
 * @param [out] _str1 splitted string, which is before delimiter
 * @param [out] _str2 splitted string, which is after delimiter
 * @param [out] _delim_pos position of delimiter in original string
 * @return true
 * @return false
 */
bool SplitString(const std::string& _str, const std::string& _delim, std::string& _str1, std::string& _str2,
                 Size& _delim_pos);
bool SplitString(const std::string& _str, const std::string& _delim, std::string& _str1, std::string& _str2);

/**
 * @brief Split string according to delimiter
 *
 * @param [in] _str input string
 * @param [in] _delim delimiter
 * @param [out] _vec_str vector of splitted string
 * @param [out] _vec_delim_pos vector for position of delimiter in original
 *              string
 * @return true
 * @return false
 */
bool SplitString(const std::string& _str, const std::string& _delim, std::vector<std::string>& _vec_str,
                 std::vector<Size>& _vec_delim_pos);
bool SplitString(const std::string& _str, const std::string& _delim, std::vector<std::string>& _vec_str);

/**
 * @brief Get string between delimiter1 and delimiter2
 *
 * @param [in] _str1 input string
 * @param [in] _delim1
 * @param [in] _delim2
 * @param [out] _str2 string between delimiter1/2
 * @return true
 * @return false
 */
bool GetStringBetween(const std::string& _str1, const std::string& _delim1, const std::string& _delim2,
                      std::string& _str2, const Size _id_left = 0, const Size _id_right = 0);

/**
 * @brief Delete all spaces in string
 *
 * @param [in|out] _str
 */
void DeleteAllSpaces(std::string& _str);

/**
 * @brief Replace specific sub-string with other sub-string
 * @param[in,out] _str original string to be modified
 * @param[in] _from sub-string to be replaced
 * @param[in] _to expected sub-string
 */
void ReplaceString(std::string& _str, const std::string& _from, const std::string& _to);

/**
 * @brief Delete termination character at the end of string, default is enter
 *
 * @param _str
 */
void DeleteEnd(std::string& _str, const char _end = '\r');

/// @brief circular deletion the character if it it the tail of the str
///
/// @param [in] _end tail character to be deleted
/// @param [out] _str origin string
///
/// @return nothing
void DeleteEndRecursion(::std::string& _str, const char _end);

/// @brief deal with the path, if the tail of the path is not '/',
/// then will add '/'
///
/// @param [out] filePath, the file path which to be dealed with
/// @return Nothing
///
void DealWithFilePathEOF(::std::string& _file_path);

/**
 * @brief Read a text file dedicated to a series of 3D points given
 * in forms of "x,y,z" per line
 * @param[in] _filename file name
 * @param[out] _line vector of points to be filled
 */
void ReadFromFile_XYH(const std::string& _filename, map::VecXYH& _line);

/**
 * @brief Read a text file dedicated to muitiple lines given
 * in forms of "id, x,y,z" per line
 * @param[in] _filename file name
 * @param[out] _lines vector of points to be filled
 */
void ReadFromFile_ID_XYH(const std::string& _filename, HashmapLine3D& _lines);

/**
 * @brief Get all files' name in directory
 *        TODO: this is only for linux system!!!
 *
 * @param [in] _path folder path
 * @param [out] _files vector of file names
 */
void GetAllFilesFromDirectory(const std::string& _path, std::vector<std::string>& _files);

/**
 * @brief Load topic infomation from bag file by topic name
 * on the process, a intermediate file would be created,
 * named xxx.txt in the /tmp folder
 *
 * @param [in] _bag_file_name ros bag file
 * @param [in] _topic_name topic name
 * @param [out] _topic_list list of topic struct
 */
// 92 is the limit size of odometry format
const int odometry_separate_count_ = 92;
template <typename T>
bool LoadTopicFromRosBag(const std::string& _bag_file_name, const std::string& _topic_name,
                         std::vector<T>& _topic_list);
/**
 * @brief use 'system' function to execute shell command,
 *        but now it doesn't support to execute the command which has its result,
 *        such as 'ls'
 *
 * @param [in] _command
 * @param [out] true success
 *              false failure
 */
bool ExecuteShellCommand(const std::string& _command);

/**
 * @brief check if a file or a directory exists
 *
 * @param [in] _file_path or directory path
 * @param [out] true exists
 *              false not exists
 */
bool IsFileOrDirExist(const std::string& _path);

/**
 * @brief remove a file or a directory.
 *       if the directory doesn't exist, return true.
 *
 * @param [in] _path
 * @param [out] true  success
 *              false failed
 */
bool RemoveFileOrDir(const std::string& _path);

/**
 * @brief make a directory.
 *        if the direcotry already exists, return true and do nothing.
 *
 * @param [in] _path
 * @param [out] true  success
 *              false failed
 */
bool Mkdir(const std::string& _path);

/**
 * @brief Get vector of key values from a text file
 * @param[in] _filename file name
 * @param[out] _line vector of key values to be filled out
 */
void ReadFromFile_Vector(const std::string& _filename, map::MapFeatureIdVectorType& _vec);

/**
 * @brief Write a vector of key values into a text file
 * @param[in] _name file name
 * @param[in] _vec vector of key values
 * @param[in] _write_after_last_time true for append; false for re-write
 */
void WriteIntoText(const std::string& _name, const MapFeatureIdVectorType& _vec, const bool _write_after_last_time);

/**
 * @brief Trans odometry to local map odometry.
 * @param[in] odo A odometry.
 * @param[out] local_odo A local map odometry.
 */
void Odometry2LocalMapOdometry(holo::common::Odometryd const& odo, holo::common::LocalMapOdometryd& local_odo);

/**
 * @brief Trans local map odometry to odometry.
 * @param[in] local_odo A local map odometry.
 * @param[out] odo A  odometry.
 */
void LocalMapOdometry2Odometry(holo::common::LocalMapOdometryd const& local_odo, holo::common::Odometryd& odo);
//////////////////////////////////////////////////////////////////////////
}  // namespace utility
}  // namespace map
}  // namespace holo

#endif /* HOLO_MAP_MATH_UTILITY_H_ */
