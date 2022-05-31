/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file monitor.cpp
 * @brief This file tests and demonstrates how to monitor opendds bus.
 * @author Zhang Jiannan(zhangjiannan@holomaitc.com)
 * @date 2020-07-12
 */

#include <iostream>
#include <opendds_wrapper/opendds_bus.h>

using BusType = opendds_wrapper::DdsBus;

void ShowBuiltInParticipantChanges(DDS::DataReader* dr)
{
    std::cout << "Checking participant bit data" << std::endl;
    DDS::ParticipantBuiltinTopicDataDataReader* reader = DDS::ParticipantBuiltinTopicDataDataReader::_narrow(dr);
    DDS::ParticipantBuiltinTopicDataSeq         samples;
    DDS::SampleInfoSeq                          infos;
    reader->read(samples, infos, DDS::LENGTH_UNLIMITED, DDS::NOT_READ_SAMPLE_STATE,
                                         DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);

    std::cout << infos.length() << " sample infos read" << std::endl;
    for (size_t i = 0; i < infos.length(); ++i)
    {
        std::cout << "sample info #" << i << std::endl;
        std::cout << "SampleState: " << infos[i].sample_state << std::endl;
        std::cout << "ViewState: " << infos[i].view_state << std::endl;
        std::cout << "InstanceState: " << infos[i].instance_state << std::endl;
        std::cout << "Disposed_generation_count: " << infos[i].disposed_generation_count << std::endl;
        std::cout << "No_writers_generation_count: " << infos[i].no_writers_generation_count << std::endl;
        std::cout << "Sample_rank: " << infos[i].sample_rank << std::endl;
        std::cout << "Generation_rank: " << infos[i].generation_rank << std::endl;
        std::cout << "Absolute_generation_rank: " << infos[i].absolute_generation_rank << std::endl;
        std::cout << "Source_timestamp: " << infos[i].source_timestamp.sec << "." << infos[i].source_timestamp.nanosec
                  << std::endl;
        std::cout << "instance_handle: " << infos[i].instance_handle << std::endl;
        std::cout << "valid_data: " << infos[i].valid_data << std::endl;

        if (infos[i].valid_data)
        {
            std::cout << "\tsample:" << std::endl;
            std::cout << "\tKey: " << std::hex << samples[i].key.value[0] << "." << samples[i].key.value[1] << "."
                      << samples[i].key.value[2] << std::endl;
            std::cout << "\tuser_data: ";
            for (size_t j = 0; j < samples[i].user_data.value.length(); ++j)
            {
                std::cout << samples[i].user_data.value[j] << ",";
            }
            std::cout << std::dec << std::endl;
        }

        std::cout << std::endl;
    }
    reader->return_loan(samples, infos);
}

void ShowBuiltInTopicChanges(DDS::DataReader* dr)
{
    std::cout << "Checking topic bit data" << std::endl;
    DDS::TopicBuiltinTopicDataDataReader* reader = DDS::TopicBuiltinTopicDataDataReader::_narrow(dr);
    DDS::TopicBuiltinTopicDataSeq         samples;
    DDS::SampleInfoSeq                    infos;
    reader->read(samples, infos, DDS::LENGTH_UNLIMITED, DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);

    std::cout << infos.length() << " sample infos read" << std::endl;
    for (size_t i = 0; i < infos.length(); ++i)
    {
        std::cout << "sample info #" << i << std::endl;
        std::cout << "SampleState: " << infos[i].sample_state << std::endl;
        std::cout << "ViewState: " << infos[i].view_state << std::endl;
        std::cout << "InstanceState: " << infos[i].instance_state << std::endl;
        std::cout << "Disposed_generation_count: " << infos[i].disposed_generation_count << std::endl;
        std::cout << "No_writers_generation_count: " << infos[i].no_writers_generation_count << std::endl;
        std::cout << "Sample_rank: " << infos[i].sample_rank << std::endl;
        std::cout << "Generation_rank: " << infos[i].generation_rank << std::endl;
        std::cout << "Absolute_generation_rank: " << infos[i].absolute_generation_rank << std::endl;
        std::cout << "Source_timestamp: " << infos[i].source_timestamp.sec << "." << infos[i].source_timestamp.nanosec
                  << std::endl;
        std::cout << "instance_handle: " << infos[i].instance_handle << std::endl;
        std::cout << "valid_data: " << infos[i].valid_data << std::endl;

        if (infos[i].valid_data)
        {
            std::cout << "\tsample:" << std::endl;
            std::cout << "\tKey: " << std::hex << samples[i].key.value[0] << "." << samples[i].key.value[1] << "."
                      << samples[i].key.value[2] << std::dec << std::endl;
            std::cout << "\tTopicName: " << samples[i].name << std::endl;
            std::cout << "\tTopicType: " << samples[i].type_name << std::endl;
        }

        std::cout << std::endl;
    }
    reader->return_loan(samples, infos);
}

