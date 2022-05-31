/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file opendds_bus.h
 * @brief This header file defines OpenDDS wrapper object.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-07
 */

#include <opendds_wrapper/details/bus.h>

#include <map>
#include <unordered_map>
// TODO wrap system calls
#include <csignal>

#include "opendds_wrapper/details/exceptions.h"

namespace opendds_wrapper
{
static volatile bool                      g_opendds_is_running = false;
static std::string                        g_opendds_node_name  = std::string("");
WaitSet                                   DdsBus::waitset_{};
std::shared_ptr<holo::thread::ThreadPool> DdsBus::pool_sharedptr_{nullptr};

DdsBus::DdsBus(DDS::DomainId_t id, std::string const& ns)
  : participant_{}, publisher_{}, subscriber_{}, namespace_{stripDelimiter(ns)}
{
    DDS::DomainParticipantFactory* factory = TheParticipantFactory;
    if (nullptr == factory)
    {
        throw opendds_wrapper::exceptions::OpenddsInternalErrorException(
            "Failed to create domain participant factory!");
    }

    // Set user data qos
    DDS::DomainParticipantQos qos;
    factory->get_default_participant_qos(qos);
    qos.user_data.value.length(g_opendds_node_name.size());
    std::memcpy(&qos.user_data.value[0], g_opendds_node_name.c_str(), g_opendds_node_name.size());

    participant_ = factory->create_participant(id, qos, nullptr, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (nullptr == participant_)
    {
        throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to create domain participant!");
    }
    publisher_  = participant_->create_publisher(PUBLISHER_QOS_DEFAULT, nullptr, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    subscriber_ = participant_->create_subscriber(SUBSCRIBER_QOS_DEFAULT, nullptr, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if ((nullptr == publisher_) || (nullptr == subscriber_))
    {
        throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to create publisher and subscriber!");
    }
}

DdsBus::~DdsBus()
{
    // participant_->delete_publisher(publisher_);
    // participant_->delete_subscriber(subscriber_);
    participant_->delete_contained_entities();
    DDS::DomainParticipantFactory* factory = TheParticipantFactory;
    factory->delete_participant(participant_);
    TheServiceParticipant->shutdown();
}

void DdsBus::DeleteWriter(std::string const& topic_name)
{
    DDS::DataWriter*  writer = publisher_->lookup_datawriter(insertNamespace(topic_name).c_str());
    DDS::ReturnCode_t code;
    if (nullptr == writer)
    {
        throw opendds_wrapper::exceptions::NoSuchWriterException(topic_name);
    }
    DDS::Topic* topic = writer->get_topic();
    code              = participant_->delete_topic(topic);
    if (DDS::RETCODE_OK != code)
    {
        throw opendds_wrapper::exceptions::DeleteTopicErrorException(topic_name, code);
    }
    code = publisher_->delete_datawriter(writer);
    if (DDS::RETCODE_OK != code)
    {
        throw opendds_wrapper::exceptions::DeleteWriterErrorException(topic_name, code);
    }
}

void DdsBus::DeleteReader(std::string const& topic_name)
{
    DDS::DataReader* reader = subscriber_->lookup_datareader(insertNamespace(topic_name).c_str());
    if (nullptr == reader)
    {
        throw opendds_wrapper::exceptions::NoSuchReaderException(topic_name);
    }

    DDS::StatusCondition* status_condition = reader->get_statuscondition();
    if (nullptr == status_condition)
    {
        throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to get reader status condition");
    }

    waitset_.DeleteCallback(status_condition);
    waitset_.DeleteSchedule(status_condition);

    DDS::ReturnCode_t code;
    code = subscriber_->delete_datareader(reader);
    if (DDS::RETCODE_OK != code)
    {
        throw opendds_wrapper::exceptions::DeleteReaderErrorException(topic_name, code);
    }
}

std::vector<DdsBus::TopicDescriptionType> DdsBus::GetTopicList()
{
    std::vector<DdsBus::TopicDescriptionType> topics = {};

    DDS::Subscriber* bis = participant_->get_builtin_subscriber();
    if (nullptr == bis)
    {
        return topics;
    }

    DDS::TopicBuiltinTopicDataDataReader* reader =
        DDS::TopicBuiltinTopicDataDataReader::_narrow(bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_TOPIC_TOPIC));

    DDS::TopicBuiltinTopicDataSeq samples;
    DDS::SampleInfoSeq            infos;

    reader->read(samples, infos, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                 DDS::ANY_INSTANCE_STATE);

    using ITMap = std::unordered_map<DDS::InstanceHandle_t, DDS::TopicBuiltinTopicData*>;
    ITMap instance_map;

    for (size_t i = 0U; i < infos.length(); ++i)
    {
        ITMap::const_iterator it = instance_map.find(infos[i].instance_handle);
        if (infos[i].valid_data)
        {
            if (instance_map.end() == it)
            {
                instance_map[infos[i].instance_handle] = &samples[i];
            }
            else
            {
                std::cout << "duplicate instance " << infos[i].instance_handle << " detected" << std::endl;
            }
        }
        else
        {
            if (instance_map.end() == it)
            {
                std::cout << "Unknown instance " << infos[i].instance_handle << " deleted" << std::endl;
            }
            else
            {
                instance_map.erase(it);
            }
        }
    }

    using TNMap = std::map<std::string, std::string>;
    TNMap topic_map;

    for (ITMap::value_type& p : instance_map)
    {
        TNMap::const_iterator it = topic_map.find(std::string(p.second->name));
        if (topic_map.end() == it)
        {
            topic_map.emplace(std::make_pair(std::string(p.second->name), std::string(p.second->type_name)));
        }
        else
        {
            if (it->second != std::string(p.second->type_name))
            {
                std::cout << "inconsistant topic detected" << std::endl;
            }
        }
    }

    for (TNMap::value_type& p : topic_map)
    {
        DdsBus::TopicDescriptionType desc;
        desc.topic_name = p.first;
        desc.type_name  = p.second;
        topics.push_back(desc);
    }

    return topics;
}

std::vector<std::string> DdsBus::GetNodeList()
{
    std::vector<std::string> nodes = {};

    DDS::Subscriber* bis = participant_->get_builtin_subscriber();
    if (nullptr == bis)
    {
        return nodes;
    }

    DDS::ParticipantBuiltinTopicDataDataReader* reader = DDS::ParticipantBuiltinTopicDataDataReader::_narrow(
        bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_PARTICIPANT_TOPIC));

    DDS::ParticipantBuiltinTopicDataSeq samples;
    DDS::SampleInfoSeq                  infos;

    reader->read(samples, infos, DDS::LENGTH_UNLIMITED, DDS::ANY_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                 DDS::ANY_INSTANCE_STATE);

    using IPMap = std::unordered_map<DDS::InstanceHandle_t, DDS::ParticipantBuiltinTopicData*>;
    IPMap instance_map;

    for (size_t i = 0U; i < infos.length(); ++i)
    {
        IPMap::const_iterator it = instance_map.find(infos[i].instance_handle);
        if (infos[i].valid_data)
        {
            if (instance_map.end() == it)
            {
                instance_map[infos[i].instance_handle] = &samples[i];
            }
            else
            {
                std::cout << "duplicate instance " << infos[i].instance_handle << " detected" << std::endl;
            }
        }
        else
        {
            if (instance_map.end() == it)
            {
                std::cout << "Unknown instance " << infos[i].instance_handle << " deleted" << std::endl;
            }
            else
            {
                instance_map.erase(it);
            }
        }
    }

    for (IPMap::value_type& p : instance_map)
    {
        nodes.emplace_back(hexString(p.second->key.value[0]) + "." + hexString(p.second->key.value[1]) + "." +
                           hexString(p.second->key.value[2]));
    }

    return nodes;
}

std::string DdsBus::GetId()
{
    OpenDDS::DCPS::DomainParticipantImpl* participant =
        dynamic_cast<OpenDDS::DCPS::DomainParticipantImpl*>(participant_);

    OpenDDS::DCPS::GUID_t id = participant->get_id();
    return g_opendds_node_name + '-' + hexString(&id.guidPrefix[4U], 4U) + "-" + hexString(&id.guidPrefix[8U], 4U) +
           "-" + hexString(&id.entityId.entityKey[0U], 4U);
}

static void killOpendds()
{
    g_opendds_is_running = false;
    OpenDDS::DCPS::DomainParticipantFactoryImpl* factory =
        dynamic_cast<OpenDDS::DCPS::DomainParticipantFactoryImpl*>(TheParticipantFactory);
    OpenDDS::DCPS::DomainParticipantFactoryImpl::DPMap dpmap = factory->participants();
    std::cout << "Kill OpenDDS!" << std::endl;
    for (auto iter = dpmap.begin(); iter != dpmap.end(); ++iter)
    {
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2)
        {
            (*iter2)->delete_contained_entities();
            factory->delete_participant(iter2->in());
        }
    }
    TheServiceParticipant->shutdown();
}

void DdsBus::Initialize(int argc, char** argv, std::string const& name)
{
    static char const* const ARG_NAME              = "-DCPSConfigFile";
    static char const* const DCPS_CONFIG_FILE_PATH = "config/opendds_config.ini";

    DDS::DomainParticipantFactory* factory          = nullptr;
    bool                           config_specified = false;
    for (int i = 0; i < argc; ++i)
    {
        if (0 == strcmp(argv[i], "-DCPSConfigFile"))
        {
            int argnum       = argc - i > 2 ? 2 : argc - i;
            config_specified = true;
            factory          = TheParticipantFactoryWithArgs(argnum, &argv[i]);
            break;
        }
    }
    if (!config_specified)
    {
        int   argnum      = 2;
        char* argvalue[2] = {};

        char* holo_root = getenv("HOLO_ROOT");

        if (nullptr == holo_root)
        {
            std::cerr << "-DCPSConfigFile not specified and HOLO_ROOT environment variable not set!" << std::endl;
            std::cerr << "Unable to load configuration file for opendds. Program quit!" << std::endl;
            exit(-1);
        }

        argvalue[0] = const_cast<char*>(ARG_NAME);

        std::string args = std::string(holo_root) + '/' + std::string(DCPS_CONFIG_FILE_PATH);
        argvalue[1]      = const_cast<char*>(args.c_str());

        factory = TheParticipantFactoryWithArgs(argnum, argvalue);
    }

    if (nullptr == factory)
    {
        std::cerr << "Failed to create domain participant factory. Program quit!" << std::endl;
        exit(-1);
    }

    g_opendds_is_running = true;
    g_opendds_node_name  = NAMESPACE_DELIMITER + name;
}

void DdsBus::SignalHandler(int sig)
{
    switch (sig)
    {
        case SIGABRT:
        case SIGFPE:
        case SIGILL:
        case SIGQUIT:
        case SIGSEGV:
            killOpendds();
            signal(sig, SIG_DFL);
            raise(sig);
            break;
        case SIGALRM:
        case SIGHUP:
        case SIGINT:
        case SIGKILL:
        case SIGPIPE:
        case SIGTERM:
            g_opendds_is_running = false;
            if (pool_sharedptr_)
            {
                pool_sharedptr_->Pause();
            }
            break;
        default:
            return;
    }
}

bool DdsBus::IsRunning()
{
    return g_opendds_is_running;
}

void DdsBus::Spin(size_t threads)
{
    pool_sharedptr_ = std::make_shared<holo::thread::ThreadPool>(threads);

    DDS::ConditionSeq condition_seq;
    // condition_seq.maximum(64);  // FIXME condition_seq max size should depends on reader count

    while (g_opendds_is_running)
    {
        int32_t  sec{1};
        uint32_t nsec{0};

        DDS::ReturnCode_t retcode = waitset_.Wait(condition_seq, sec, nsec);

        if (retcode == DDS::RETCODE_TIMEOUT)
        {
            continue;
        }
        else if (retcode != DDS::RETCODE_OK)
        {
            throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to wait for WaitSet");
        }

        int condition_seq_len = condition_seq.length();

        for (int i = 0; i < condition_seq_len; ++i)
        {
            if (!waitset_.GetSchedule(condition_seq[i]))
            {
                waitset_.SetSchedule(condition_seq[i], true);
                try
                {
                    pool_sharedptr_->AddTask(waitset_.GetCallback(condition_seq[i]));
                }
                catch (std::runtime_error const& e)
                {
                    if (!g_opendds_is_running)
                        break;
                    else
                        throw e;
                }
                catch (holo::thread::TaskQueueIsFullException const& e)
                {
                    if (!g_opendds_is_running)
                        break;
                    else
                        throw e;
                }
                catch (holo::thread::ThreadPoolPauseStatusException const& e)
                {
                    if (!g_opendds_is_running)
                        break;
                    else
                        throw e;
                }
                catch (opendds_wrapper::exceptions::InvalidConditionException const& e)
                {
                    continue;
                }
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
    }

    pool_sharedptr_->WaitAndDestroy();
}

DDS::DataWriter* DdsBus::createOpenddsDataWriter(OpenDDS::DCPS::TypeSupportImpl* type_support,
                                                 std::string const& topic_name, char const* type_name)
{
    if (nullptr == type_support)
    {
        throw opendds_wrapper::exceptions::OpenddsInternalErrorException(
            std::string("Invalid type support impl for topic " + topic_name + " type name " + type_name));
    }

    DDS::ReturnCode_t code;

    char const* register_name = type_name;

    if (type_name == nullptr)
    {
        register_name = type_support->get_type_name();
    }

    code = type_support->register_type(participant_, register_name);
    if (DDS::RETCODE_OK != code)
    {
        throw opendds_wrapper::exceptions::TypeRegistrationFailedException(topic_name, register_name, code);
    }
    DDS::Topic* topic = participant_->create_topic(topic_name.c_str(), register_name, TOPIC_QOS_DEFAULT, nullptr,
                                                   OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (type_name == nullptr)
    {
        delete[] register_name;
    }

    if (nullptr == topic)
    {
        throw opendds_wrapper::exceptions::CreateTopicFailedException(topic_name);
    }
    DDS::DataWriter* writer =
        publisher_->create_datawriter(topic, DATAWRITER_QOS_DEFAULT, nullptr, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (nullptr == writer)
    {
        throw opendds_wrapper::exceptions::CreateWriterFailedException(topic_name);
    }
    return writer;
}

DDS::DataReader* DdsBus::createOpenddsDataReader(OpenDDS::DCPS::TypeSupportImpl* type_support,
                                                 std::string const& topic_name, char const* type_name,
                                                 DDS::DataReaderListener* listener)
{
    if (nullptr == type_support)
    {
        throw opendds_wrapper::exceptions::OpenddsInternalErrorException(
            std::string("Invalid type support impl for topic " + topic_name + " type name " + type_name));
    }

    DDS::ReturnCode_t code;

    char const* register_name = type_name;

    if (type_name == nullptr)
    {
        register_name = type_support->get_type_name();
    }

    code = type_support->register_type(participant_, register_name);
    if (DDS::RETCODE_OK != code)
    {
        throw opendds_wrapper::exceptions::TypeRegistrationFailedException(topic_name, register_name, code);
    }

    DDS::Topic* topic = participant_->create_topic(topic_name.c_str(), register_name, TOPIC_QOS_DEFAULT, nullptr,
                                                   OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (type_name == nullptr)
    {
        delete[] register_name;
    }

    if (nullptr == topic)
    {
        throw opendds_wrapper::exceptions::CreateTopicFailedException(topic_name);
    }

    DDS::DataReaderQos dr_qos;
    subscriber_->get_default_datareader_qos(dr_qos);
    dr_qos.history.kind  = DDS::KEEP_LAST_HISTORY_QOS;
    dr_qos.history.depth = 64;

    DDS::DataReader* reader =
        subscriber_->create_datareader(topic, dr_qos, listener, OpenDDS::DCPS::DEFAULT_STATUS_MASK);
    if (nullptr == reader)
    {
        throw opendds_wrapper::exceptions::CreateReaderFailedException(topic_name);
    }
    return reader;
}

}  // namespace opendds_wrapper
