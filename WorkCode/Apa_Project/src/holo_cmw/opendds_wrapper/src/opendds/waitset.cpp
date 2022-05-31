#include <opendds_wrapper/details/waitset.h>

namespace opendds_wrapper
{
WaitSet::WaitSet() : callback_map_{}, schedule_map_{}, waitset_{}
{
}

void WaitSet::AddCallback(DDS::Condition* condition, std::function<void()> const& callback)
{
    {
        std::lock_guard<std::mutex> locker{callback_mutex_};
        callback_map_[condition] = callback;
    }

    DDS::ReturnCode_t retcode = waitset_.attach_condition(condition);
    if (retcode != DDS::RETCODE_OK)
    {
        throw opendds_wrapper::exceptions::OpenddsInternalErrorException("Failed to attach_condition");
    }
}

std::function<void()> WaitSet::GetCallback(DDS::Condition* condition)
{
    std::lock_guard<std::mutex> locker{callback_mutex_};
    CallbackMap::const_iterator it = callback_map_.find(condition);
    if (it != callback_map_.end())
    {
        return it->second;
    }

    throw opendds_wrapper::exceptions::InvalidConditionException{"waitset callback is not exist!"};
}

void WaitSet::DeleteCallback(DDS::Condition* condition)
{
    std::lock_guard<std::mutex> locker{callback_mutex_};

    DDS::ReturnCode_t retcode = waitset_.detach_condition(condition);
    if (retcode != DDS::RETCODE_OK)
    {
    }

    CallbackMap::iterator it = callback_map_.find(condition);
    if (it != callback_map_.end())
    {
        it = callback_map_.erase(it);
    }
}

void WaitSet::DeleteAllCallback()
{
    std::lock_guard<std::mutex> locker{callback_mutex_};
    for (auto const& it : callback_map_)
    {
        DDS::ReturnCode_t retcode = waitset_.detach_condition(it.first);
        if (retcode != DDS::RETCODE_OK)
        {
        }
    }
    callback_map_.clear();
}

DDS::ReturnCode_t WaitSet::Wait(DDS::ConditionSeq& seq, int32_t sec, uint32_t nsec)
{
    return waitset_.wait(seq, {sec, nsec});
}

void WaitSet::AddSchedule(DDS::Condition* condition)
{
    std::lock_guard<std::mutex> locker{schedule_mutex_};
    ScheduleMap::iterator       it = schedule_map_.find(condition);
    if (it == schedule_map_.end())
    {
        schedule_map_[condition] = false;
    }
}

void WaitSet::SetSchedule(DDS::Condition* condition, bool schedule)
{
    std::lock_guard<std::mutex> locker{schedule_mutex_};
    ScheduleMap::iterator       it = schedule_map_.find(condition);
    if (it != schedule_map_.end())
    {
        it->second = schedule;
        return;
    }

    throw opendds_wrapper::exceptions::InvalidConditionException{"WaitSet::SetSchedule: condition is not exist!"};
}

bool WaitSet::GetSchedule(DDS::Condition* condition)
{
    std::lock_guard<std::mutex> locker{schedule_mutex_};
    ScheduleMap::iterator       it = schedule_map_.find(condition);
    if (it != schedule_map_.end())
    {
        return it->second;
    }

    throw opendds_wrapper::exceptions::InvalidConditionException{"WaitSet::SetSchedule: condition is not exist!"};
}

void WaitSet::DeleteSchedule(DDS::Condition* condition)
{
    std::lock_guard<std::mutex> locker{schedule_mutex_};
    ScheduleMap::iterator       it = schedule_map_.find(condition);
    if (it != schedule_map_.end())
    {
        it = schedule_map_.erase(it);
    }
}

void WaitSet::DeleteAllSchedule()
{
    std::lock_guard<std::mutex> locker{schedule_mutex_};
    schedule_map_.clear();
}

}  // namespace opendds_wrapper
