/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file reader.h
 * @brief This header file defines OpenDDS reader object.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-07
 */

#ifndef OPENDDS_WRAPPER_DETAILS_READER_H_
#define OPENDDS_WRAPPER_DETAILS_READER_H_

#include <cstring>
#include <exception>

#include "bus.h"
#include "exceptions.h"

namespace opendds_wrapper
{
namespace details
{
/**
 * @brief ReaderBase object wraps operations related to OpenDDS DataReader
 *
 * @tparam M Message type.
 */
template <typename M>
class ReaderBase
{
protected:
    using MessageType         = M;
    using MessageSequenceType = typename OpenDDS::DCPS::DDSTraits<MessageType>::MessageSequenceType;
    using TypeSupportType     = typename OpenDDS::DCPS::DDSTraits<MessageType>::TypeSupportType;
    using TypeSupportTypeImpl = typename OpenDDS::DCPS::DDSTraits<MessageType>::TypeSupportTypeImpl;
    using DataWriterType      = typename OpenDDS::DCPS::DDSTraits<MessageType>::DataWriterType;
    using DataReaderType      = typename OpenDDS::DCPS::DDSTraits<MessageType>::DataReaderType;
    using LessThanType        = typename OpenDDS::DCPS::DDSTraits<MessageType>::LessThanType;

public:
    /**
     * @brief Get topic name
     *
     * @return Topic name
     */
    std::string GetTopicName()
    {
        char*       name = reader_->get_topicdescription()->get_name();
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
        char*       name = reader_->get_topicdescription()->get_type_name();
        std::string value(name);
        delete[] name;
        return value;
    }

    /**
     * @brief Get number of matched writers
     *
     * @return Matched writer count.
     */
    size_t GetMatchedWriterCount()
    {
        DDS::SubscriptionMatchedStatus matches;
        if (DDS::RETCODE_OK != reader_->get_subscription_matched_status(matches))
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to get reader matched status");
        }
        return static_cast<size_t>(matches.current_count);
    }

    /**
     * @brief Reset sample receive callback function
     */
    void ResetOnDataAvailableCallback()
    {
        DDS::StatusCondition* status_condition = reader_->get_statuscondition();
        if (nullptr == status_condition)
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to get reader status condition");
        }

        // reader_->
        // TODO  change status
        //

        // or
        waitset_->DeleteCallback(status_condition);
        waitset_->DeleteSchedule(status_condition);
    }

    /**
     * @brief Set sample receive callback function
     *
     * @param callback Callback function
     */
    void SetOnDataAvailableCallback(std::function<void(MessageType const&)> callback)
    {
        DDS::StatusCondition* status_condition = reader_->get_statuscondition();
        if (nullptr == status_condition)
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to get reader status condition");
        }

        DDS::ReturnCode_t retcode = status_condition->set_enabled_statuses(DDS::DATA_AVAILABLE_STATUS);
        if (retcode != DDS::RETCODE_OK)
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to set_enabled_statuses");
        }

        DataReaderType* reader  = reader_;
        WaitSet*        waitset = waitset_;

        waitset_->AddSchedule(status_condition);
        waitset_->AddCallback(status_condition, [reader, waitset, status_condition, callback]() -> void {
            DDS::StatusMask triggeredmask = reader->get_status_changes();
            if (triggeredmask & DDS::DATA_AVAILABLE_STATUS)
            {
                DDS::ReturnCode_t   retcode     = DDS::RETCODE_OK;
                DataReaderType*     data_reader = DataReaderType::_narrow(reader);
                DDS::SampleInfoSeq  sample_infos;
                MessageSequenceType samples;

                do
                {
                    retcode = data_reader->take(samples, sample_infos, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
                                                DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);
                    for (ssize_t idx = 0; idx < samples.length(); idx++)
                    {
                        if (sample_infos[idx].valid_data)
                        {
                            callback(samples[idx]);
                        }
                    }

                    data_reader->return_loan(samples, sample_infos);

                } while (retcode != DDS::RETCODE_NO_DATA);
            }
            waitset->SetSchedule(status_condition, false);
        });
    }

    friend class ::opendds_wrapper::DdsBus;

    /**
     * @brief Construct reader with OpenDDS DataReader object
     *
     * @param reader Pointer to OpenDDS DataReaer object
     */
    ReaderBase(DataReaderType* reader, WaitSet* waitset) noexcept : reader_{reader}, waitset_{waitset}
    {
    }

    /**
     * @brief Default constructor
     */
    ReaderBase() noexcept : reader_{nullptr}, waitset_{nullptr}
    {
    }

protected:
    ~ReaderBase() = default;

    DataReaderType* reader_;   ///< OpenDDS DataReader object
    WaitSet*        waitset_;  ///< DataReader WaitSet
};

template <typename V, typename Traits>
class Reader : public ReaderBase<typename Traits::MessageType>
{
public:
    using Base                 = ReaderBase<typename Traits::MessageType>;
    using ValueType            = V;
    using MessageType          = typename Base::MessageType;
    using ConversionTraitsType = Traits;

