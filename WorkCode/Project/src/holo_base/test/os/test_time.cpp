#include <holo/os/time.h>

#include <holo/os/predefine.h>
#include <gtest/gtest.h>

#if defined(HOLO_PLATFORM_LINUX)

#include <iostream>

#elif defined(HOLO_PLATFORM_QNX)
// @TODO zhaofx 2019-09-12: Gtest for QNX
#else
error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif

#if defined(HOLO_PLATFORM_LINUX)
TEST(TestHoloTime, TestLocalTime)
{
    ::holo::uint32_t sec   = 0U;
    ::holo::uint32_t n_sec = 0U;
    ASSERT_TRUE(::holo::os::GetLocalTime(sec, n_sec));

    struct timespec t;
    clock_gettime(CLOCK_MONOTONIC, &t);

    ::holo::uint32_t truth_sec   = static_cast<::holo::uint32_t>(t.tv_sec);
    ::holo::uint32_t truth_n_sec = static_cast<::holo::uint32_t>(t.tv_nsec);

    ASSERT_NEAR(::holo::float64_t(sec + n_sec / 1e9), ::holo::float64_t(truth_sec + truth_n_sec / 1e9), 0.001);
}

TEST(TestHoloTime, TestSystemTime)
{
    ::holo::uint32_t sec   = 0U;
    ::holo::uint32_t n_sec = 0U;
    ASSERT_TRUE(::holo::os::GetSystemTime(sec, n_sec));

    struct timespec t;
    clock_gettime(CLOCK_REALTIME, &t);

    ::holo::uint32_t truth_sec   = static_cast<::holo::uint32_t>(t.tv_sec);
    ::holo::uint32_t truth_n_sec = static_cast<::holo::uint32_t>(t.tv_nsec);

    ASSERT_NEAR(::holo::float64_t(sec + n_sec / 1e9), ::holo::float64_t(truth_sec + truth_n_sec / 1e9), 0.001);
}

TEST(TestHoloSleep, TestSleep)
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    ::holo::os::Sleep(0.01f);
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);

    ::holo::uint32_t start_second      = static_cast<::holo::uint32_t>(start.tv_sec);
    ::holo::uint32_t start_nanoseconds = static_cast<::holo::uint32_t>(start.tv_nsec);

    ::holo::uint32_t  end_second      = static_cast<::holo::uint32_t>(end.tv_sec);
    ::holo::uint32_t  end_nanoseconds = static_cast<::holo::uint32_t>(end.tv_nsec);
    ::holo::float64_t remainder       = (end_nanoseconds - start_nanoseconds) / 1e9;
    ::holo::float64_t duration        = (end_second - start_second) + remainder;
    ASSERT_NEAR(duration, 0.01, 0.001);
}

TEST(TestHoloSleep, TestSleepForZero)
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    ::holo::os::Sleep(0.0);
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);

    ::holo::uint32_t start_second      = static_cast<::holo::uint32_t>(start.tv_sec);
    ::holo::uint32_t start_nanoseconds = static_cast<::holo::uint32_t>(start.tv_nsec);

    ::holo::uint32_t  end_second      = static_cast<::holo::uint32_t>(end.tv_sec);
    ::holo::uint32_t  end_nanoseconds = static_cast<::holo::uint32_t>(end.tv_nsec);
    ::holo::float64_t remainder       = (end_nanoseconds - start_nanoseconds) / 1e9;
    ::holo::float64_t duration        = (end_second - start_second) + remainder;
    ASSERT_NEAR(duration, 0.0, 0.001);
}

TEST(TestHoloSleep, TestSleepForNegative)
{
    struct timespec start;
    clock_gettime(CLOCK_MONOTONIC, &start);

    ::holo::os::Sleep(-10.0);
    struct timespec end;
    clock_gettime(CLOCK_MONOTONIC, &end);

    ::holo::uint32_t start_second      = static_cast<::holo::uint32_t>(start.tv_sec);
    ::holo::uint32_t start_nanoseconds = static_cast<::holo::uint32_t>(start.tv_nsec);

    ::holo::uint32_t  end_second      = static_cast<::holo::uint32_t>(end.tv_sec);
    ::holo::uint32_t  end_nanoseconds = static_cast<::holo::uint32_t>(end.tv_nsec);
    ::holo::float64_t remainder       = (end_nanoseconds - start_nanoseconds) / 1e9;
    ::holo::float64_t duration        = (end_second - start_second) + remainder;
    ASSERT_NEAR(duration, 0.0, 0.001);
}
#elif defined(HOLO_PLATFORM_QNX)
// @TODO zhaofx 2019-09-12: Gtest for QNX
#else
error "HOLO_BUILD_PLATFORM is wrong, please check it."
#endif

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