void ShowBuiltInPublicationChanges(DDS::DataReader* dr)
{
    std::cout << "Checking publication bit data" << std::endl;
    DDS::PublicationBuiltinTopicDataDataReader* reader = DDS::PublicationBuiltinTopicDataDataReader::_narrow(dr);
    DDS::PublicationBuiltinTopicDataSeq         samples;
    DDS::SampleInfoSeq                          infos;
    reader->read(samples, infos, DDS::LENGTH_UNLIMITED, DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);

    std::cout << infos.length() << " sample infos read" << std::endl;
    for (size_t i = 0; i < infos.length(); ++i)
    {
        std::cout << "sample info #" << i << std::endl;
        std::cout << "SampleState: " << infos[i].sample_state << std::endl;
        std::cout << "ViewState: " << infos[i].view_state << std::endl;
        std::cout << "InstanceState: " << infos[i].instance_state << std::endl;
        std::cout << "Disposed_generation_count: " << infos[i].disposed_generation_count << std::endl;
        std::cout << "No_writers_generation_count: " << infos[i].no_writers_generation_count << std::endl;
        std::cout << "Sample_rank: " << infos[i].sample_rank << std::endl;
        std::cout << "Generation_rank: " << infos[i].generation_rank << std::endl;
        std::cout << "Absolute_generation_rank: " << infos[i].absolute_generation_rank << std::endl;
        std::cout << "Source_timestamp: " << infos[i].source_timestamp.sec << "." << infos[i].source_timestamp.nanosec
                  << std::endl;
        std::cout << "instance_handle: " << infos[i].instance_handle << std::endl;
        std::cout << "valid_data: " << infos[i].valid_data << std::endl;

        if (infos[i].valid_data)
        {
            std::cout << "\tsample:" << std::endl;
            std::cout << "\tKey: " << std::hex << samples[i].key.value[0] << "." << samples[i].key.value[1] << "."
                      << samples[i].key.value[2] << std::endl;
            std::cout << "\tParticipantKey: " << samples[i].participant_key.value[0] << "."
                      << samples[i].participant_key.value[1] << "." << samples[i].participant_key.value[2] << std::dec
                      << std::endl;
            std::cout << "\tTopicName: " << samples[i].topic_name << std::endl;
            std::cout << "\tTopicType: " << samples[i].type_name << std::endl;
        }

        std::cout << std::endl;
    }
    reader->return_loan(samples, infos);
}

