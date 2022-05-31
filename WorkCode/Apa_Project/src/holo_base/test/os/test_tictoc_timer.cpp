#include <holo/os/tictoc_timer.h>
#include <gtest/gtest.h>

TEST(TestHoloSleep, TicTocTimer)
{
    ::holo::TicTocTimer tictoc;
    tictoc.Tic();

    struct timespec sleep_time;
    sleep_time.tv_sec =0;
    sleep_time.tv_nsec = 10000000;
    nanosleep(&sleep_time, NULL);

    ASSERT_NEAR(0.01, tictoc.Elapsed(), 0.001);

    tictoc.Tic();
    sleep_time.tv_sec =0;
    sleep_time.tv_nsec = 20000000;
    nanosleep(&sleep_time, NULL);
    ASSERT_NEAR(0.02, tictoc.Elapsed(), 0.001);

    tictoc.Tic();
    ASSERT_NEAR(0.0, tictoc.Elapsed(), 0.001);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
