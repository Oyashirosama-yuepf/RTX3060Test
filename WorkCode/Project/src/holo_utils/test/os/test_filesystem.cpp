

/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_file_system.cpp
 * @brief unit test for file system class
 * @author zhouhuishuang@holomatic.com
 * @date 2022-02-15
 */
#include <gtest/gtest.h>
#include <holo/os/filesystem.h>
using FileSystem = holo::os::FileSystem;

TEST(FileSystem, ListFiles)
{
    FileSystem               fp;
    std::vector<std::string> res;
    fp.ListFiles("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config", false, res);
    for (auto path : res)
        std::cout << path << std::endl;

    fp.ListFiles("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config", true, res);
    for (auto path : res)
        std::cout << path << std::endl;
}

TEST(FileSystem, IsFile)
{
    FileSystem fp;
    ASSERT_FALSE(fp.IsFile("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/record_topics.json"));
    ASSERT_TRUE(fp.IsFile("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/record_topics.yaml"));
}

TEST(FileSystem, IsDirectory)
{
    FileSystem fp;
    ASSERT_TRUE(fp.IsDirectory("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config"));
    ASSERT_FALSE(fp.IsDirectory("/home/holo/test_workspace4/output/native/relwithdebinfo/target/xxx"));
    ASSERT_FALSE(
        fp.IsDirectory("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/record_topics.yaml"));
}

TEST(FileSystem, CreateFile)
{
    FileSystem fp;
    fp.CreateFile("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/xxx.yaml");
    ASSERT_TRUE(fp.IsFile("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/xxx.yaml"));
}

TEST(FileSystem, CreateFolder)
{
    FileSystem fp;
    fp.CreateFolder("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/a3");
    ASSERT_TRUE(fp.IsDirectory("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/a3"));
}

TEST(FileSystem, RemoveFile)
{
    FileSystem fp;
    fp.CreateFile("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/xxx.yaml");
    ASSERT_TRUE(fp.RemoveFile("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/xxx.yaml"));
}

TEST(FileSystem, RemoveFolder)
{
    FileSystem fp;
    fp.CreateFolder("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/a3");
    ASSERT_TRUE(fp.RemoveFolder("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/a3"));
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
