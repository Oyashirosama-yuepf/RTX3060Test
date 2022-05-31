#include <gtest/gtest.h>

using namespace holo_cmw;

TEST(Sample, All)
{
    ASSERT_TRUE(true);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
