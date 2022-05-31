#ifdef __linux__
#include <execinfo.h>/* for backtrace() */
#elif __QNX__
#else
#endif

#include <holo/os/signal_handler.h>
#include <signal.h>
#include <iostream>
#include <sstream>

namespace holo
{
namespace os
{
static constexpr holo::int32_t BACKTRACE_SIZE{64};
std::mutex                     SignalHandler::mutex_{};
SignalHandler::TaskMap         SignalHandler::signal_handler_map_{};
using StackTraceHandler = std::function<void(std::string const&)>;
StackTraceHandler SignalHandler::stack_trace_handler_{};

/*
 * Signal        x86/ARM     Alpha/   MIPS   PARISC   Notes
                   most others   SPARC
       ─────────────────────────────────────────────────────────────────
       SIGHUP           1           1       1       1
       SIGINT           2           2       2       2
       SIGQUIT          3           3       3       3
       SIGILL           4           4       4       4
       SIGTRAP          5           5       5       5
       SIGABRT          6           6       6       6
       SIGIOT           6           6       6       6
       SIGBUS           7          10      10      10
       SIGEMT           -           7       7      -
       SIGFPE           8           8       8       8
       SIGKILL          9           9       9       9
       SIGUSR1         10          30      16      16
       SIGSEGV         11          11      11      11
       SIGUSR2         12          31      17      17
       SIGPIPE         13          13      13      13
       SIGALRM         14          14      14      14
       SIGTERM         15          15      15      15
       SIGSTKFLT       16          -       -        7
       SIGCHLD         17          20      18      18
       SIGCLD           -          -       18      -
       SIGCONT         18          19      25      26
       SIGSTOP         19          17      23      24
       SIGTSTP         20          18      24      25
       SIGTTIN         21          21      26      27
       SIGTTOU         22          22      27      28
       SIGURG          23          16      21      29
       SIGXCPU         24          24      30      12
       SIGXFSZ         25          25      31      30
       SIGVTALRM       26          26      28      20
       SIGPROF         27          27      29      21
       SIGWINCH        28          28      20      23
       SIGIO           29          23      22      22
       SIGPOLL                                            Same as SIGIO
       SIGPWR          30         29/-     19      19
       SIGINFO          -         29/-     -       -
       SIGLOST          -         -/29     -       -
       SIGSYS          31          12      12      31
       SIGUNUSED       31          -       -       31
 * */
using CoreGroupArrayType = std::array<holo::int32_t, SignalHandler::SIGNAL_CORE_GROUP_SIZE>;
CoreGroupArrayType SignalHandler::signal_core_group_{SIGABRT, SIGBUS, SIGFPE,  SIGILL,  SIGIOT, SIGQUIT,
                                                     SIGSEGV, SIGSYS, SIGTRAP, SIGXCPU, SIGXFSZ};

// The signals SIGKILL and SIGSTOP cannot be caught, blocked, or ignored.
using TermGroupArrayType = std::array<holo::int32_t, SignalHandler::SIGNAL_TERM_GROUP_SIZE>;
TermGroupArrayType SignalHandler::signal_term_group_{SIGALRM, SIGHUP,  SIGINT,  SIGKILL, SIGPIPE,  SIGPOLL,
                                                     SIGPROF, SIGTERM, SIGUSR1, SIGUSR2, SIGVTALRM};

using IgnoreGroupArrayType = std::array<holo::int32_t, SignalHandler::SIGNAL_IGNORE_GROUP_SIZE>;
IgnoreGroupArrayType SignalHandler::signal_ignore_group_{SIGCHLD, SIGURG, SIGWINCH};

void SignalHandler::insertHandler(holo::int32_t const signo, holo::int32_t const index, TaskPack const& task_pack)
{
    std::lock_guard<std::mutex> const locker{mutex_};
    TaskMap::iterator const           map_it{signal_handler_map_.find(signo)};

    if (map_it != signal_handler_map_.end())
    {
        TaskList& list{map_it->second};
        if (index == -1)
        {
            list.emplace_back(task_pack);
        }
        else
        {
            if (static_cast<holo::int32_t>(list.size()) > index)
            {
                TaskList::const_iterator const list_it{list.cbegin()};
                (void)list.insert(list_it + index, task_pack);
            }
            else
            {
                list.emplace_back(task_pack);
            }
        }
    }
    else
    {
        TaskList list{};
        list.emplace_back(task_pack);
        (void)signal_handler_map_.emplace(signo, list);
    }
}

void SignalHandler::CleanHandler(holo::int32_t const signo)
{
    (void)signal(signo, SIG_DFL);

    std::lock_guard<std::mutex> const locker{mutex_};
    (void)signal_handler_map_.erase(signo);
}

void SignalHandler::CleanHandler(holo::int32_t signo, std::string const& handler_name)
{
    std::lock_guard<std::mutex> locker{mutex_};

    TaskMap::iterator map_it{signal_handler_map_.find(signo)};

    if (map_it != signal_handler_map_.end())
    {
        TaskList&          task_list = map_it->second;
        TaskList::iterator list_it   = task_list.begin();
        while (list_it != task_list.end())
        {
            if (handler_name == list_it->name)
            {
                list_it = task_list.erase(list_it);
                continue;
            }

            ++list_it;
        }

        if (0U == task_list.size())
        {
            (void)signal(signo, SIG_DFL);
        }
    }
}

void SignalHandler::CleanTermGroupHandler()
{
    for (size_t i = 0U; i < SIGNAL_TERM_GROUP_SIZE; i++)
    {
        CleanHandler(signal_term_group_[i]);
    }
}

void SignalHandler::CleanCoreGroupHandler()
{
    for (size_t i = 0U; i < SIGNAL_CORE_GROUP_SIZE; i++)
    {
        CleanHandler(signal_core_group_[i]);
    }
}

void SignalHandler::CleanIgnoreGroupHandler()
{
    for (size_t i = 0U; i < SIGNAL_IGNORE_GROUP_SIZE; i++)
    {
        CleanHandler(signal_ignore_group_[i]);
    }
}

std::vector<std::string> SignalHandler::GetHandler(holo::int32_t const signo)
{
    std::vector<std::string> result{};

    std::lock_guard<std::mutex> const locker{mutex_};

    TaskMap::iterator const map_it{signal_handler_map_.find(signo)};

    if (map_it != signal_handler_map_.end())
    {
        TaskList& task_list{map_it->second};
        for (auto const& task : task_list)
        {
            result.emplace_back(task.name);
        }
    }

    return result;
}
void SignalHandler::InstallStackTraceHandler(std::function<void(std::string const&)> const& handler)
{
    stack_trace_handler_ = handler;
}

void SignalHandler::dump(holo::int32_t const signo)
{
    (void)signo;

#ifdef __linux__
    void*             buffer[BACKTRACE_SIZE];
    std::stringstream sout;

    holo::int32_t nptrs = backtrace(buffer, BACKTRACE_SIZE);

    char** backtrace_info = backtrace_symbols(buffer, nptrs);
    if (backtrace_info == nullptr)
    {
        std::cout << "backtrace_symbols nonsupport!" << std::endl;
        return;
    }

    sout << "receive signal number is:" << signo << std::endl;
    sout << "stack trace:" << std::endl;
    for (holo::int32_t i = 0; i < nptrs; i++)
    {
        sout << "[" << i << "] " << backtrace_info[i] << std::endl;
    }

    free(backtrace_info);

    if (stack_trace_handler_)
    {
        stack_trace_handler_(sout.str());
    }
#endif
}

void SignalHandler::signalHandle(holo::int32_t const signo)
{
    dump(signo);

    HandlerAction action = doTasks(signo);

    if (HandlerAction::CONTINUE == action)
    {
        (void)signal(signo, SIG_DFL);

        (void)raise(signo);
    }
}

HandlerAction SignalHandler::doTasks(holo::int32_t const signo)
{
    TaskList task_list{};

    {
        std::lock_guard<std::mutex> locker{mutex_};

        TaskMap::iterator map_it{signal_handler_map_.find(signo)};

        if (map_it != signal_handler_map_.end())
        {
            task_list = map_it->second;
        }
    }

    HandlerAction action{HandlerAction::CONTINUE};

    for (auto const& task : task_list)
    {
        action = task.func();
        if (HandlerAction::BREAK == action)
        {
            break;
        }
    }

    return action;
}

}  // namespace os
}  // namespace holo
