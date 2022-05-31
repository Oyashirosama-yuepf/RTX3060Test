/* Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file writer.h
 * @brief This header defines the StreamWriter/NullWriter class
 * @author moxiao@holomatic.com
 * @date 2021-09-06
 */

#ifndef HOLO_LOG_LOG4CPLUS_WRITER_H_
#define HOLO_LOG_LOG4CPLUS_WRITER_H_

#include <holo/core/types.h>

#include "loglevel.h"
#include "ostream.h"

namespace holo
{
namespace log
{
namespace log4cplus
{
/**
 * @brief This class more or less represents a particular log message.
 * You create an instance of StreamWriter and then stream stuff to it.
 * When you finish streaming to it, ~StreamWriter() is called and the
 * full message gets streamed to the appropriate destination.
 *
 * You shouldn't actually use StreamWriter's constructor to log things,
 * though.  You should use the LOG() macro.
 */
class StreamWriter final
{
public:
    /**
     * @brief Constructor
     *
     * @param file Source code file
     * @param function Function
     * @param line Source code file line
     * @param level LogLevel
     */
    StreamWriter(holo::char_t const* file, holo::char_t const* function, holo::uint32_t line, LogLevel level);

    /**
     * @brief Destroys the StreamWriter object.
     */
    ~StreamWriter() noexcept;

    /**
     * @brief Return the ostringstream object for logging
     *
     * @return std::ostringstream &
     */
    OStream& stream();

private:
    StreamWriter(StreamWriter const&) = delete;
    StreamWriter& operator=(StreamWriter const&) = delete;

    holo::char_t const* file_;
    holo::char_t const* function_;
    holo::uint32_t      line_;
    LogLevel            level_;
};

/**
 * @brief A class for which we define operator<<, which does nothing.
 */
class NullWriter final
{
public:
    NullWriter(NullWriter const&) = delete;
    NullWriter& operator=(NullWriter const&) = delete;

    /**
     * @brief default constructor
     */
    NullWriter() = default;

    /**
     * @brief Do nothing.
     *
     * @return NullWriter &
     */
    NullWriter& stream()
    {
        return *this;
    }

    /**
     * @brief Do nothing. the message will be quietly discarded.
     *
     * @tparam T
     * @param T const &
     *
     * @return NullWriter &
     */
    template <typename T>
    NullWriter& operator<<(T const&)
    {
        return *this;
    }

    /**
     * @brief Do nothing. the message will be quietly discarded.
     * Compatible with C + + standard library functions:
     * std::endl, std::ends, std::flush...
     *
     * @param std::ostream &(*)(std::ostream &)
     *
     * @return NullWriter &
     */
    NullWriter& operator<<(std::ostream& (*)(std::ostream&))
    {
        return *this;
    }

    /**
     * @brief Do nothing. the message will be quietly discarded.
     * Compatible with C + + standard library functions:
     * std::hex, std::dec, std::oct...
     *
     * @param std::ios_base &(*)(std::ios_base &)
     *
     * @return NullWriter &
     */
    NullWriter& operator<<(std::ios_base& (*)(std::ios_base&))
    {
        return *this;
    }
};

}  // namespace log4cplus

}  // namespace log

}  // namespace holo

#endif
