/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file umb_interface.h
 * @brief define the umb interface class
 * @author liuya<liuya@holomatic.com>
 * @date 2020-11-23
 */

#ifndef HOLO_SENSORS_CMW_APP_INTERFACE_UMB_INTERFACE_H
#define HOLO_SENSORS_CMW_APP_INTERFACE_UMB_INTERFACE_H

#include <holo/sensors/common/interface.h>
#include <holo/sensors/umb/umb.h>
#include <holo/utils/yaml.h>
#include <holo_c/core/types.h>
#include <semaphore.h>

#include <condition_variable>
#include <functional>
#include <mutex>
#include <stdexcept>
#include <thread>

namespace holo
{
namespace sensors
{
namespace interface
{
using holo::sensors::common::InterfaceT;

struct UmbInterfaceParam
{
    uint32_t domain_id;
    uint32_t topic_id;
};

template <typename T>
class UmbInterface : public InterfaceT<T>
{
public:
    UmbInterface() = delete;
    UmbInterface(const UmbInterfaceParam& param) : inst_id_(0), running_(true)
    {
        try
        {
            Init(param);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "umb interface constructor failed: " << e.what();
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }
    }
    UmbInterface(const holo::yaml::Node& node) : inst_id_(0), running_(true)
    {
        UmbInterfaceParam param;
        param.domain_id = node["domain_id"].as<uint32_t>();
        param.topic_id  = node["topic_id"].as<uint32_t>();

        LOG(INFO) << "domain_id = " << param.domain_id;
        LOG(INFO) << "topic_id = " << param.topic_id;

        try
        {
            Init(param);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "umb interface constructor failed: " << e.what();
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }
    }
    ~UmbInterface()
    {
        running_ = false;
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
    }

private:
    static int umb_callback(umb_inst_id_t inst_id, umb_msgbuff_t* data, umb_timestamp_t* stamp, void* param)
    {
        (void)inst_id;
        (void)stamp;
        (void)param;

        memcpy(umb_data, data->buff, data->len);
        umb_length = data->len;

        sem_post(&semaphore_);

        return 0;
    }

    void Init(const UmbInterfaceParam& param)
    {
        (void)param;
        umb_errcode_e ret = (umb_errcode_e)0;

        umb_init(NULL, NULL);
        sem_init(&semaphore_, 0, 0);

        ret = umb_sub_reg(&inst_id_, param.domain_id, param.topic_id, umb_callback, NULL);

        if (ret != UMB_ERRCODE_OK)
        {
            LOG(INFO) << "umb sub register failed";
            throw std::runtime_error("umb sub register failed");
        }
        else
        {
            /* cteate thread */
            std::function<void()> handler = std::bind(&UmbInterface<T>::Thread, this);
            thread_                       = std::make_shared<std::thread>(handler);
        }
    }

    void Thread()
    {
        while (running_)
        {
            struct timespec ts;

            ts.tv_sec  = 1;
            ts.tv_nsec = 0;

            if (sem_timedwait(&semaphore_, &ts) == 0)
            {
                InterfaceT<T>::ParseData(umb_data, umb_length);
            }
        }
    }

private:
    umb_inst_id_t                inst_id_;
    std::shared_ptr<std::thread> thread_;
    bool                         running_;

private:
    static uint8_t  umb_data[1400];
    static uint32_t umb_length;

    static sem_t semaphore_;
};

template <typename T>
uint8_t UmbInterface<T>::umb_data[1400];

template <typename T>
uint32_t UmbInterface<T>::umb_length;

template <typename T>
sem_t UmbInterface<T>::semaphore_;

}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif
