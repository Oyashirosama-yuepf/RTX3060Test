#ifndef STORAGE_H_
#define STORAGE_H_

#include <opendds_wrapper/opendds_bus.h>
#include <dds/DCPS/GuidConverter.h>

#include <map>
#include <mutex>

#include "Description.h"

class Storage
{
public:
    using GuidType = OpenDDS::DCPS::GUID_t;

    Storage(opendds_wrapper::DdsBus& bus)
      : dpi_(dynamic_cast<OpenDDS::DCPS::DomainParticipantImpl*>(bus.NpGetParticipant()))
    {
    }

    void Process()
    {
        DDS::WaitSet          ws;
        DDS::ReturnCode_t     retcode;
        DDS::Subscriber*      bis       = dpi_->get_builtin_subscriber();
        DDS::StatusCondition* condition = bis->get_statuscondition();
        ws.attach_condition(condition);

        DDS::DataReader* participant_reader  = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_PARTICIPANT_TOPIC);
        DDS::DataReader* topic_reader        = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_TOPIC_TOPIC);
        DDS::DataReader* subscription_reader = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_SUBSCRIPTION_TOPIC);
        DDS::DataReader* publication_reader  = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_PUBLICATION_TOPIC);

        while (true)
        {
            DDS::ConditionSeq conditions;
            retcode = ws.wait(conditions, DDS::Duration_t{10, 0});

            if (DDS::RETCODE_TIMEOUT == retcode)
            {
                continue;
            }

            if (DDS::RETCODE_OK == retcode)
            {
                if (participant_reader->get_status_changes())
                {
                    ParticipantChangeHandler(participant_reader);
                }

                if (topic_reader->get_status_changes())
                {
                    TopicChangeHandler(topic_reader);
                }

                if (subscription_reader->get_status_changes())
                {
                    SubscriptionChangeHandler(subscription_reader);
                }

                if (publication_reader->get_status_changes())
                {
                    PublicationChangeHandler(publication_reader);
                }
            }
        }
    }

    void ProcessOnce()
    {
        DDS::Subscriber*      bis       = dpi_->get_builtin_subscriber();

        DDS::DataReader* participant_reader  = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_PARTICIPANT_TOPIC);
        DDS::DataReader* topic_reader        = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_TOPIC_TOPIC);
        DDS::DataReader* subscription_reader = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_SUBSCRIPTION_TOPIC);
        DDS::DataReader* publication_reader  = bis->lookup_datareader(OpenDDS::DCPS::BUILT_IN_PUBLICATION_TOPIC);

        if (participant_reader->get_status_changes())
        {
            ParticipantChangeHandler(participant_reader);
        }

        if (topic_reader->get_status_changes())
        {
            TopicChangeHandler(topic_reader);
        }

        if (subscription_reader->get_status_changes())
        {
            SubscriptionChangeHandler(subscription_reader);
        }

        if (publication_reader->get_status_changes())
        {
            PublicationChangeHandler(publication_reader);
        }
    }

    void GetParticipantDescriptions(TopologyDescription& topo)
    {
        lock_.lock();
        topo.Value() = "Participants";
        topo.Childs().clear();
        for (auto const& v : participant_data_)
        {
            std::string node_name;
            if(v.second.data.user_data.value.length() == 0)
            {
                node_name = "anonymous";
            }
            else
            {
                node_name = reinterpret_cast<char const*>(&v.second.data.user_data.value[0]);
            }
            node_name += " (" + std::string(OpenDDS::DCPS::GuidConverter(v.first)) + ")";
            topo.Childs().emplace_back(node_name);
            auto& pnode = topo.Childs().back();
            pnode.Childs().emplace_back("writers");
            auto& wnode = pnode.Childs().back();
            for (auto const& wid : v.second.writers)
            {
                wnode.Childs().emplace_back(std::string(publication_data_[wid].topic_name.in()) + " (" +
                                            std::string(publication_data_[wid].type_name.in()) + ')');
            }
            pnode.Childs().emplace_back("readers");
            auto& rnode = pnode.Childs().back();
            for (auto const& rid : v.second.readers)
            {
                rnode.Childs().emplace_back(std::string(subscription_data_[rid].topic_name.in()) + " (" +
                                            std::string(subscription_data_[rid].type_name.in()) + ')');
            }
        }
        lock_.unlock();
    }

    void GetTopicDescriptions(TopologyDescription& topo)
    {
        lock_.lock();
        topo.Value() = "Topics";
        topo.Childs().clear();
        for (auto const& t : topic_data_)
        {
            topo.Childs().emplace_back(std::string(t.second.name.in()) + " (" + std::string(t.second.type_name.in()) +
                                       ')' + " (" + std::string(OpenDDS::DCPS::GuidConverter(t.first)) + ')');
        }
        lock_.unlock();
    }

