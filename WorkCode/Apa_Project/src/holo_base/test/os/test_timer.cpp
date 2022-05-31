#include <holo/os/timer.h>
#include <gtest/gtest.h>

TEST(TestTimer, TimerGeneral)
{
    ::holo::Timer timer(100.0f);
    timer.Start();
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    ::holo::uint32_t start_second      = static_cast<::holo::uint32_t>(start.tv_sec);
    ::holo::uint32_t start_nanoseconds = static_cast<::holo::uint32_t>(start.tv_nsec);

    timer.Stop();
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    ::holo::uint32_t end_second      = static_cast<::holo::uint32_t>(end.tv_sec);
    ::holo::uint32_t end_nanoseconds = static_cast<::holo::uint32_t>(end.tv_nsec);

    ASSERT_GT(
        (::holo::float64_t(end_second - start_second) + ::holo::float64_t(end_nanoseconds - start_nanoseconds) / 1e9),
        0.01);
}

TEST(TestTimer, TimerSleep)
{
    // hz is 100.0, duration is (1 / 100.0) second
    ::holo::Timer timer(100.0f);
    timer.Start();
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    ::holo::uint32_t start_second      = static_cast<::holo::uint32_t>(start.tv_sec);
    ::holo::uint32_t start_nanoseconds = static_cast<::holo::uint32_t>(start.tv_nsec);

    timer.Stop();
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    ::holo::uint32_t end_second      = static_cast<::holo::uint32_t>(end.tv_sec);
    ::holo::uint32_t end_nanoseconds = static_cast<::holo::uint32_t>(end.tv_nsec);

    ASSERT_GT(
        (::holo::float64_t(end_second - start_second) + ::holo::float64_t(end_nanoseconds - start_nanoseconds) / 1e9),
        ::holo::float64_t(1 / 100.0));
}
#if 0
// These two unit tests cost to much time, so comment them.
TEST(TestTimer, TimerZeroHZ)
{
    ::holo::Timer timer(0.0f);
    timer.Start();
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    ::holo::uint32_t start_second      = static_cast<::holo::uint32_t>(start.tv_sec);
    ::holo::uint32_t start_nanoseconds = static_cast<::holo::uint32_t>(start.tv_nsec);

    timer.Stop();
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    ::holo::uint32_t end_second      = static_cast<::holo::uint32_t>(end.tv_sec);
    ::holo::uint32_t end_nanoseconds = static_cast<::holo::uint32_t>(end.tv_nsec);

    ASSERT_GT(((end_second - start_second) + ::holo::float64_t(end_nanoseconds - start_nanoseconds) / 1e9), 1.0);
}

TEST(TestTimer, TimerNegativeHZ)
{
    ::holo::Timer timer(-100.0f);
    timer.Start();
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    ::holo::uint32_t start_second      = static_cast<::holo::uint32_t>(start.tv_sec);
    ::holo::uint32_t start_nanoseconds = static_cast<::holo::uint32_t>(start.tv_nsec);

    timer.Stop();
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    ::holo::uint32_t end_second      = static_cast<::holo::uint32_t>(end.tv_sec);
    ::holo::uint32_t end_nanoseconds = static_cast<::holo::uint32_t>(end.tv_nsec);

    ASSERT_GT(((end_second - start_second) + ::holo::float64_t(end_nanoseconds - start_nanoseconds) / 1e9), 1.0);
}

TEST(TestTimer, TimerSmallHZ)
{
    ::holo::Timer timer(0.5f);
    timer.Start();
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);
    ::holo::uint32_t start_second      = static_cast<::holo::uint32_t>(start.tv_sec);
    ::holo::uint32_t start_nanoseconds = static_cast<::holo::uint32_t>(start.tv_nsec);

    std::this_thread::sleep_for(std::chrono::duration<::holo::float64_t, std::milli>(1000));

    timer.Stop();
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);
    ::holo::uint32_t end_second      = static_cast<::holo::uint32_t>(end.tv_sec);
    ::holo::uint32_t end_nanoseconds = static_cast<::holo::uint32_t>(end.tv_nsec);

    ASSERT_GT(((end_second - start_second) + ::holo::float64_t(end_nanoseconds - start_nanoseconds) / 1e9), 1.0 / 0.5f);

    //////////////////////////////////////////////////////////////////////////////////////////////
    timer.Start();
    clock_gettime(CLOCK_MONOTONIC, &start);
    start_second      = static_cast<::holo::uint32_t>(start.tv_sec);
    start_nanoseconds = static_cast<::holo::uint32_t>(start.tv_nsec);

    std::this_thread::sleep_for(std::chrono::duration<::holo::float64_t, std::milli>(3000));

    timer.Stop();
    clock_gettime(CLOCK_MONOTONIC, &end);
    end_second      = static_cast<::holo::uint32_t>(end.tv_sec);
    end_nanoseconds = static_cast<::holo::uint32_t>(end.tv_nsec);

    ASSERT_NEAR(3.0, ((end_second - start_second) + ::holo::float64_t(end_nanoseconds - start_nanoseconds) / 1e9),
                0.001);
}
#endif

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
