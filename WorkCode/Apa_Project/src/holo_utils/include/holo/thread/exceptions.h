#ifndef HOLO_THREAD_EXCEPTIONS_H_
#define HOLO_THREAD_EXCEPTIONS_H_

#include <exception>
#include <string>

namespace holo
{
namespace thread
{
class ThreadException : public std::exception
{
public:
    const char* what() const noexcept
    {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};

class ThreadPoolPauseStatusException : public ThreadException
{
public:
    ThreadPoolPauseStatusException(std::string const& msg)
    {
        msg_ = msg;
    }
};

class TaskQueueIsFullException : public ThreadException
{
public:
    TaskQueueIsFullException(std::string const& msg)
    {
        msg_ = msg;
    }
};

class IllegalParameterException : public ThreadException
{
public:
    IllegalParameterException(std::string const& msg)
    {
        msg_ = msg;
    }
};

class LogicalErrorException : public ThreadException
{
public:
    LogicalErrorException(std::string const& msg)
    {
        msg_ = msg;
    }
};

class IllegalAddressException : public ThreadException
{
public:
    IllegalAddressException(std::string const& msg)
    {
        msg_ = msg;
    }
};

class DoubleFreeException : public ThreadException
{
public:
    DoubleFreeException(std::string const& msg)
    {
        msg_ = msg;
    }
};

}  // namespace thread
}  // namespace holo

#endif