protected:
    struct ParticipantNode
    {
        DDS::ParticipantBuiltinTopicData                     data;
        std::set<GuidType, OpenDDS::DCPS::GUID_tKeyLessThan> writers;
        std::set<GuidType, OpenDDS::DCPS::GUID_tKeyLessThan> readers;
    };

    GuidType bitParticipantGuid(DDS::BuiltinTopicKey_t key)
    {
        return OpenDDS::DCPS::bit_key_to_repo_id(key);
    }

    GuidType bitTopicGuid(DDS::BuiltinTopicKey_t key)
    {
        return OpenDDS::DCPS::bit_key_to_repo_id(key);
    }

    GuidType bitPublicationGuid(DDS::BuiltinTopicKey_t key)
    {
        return OpenDDS::DCPS::bit_key_to_repo_id(key);
    }

    GuidType bitSubscriptionGuid(DDS::BuiltinTopicKey_t key)
    {
        return OpenDDS::DCPS::bit_key_to_repo_id(key);
    }

    GuidType InstanceToGuid(DDS::InstanceHandle_t handle)
    {
        return dpi_->get_repoid(handle);
    }

    void ParticipantChangeHandler(DDS::DataReader* dr)
    {
        DDS::ParticipantBuiltinTopicDataDataReader* reader = DDS::ParticipantBuiltinTopicDataDataReader::_narrow(dr);
        DDS::ParticipantBuiltinTopicDataSeq         samples;
        DDS::SampleInfoSeq                          infos;
        reader->read(samples, infos, DDS::LENGTH_UNLIMITED, DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                     DDS::ANY_INSTANCE_STATE);

        lock_.lock();
        for (size_t i = 0; i < infos.length(); ++i)
        {
            if (infos[i].valid_data)
            {
                // New participant
                GuidType id = bitParticipantGuid(samples[i].key);
                if (participant_data_.find(id) == participant_data_.end())
                {
                    ParticipantNode node;
                    node.data             = samples[i];
                    node.writers          = {};
                    node.readers          = {};
                    participant_data_[id] = std::move(node);
                }
                else
                {
                    std::cerr << "Unable to add participant. Participant GUID: "
                              << std::string(OpenDDS::DCPS::GuidConverter(id)) << " already discovered!" << std::endl;
                }
            }
            else
            {
                // participant removed
                GuidType id = InstanceToGuid(infos[i].instance_handle);
                if (participant_data_.find(id) == participant_data_.end())
                {
                    std::cerr << "Unable to remove participant. Participant GUID: "
                              << std::string(OpenDDS::DCPS::GuidConverter(id)) << " is not discovered!" << std::endl;
                }
                else
                {
                    participant_data_.erase(id);
                }
            }
        }
        lock_.unlock();
        reader->return_loan(samples, infos);
    }

    void TopicChangeHandler(DDS::DataReader* dr)
    {
        DDS::TopicBuiltinTopicDataDataReader* reader = DDS::TopicBuiltinTopicDataDataReader::_narrow(dr);
        DDS::TopicBuiltinTopicDataSeq         samples;
        DDS::SampleInfoSeq                    infos;
        reader->read(samples, infos, DDS::LENGTH_UNLIMITED, DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                     DDS::ANY_INSTANCE_STATE);

        lock_.lock();
        for (size_t i = 0; i < infos.length(); ++i)
        {
            if (infos[i].valid_data)
            {
                GuidType id = bitTopicGuid(samples[i].key);
                if (topic_data_.find(id) == topic_data_.end())
                {
                    topic_data_[id] = samples[i];
                }
                else
                {
                    std::cerr << "Unable to add topic. Topic GUID: " << std::string(OpenDDS::DCPS::GuidConverter(id))
                              << " already discovered!" << std::endl;
                }
            }
            else
            {
                GuidType id = InstanceToGuid(infos[i].instance_handle);
                if (topic_data_.find(id) == topic_data_.end())
                {
                    std::cerr << "Unable to remove topic. Topic GUID: " << std::string(OpenDDS::DCPS::GuidConverter(id))
                              << " is not discovered!" << std::endl;
                }
                else
                {
                    topic_data_.erase(id);
                }
            }
        }
        lock_.unlock();
        reader->return_loan(samples, infos);
    }

    void PublicationChangeHandler(DDS::DataReader* dr)
    {
        DDS::PublicationBuiltinTopicDataDataReader* reader = DDS::PublicationBuiltinTopicDataDataReader::_narrow(dr);
        DDS::PublicationBuiltinTopicDataSeq         samples;
        DDS::SampleInfoSeq                          infos;
        reader->read(samples, infos, DDS::LENGTH_UNLIMITED, DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                     DDS::ANY_INSTANCE_STATE);

        lock_.lock();
        for (size_t i = 0; i < infos.length(); ++i)
        {
            if (infos[i].valid_data)
            {
                GuidType id     = bitPublicationGuid(samples[i].key);
                GuidType par_id = bitParticipantGuid(samples[i].participant_key);
                if (publication_data_.find(id) == publication_data_.end())
                {
                    publication_data_[id] = samples[i];
                    if (participant_data_.find(par_id) != participant_data_.end())
                    {
                        participant_data_[par_id].writers.emplace(id);
                    }
                }
                else
                {
                    std::cerr << "Unable to add data writer. Writer GUID: "
                              << std::string(OpenDDS::DCPS::GuidConverter(id)) << " already discovered!" << std::endl;
                }
            }
            else
            {
                GuidType id = InstanceToGuid(infos[i].instance_handle);
                if (publication_data_.find(id) == publication_data_.end())
                {
                    std::cerr << "Unable to remove data writer. Writer GUID: "
                              << std::string(OpenDDS::DCPS::GuidConverter(id)) << " is not discovered!" << std::endl;
                }
                else
                {
                    publication_data_.erase(id);
                }
            }
        }
        lock_.unlock();
        reader->return_loan(samples, infos);
    }

    void SubscriptionChangeHandler(DDS::DataReader* dr)
    {
        DDS::SubscriptionBuiltinTopicDataDataReader* reader = DDS::SubscriptionBuiltinTopicDataDataReader::_narrow(dr);
        DDS::SubscriptionBuiltinTopicDataSeq         samples;
        DDS::SampleInfoSeq                           infos;
        reader->read(samples, infos, DDS::LENGTH_UNLIMITED, DDS::NOT_READ_SAMPLE_STATE, DDS::ANY_VIEW_STATE,
                     DDS::ANY_INSTANCE_STATE);

        lock_.lock();
        for (size_t i = 0; i < infos.length(); ++i)
        {
            if (infos[i].valid_data)
            {
                GuidType id     = bitSubscriptionGuid(samples[i].key);
                GuidType par_id = bitParticipantGuid(samples[i].participant_key);
                if (subscription_data_.find(id) == subscription_data_.end())
                {
                    subscription_data_[id] = samples[i];
                    if (participant_data_.find(par_id) != participant_data_.end())
                    {
                        participant_data_[par_id].readers.emplace(id);
                    }
                }
                else
                {
                    std::cerr << "Unable to add data reader. Reader GUID: "
                              << std::string(OpenDDS::DCPS::GuidConverter(id)) << " already discovered!" << std::endl;
                }
            }
            else
            {
                GuidType id = InstanceToGuid(infos[i].instance_handle);
                if (subscription_data_.find(id) == subscription_data_.end())
                {
                    std::cerr << "Unable to remove data reader. Reader GUID: "
                              << std::string(OpenDDS::DCPS::GuidConverter(id)) << " is not discovered!" << std::endl;
                }
                else
                {
                    subscription_data_.erase(id);
                }
            }
        }
        lock_.unlock();
        reader->return_loan(samples, infos);
    }

private:
    OpenDDS::DCPS::DomainParticipantImpl* dpi_;

    std::map<GuidType, ParticipantNode, OpenDDS::DCPS::GUID_tKeyLessThan>                   participant_data_;
    std::map<GuidType, DDS::TopicBuiltinTopicData, OpenDDS::DCPS::GUID_tKeyLessThan>        topic_data_;
    std::map<GuidType, DDS::PublicationBuiltinTopicData, OpenDDS::DCPS::GUID_tKeyLessThan>  publication_data_;
    std::map<GuidType, DDS::SubscriptionBuiltinTopicData, OpenDDS::DCPS::GUID_tKeyLessThan> subscription_data_;

    mutable std::mutex lock_;
};

#endif
