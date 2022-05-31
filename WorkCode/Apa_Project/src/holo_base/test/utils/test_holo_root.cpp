/*!
 *  \brief Unit test for holo_root utils
 *  \author zhangjiannan(zhangjiannan@holomatic.com)
 *  \date 2019-1-21
 *  \attention Copyright © Holomatic Technology (Beijing) Co.Ltd
 *  \attention Please refer to COPYRIGHT.txt for complete terms of copyright notice.
 */

#include <iostream>
#include <gtest/gtest.h>
#include <holo/utils/holo_root.h>
#include <stdlib.h>

TEST(TestHoloRootFunctions, TestHoloRoot)
{
    ASSERT_TRUE(holo::IsAbsolutePath("/opt/holo"));
    ASSERT_FALSE(holo::IsAbsolutePath("opt/holo"));
    unsetenv("HOLO_ROOT");
    unsetenv("HOLO_3RDPARTY_ROOT");
    unsetenv("HOLO_CONFIG_ROOT");
    unsetenv("HOLO_LOG_ROOT");
    ASSERT_TRUE(holo::GetHoloRootDirectory() == "/opt/holo");
    ASSERT_TRUE(holo::GetHoloConfigRootDirectory() == "/opt/holo/config");
    ASSERT_TRUE(holo::GetHoloLogRootDirectory() == "/opt/holo/log");

    setenv("HOLO_CONFIG_ROOT", "/etc/holo/config", true);
    ASSERT_TRUE(holo::GetHoloRootDirectory() == "/opt/holo");
    ASSERT_TRUE(holo::GetHoloConfigRootDirectory() == "/etc/holo/config");
    ASSERT_TRUE(holo::GetHoloLogRootDirectory() == "/opt/holo/log");
    unsetenv("HOLO_CONFIG_ROOT");

    setenv("HOLO_LOG_ROOT", "/var/holo/log", true);
    ASSERT_TRUE(holo::GetHoloRootDirectory() == "/opt/holo");
    ASSERT_TRUE(holo::GetHoloConfigRootDirectory() == "/opt/holo/config");
    ASSERT_TRUE(holo::GetHoloLogRootDirectory() == "/var/holo/log");
    unsetenv("HOLO_LOG_ROOT");

    setenv("HOLO_ROOT", "/opt/holo2", true);
    ASSERT_TRUE(holo::GetHoloRootDirectory() == "/opt/holo2");
    ASSERT_TRUE(holo::GetHoloConfigRootDirectory() == "/opt/holo2/config");
    ASSERT_TRUE(holo::GetHoloLogRootDirectory() == "/opt/holo2/log");
    unsetenv("HOLO_ROOT");

    std::string path = "test/config.yaml";
    ASSERT_TRUE("/test/config.yaml" == holo::GetFileAbsolutePath(path));
    ASSERT_TRUE("/opt/holo/test/config.yaml" == holo::GetFileAbsolutePath(path, "/opt/holo"));

    setenv("HOLO_ROOT", "/opt/holo3", true);
    ASSERT_TRUE("/opt/holo3/log/test/config.yaml" == holo::GetLogFileAbsolutePath(path));
    ASSERT_TRUE("/opt/holo3/config/test/config.yaml" == holo::GetConfigFileAbsolutePath(path));
    unsetenv("HOLO_ROOT");

}

TEST(TestCreateDirectories, TestHoloRoot)
{
    setenv("HOLO_ROOT", "/tmp/holo/unit_test", true);
    ASSERT_TRUE(holo::CreateHoloLogSubdirectory("base/holo_root"));
    ASSERT_TRUE(holo::CreateHoloLogSubdirectory("base/holo_root/"));
    struct stat statbuf;
    ASSERT_EQ(0, stat("/tmp/holo/unit_test/log/base/holo_root", &statbuf));
    ASSERT_EQ(1, S_ISDIR(statbuf.st_mode));
    //TODO remove created directory
}

TEST(TestCreateDirectories, IsAbsolutePath)
{
    ASSERT_FALSE(holo::IsAbsolutePath(""));
}

TEST(TestCreateDirectories, GetFileAbsolutePath)
{
    holo::GetFileAbsolutePath("/holo", "/matic");
}

TEST(TestCreateDirectories, GetParentDirectory)
{
    holo::GetParentDirectory("/holo/matic/xxx");
    holo::GetParentDirectory("/holo/matic/xxx/");
    holo::GetParentDirectory("/holo/matic/xxx/xxx.txt");
    holo::GetParentDirectory("xxx.txt");

}

TEST(TestCreateDirectories, CreateHoloLogSubdirectory)
{
    holo::CreateHoloLogSubdirectory("xxx");
    holo::CreateHoloLogSubdirectory("/xxx");
    holo::CreateHoloLogSubdirectory("xxx.txt");
    holo::CreateHoloLogSubdirectory("");
}

TEST(TestCreateDirectories, GetCurrentExecPath)
{
    holo::GetCurrentExecPath();
}

TEST(TestCreateDirectories, GetCurrentExecDirectory)
{
    holo::GetCurrentExecDirectory();
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
