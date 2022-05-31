#ifndef HOLO_OS_SIGNAL_HANDLER_H
#define HOLO_OS_SIGNAL_HANDLER_H

#include <holo/core/types.h>
#include <holo/os/handler_action.h>
#include <array>
#include <csignal>
#include <functional>
#include <future>
#include <map>
#include <mutex>
#include <string>
#include <type_traits>
#include <vector>

namespace holo
{
namespace os
{
class SignalHandler final
{
    struct TaskPack
    {
        TaskPack() : name{}, func{nullptr}
        {
        }

        std::string                    name;
        std::function<HandlerAction()> func;
    };

    using TaskList = std::vector<TaskPack>;
    using TaskMap  = std::map<holo::int32_t, TaskList>;

public:
    static constexpr size_t SIGNAL_CORE_GROUP_SIZE{11U};
    static constexpr size_t SIGNAL_TERM_GROUP_SIZE{11U};
    static constexpr size_t SIGNAL_IGNORE_GROUP_SIZE{3U};

    template <typename Handler, typename... Args>
    static void RegisterHandler(holo::int32_t const signo, std::string const& handler_name, Handler&& handler,
                                Args&&... args)
    {
        using return_type = typename std::result_of<Handler(Args...)>::type;
        static_assert(std::is_same<typename std::decay<return_type>::type, HandlerAction>::value, "");

        RegisterHandler(signo, handler_name, -1, std::forward<Handler>(handler), std::forward<Args>(args)...);
    }

    template <typename Handler, typename... Args>
    static void RegisterHandler(holo::int32_t const signo, std::string const& handler_name, holo::int32_t const index,
                                Handler&& handler, Args&&... args)
    {
        using return_type = typename std::result_of<Handler(Args...)>::type;
        static_assert(std::is_same<typename std::decay<return_type>::type, HandlerAction>::value, "");

        TaskPack task_pack = packageTask(handler_name, std::forward<Handler>(handler), std::forward<Args>(args)...);

        insertHandler(signo, index, task_pack);

        (void)signal(signo, signalHandle);
    }

    template <typename Handler, typename... Args>
    static void RegisterTermGroupHandler(std::string const& handler_name, Handler&& handler, Args&&... args)
    {
        using return_type = typename std::result_of<Handler(Args...)>::type;
        static_assert(std::is_same<typename std::decay<return_type>::type, HandlerAction>::value, "");

        RegisterTermGroupHandler(handler_name, -1, std::forward<Handler>(handler), std::forward<Args>(args)...);
    }

    template <typename Handler, typename... Args>
    static void RegisterTermGroupHandler(std::string const& handler_name, holo::int32_t const index, Handler&& handler,
                                         Args&&... args)
    {
        using return_type = typename std::result_of<Handler(Args...)>::type;
        static_assert(std::is_same<typename std::decay<return_type>::type, HandlerAction>::value, "");

        TaskPack task_pack = packageTask(handler_name, std::forward<Handler>(handler), std::forward<Args>(args)...);

        for (size_t i = 0U; i < SIGNAL_TERM_GROUP_SIZE; i++)
        {
            insertHandler(signal_term_group_[i], index, task_pack);

            (void)signal(signal_term_group_[i], signalHandle);
        }
    }

    template <typename Handler, typename... Args>
    static void RegisterCoreGroupHandler(std::string const& handler_name, Handler&& handler, Args&&... args)
    {
        using return_type = typename std::result_of<Handler(Args...)>::type;
        static_assert(std::is_same<typename std::decay<return_type>::type, HandlerAction>::value, "");

        RegisterCoreGroupHandler(handler_name, -1, std::forward<Handler>(handler), std::forward<Args>(args)...);
    }

    template <typename Handler, typename... Args>
    static void RegisterCoreGroupHandler(std::string const& handler_name, holo::int32_t const index, Handler&& handler,
                                         Args&&... args)
    {
        using return_type = typename std::result_of<Handler(Args...)>::type;
        static_assert(std::is_same<typename std::decay<return_type>::type, HandlerAction>::value, "");

        TaskPack task_pack = packageTask(handler_name, std::forward<Handler>(handler), std::forward<Args>(args)...);

        for (size_t i = 0U; i < SIGNAL_CORE_GROUP_SIZE; i++)
        {
            insertHandler(signal_core_group_[i], index, task_pack);

            (void)signal(signal_core_group_[i], signalHandle);
        }
    }

    template <typename Handler, typename... Args>
    static void RegisterIgnoreGroupHandler(std::string const& handler_name, Handler&& handler, Args&&... args)
    {
        using return_type = typename std::result_of<Handler(Args...)>::type;
        static_assert(std::is_same<typename std::decay<return_type>::type, HandlerAction>::value, "");

        RegisterIgnoreGroupHandler(handler_name, -1, std::forward<Handler>(handler), std::forward<Args>(args)...);
    }

    template <typename Handler, typename... Args>
    static void RegisterIgnoreGroupHandler(std::string const& handler_name, holo::int32_t const index,
                                           Handler&& handler, Args&&... args)
    {
        using return_type = typename std::result_of<Handler(Args...)>::type;
        static_assert(std::is_same<typename std::decay<return_type>::type, HandlerAction>::value, "");

        TaskPack task_pack = packageTask(handler_name, std::forward<Handler>(handler), std::forward<Args>(args)...);

        for (size_t i = 0U; i < SIGNAL_IGNORE_GROUP_SIZE; i++)
        {
            insertHandler(signal_ignore_group_[i], index, task_pack);

            signal(signal_ignore_group_[i], signalHandle);
        }
    }

    static void CleanHandler(holo::int32_t signo);
    static void CleanHandler(holo::int32_t signo, std::string const& handler_name);
    static void CleanTermGroupHandler();
    static void CleanCoreGroupHandler();
    static void CleanIgnoreGroupHandler();

    static std::vector<std::string> GetHandler(holo::int32_t const signo);

    static void InstallStackTraceHandler(std::function<void(std::string const&)> const& handler);

private:
    SignalHandler() = delete;
    static void          dump(holo::int32_t const signo);
    static void          signalHandle(holo::int32_t const signo);
    static HandlerAction doTasks(holo::int32_t const signo);

    template <typename Handler, typename... Args>
    static TaskPack packageTask(std::string const& handler_name, Handler&& handler, Args&&... args)
    {
        auto task = std::bind(std::forward<Handler>(handler), std::forward<Args>(args)...);

        TaskPack task_pack{};
        task_pack.name = handler_name;
        task_pack.func = task;

        return task_pack;
    }

    static void insertHandler(holo::int32_t const signo, holo::int32_t const index, TaskPack const& task_pack);

private:
    static std::mutex                                          mutex_;
    static TaskMap                                             signal_handler_map_;
    static std::array<holo::int32_t, SIGNAL_CORE_GROUP_SIZE>   signal_core_group_;
    static std::array<holo::int32_t, SIGNAL_TERM_GROUP_SIZE>   signal_term_group_;
    static std::array<holo::int32_t, SIGNAL_IGNORE_GROUP_SIZE> signal_ignore_group_;
    static std::function<void(std::string const&)>             stack_trace_handler_;
};

}  // namespace os
}  // namespace holo

#endif
