/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file bus.h
 * @brief This header file defines OpenDDS wrapper object.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-07
 */

#ifndef OPENDDS_WRAPPER_DETAILS_BUS_H_
#define OPENDDS_WRAPPER_DETAILS_BUS_H_

#include <cstring>
#include <exception>

#include <dds/DCPS/BuiltInTopicUtils.h>
#include <dds/DCPS/Marked_Default_Qos.h>
#include <dds/DCPS/Service_Participant.h>
#include <dds/DCPS/TypeSupportImpl.h>
#include <dds/DCPS/WaitSet.h>
#include <dds/DdsDcpsC.h>
#include <dds/DdsDcpsCoreC.h>

#include <holo/thread/thread_pool.h>
#include "common.h"
#include "exceptions.h"
#include "traits.h"
#include "waitset.h"

namespace opendds_wrapper
{
class DdsBus
{
public:
    using BuiltinMessageType   = details::BuiltinMessage;
    using TopicDescriptionType = details::TopicDescription;
    using DurationType         = details::Duration;

    template <typename V, typename Serializer = holo::serialization::Serializer<>,
              typename Deserializer = holo::serialization::Deserializer<>>
    using SerializationTraitsType = SerializationTraits<V, Serializer, Deserializer>;

    template <typename V>
    using MemcpyTraitsType = MemcpyTraits<V>;

    template <typename V, typename M = typename DefaultMessageTraits<V>::MessageType>
    using DefaultConversionTraitsType = DefaultConversionTraits<V, M>;

    template <typename V>
    struct DefaultTraits
    {
        using type = SerializationTraitsType<V>;
    };

    template <typename V, typename Traits = typename DefaultTraits<V>::type>
    using ReaderType = details::Reader<V, Traits>;

    template <typename V, typename Traits = typename DefaultTraits<V>::type>
    using WriterType = details::Writer<V, Traits>;


    /**
     * @brief Construct with domain id and domain participant tag.
     *
     * @param id Domain id
     * @param ns namespace for this participant
     */
    DdsBus(DDS::DomainId_t id, std::string const& ns = "");

    /**
     * @brief Destructor
     */
    ~DdsBus();

    /**
     * @brief Add writer to opendds bus with topic name.
     *
     * @tparam V Topic value type
     * @tparam Traits Conversion traits type
     * @param topic_name Topic name
     *
     * @return Writer object.
     */
    template <typename V, typename Traits = typename DefaultTraits<V>::type>
    WriterType<V, Traits> AddWriter(std::string const& topic_name)
    {
        return WriterType<V, Traits>(WriterType<V, Traits>::DataWriterType::_narrow(createOpenddsDataWriter(
            new typename WriterType<V, Traits>::TypeSupportTypeImpl(), insertNamespace(topic_name), nullptr)));
    }

    /**
     * @brief Add reader to opendds bus with topic name
     *
     * @tparam V Topic value type
     * @tparam Traits Conversion traits type
     * @param topic_name Topic name
     *
     * @return Reader object.
     */
    template <typename V, typename Traits = typename DefaultTraits<V>::type>
    ReaderType<V, Traits> AddReader(std::string const& topic_name)
    {
        return ReaderType<V, Traits>(ReaderType<V, Traits>::DataReaderType::_narrow(createOpenddsDataReader(
                                         new typename ReaderType<V, Traits>::TypeSupportTypeImpl(),
                                         insertNamespace(topic_name), nullptr, nullptr)),
                                     &waitset_);
    }

    /**
     * @brief Get writer object with topic name
     *
     * @tparam V Topic value type
     * @tparam Traits Conversion traits type
     * @param topic_name Topic name
     *
     * @return Writer object
     */
    template <typename V, typename Traits = typename DefaultTraits<V>::type>
    WriterType<V, Traits> GetWriter(std::string const& topic_name)
    {
        DDS::DataWriter* writer = publisher_->lookup_datawriter(insertNamespace(topic_name).c_str());
        if (nullptr == writer)
        {
            throw opendds_wrapper::exceptions::NoSuchWriterException(topic_name);
        }
        return WriterType<V, Traits>(WriterType<V, Traits>::DataWriterType::_narrow(writer));
    }

