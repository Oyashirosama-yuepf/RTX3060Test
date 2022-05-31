#ifndef HOLO_LOG_LOG4CPLUS_OSTREAM_H_
#define HOLO_LOG_LOG4CPLUS_OSTREAM_H_

#include <holo/core/types.h>
#include <ostream>

#include "streambuf.h"

namespace holo
{
namespace log
{
namespace log4cplus
{
class OStream : public std::ostream
{
public:
    using Base = std::ostream;

    OStream(holo::uint32_t const size) : Base{nullptr}, streambuf_{size}
    {
        static_cast<void>(Base::rdbuf(&streambuf_));
    }

    holo::int32_t Count() const
    {
        return streambuf_.Count();
    }

    void Trunc()
    {
        streambuf_.Trunc();
    }

    void Reset()
    {
        streambuf_.Reset();
    }

    holo::char_t* str() const
    {
        return streambuf_.Begin();
    }

private:
    OStream(OStream const&);
    OStream(OStream&&);
    OStream& operator=(OStream const&) &;
    OStream& operator=(OStream&&) &;

    StreamBuf streambuf_;
};

}  // namespace log4cplus

}  // namespace log

}  // namespace holo

#endif
