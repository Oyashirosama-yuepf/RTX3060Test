#ifndef HOLO_NETWORK_SOCKET_H
#define HOLO_NETWORK_SOCKET_H

#include <holo/core/types.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <functional> /*for std::hash*/
#include <string>

namespace holo
{
namespace network
{
/**
 * @brief Only support IPv4 (Expand IPv6 if necessary)
 */
class Socket
{
public:
    static constexpr holo::int32_t INVALID_FD{-1};
    static constexpr holo::int32_t DEFAULT_DELAY_SECONDS{5};

    enum class CloseWaitState : holo::uint8_t
    {
        DEFAULT = 0,
        NO_WAIT = 1,
        DELAY   = 2,
    };

    Socket() noexcept;
    Socket(holo::int32_t const fd) noexcept;

    Socket(Socket const& that) noexcept;
    Socket(Socket&& that) noexcept;
    Socket&      operator=(Socket const& that) noexcept;
    Socket&      operator=(Socket&& that) noexcept;
    holo::bool_t operator==(Socket const& that) const;
    holo::bool_t operator!=(Socket const& that) const;

    /**
     * @brief If fd_ is already open, nothing will be done
     *
     * @param domain  Only support AF_INET, (AF_LOCAL, AF_INET6 not support, if necessary?)
     * @param type Only support SOCK_STREAM, ( SOCK_DGRAM not support).
     *
     * @return
     */
    void Open(holo::int32_t const domain, holo::int32_t const type);
    void Close() const;

    void          Bind(std::string const& ip, holo::int32_t const port) const;
    void          Bind(holo::int32_t const port) const;
    void          Listen(holo::int32_t const backlog = 16) const;
    Socket        Accept() const;
    Socket        Accept(std::string& client_ip, holo::int32_t& client_port) const;
    holo::int32_t Connect(std::string const& ip, holo::int32_t const port) const;

    /**
     * @brief if socket is O_NONBLOCK, This function is a synchronous operation
     *
     * @param ip
     * @param port
     * @param seconds
     *
     * @return
     */
    holo::int32_t Connect(std::string const& ip, holo::int32_t const port, holo::int32_t const seconds) const;

    holo::int32_t Recv(holo::uint8_t* recv_buffer, holo::int32_t const recv_buffer_len) const;

    /**
     * @brief send data
     * default use MSG_NOSIGNAL flag
     *
     * @param data
     * @param data_len
     *
     * @return
     */
    holo::int32_t Send(holo::uint8_t const* data, holo::int32_t const data_len) const;

    /**
     * @brief if socket is O_NONBLOCK, This function is a synchronous operation
     * default use MSG_NOSIGNAL flag
     *
     * @param send_buffer
     * @param len
     * @param seconds
     *
     * @return
     */
    holo::int32_t Send(holo::uint8_t const* data, holo::int32_t const data_len, holo::int32_t const seconds) const;

    holo::int32_t GetFd() const noexcept;
    holo::bool_t  IsOpen() const noexcept;

    void          SetSendBufferSize(holo::int32_t const size) const;
    holo::int32_t GetSendBufferSize() const;

    void          SetRecvBufferSize(holo::int32_t const size) const;
    holo::int32_t GetRecvBufferSize() const;

    void SetReuseAddr() const;
    void SetNonBlock(holo::bool_t const non_block) const;
    void SetCloseWait(CloseWaitState const state, holo::int32_t const seconds = DEFAULT_DELAY_SECONDS) const;
    void SetTcpNoDelay() const;
    void SetKeepAlive() const;

    holo::bool_t IsReadable() const;

    holo::bool_t GetPeerName(std::string& ip, holo::int32_t& port) const;
    holo::bool_t GetSockName(std::string& ip, holo::int32_t& port) const;

private:
    holo::int32_t checkConnect(holo::int32_t const fd, holo::int32_t const seconds) const;

private:
    holo::int32_t fd_;
};

}  // namespace network
}  // namespace holo

namespace std
{
template <>
struct hash<::holo::network::Socket>
{
    using result_type   = std::size_t;
    using argument_type = ::holo::network::Socket;

    result_type operator()(argument_type const& socket) const
    {
        return static_cast<result_type>(socket.GetFd());
    }
};
}  // namespace std

#endif
