#ifndef HOLO_LOG_LOG4CPLUS_STREAMBUF_H_
#define HOLO_LOG_LOG4CPLUS_STREAMBUF_H_

#include <assert.h>
#include <holo/core/types.h>
#include <streambuf>
#include <vector>

namespace holo
{
namespace log
{
namespace log4cplus
{
class StreamBuf : public std::streambuf
{
public:
    using Base        = std::streambuf;
    using char_type   = Base::char_type;
    using traits_type = Base::traits_type;
    using int_type    = Base::int_type;
    using pos_type    = Base::pos_type;
    using off_type    = Base::off_type;

    StreamBuf(holo::uint32_t const size) : Base{}, buf_(size)
    {
        assert(size >= 1U);
        buf_[size - 1U] = '\0';
        Base::setp(&buf_[0U], &buf_[size - 1U]);
    }

    int_type overflow(int_type ch) override
    {
        return ch;
    }

    holo::int32_t Count() const
    {
        return static_cast<holo::int32_t>(Base::pptr() - Base::pbase());
    }

    holo::char_t* Begin() const
    {
        return Base::pbase();
    }

    void Trunc()
    {
        *(Base::pptr()) = '\0';
    }

    void Reset()
    {
        buf_[0U]            = '\0';
        holo::uint32_t size = buf_.size();
        Base::setp(&buf_[0U], &buf_[size - 1U]);
    }

private:
    std::vector<char_type> buf_;
};

}  // namespace log4cplus

}  // namespace log

}  // namespace holo

#endif