    using MessageSequenceType = typename Base::MessageSequenceType;
    using TypeSupportType     = typename Base::TypeSupportType;
    using TypeSupportTypeImpl = typename Base::TypeSupportTypeImpl;
    using DataWriterType      = typename Base::DataWriterType;
    using DataReaderType      = typename Base::DataReaderType;
    using LessThanType        = typename Base::LessThanType;

    using Base::Base;
    using Base::SetOnDataAvailableCallback;

    template <typename V_ = ValueType, typename std::enable_if<!std::is_same<V_, MessageType>::value>::type* = nullptr>
    void SetOnDataAvailableCallback(std::function<void(ValueType const&)> callback)
    {
        DDS::StatusCondition* status_condition = this->reader_->get_statuscondition();
        if (nullptr == status_condition)
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to get reader status condition");
        }

        DDS::ReturnCode_t retcode = status_condition->set_enabled_statuses(DDS::DATA_AVAILABLE_STATUS);
        if (retcode != DDS::RETCODE_OK)
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to set_enabled_statuses");
        }

        DataReaderType* reader  = this->reader_;
        WaitSet*        waitset = this->waitset_;

        this->waitset_->AddSchedule(status_condition);
        this->waitset_->AddCallback(status_condition, [reader, waitset, status_condition, callback]() -> void {
            DDS::StatusMask triggeredmask = reader->get_status_changes();
            if (triggeredmask & DDS::DATA_AVAILABLE_STATUS)
            {
                DDS::ReturnCode_t   retcode     = DDS::RETCODE_OK;
                DataReaderType*     data_reader = DataReaderType::_narrow(reader);
                DDS::SampleInfoSeq  sample_infos;
                MessageSequenceType samples;

                do
                {
                    retcode = data_reader->take(samples, sample_infos, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
                                                DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);
                    for (ssize_t idx = 0; idx < samples.length(); idx++)
                    {
                        if (sample_infos[idx].valid_data)
                        {
                            ValueType value;
                            ConversionTraitsType::Convert(samples[idx], value);
                            callback(value);
                        }
                    }

                    data_reader->return_loan(samples, sample_infos);

                } while (retcode != DDS::RETCODE_NO_DATA);
            }
            waitset->SetSchedule(status_condition, false);
        });
    }
};

template <typename Traits>
class Reader<uint8_t*, Traits> : public ReaderBase<BuiltinBuffer>
{
public:
    using Base                 = ReaderBase<BuiltinBuffer>;
    using ValueType            = uint8_t*;
    using MessageType          = typename Base::MessageType;
    using ConversionTraitsType = Traits;

    using MessageSequenceType = typename Base::MessageSequenceType;
    using TypeSupportType     = typename Base::TypeSupportType;
    using TypeSupportTypeImpl = typename Base::TypeSupportTypeImpl;
    using DataWriterType      = typename Base::DataWriterType;
    using DataReaderType      = typename Base::DataReaderType;
    using LessThanType        = typename Base::LessThanType;

    using Base::Base;
    using Base::SetOnDataAvailableCallback;

    void SetOnDataAvailableCallback(std::function<void(uint8_t const* buffer, size_t size)> callback)
    {
        DDS::StatusCondition* status_condition = this->reader_->get_statuscondition();
        if (nullptr == status_condition)
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to get reader status condition");
        }

        DDS::ReturnCode_t retcode = status_condition->set_enabled_statuses(DDS::DATA_AVAILABLE_STATUS);
        if (retcode != DDS::RETCODE_OK)
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to set_enabled_statuses");
        }

        DataReaderType* reader  = this->reader_;
        WaitSet*        waitset = this->waitset_;

        this->waitset_->AddSchedule(status_condition);
        this->waitset_->AddCallback(status_condition, [reader, waitset, status_condition, callback]() -> void {
            DDS::StatusMask triggeredmask = reader->get_status_changes();
            if (triggeredmask & DDS::DATA_AVAILABLE_STATUS)
            {
                DDS::ReturnCode_t   retcode     = DDS::RETCODE_OK;
                DataReaderType*     data_reader = DataReaderType::_narrow(reader);
                DDS::SampleInfoSeq  sample_infos;
                MessageSequenceType samples;

                do
                {
                    retcode = data_reader->take(samples, sample_infos, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE,
                                                DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);
                    for (ssize_t idx = 0; idx < samples.length(); idx++)
                    {
                        if (sample_infos[idx].valid_data)
                        {
                            callback(&samples[idx].value[0], samples[idx].value.length());
                        }
                    }

                    data_reader->return_loan(samples, sample_infos);

                } while (retcode != DDS::RETCODE_NO_DATA);
            }
            waitset->SetSchedule(status_condition, false);
        });
    }
};  // namespace details

}  // namespace details
}  // namespace opendds_wrapper

#endif