void ShowBuiltInSubscriptionChanges(DDS::DataReader* dr)
{
    std::cout << "Checking subscription bit data" << std::endl;
    DDS::SubscriptionBuiltinTopicDataDataReader* reader = DDS::SubscriptionBuiltinTopicDataDataReader::_narrow(dr);
    DDS::SubscriptionBuiltinTopicDataSeq         samples;
    DDS::SampleInfoSeq                           infos;
    reader->read(samples, infos, DDS::LENGTH_UNLIMITED, DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE, DDS::ANY_INSTANCE_STATE);

    std::cout << infos.length() << " sample infos read" << std::endl;
    for (size_t i = 0; i < infos.length(); ++i)
    {
        std::cout << "sample info #" << i << std::endl;
        std::cout << "SampleState: " << infos[i].sample_state << std::endl;
        std::cout << "ViewState: " << infos[i].view_state << std::endl;
        std::cout << "InstanceState: " << infos[i].instance_state << std::endl;
        std::cout << "Disposed_generation_count: " << infos[i].disposed_generation_count << std::endl;
        std::cout << "No_writers_generation_count: " << infos[i].no_writers_generation_count << std::endl;
        std::cout << "Sample_rank: " << infos[i].sample_rank << std::endl;
        std::cout << "Generation_rank: " << infos[i].generation_rank << std::endl;
        std::cout << "Absolute_generation_rank: " << infos[i].absolute_generation_rank << std::endl;
        std::cout << "Source_timestamp: " << infos[i].source_timestamp.sec << "." << infos[i].source_timestamp.nanosec
                  << std::endl;
        std::cout << "instance_handle: " << infos[i].instance_handle << std::endl;
        std::cout << "valid_data: " << infos[i].valid_data << std::endl;

        if (infos[i].valid_data)
        {
            std::cout << "\tsample:" << std::endl;
            std::cout << "\tKey: " << std::hex << samples[i].key.value[0] << "." << samples[i].key.value[1] << "."
                      << samples[i].key.value[2] << std::endl;
            std::cout << "\tParticipantKey: " << samples[i].participant_key.value[0] << "."
                      << samples[i].participant_key.value[1] << "." << samples[i].participant_key.value[2] << std::dec
                      << std::endl;
            std::cout << "\tTopicName: " << samples[i].topic_name << std::endl;
            std::cout << "\tTopicType: " << samples[i].type_name << std::endl;
        }

        std::cout << std::endl;
    }
    reader->return_loan(samples, infos);
}

int main(int argc, char** argv)
{
    BusType::Initialize(argc, argv, "monitor");
    signal(SIGINT, BusType::SignalHandler);
    BusType bus(100, std::string("Data"));

    OpenDDS::DCPS::DomainParticipantImpl* participant =
        dynamic_cast<OpenDDS::DCPS::DomainParticipantImpl*>(bus.GetParticipant());

    std::cout << "Bus name = " << bus.GetId() << std::endl;

    DDS::WaitSet          ws;
    DDS::ReturnCode_t     retcode;
    DDS::Subscriber*      bis       = participant->get_builtin_subscriber();
    DDS::StatusCondition* condition = bis->get_statuscondition();
    ws.attach_condition(condition);

    while (BusType::IsRunning())
    {
        DDS::ConditionSeq conditions;
        retcode = ws.wait(conditions, DDS::Duration_t{10, 0});
        if (DDS::RETCODE_TIMEOUT == retcode)
        {
            auto tlist = bus.GetTopicList();
            for (auto& topic_desc : tlist)
            {
                std::cout << "topic_name: " << topic_desc.topic_name << std::endl
                          << "topic_type: " << topic_desc.type_name << std::endl
                          << std::endl;
            }

            auto plist = bus.GetNodeList();
            for (auto& name : plist)
            {
                std::cout << "node id: " << name << std::endl;
            }
            continue;
        }
        if (DDS::RETCODE_OK == retcode)
        {
            std::cout << "#############################################################################" << std::endl;
            DDS::DataReader* participant_reader = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_PARTICIPANT_TOPIC);
            std::cout << "parcitipant_reader status change = " << participant_reader->get_status_changes() << std::endl;
            ShowBuiltInParticipantChanges(participant_reader);

            std::cout << "----------------" << std::endl;
            DDS::DataReader* topic_reader = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_TOPIC_TOPIC);
            std::cout << "topic_reader status change = " << topic_reader->get_status_changes() << std::endl;
            ShowBuiltInTopicChanges(topic_reader);
            std::cout << "----------------" << std::endl;

            DDS::DataReader* subscription_reader = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_SUBSCRIPTION_TOPIC);
            std::cout << "subscription_reader status change = " << subscription_reader->get_status_changes()
                      << std::endl;
            ShowBuiltInSubscriptionChanges(subscription_reader);
            std::cout << "----------------" << std::endl;

            DDS::DataReader* publication_reader = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_PUBLICATION_TOPIC);
            std::cout << "publication_reader status change = " << publication_reader->get_status_changes() << std::endl;
            ShowBuiltInPublicationChanges(publication_reader);
        }
    }

    return 0;
}
