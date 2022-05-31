/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file tcpcli_interface.h
 * @brief define the udp interface class
 * @author guoguangchao<guoguangchao@holomatic.com>
 * @date 2020-07-28
 */

#ifndef HOLO_SENSORS_CMW_APP_INTERFACE_TCPCLI_INTERFACE_H
#define HOLO_SENSORS_CMW_APP_INTERFACE_TCPCLI_INTERFACE_H

#include <holo/os/timer.h>
#include <holo/sensors/common/interface.h>
#include <holo/utils/yaml.h>
#include <holo_c/core/types.h>
#include <holo/sensors/interface/holo_socket/tcp_client.h>
#include <errno.h>
#include <functional>
#include <mutex>
#include <thread>

namespace holo
{
namespace sensors
{
namespace interface
{
namespace tcpcli
{
using RecvDataCallbackType = std::function<std::pair<uint8_t*, uint32_t>(uint8_t*, uint32_t)>;
}

using holo::sensors::common::InterfaceT;

#ifndef HOLO_SENSORS_INTERFACE_SOCKET_ADDR
#define HOLO_SENSORS_INTERFACE_SOCKET_ADDR
struct SocketAddr
{
    std::string ip;
    uint16_t    port;
};
#endif

struct TcpcliInterfaceParam
{
    SocketAddr addr;
    int32_t    timeout = -1;
};

template <typename T>
class TcpcliInterface : public InterfaceT<T>
{
public:
    TcpcliInterface() = delete;
    TcpcliInterface(const TcpcliInterfaceParam& param) : param_(param), connected_(false), running_(true)
    {
        Init(param_);
    }
    TcpcliInterface(const holo::yaml::Node& node) : connected_(false), running_(true)
    {
        param_.addr.ip   = node["ip"].as<std::string>();
        param_.addr.port = node["port"].as<uint16_t>();
        param_.timeout   = node["timeout"].as<int32_t>();
        LOG(INFO) << "address = " << param_.addr.ip << ":" << static_cast<uint32_t>(param_.addr.port)
                  << ", timeout = " << param_.timeout;
        Init(param_);
    }
    ~TcpcliInterface()
    {
        running_ = false;
        if (thread_ && thread_->joinable())
        {
            thread_->join();
        }
    }

    bool_t IsConnected() const noexcept
    {
        return connected_;
    }

    int32_t Send(const uint8_t* buffer, uint32_t size)
    {
        if (!connected_)
        {
            return -1;
        }
        std::lock_guard<std::mutex> guard(tmutex_);
        return socket_->Send(buffer, size);
    }

    int32_t Send(const std::string& data)
    {
        if (!connected_)
        {
            return -1;
        }
        std::lock_guard<std::mutex> guard(tmutex_);
        return socket_->Send(reinterpret_cast<const uint8_t*>(data.c_str()), data.size());
    }

    int32_t Send(const T& data)
    {
        if (!connected_)
        {
            return -1;
        }
        uint32_t size = data.GetSerializedSize();
        uint8_t  tdata[size];
        (void)std::memset(tdata, 0, sizeof(tdata));
        uint32_t                    tsize = data.Serialize(tdata, sizeof(tdata));
        std::lock_guard<std::mutex> guard(tmutex_);
        return socket_->Send(tdata, tsize);
    }

    void InstallRecvCallback(const tcpcli::RecvDataCallbackType& callback) noexcept
    {
        if (callback)
        {
            recv_data_callback_ = callback;
            return;
        }
        recv_data_callback_ = std::bind(&TcpcliInterface::DropData, this, std::placeholders::_1, std::placeholders::_2);
    }

private:
    void Init(const TcpcliInterfaceParam& param)
    {
        try
        {
            socket_ = std::make_shared<HoloSocketTcpClient>(param.addr.ip, param.addr.port);
        }
        catch (const std::exception& e)
        {
            std::ostringstream oss;
            oss << "tcp client interface constructor failed: " << e.what();
            LOG(ERROR) << oss.str();
            throw std::runtime_error(oss.str());
        }
        /* cteate thread */
        std::function<void()> handler = std::bind(&TcpcliInterface::Thread, this);
        thread_                       = std::make_shared<std::thread>(handler);
        recv_data_callback_           = std::bind(&TcpcliInterface::RecvData, this, std::placeholders::_1,
                                                  std::placeholders::_2);
    }

