#include <arpa/inet.h> /*for inet_addr*/
#include <assert.h>
#include <errno.h>
#include <fcntl.h>
#include <netinet/in.h>  /* for IPPROTO_TCP*/
#include <netinet/tcp.h> /* for TCP_NODELAY*/
#include <string.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdexcept>

#include <holo/network/exception.h>
#include <holo/network/socket.h>

namespace holo
{
namespace network
{
Socket::Socket() noexcept : fd_{INVALID_FD}
{
}

Socket::Socket(holo::int32_t const fd) noexcept : fd_{fd}
{
}

Socket::Socket(Socket const& that) noexcept
{
    fd_ = that.fd_;
}

Socket::Socket(Socket&& that) noexcept
{
    fd_ = that.fd_;
}

Socket& Socket::operator=(Socket const& that) noexcept
{
    fd_ = that.fd_;
    return *this;
}

Socket& Socket::operator=(Socket&& that) noexcept
{
    fd_ = that.fd_;
    return *this;
}
holo::bool_t Socket::operator==(Socket const& that) const
{
    return fd_ == that.fd_;
}

holo::bool_t Socket::operator!=(Socket const& that) const
{
    return !(*this == that);
}

void Socket::Open(holo::int32_t const domain, holo::int32_t const type)
{
    assert(AF_INET == domain);
    assert(SOCK_STREAM == type);

    if (INVALID_FD != fd_)
    {
        return;
    }

    fd_ = ::socket(domain, type, 0);

    if (INVALID_FD == fd_)
    {
        std::string error_info = "open socket error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

void Socket::Close() const
{
    if (INVALID_FD == fd_)
    {
        return;
    }

    ::close(fd_);
    // fd_ = INVALID_FD;
}

void Socket::Bind(std::string const& ip, holo::int32_t const port) const
{
    assert(INVALID_FD != fd_);

    struct sockaddr_in sock_addr;
    ::memset(&sock_addr, 0, sizeof(struct sockaddr_in));
    sock_addr.sin_family = AF_INET;
    if (!ip.empty())
    {
        sock_addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    }
    else
    {
        std::string error_info = "ip NOT set!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
    sock_addr.sin_port = htons(port);

    if (::bind(fd_, (struct sockaddr*)(&sock_addr), sizeof(sock_addr)) < 0)
    {
        std::string error_info = "bind socket error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

void Socket::Bind(holo::int32_t const port) const
{
    assert(INVALID_FD != fd_);

    struct sockaddr_in sock_addr;
    ::memset(&sock_addr, 0, sizeof(struct sockaddr_in));
    sock_addr.sin_family      = AF_INET;
    sock_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    sock_addr.sin_port        = htons(port);

    if (::bind(fd_, (struct sockaddr*)(&sock_addr), sizeof(sock_addr)) < 0)
    {
        std::string error_info = "bind socket error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

void Socket::Listen(holo::int32_t const backlog) const
{
    assert(INVALID_FD != fd_);

    if (::listen(fd_, backlog) < 0)
    {
        std::string error_info = "listen socket error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

Socket Socket::Accept() const
{
    assert(INVALID_FD != fd_);

    holo::int32_t      fd{INVALID_FD};
    struct sockaddr_in client_addr;
    socklen_t          client_addr_len = sizeof(client_addr);

    while ((fd = ::accept(fd_, (struct sockaddr*)&client_addr, &client_addr_len)) < 0 && errno == EINTR)
        ;

    if (INVALID_FD == fd)
    {
        std::string error_info = "accpet socket error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    Socket socket{fd};

    return socket;
}

Socket Socket::Accept(std::string& client_ip, holo::int32_t& client_port) const
{
    assert(INVALID_FD != fd_);

    holo::int32_t      fd{INVALID_FD};
    struct sockaddr_in client_addr;
    socklen_t          client_addr_len = sizeof(client_addr);

    while ((fd = ::accept(fd_, (struct sockaddr*)&client_addr, &client_addr_len)) < 0 && errno == EINTR)
        ;

    if (INVALID_FD == fd)
    {
        std::string error_info = "accpet socket error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    client_port = ntohs(client_addr.sin_port);
    client_ip   = static_cast<holo::char_t*>(::inet_ntoa(client_addr.sin_addr));
    Socket socket{fd};

    return socket;
}

holo::int32_t Socket::Connect(std::string const& ip, holo::int32_t const port) const
{
    assert(INVALID_FD != fd_);

    holo::int32_t      ret{-1};
    struct sockaddr_in sock_addr;
    ::memset(&sock_addr, 0, sizeof(struct sockaddr_in));
    sock_addr.sin_family = AF_INET;
    if (!ip.empty())
    {
        sock_addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    }
    else
    {
        std::string error_info = "ip NOT set!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
    sock_addr.sin_port = htons(port);

    while ((ret = ::connect(fd_, (struct sockaddr*)(&sock_addr), sizeof(sock_addr))) < 0 && errno == EINTR)
        ;

    if (-1 == ret && EINPROGRESS != errno)
    {
        std::string error_info = "connect  error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    return ret;
}

holo::int32_t Socket::Connect(std::string const& ip, holo::int32_t const port, holo::int32_t const seconds) const
{
    assert(INVALID_FD != fd_);

    holo::int32_t      ret{-1};
    struct sockaddr_in sock_addr;
    ::memset(&sock_addr, 0, sizeof(struct sockaddr_in));
    sock_addr.sin_family = AF_INET;
    if (!ip.empty())
    {
        sock_addr.sin_addr.s_addr = ::inet_addr(ip.c_str());
    }
    else
    {
        std::string error_info = "ip NOT set!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
    sock_addr.sin_port = htons(port);

    while ((ret = ::connect(fd_, (struct sockaddr*)(&sock_addr), sizeof(sock_addr))) < 0 && errno == EINTR)
        ;

    if (-1 == ret)
    {
        if (EINPROGRESS == errno)
        {
            return checkConnect(fd_, seconds);
        }
        else
        {
            std::string error_info = "connect  error!";
            error_info += strerror(errno);
            throw holo::exception::RuntimeErrorException{error_info};
        }
    }

    return ret;
}

holo::int32_t Socket::checkConnect(holo::int32_t const fd, holo::int32_t const seconds) const
{
    holo::int32_t ret{-1};

    struct timeval time_out;
    time_out.tv_sec  = seconds;
    time_out.tv_usec = 0;

    fd_set fds;

    do
    {
        FD_ZERO(&fds);
        FD_SET(fd, &fds);
        ret = ::select(fd + 1, 0, &fds, 0, &time_out);
    } while (ret < 0 && errno == EINTR);

    if (0 > ret)
    {
        return -1;
    }
    else if (0 == ret)
    {
        return -1;
    }
    else
    {
        holo::int32_t error;
        holo::int32_t error_len = sizeof(error);

        ret = ::getsockopt(fd, SOL_SOCKET, SO_ERROR, (void*)&error, (socklen_t*)&error_len);

        if (0 < ret || 0 != error)
        {
            return -1;
        }
        else
        {
            return 0;
        }
    }
}

holo::int32_t Socket::Recv(holo::uint8_t* recv_buffer, holo::int32_t const recv_buffer_len) const
{
    assert(0 < recv_buffer_len);

    return ::recv(fd_, recv_buffer, recv_buffer_len, 0);
}

holo::int32_t Socket::Send(holo::uint8_t const* data, holo::int32_t const data_len) const
{
    assert(0 < data_len);

    return ::send(fd_, data, data_len, MSG_NOSIGNAL);
}

holo::int32_t Socket::Send(holo::uint8_t const* data, holo::int32_t const data_len, holo::int32_t const seconds) const
{
    assert(0 < data_len);

    holo::int32_t has_send_len = ::send(fd_, data, data_len, MSG_NOSIGNAL);

    if (has_send_len == data_len)
    {
        return has_send_len;
    }

    holo::int32_t ret{-1};
    holo::int32_t time_out_count{5};
    holo::int32_t need_to_send_len{data_len - has_send_len};

    struct timeval time_out;
    time_out.tv_sec  = seconds;
    time_out.tv_usec = 0;

    fd_set fds;

    do
    {
        FD_ZERO(&fds);
        FD_SET(fd_, &fds);

        ret = ::select(fd_ + 1, NULL, &fds, NULL, &time_out);

        if (ret < 0)
        {
            break;
        }
        else if (ret == 0)
        {
            time_out_count++;
        }
        else
        {
            ret = ::send(fd_, data + has_send_len, need_to_send_len, MSG_NOSIGNAL);
            has_send_len += ret;
            need_to_send_len -= ret;
        }
    } while (need_to_send_len > 0 && time_out_count < 5);

    return has_send_len;
}

holo::int32_t Socket::GetFd() const noexcept
{
    return fd_;
}

holo::bool_t Socket::IsOpen() const noexcept
{
    return INVALID_FD != fd_;
}

void Socket::SetSendBufferSize(holo::int32_t const size) const
{
    if (::setsockopt(fd_, SOL_SOCKET, SO_SNDBUF, (char const*)&size, sizeof(size)) == -1)
    {
        std::string error_info = "SetSendBufferSize  error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

holo::int32_t Socket::GetSendBufferSize() const
{
    holo::int32_t optval{0};
    socklen_t     optlen{sizeof(optval)};

    if (::getsockopt(fd_, SOL_SOCKET, SO_SNDBUF, (char*)&optval, &optlen) == -1)
    {
        std::string error_info = "GetSendBufferSize  error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    return optval;
}

void Socket::SetRecvBufferSize(holo::int32_t const size) const
{
    if (::setsockopt(fd_, SOL_SOCKET, SO_RCVBUF, (char const*)&size, sizeof(size)) == -1)
    {
        std::string error_info = "SetRecvBufferSize  error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

holo::int32_t Socket::GetRecvBufferSize() const
{
    holo::int32_t optval{0};
    socklen_t     optlen{sizeof(optval)};

    if (::getsockopt(fd_, SOL_SOCKET, SO_RCVBUF, (char*)&optval, &optlen) == -1)
    {
        std::string error_info = "GetRecvBufferSize  error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    return optval;
}

void Socket::SetReuseAddr() const
{
    holo::int32_t optval{1};

    if (::setsockopt(fd_, SOL_SOCKET, SO_REUSEADDR, (char*)&optval, sizeof(optval)) == -1)
    {
        std::string error_info = "SetReuseAddr  error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

void Socket::SetNonBlock(holo::bool_t const non_block) const
{
    holo::int32_t flags{0};

    if ((flags = ::fcntl(fd_, F_GETFL, 0)) == -1)
    {
        std::string error_info = "SetBlock: fcntl [F_GETFL] error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    if (non_block)
    {
        flags |= O_NONBLOCK;
    }
    else
    {
        flags &= ~O_NONBLOCK;
    }

    if (::fcntl(fd_, F_SETFL, flags) == -1)
    {
        std::string error_info = "SetBlock: fcntl [F_SETFL] error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

void Socket::SetCloseWait(CloseWaitState const state, holo::int32_t const seconds) const
{
    struct linger l;
    (void)seconds;
    if (CloseWaitState::NO_WAIT == state)
    {
        l.l_onoff  = 1;
        l.l_linger = 0;
    }
    else if (CloseWaitState::DELAY == state)
    {
        l.l_onoff  = 1;
        l.l_linger = seconds;
    }
    else
    {
        l.l_onoff  = 0;
        l.l_linger = 0;
    }

    if (::setsockopt(fd_, SOL_SOCKET, SO_LINGER, (char*)&l, sizeof(l)) == -1)
    {
        std::string error_info = "SetCloseWait  error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

void Socket::SetTcpNoDelay() const
{
    holo::int32_t optval{1};

    if (::setsockopt(fd_, IPPROTO_TCP, TCP_NODELAY, (char*)&optval, sizeof(optval)) == -1)
    {
        std::string error_info = "SetTcpNoDelay  error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

void Socket::SetKeepAlive() const
{
    holo::int32_t optval{1};

    if (::setsockopt(fd_, SOL_SOCKET, SO_KEEPALIVE, (char*)&optval, sizeof(optval)) == -1)
    {
        std::string error_info = "SetKeepAlive  error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }
}

holo::bool_t Socket::IsReadable() const
{
    holo::uint8_t recv_buffer[1];
    holo::int32_t read_len = ::recv(fd_, recv_buffer, 1, MSG_PEEK);
    if (read_len <= 0)
    {
        return false;
    }
    return true;
}

holo::bool_t Socket::GetPeerName(std::string& ip, holo::int32_t& port) const
{
    struct sockaddr_in peer_addr;
    socklen_t          peer_addr_len = sizeof(peer_addr);

    if (::getpeername(fd_, (struct sockaddr*)&peer_addr, &peer_addr_len) < 0)
    {
        std::string error_info = "GetPeerName error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    port = ntohs(peer_addr.sin_port);
    ip   = static_cast<holo::char_t*>(::inet_ntoa(peer_addr.sin_addr));

    return true;
}

holo::bool_t Socket::GetSockName(std::string& ip, holo::int32_t& port) const
{
    struct sockaddr_in sock_addr;
    socklen_t          sock_addr_len = sizeof(sock_addr);

    if (::getsockname(fd_, (struct sockaddr*)&sock_addr, &sock_addr_len) < 0)
    {
        std::string error_info = "GetSockName error!";
        error_info += strerror(errno);
        throw holo::exception::RuntimeErrorException{error_info};
    }

    port = ntohs(sock_addr.sin_port);
    ip   = static_cast<holo::char_t*>(::inet_ntoa(sock_addr.sin_addr));

    return true;
}

}  // namespace network
}  // namespace holo
