/**
 * @file utils.cpp
 * @author liwenchao (liwenchao@holomatic.com)
 * @brief 
 * @date 2020-09-24
 * 
 * @copyright Copyright (c) 2020
 * 
 */

#include <include/utils.h>
#include <termios.h>

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

std::string getTime()
{
    time_t t          = time(NULL);
    char   result[64] = {0};
    strftime(result, sizeof(result) - 1, "%Y-%m-%d-%H-%M-%S", localtime(&t));
    return result;
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

/* cmw-related global function */
bool is_on_playing()
{
    return !is_cmw_app_abort;
}

void set_stop_flag()
{
    is_cmw_app_abort = true;
}

void set_cmw_spin()
{
    is_cmw_app_spin = true;
}

void set_play_flag()
{
    is_cmw_app_abort = false;
}

}  // namespace holo_cmw