    void TryConnect(const bool_t reconnect = false)
    {
        holo::Timer timer(1.0f);
        LOG(INFO) << "try to connect: " << param_.addr.ip << ":" << param_.addr.port;
        while (running_ && !connected_)
        {
            timer.Start();
            int32_t retval = 0;
            if (!reconnect)
            {
                retval = socket_->Connect();
            }
            else
            {
                retval = socket_->Reconnect();
            }
            if (retval == 0)
            {
                LOG(INFO) << "connected: " << param_.addr.ip << ":" << param_.addr.port;
                connected_ = true;
                break;
            }
            LOG(ERROR) << "connection failed, will retry after 1s...";
            timer.Stop();
        }
    }

    std::pair<uint8_t*, uint32_t> RecvData(uint8_t* rdata, uint32_t rbyte)
    {
        return std::pair<uint8_t*, uint32_t>(rdata, rbyte);
    }

    std::pair<uint8_t*, uint32_t> DropData(uint8_t* rdata, uint32_t rbyte)
    {
        (void)rdata;
        (void)rbyte;
        return std::pair<uint8_t*, uint32_t>(nullptr, 0);
    }

    void Thread()
    {
        /* connect */
        TryConnect();

        /* alloc data */
        uint8_t * rdata = nullptr;
        while (running_)
        {
            if((rdata = new uint8_t[1024 * 64]))
            {
                break;
            }
            LOG(ERROR) << "memory alloc failed, will retry after 1s...";
            usleep(1000000u);
        }

        /* communication */
        while (running_)
        {
            fd_set fds;
            FD_ZERO(&fds);
            FD_SET(socket_->GetFd(), &fds);
            struct timeval tv;
            tv.tv_sec  = static_cast<int32_t>(param_.timeout / 1000);
            tv.tv_usec = static_cast<int32_t>((param_.timeout % 1000) * 1000);
            if (select(socket_->GetFd() + 1, &fds, NULL, NULL, &tv) <= 0)
            {
                continue;
            }
            int32_t rcode  = -1;
            int32_t rbytes = 0;
            if (-1 == (rcode = socket_->Receive(rdata, sizeof(rdata), rbytes)))
            {
                continue;
            }
            if (rcode != ErrorCode::E_OK)
            {
                LOG(ERROR) << "socket communication error: " << rcode << ", " << strerror(errno);
                if (rcode == ErrorCode::E_WRONG_SOCKET || rcode == ErrorCode::E_SOCKET_CLOSE)
                {
                    connected_ = false;
                    TryConnect(true);
                    continue;
                }
            }
            /* parsing data */
            uint32_t offset = 0;
            while (true)
            {
                std::pair<uint8_t*, uint32_t> item =
                    recv_data_callback_(rdata + offset, rbytes - offset);
                if (static_cast<uint32_t>(item.second) == 0)
                {
                    break;
                }
                InterfaceT<T>::ParseData(item.first, item.second);
                offset += item.second;
            }
        }

        /* release data */
        if (rdata)
        {
            delete[] rdata;
        }
    }

private:
    std::mutex                           tmutex_;
    std::shared_ptr<HoloSocketTcpClient> socket_;
    std::shared_ptr<std::thread>         thread_;
    TcpcliInterfaceParam                 param_;
    bool_t                               connected_;
    bool_t                               running_;
    tcpcli::RecvDataCallbackType         recv_data_callback_;
};

}  // namespace interface
}  // namespace sensors
}  // namespace holo

#endif
