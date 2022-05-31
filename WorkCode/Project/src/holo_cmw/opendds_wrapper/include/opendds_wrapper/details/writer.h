/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file writer.h
 * @brief This header file defines OpenDDS writer object.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-07
 */

#ifndef OPENDDS_WRAPPER_DETAILS_WRITER_H_
#define OPENDDS_WRAPPER_DETAILS_WRITER_H_

#include <cstring>
#include <exception>

#include "bus.h"
#include "exceptions.h"

namespace opendds_wrapper
{
namespace details
{
/**
 * @brief WriterBase object wraps operations related to OpenDDS DataWriter
 *
 * @tparam M Message type.
 */
template <typename M>
class WriterBase
{
public:
    using MessageType         = M;
    using MessageSequenceType = typename OpenDDS::DCPS::DDSTraits<MessageType>::MessageSequenceType;
    using TypeSupportType     = typename OpenDDS::DCPS::DDSTraits<MessageType>::TypeSupportType;
    using TypeSupportTypeImpl = typename OpenDDS::DCPS::DDSTraits<MessageType>::TypeSupportTypeImpl;
    using DataWriterType      = typename OpenDDS::DCPS::DDSTraits<MessageType>::DataWriterType;
    using DataReaderType      = typename OpenDDS::DCPS::DDSTraits<MessageType>::DataReaderType;
    using LessThanType        = typename OpenDDS::DCPS::DDSTraits<MessageType>::LessThanType;

    /**
     * @brief Get topic name.
     *
     * @return Topic name
     */
    std::string GetTopicName()
    {
        char*       name = writer_->get_topic()->get_name();
        std::string value(name);
        delete[] name;
        return value;
    }

    /**
     * @brief Get topic type name
     *
     * @return Type name
     */
    std::string GetTypeName()
    {
        char*       name = writer_->get_topic()->get_type_name();
        std::string value(name);
        delete[] name;
        return value;
    }

    /**
     * @brief Get number of readers matched to this writer.
     *
     * @return Reader matched count
     */
    size_t GetMatchedReaderCount()
    {
        DDS::PublicationMatchedStatus matches;
        if (DDS::RETCODE_OK != writer_->get_publication_matched_status(matches))
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to get publication matched status");
        }
        return static_cast<size_t>(matches.current_count);
    }

    /**
     * @brief Write a sample
     *
     * @param sample Sample data.
     */
    void Write(MessageType const& sample)
    {
        writer_->write(sample, DDS::HANDLE_NIL);
    }

    bool WaitSubscription(::opendds_wrapper::DdsBus::DurationType timeout = {DDS::DURATION_INFINITE_SEC, DDS::DURATION_INFINITE_NSEC})
    {
        DDS::WaitSet          ws;
        DDS::StatusCondition* condition = writer_->get_statuscondition();
        condition->set_enabled_statuses(DDS::PUBLICATION_MATCHED_STATUS);
        ws.attach_condition(condition);
        DDS::ConditionSeq condition_seq;

        DDS::ReturnCode_t ret = ws.wait(condition_seq, {timeout.sec, timeout.nsec});

        ws.detach_condition(condition);

        if (DDS::RETCODE_OK == ret)
        {
            return true;
        }
        else if (DDS::RETCODE_TIMEOUT == ret)
        {
            return false;
        }
        else
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to wait for WaitSet");
        }
    }

    friend class ::opendds_wrapper::DdsBus;

    /**
     * @brief Construct with underlying OpenDDS DataWriter.
     *
     * @param writer Pointer to DataWriter.
     */
    WriterBase(DataWriterType* writer) noexcept: writer_{writer}
    {
    }

    /**
     * @brief Default constructor
     */
    WriterBase() noexcept: writer_{nullptr}
    {
    }

protected:
    ~WriterBase() = default;

private:
    DataWriterType* writer_; ///< OpenDDS data writer object
};

template <typename V, typename Traits>
class Writer : public WriterBase<typename Traits::MessageType>
{
public:
    using Base        = WriterBase<typename Traits::MessageType>;
    using ValueType   = V;
    using MessageType = typename Base::MessageType;
    using ConversionTraitsType = Traits;

    using MessageSequenceType = typename Base::MessageSequenceType;
    using TypeSupportType     = typename Base::TypeSupportType;
    using TypeSupportTypeImpl = typename Base::TypeSupportTypeImpl;
    using DataWriterType      = typename Base::DataWriterType;
    using DataReaderType      = typename Base::DataReaderType;
    using LessThanType        = typename Base::LessThanType;

    using Base::Base;
    using Base::Write;

    template <typename V_ = ValueType, typename std::enable_if<!std::is_same<V_, MessageType>::value>::type* = nullptr>
    void Write(ValueType const& sample)
    {
        MessageType message;
        ConversionTraitsType::Convert(sample, message);
        Base::Write(message);
    }
};

template <typename Traits>
class Writer<uint8_t*, Traits> : public WriterBase<BuiltinBuffer>
{
public:
    using Base        = WriterBase<BuiltinBuffer>;
    using ValueType   = uint8_t*;
    using MessageType = typename Base::MessageType;
    using ConversionTraitsType = Traits;

    using MessageSequenceType = typename Base::MessageSequenceType;
    using TypeSupportType     = typename Base::TypeSupportType;
    using TypeSupportTypeImpl = typename Base::TypeSupportTypeImpl;
    using DataWriterType      = typename Base::DataWriterType;
    using DataReaderType      = typename Base::DataReaderType;
    using LessThanType        = typename Base::LessThanType;

    using Base::Base;
    using Base::Write;

    void Write(uint8_t const* buffer, size_t size)
    {
        MessageType message;
        message.value.length(size);
        std::memcpy(&message.value[0], buffer, size);
        Base::Write(message);
    }
};

}  // namespace details
}  // namespace opendds_wrapper

#endif
