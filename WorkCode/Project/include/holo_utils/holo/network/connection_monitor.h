#ifndef HOLO_NETWORK_CONNECTION_MONITOR_H
#define HOLO_NETWORK_CONNECTION_MONITOR_H

#include <atomic>
#include <functional>
#include <memory>

#include "common.h"
#include "poller.h"
#include "selector.h"
#include "socket.h"

#if defined(__linux__)
#include "epoller.h"
#endif

namespace holo
{
namespace network
{
class ConnectionMonitor : public std::enable_shared_from_this<ConnectionMonitor>
{
public:
#if defined(__linux__)
    using MultiplexerType = Epoller;
#else
    using MultiplexerType = Poller;
#endif

    // using MultiplexerType = Selector;

    ConnectionMonitor() noexcept;
    virtual ~ConnectionMonitor() noexcept;

    void Init();
    void Destroy();

    /**
     * @brief connection uninitialized!  need to call connect() function
     *
     * @param callback
     */
    void SetUninitializedCallback(std::function<void(Socket const)> const& callback);

    /**
     * @brief connection successful!  you can start to send data
     *
     * @param callback
     */
    void SetConnectedCallback(std::function<void(Socket const)> const& callback);
    /**
     * @brief read the data until read() return -1
     *
     * @param callback
     */
    void SetReadCallback(std::function<void(Socket const)> const& callback);
    /**
     * @brief connection disconnected, you must be close socket
     *
     * @param callback
     */
    void SetClosedCallback(std::function<void(Socket const)> const& callback);

    /**
     * @brief Not implemented.   Reserved api.
     *
     * @param callback
     */
    void SetWriteCallback(std::function<void(Socket const)> const& callback);

    void AddConnection(Socket const socket);
    void DelConnection(Socket const socket);

    void ProcessEventOnce();

private:
    void readEventCallback(Socket const socket);
    void writeEventCallback(Socket const socket);
    void errorEventCallback(Socket const socket);
    void hangupEventCallback(Socket const socket);

private:
    MultiplexerType                   io_multiplexer_;
    std::function<void(Socket const)> uninitialized_callback_;
    std::function<void(Socket const)> connected_callback_;
    std::function<void(Socket const)> read_callback_;
    std::function<void(Socket const)> closed_callback_;
    std::function<void(Socket const)> write_callback_;
};

}  // namespace network
}  // namespace holo

#endif