    /**
     * @brief Get reader object with topic name
     *
     * @tparam V Topic value type
     * @tparam Traits Conversion traits type
     * @param topic_name Topic name
     *
     * @return Reader object
     */
    template <typename V, typename Traits = typename DefaultTraits<V>::type>
    ReaderType<V, Traits> GetReader(std::string const& topic_name)
    {
        DDS::DataReader* reader = subscriber_->lookup_datareader(insertNamespace(topic_name).c_str());
        if (nullptr == reader)
        {
            throw opendds_wrapper::exceptions::NoSuchReaderException(topic_name);
        }
        return ReaderType<V, Traits>(ReaderType<V, Traits>::DataReaderType::_narrow(reader), &waitset_);
    }

    /**
     * @brief Delete writer object with topic name
     *
     * @param topic_name Topic name
     */
    void DeleteWriter(std::string const& topic_name);

    /**
     * @brief Delete writer object
     *
     * @tparam V Topic value type
     * @tparam Traits Conversion traits type
     * @param writer The writer object
     */
    template <typename V, typename Traits = typename DefaultTraits<V>::type>
    void DeleteWriter(WriterType<V, Traits>& writer)
    {
        DDS::ReturnCode_t code;
        std::string       topic_name = writer.GetTopicName();
        DDS::Topic*       topic      = writer.writer_->get_topic();
        code                         = publisher_->delete_datawriter(writer.writer_);
        if (DDS::RETCODE_OK != code)
        {
            throw opendds_wrapper::exceptions::DeleteWriterErrorException(topic_name, code);
        }
        code = participant_->delete_topic(topic);
        if (DDS::RETCODE_OK != code)
        {
            throw opendds_wrapper::exceptions::DeleteTopicErrorException(topic_name, code);
        }
    }

    /**
     * @brief Delete reader object with topic name
     *
     * @param topic_name Topic name
     */
    void DeleteReader(std::string const& topic_name);

    /**
     * @brief Delete reader object
     *
     * @tparam V Topic value type
     * @tparam Traits Conversion traits type
     * @param reader The reader object
     */
    template <typename V, typename Traits = typename DefaultTraits<V>::type>
    void DeleteReader(ReaderType<V, Traits>& reader)
    {
        DDS::ReturnCode_t      code;
        std::string            topic_name = reader.GetTopicName();
        DDS::TopicDescription* topic      = reader.reader_->get_topicdescription();

        DDS::StatusCondition* status_condition = reader.reader_->get_statuscondition();
        if (nullptr == status_condition)
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to get reader status condition");
        }

        waitset_.DeleteCallback(status_condition);
        waitset_.DeleteSchedule(status_condition);

        code = subscriber_->delete_datareader(reader.reader_);
        if (DDS::RETCODE_OK != code)
        {
            throw opendds_wrapper::exceptions::DeleteReaderErrorException(topic_name, code);
        }
        code = participant_->delete_topic(dynamic_cast<DDS::Topic*>(topic));
        if (DDS::RETCODE_OK != code)
        {
            throw opendds_wrapper::exceptions::DeleteTopicErrorException(topic_name, code);
        }
    }

    void Enable()
    {
        participant_->enable();
    }

    DDS::DomainParticipant* GetParticipant()
    {
        return participant_;
    }

    DDS::Publisher* GetPublisher()
    {
        return publisher_;
    }

    DDS::Subscriber* GetSubscriber()
    {
        return subscriber_;
    }

    /**
     * @brief Get discovered topic list
     *
     * @return list of TopicDescription
     *
     * @note DCPSBit config must set to 1 to enable topic discovery
     */
    std::vector<TopicDescriptionType> GetTopicList();

