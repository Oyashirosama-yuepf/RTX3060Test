/**
 * @brief This header file defines all exceptions.
 * @author zhangjiannan(zhangjiannan@holomaitc.com)
 * @date Oct 30, 2019
 * @attention Copyright Holomatic Technology (Beijing) Co.Ltd
 * @attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#ifndef HOLO_CORE_EXCEPTION_H_
#define HOLO_CORE_EXCEPTION_H_

#include <string>
#include <cstring>
#include <stdexcept>

namespace holo
{
namespace exception
{
class OutOfRangeException : public std::out_of_range
{
public:
    explicit OutOfRangeException(std::string const& what_arg) noexcept : std::out_of_range("")
    {
        std::strncpy(what_arg_, what_arg.c_str(), 255U);
    }

    explicit OutOfRangeException(char const* what_arg) noexcept : std::out_of_range("")
    {
        std::strncpy(what_arg_, what_arg, 255U);
    }

    virtual ~OutOfRangeException() noexcept
    {
    }

    virtual char const* what() const noexcept
    {
        return what_arg_;
    }

private:
    char what_arg_[256U];
};

class BadAllocException : public std::bad_alloc
{
public:
    BadAllocException() noexcept
    {
    }

    virtual ~BadAllocException() noexcept
    {
    }
};

class RuntimeErrorException : public std::runtime_error
{
public:
    explicit RuntimeErrorException(const std::string& what_arg) noexcept : std::runtime_error("")
    {
        std::strncpy(what_arg_, what_arg.c_str(), 255U);
    }

    explicit RuntimeErrorException(const char* what_arg) noexcept : std::runtime_error("")
    {
        std::strncpy(what_arg_, what_arg, 255U);
    }

    virtual ~RuntimeErrorException() noexcept
    {
    }

    virtual char const* what() const noexcept
    {
        return what_arg_;
    }

private:
    char what_arg_[256U];
};

class OperationNotPermittedException : public std::exception
{
};

}  // namespace exception

}  // namespace holo

#endif
