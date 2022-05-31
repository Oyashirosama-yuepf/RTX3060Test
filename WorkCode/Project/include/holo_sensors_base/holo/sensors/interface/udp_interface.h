/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file udp_interface.h
 * @brief define the udp interface class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-07-28
 */

#ifndef HOLO_SENSORS_CMW_APP_INTERFACE_UDP_INTERFACE_H
#define HOLO_SENSORS_CMW_APP_INTERFACE_UDP_INTERFACE_H

#include <functional>
#include <mutex>
#include <thread>

#include <holo/sensors/common/interface.h>
#include <holo/sensors/interface/holo_socket/udp_server.h>
#include <holo/thread/sync_queue.h>
#include <holo/utils/yaml.h>
#include <holo_c/core/types.h>

namespace holo
{
namespace sensors
{
namespace interface
{
using holo::sensors::common::InterfaceT;

#ifndef HOLO_SENSORS_INTERFACE_SOCKET_ADDR
#define HOLO_SENSORS_INTERFACE_SOCKET_ADDR
struct SocketAddr
{
    std::string ip;
    uint16_t    port;
};
#endif

struct UdpInterfaceParam
{
public:
    UdpInterfaceParam() = default;
    UdpInterfaceParam(const holo::yaml::Node& node)
    {
        std::string type = node["type"].as<std::string>();
        if (type != std::string("udp"))
        {
            std::ostringstream oss;
            oss << "udp interface params found invalid type: " << type;
            LOG(ERROR) << oss.str();
            throw std::invalid_argument(oss.str());
        }
        addr.ip   = node["ip"].as<std::string>();
        addr.port = node["port"].as<uint16_t>();
        timeout   = node["timeout"].as<int32_t>();
    }

public:
    SocketAddr addr;
    int32_t    timeout;
};

template <typename T>
class UdpInterface : public InterfaceT<T>
{
public:
    UdpInterface() = delete;
    UdpInterface(const UdpInterfaceParam& param, bool is_async = false, uint32_t task_count = 1000)
      : running_(true), is_async_(is_async), idle_buffer_(task_count), task_queue_(task_count)
    {
        Init(param);
    }
    UdpInterface(const holo::yaml::Node& node, bool is_async = false, uint32_t task_count = 1000)
      : running_(true), is_async_(is_async), idle_buffer_(task_count), task_queue_(task_count)
    {
        UdpInterfaceParam param;
        param.addr.ip   = node["ip"].as<std::string>();
        param.addr.port = node["port"].as<uint16_t>();
        param.timeout   = node["timeout"].as<int32_t>();
        LOG(INFO) << "address = " << param.addr.ip << ":" << static_cast<uint32_t>(param.addr.port)
                  << ", timeout = " << param.timeout;
        Init(param);
    }

    int32_t Send(const uint8_t* buffer, uint32_t size, const struct sockaddr_in* addr)
    {
        std::lock_guard<std::mutex> guard(tmutex_);
        return socket_->Send(buffer, size, addr);
    }

    int32_t Send(const T& data, const struct sockaddr_in* addr)
    {
        uint32_t size = data.GetSerializedSize();
        uint8_t  tdata[size];
        (void)std::memset(tdata, 0, sizeof(tdata));
        uint32_t                    tsize = data.Serialize(tdata, sizeof(tdata));
        std::lock_guard<std::mutex> guard(tmutex_);
        return socket_->Send(tdata, tsize, addr);
    }

    ~UdpInterface()
    {
        running_ = false;
        if (recv_thread_ && recv_thread_->joinable())
        {
            recv_thread_->join();
        }
        if (parse_thread_ && parse_thread_->joinable())
        {
            parse_thread_->join();
        }
        idle_buffer_.BreakWait();
        task_queue_.BreakWait();
    }

    size_t GetIdleBufferCount() noexcept
    {
        return idle_buffer_.Size();
    }

    size_t GetTaskQueueCount() noexcept
    {
        return task_queue_.Size();
    }

private:
    void Init(const UdpInterfaceParam& param)
    {
        try
        {
            socket_ = std::make_shared<HoloSocketUdpServer>(param.addr.ip, param.addr.port, param.timeout);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "udp interface constructor failed: " << e.what();
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }
        /* create thread */
        std::function<void()> handler1 = std::bind(&UdpInterface::Thread, this);
        recv_thread_                   = std::make_shared<std::thread>(handler1);

        if (is_async_)
        {
            std::function<void()> handler2 = std::bind(&UdpInterface::Parse, this);
            parse_thread_                  = std::make_shared<std::thread>(handler2);
        }
    }

    void Thread()
    {
        Buffer         buffer;
        int32_t        rcode;
        holo::uint32_t milliseconds{0U};

        while (running_)
        {
            /* get buffer */
            if (!idle_buffer_.WaitForTake(buffer, milliseconds))
            {
                /* create buffer */
                std::shared_ptr<uint8_t> temp(new uint8_t[Buffer::BUFFER_SIZE]);
                buffer.data  = temp;
                buffer.bytes = 0;
            }
            /* recv data */
            (void)std::memset(&cli_addr_, 0, sizeof(cli_addr_));
            if (-1 == (rcode = socket_->Receive(buffer.data.get(), Buffer::BUFFER_SIZE, buffer.bytes, &cli_addr_)))
            {
                idle_buffer_.TryPush(buffer);
                continue;
            }
            if (rcode != ErrorCode::E_OK)
            {
                LOG(ERROR) << "socket communication error: " << rcode;
                if (rcode == ErrorCode::E_WRONG_SOCKET || rcode == ErrorCode::E_SOCKET_CLOSE)
                {
                    idle_buffer_.TryPush(buffer);
                    break;  // exit? think twice here
                }
            }
            /* process task */
            if (is_async_)
            {
                buffer.cli_addr = cli_addr_;
                /* add task */
                if (!task_queue_.TryPush(buffer))
                {
                    throw std::runtime_error{"task queue is Full or Destroy!"};
                }
            }
            else
            {
                InterfaceT<T>::ParseData(buffer.data.get(), buffer.bytes, (void*)&cli_addr_);
                idle_buffer_.TryPush(buffer);
            }
        }
    }

    void Parse()
    {
        Buffer         buffer;
        holo::uint32_t milliseconds{1000U};

        /* parsing data */
        while (running_)
        {
            if (!task_queue_.WaitForTake(buffer, milliseconds))
            {
                continue;
            }
            InterfaceT<T>::ParseData(buffer.data.get(), buffer.bytes, (void*)&buffer.cli_addr);
            idle_buffer_.TryPush(buffer);
        }
    }

private:
    struct Buffer
    {
        Buffer() : data(nullptr), bytes(0)
        {
        }

        static const uint32_t    BUFFER_SIZE = 1024 * 64;
        std::shared_ptr<uint8_t> data;
        int32_t                  bytes;
        struct sockaddr_in       cli_addr; /* data from who */
    };

private:
    std::mutex                           tmutex_;
    std::shared_ptr<HoloSocketUdpServer> socket_;
    std::shared_ptr<std::thread>         recv_thread_;
    std::shared_ptr<std::thread>         parse_thread_;
    bool                                 running_;
    bool                                 is_async_;
    holo::thread::SyncQueue<Buffer>      idle_buffer_;
    holo::thread::SyncQueue<Buffer>      task_queue_;
    struct sockaddr_in                   cli_addr_;
};  // namespace interface

}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif
