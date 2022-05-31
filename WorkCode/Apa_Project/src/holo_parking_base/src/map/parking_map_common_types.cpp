#include <holo/parking/map/parking_map_common_types.h>

namespace holo
{
namespace parking
{
namespace map
{
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapPoint::UpdateState()
{
    Scalar mean, cov, square_error_sum = 0, error_sum = 0;

    if (!reprojection_errors.size())
    {
        return;
    }

    for (const auto error : reprojection_errors)
    {
        error_sum += error;
    }
    mean = error_sum / reprojection_errors.size();

    for (const auto error : reprojection_errors)
    {
        square_error_sum += std::pow((error - mean), 2);
    }
    cov = std::sqrt(square_error_sum / reprojection_errors.size());

    if (mean >= 2 || cov >= 2)
    {
        return;
    }
    life_long_states.back() = MapPointState::MATCHED;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void MapPoint::UpdateRememberRate()
{
    // update life long state of this localization
    UpdateState();

    if (life_long_states.back() == MapPointState::CANDIDATE)
    {
        return;
    }

    const Scalar old_remember_rate = remember_rate;
    const Scalar s_increase_step   = 19;

    uint64_t the_max_not_ob_times_bear = 8;
    uint64_t current_not_ob_times_bear = 0;
    Scalar   not_ob_times              = 0.0;
    Scalar   s_decrease_init           = 0.0;
    Scalar   new_remember_rate         = 0.0;

    uint64_t s_update_times = 0;
    for (uint64_t i = 0; i < life_long_states.size() - 1; i++)
    {
        if (life_long_states[i] != MapPointState::CANDIDATE)
        {
            s_update_times++;
        }
    }
    Scalar old_s = -(s_update_times / std::log(old_remember_rate));

    if (life_long_states.back() == MapPointState::MATCHED)
    {
        Scalar new_s      = old_s + s_increase_step;
        new_remember_rate = std::exp(-((int)s_update_times + 1) / new_s);
        remember_rate     = new_remember_rate;
        return;
    }

    for (int index = life_long_states.size() - 1; index >= 0; index--)
    {
        if (life_long_states[index] != MapPointState::MATCHED)
        {
            not_ob_times = (life_long_states[index] == MapPointState::VISIBLE) ? not_ob_times + 1 : not_ob_times;
            continue;
        }

        if (index <= 10)
        {
            current_not_ob_times_bear = 3;
        }
        else
        {
            uint64_t ob_times = 0;
            for (int i = 0; i <= index; i++)
            {
                if (life_long_states[i] == MapPointState::MATCHED)
                {
                    ob_times++;
                }
            }
            current_not_ob_times_bear = std::floor((ob_times / index) * 10);
        }

        uint64_t bear_times = std::min(the_max_not_ob_times_bear, current_not_ob_times_bear);

        if (not_ob_times > bear_times)
        {
            remember_rate = 0;
            return;
        }
        Scalar s_end_stop = -(int)(index + bear_times) / std::log(0.29);

        if (not_ob_times == 1)
        {
            s_decrease_init = old_s;
        }
        else
        {
            s_decrease_init = (bear_times * old_s - (not_ob_times - 1) * s_end_stop) / (bear_times + 1 - not_ob_times);
        }

        Scalar new_s      = s_decrease_init - (s_decrease_init - s_end_stop) / bear_times * not_ob_times;
        new_remember_rate = std::exp(-((int)s_update_times + 1) / new_s);
        break;
    }
    remember_rate = new_remember_rate;
}
}  // namespace map
}  // namespace parking
}  // namespace holo
