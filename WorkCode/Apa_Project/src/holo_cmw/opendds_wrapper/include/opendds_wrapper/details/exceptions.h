/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file builtin_traits.h
 * @brief This header file defines builtin message traits.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-07
 */

#include <exception>

#ifndef OPENDDS_WRAPPER_DETAILS_EXCEPTIONS_H_
#define OPENDDS_WRAPPER_DETAILS_EXCEPTIONS_H_

namespace opendds_wrapper
{
namespace exceptions
{
class OpenddsWrapperException : public std::exception
{
public:
    const char* what() const noexcept
    {
        return msg_.c_str();
    }

protected:
    std::string msg_;
};

class OpenddsInternalErrorException : public OpenddsWrapperException
{
public:
    OpenddsInternalErrorException(std::string const& msg)
    {
        msg_ = msg;
    }
};

class NoSuchWriterException : public OpenddsWrapperException
{
public:
    NoSuchWriterException(std::string const& topic_name)
    {
        msg_ = std::string("No writer(") + topic_name + std::string(") found!");
    }
};

class NoSuchReaderException : public OpenddsWrapperException
{
public:
    NoSuchReaderException(std::string const& topic_name)
    {
        msg_ = std::string("No reader(") + topic_name + std::string(") found!");
    }
};

class CreateWriterFailedException : public OpenddsWrapperException
{
public:
    CreateWriterFailedException(std::string const& topic_name)
    {
        msg_ = std::string("Create writer(" + topic_name + ") failed");
    }
};

class DeleteWriterErrorException : public OpenddsWrapperException
{
public:
    DeleteWriterErrorException(std::string const& topic_name, DDS::ReturnCode_t code)
    {
        msg_ = std::string("Delete writer(" + topic_name + ") failed with return code " + std::to_string(code));
    }
};

class CreateReaderFailedException : public OpenddsWrapperException
{
public:
    CreateReaderFailedException(std::string const& topic_name)
    {
        msg_ = std::string("Create reader(" + topic_name + ") failed");
    }
};

class DeleteReaderErrorException : public OpenddsWrapperException
{
public:
    DeleteReaderErrorException(std::string const& topic_name, DDS::ReturnCode_t code)
    {
        msg_ = std::string("Delete reader(" + topic_name + ") failed with return code " + std::to_string(code));
    }
};

class DeleteTopicErrorException : public OpenddsWrapperException
{
public:
    DeleteTopicErrorException(std::string const& topic_name, DDS::ReturnCode_t code)
    {
        msg_ = std::string("Delete topic(" + topic_name + ") failed with return code " + std::to_string(code));
    }
};

class InvalidTopicNameException : public OpenddsWrapperException
{
public:
    InvalidTopicNameException(std::string const& topic_name)
    {
        msg_ = std::string("Invalid topic name ") + topic_name;
    }
};

class TakeSampleFailedException : public OpenddsWrapperException
{
public:
    TakeSampleFailedException(std::string const& topic_name, DDS::ReturnCode_t code)
    {
        msg_ = std::string("Datareader(") + topic_name + std::string(") failed to take sample. retcode = ") +
               std::to_string(code);
    }
};

class TypeRegistrationFailedException : public OpenddsWrapperException
{
public:
    TypeRegistrationFailedException(std::string const& topic_name, std::string const& type_name, DDS::ReturnCode_t code)
    {
        msg_ = std::string("Register topic ") + topic_name + " with type_name " + type_name +
               "Failed! Return code = " + std::to_string(code);
    }
};

class CreateTopicFailedException : public OpenddsWrapperException
{
public:
    CreateTopicFailedException(std::string const& topic_name)
    {
        msg_ = std::string("Failed to create topic ") + topic_name + ". A topic with different type name may exist.";
    }
};

class InvalidConditionException : public OpenddsWrapperException
{
public:
    InvalidConditionException(std::string const& msg)
    {
        msg_ = std::string("Invalid waitset condition. ") + msg;
    }
};

}  // namespace exceptions
}  // namespace opendds_wrapper

#endif
