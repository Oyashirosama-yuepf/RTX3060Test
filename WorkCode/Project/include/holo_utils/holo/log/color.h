#ifndef HOLO_LOG_COLOR_H_
#define HOLO_LOG_COLOR_H_

#include <holo/core/types.h>
#include <functional>
#include <ostream>

namespace holo
{
namespace log
{
using ColorType = std::ostream& (*)(std::ostream&);

enum class Color : holo::uint32_t
{
    BLACK        = 0U,
    LIGHT_BLACK  = 1U,
    RED          = 2U,
    LIGHT_RED    = 3U,
    GREEN        = 4U,
    LIGHT_GREEN  = 5U,
    YELLOW       = 6U,
    LIGHT_YELLOW = 7U,
    BLUE         = 8U,
    LIGHT_BLUE   = 9U,
    PINK         = 10U,
    LIGHT_PINK   = 11U,
    CYAN         = 12U,
    LIGHT_CYAN   = 13U,
    WHITE        = 14U,
    LIGHT_WHITE  = 15U,
    NONE         = 16U,
};

inline std::ostream& Black(std::ostream& os)
{
    return os << "\033[0;30m";
}

inline std::ostream& LightBlack(std::ostream& os)
{
    return os << "\033[1;30m";
}

inline std::ostream& Red(std::ostream& os)
{
    return os << "\033[0;31m";
}

inline std::ostream& LightRed(std::ostream& os)
{
    return os << "\033[1;31m";
}

inline std::ostream& Green(std::ostream& os)
{
    return os << "\033[0;32m";
}

inline std::ostream& LightGreen(std::ostream& os)
{
    return os << "\033[1;32m";
}

inline std::ostream& Yellow(std::ostream& os)
{
    return os << "\033[0;33m";
}

inline std::ostream& LightYellow(std::ostream& os)
{
    return os << "\033[1;33m";
}

inline std::ostream& Blue(std::ostream& os)
{
    return os << "\033[0;34m";
}

inline std::ostream& LightBlue(std::ostream& os)
{
    return os << "\033[1;34m";
}

inline std::ostream& Pink(std::ostream& os)
{
    return os << "\033[0;35m";
}

inline std::ostream& LightPink(std::ostream& os)
{
    return os << "\033[1;35m";
}

inline std::ostream& Cyan(std::ostream& os)
{
    return os << "\033[0;36m";
}

inline std::ostream& LightCyan(std::ostream& os)
{
    return os << "\033[1;36m";
}

inline std::ostream& White(std::ostream& os)
{
    return os << "\033[0;37m";
}

inline std::ostream& LightWhite(std::ostream& os)
{
    return os << "\033[1;37m";
}

inline std::ostream& None(std::ostream& os)
{
    return os << "\033[0m";
}

}  // namespace log

}  // namespace holo

namespace std
{
template <>
struct hash<::holo::log::Color>
{
    using result_type   = std::size_t;
    using argument_type = ::holo::log::Color;

    result_type operator()(argument_type const& color) const
    {
        return static_cast<result_type>(color);
    }
};

}  // namespace std

#endif
