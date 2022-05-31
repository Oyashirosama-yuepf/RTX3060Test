/**
 * @file utils.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief 
 * @date 2020-09-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <utils.h>
#include <unistd.h>
#include <termios.h>
#include <holo/os/time.h>
#if defined(HOLO_TIME_WITH_MDC_TIME)
#include <holo/sensors/utils/mdc610_utils.h>
#endif

namespace holo_cmw
{
std::string GetStrFromTerminal(const std::string& command)
{
    std::string result;
    FILE*       fp;
    if ((fp = popen(command.c_str(), "r")) == NULL)
    {
        result = "";
    }
    else
    {
        char buffer[1024];
        while (fgets(buffer, 1024, fp) != NULL)
        {
            result += buffer;
        }

        if (pclose(fp) == -1)
        {
            result = "";
        }
    }

    return result;
}

std::string getTime(int64_t timestamp)
{
#if defined(HOLO_TIME_WITH_MDC_TIME)
    time_t t = (time_t)(timestamp/1000000000);
#else
    time_t t          = time(NULL);
    (void)timestamp;
#endif
    char   result[64] = {0};
    strftime(result, sizeof(result) - 1, "%Y-%m-%d-%H-%M-%S", localtime(&t));
    return result;
}

holo::common::Timestamp GetCurrentUtcTime()
{
    uint32_t sec;
    uint32_t nsec;
    if (!holo::os::GetSystemTime(sec, nsec))
    {
        throw std::runtime_error("GetSystemTime failed");
    }
    holo::common::Timestamp utc(sec, nsec);

    return utc;
}

/* global function for capturing key event from keyboard */
static struct termios initial_settings, new_settings;

void init_keyboard()
{
    tcgetattr(STDIN_FILENO, &initial_settings);
    new_settings = initial_settings;
    new_settings.c_lflag &= ~ICANON;
    new_settings.c_lflag &= ~ECHO;
    new_settings.c_cc[VMIN]  = 1;
    new_settings.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &new_settings);
}

void close_keyboard()
{
    tcsetattr(STDIN_FILENO, TCSANOW, &initial_settings);
    // printf("\n--close keyboard\n");
}

int keyboard_hit()
{
    struct timeval tv;
    fd_set         fds;
    tv.tv_sec  = 0;
    tv.tv_usec = 0;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    return FD_ISSET(STDIN_FILENO, &fds);
}

int charToIntBig(holo::uint8_t const* src, int offset)
{
    int value;
    value = (int)(((src[offset] & 0xFF) << 24) | ((src[offset + 1] & 0xFF) << 16) | ((src[offset + 2] & 0xFF) << 8) |
                  (src[offset + 3] & 0xFF));
    return value;
}

int charToIntLittle(holo::uint8_t const* src, int offset)
{
    int value;
    value = (int)((src[offset] & 0xFF) | ((src[offset + 1] & 0xFF) << 8) | ((src[offset + 2] & 0xFF) << 16) |
                  ((src[offset + 3] & 0xFF) << 24));
    return value;
}

::holo::uint32_t uint32_t_to_big_endian(::holo::uint32_t data)
{
    return ((data & 0x000000ff) << 24 ) | ((data & 0x0000ff00) << 8) | ((data & 0x00ff0000) >> 8) | ((data & 0xff000000 ) >> 24);
}

::holo::uint64_t uint8_t_to_uint64_t(::holo::uint8_t const* buffer, std::size_t size)
{
    ::holo::uint8_t buff_data;
    ::holo::uint64_t swap_data;
    ::holo::uint64_t data = 0;

    for(size_t index = 0; index < size ; index++ )
    {
        buff_data = (*buffer);
        swap_data = buff_data;
        data += swap_data << (64 - 8 * (index + 1));
        buffer++;
    }
    return data;
}

}  // namespace holo_cmw