    /**
     * @brief Get discovered node list
     *
     * @return list of node ids.
     *
     * @note DCPSBit config must set to 1 to enable participant discovery
     */
    std::vector<std::string> GetNodeList();

    /**
     * @brief Get current node id.
     *
     * @return Node id
     *
     * @note Non dds standard API
     */
    std::string GetId();

    /**
     * @brief Initialize OpenDDS
     *
     * @param argc argument count
     * @param argv argument values
     */
    static void Initialize(int argc, char** argv, std::string const& name);

    /**
     * @brief Handler to handle signals.
     * @details This signal handler will release opendds resources and exit program or set bus running state to false
     * depending on sig number.
     * For the following signals this handler will set bus running state to false:
     * - SIGALRM
     * - SIGINT
     * - SIGKILL
     * - SIGPIPE
     * - SIGTERM
     *
     * For the following signals this handler will exit program and core dump may generated:
     * - SIGABRT
     * - SIGFPE
     * - SIGILL
     * - SIGQUIT
     * - SIGSEGV
     *
     * OpenddsBus won't register this handler automatically. It is user's responsibility to register this handler to
     * approperiate signals.
     *
     * @param sig signal number
     */
    static void SignalHandler(int sig);

    /**
     * @brief Create threads to handle event callbacks asynchronously.
     * @details For opendds the background event handler theads are managed by ACE Reactor. The number of threads is not
     * managed by user. The threads parameter won't take effect!
     *
     * @param threads Number of threads.
     */
    static void AsyncSpin(size_t threads)
    {
        std::thread runner{[threads] { DdsBus::Spin(threads); }};
        runner.detach();
    }

    /**
     * @brief Create threads to handle event callbacks. The program will be blocked.
     * @details For opendds the background event handler theads are managed by ACE Reactor. The number of threads is not
     * managed by user. The threads parameter won't take effect!
     *
     * @param threads Number of threads
     */
    static void Spin(size_t threads);

    /**
     * @brief Check if opendds bus is running
     *
     * @return True if opendds bus is in running state otherwise false
     */
    static bool IsRunning();

    /**
     * @brief non-portable method get domain participant
     *
     * @return pointer to the domain participant
     */
    DDS::DomainParticipant* NpGetParticipant() const noexcept
    {
        return participant_;
    }

protected:
    /**
     * @brief Convert integral data type to hex string.
     *
     * @tparam Scalar Type of integral scalar
     * @param data Data to convert
     * @param padding flag to indicate whether padding leading '0's.
     *
     * @return hex string
     */
    template <typename Scalar, typename std::enable_if<std::is_integral<Scalar>::value>::type* = nullptr>
    std::string hexString(Scalar data, bool padding = false)
    {
        static const char digits[] = "0123456789ABCDEF";

        std::string rc;
        size_t      i = sizeof(Scalar) * 2U - 1U;

        rc.reserve(sizeof(Scalar) * 2U);

        if (padding == false)
        {
            for (; i > 0U; --i)
            {
                uint8_t idx = (data >> (i * 4)) & 0x0f;
                if (idx != 0)
                {
                    rc.push_back(digits[idx]);
                    --i;
                    break;
                }
            }
        }

        for (; i > 0U; --i)
        {
            uint8_t idx = (data >> (i * 4)) & 0x0f;
            rc.push_back(digits[idx]);
        }
        uint8_t idx = (data)&0x0f;
        rc.push_back(digits[idx]);

        return rc;
    }

    /**
     * @brief Convert buffer data to hex string.
     *
     * @param data Pointer to data
     * @param size Size of buffer
     * @param padding flag to indicate whether padding leading '0's.
     *
     * @return hex string
     */
    std::string hexString(uint8_t const* data, size_t size, bool padding = false)
    {
        static const char digits[] = "0123456789ABCDEF";

        std::string rc;
        size_t      i = 0U;

        rc.reserve(size * 2U);

        if (padding == false)
        {
            for (; i < size * 2U - 1U; ++i)
            {
                uint8_t idx = (data[i / 2] >> ((i + 1) % 2 * 4)) & 0x0f;
                if (idx != 0U)
                {
                    rc.push_back(digits[idx]);
                    ++i;
                    break;
                }
            }
        }

        for (; i < size * 2U - 1U; ++i)
        {
            uint8_t idx = (data[i / 2] >> ((i + 1) % 2 * 4)) & 0x0f;
            rc.push_back(digits[idx]);
        }
        uint8_t idx = (data[size - 1U]) & 0x0f;
        rc.push_back(digits[idx]);

        return rc;
    }

    /**
     * @brief Create opendds datawriter with type_support and topic name
     *
     * @param type_support Opendds type support
     * @param topic_name Topic name with namespace
     *
     * @return Opendds datawriter
     */
    DDS::DataWriter* createOpenddsDataWriter(OpenDDS::DCPS::TypeSupportImpl* type_support,
                                             std::string const& topic_name, char const* type_name);

    /**
     * @brief Create opendds datareader with type_support, topic name and listener.
     *
     * @param type_support Opendds type support
     * @param topic_name Topic name with namespace
     * @param listener Opendds datareader listener
     *
     * @return Opendds datareader
     */
    DDS::DataReader* createOpenddsDataReader(OpenDDS::DCPS::TypeSupportImpl* type_support,
                                             std::string const& topic_name, char const* type_name,
                                             DDS::DataReaderListener* listener);

    std::string stripDelimiter(std::string const& topic)
    {
        std::string::size_type start = topic.find_first_not_of(NAMESPACE_DELIMITER);
        std::string::size_type end   = topic.find_last_not_of(NAMESPACE_DELIMITER);
        if ((start > end) || ((start == std::string::npos) && (end == std::string::npos)))
        {
            return std::string("");
        }
        else
        {
            return topic.substr(start, end - start + 1U);
        }
    }

    /**
     * @brief Insert namespace into a raw topic name
     *
     * @param topic Raw topic name
     *
     * @return Topic name with namespace(/namespace/topic)
     */
    std::string insertNamespace(std::string const& topic)
    {
        std::string strip_topic = stripDelimiter(topic);
        if (strip_topic.empty())
        {
            throw opendds_wrapper::exceptions::InvalidTopicNameException(topic);
        }
        if (topic[0] == NAMESPACE_DELIMITER)
        {
            return NAMESPACE_DELIMITER + strip_topic;
        }
        else
        {
            if (namespace_.empty())
            {
                return strip_topic;
            }
            else
            {
                return NAMESPACE_DELIMITER + namespace_ + NAMESPACE_DELIMITER + strip_topic;
            }
        }
    }

    /**
     * @brief Strip namespace from a full topic name
     *
     * @param full_topic Topic name with namespace
     *
     * @return Topic name stripped namespace
     */
    std::string stripNamespace(std::string const& full_topic)
    {
        if ((0 == std::strncmp(namespace_.c_str(), full_topic.c_str(), namespace_.size())) &&
            (full_topic[namespace_.size()] == NAMESPACE_DELIMITER))
        {
            return std::string(full_topic.begin() + namespace_.size(), full_topic.end());
        }
        return full_topic;
    }

private:
    DDS::DomainParticipant* participant_;  ///< OpenDDS DomainParticipant object.
    DDS::Publisher*         publisher_;    ///< OpenDDS Publisher object.
    DDS::Subscriber*        subscriber_;   ///< OpenDDS Subscriber object.
    std::string             namespace_;    ///< OpenDDS bus namespace.

    static const char                                NAMESPACE_DELIMITER = '/';
    static WaitSet                                   waitset_;
    static std::shared_ptr<holo::thread::ThreadPool> pool_sharedptr_;
};

using BusType = DdsBus;

}  // namespace opendds_wrapper

#endif
