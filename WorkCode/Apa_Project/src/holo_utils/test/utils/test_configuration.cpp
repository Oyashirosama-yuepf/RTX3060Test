/*
 * Copyright (C) HoloMatic Technology(Beijing) Co., Ltd. - All Rights Reserved
 * Unauthorized copying of this file, via any medium is strictly prohibited
 * Proprietary and confidential
 */

/**
 * @file test_configuration.cpp
 * @brief unit test for config class
 * @author zhouhuishuang@holomatic.com
 * @date 2020-11-25
 */
#include <gtest/gtest.h>

#include <holo/utils/configuration.h>

// #include <holo/common/alarm.h>
// #include <holo/common/timestamp.h>
// #include <holo/io/common/alarm.h>
// #include <holo/io/common/timestamp.h>

using Configuration = holo::utils::Configuration;
// using Timestamp     = holo::common::Timestamp;
// using Alarm         = holo::common::Alarm;

#if 0
TEST(Configuration, getConfigPathFromEnv_No_Environment)
{
    Configuration config;
    EXPECT_THROW(config.getConfigPathFromEnv(), holo::exception::RuntimeErrorException());
}

TEST(Configuration, getConfigPathFromEnv_HOLO_CONFIG_ROOT)
{
    Configuration config;
    char env[] = "HOLO_CONFIG_ROOT=/xxx/yyy";
    putenv(env); 
    ASSERT_EQ("/xxx/yyy", config.getConfigPathFromEnv());
    unsetenv("HOLO_CONFIG_ROOT");
}

TEST(Configuration, getConfigPathFromEnv_HOLO_ROOT)
{
    Configuration config;
    char env[] = "HOLO_ROOT=/xxx/yyy";
    putenv(env); 
    ASSERT_EQ("/xxx/yyy/config", config.getConfigPathFromEnv());
    unsetenv("HOLO_ROOT");
}

/**
 * @brief Test absolute path
 */
TEST(Configuration, getAbsolutePath_1)
{
    Configuration config;
    std::string path = "/holo/home/xxx";
    ASSERT_EQ(path, config.getAbsolutePath(path));
}

/**
 * @brief Test relative path
 */
TEST(Configuration, getAbsolutePath_2)
{
    Configuration config;
    char env[] = "HOLO_CONFIG_ROOT=/xxx/yyy";
    putenv(env); 

    ASSERT_EQ("/xxx/yyy/intrinsic", config.getAbsolutePath("intrinsic"));
    unsetenv("HOLO_CONFIG_ROOT");

    char env2[] = "HOLO_ROOT=/xxx/zzz";
    putenv(env2); 
    ASSERT_EQ("/xxx/zzz/config/intrinsic", config.getAbsolutePath("intrinsic"));
    unsetenv("HOLO_ROOT");

    EXPECT_THROW(config.getAbsolutePath("intrinsic"), holo::exception::RuntimeErrorException);
}

TEST(Configuration, startsWith)
{
    Configuration config;
    ASSERT_TRUE(config.startsWith("/abcde", "/"));
    ASSERT_TRUE(config.startsWith("/abcde", "/abc"));
    ASSERT_FALSE(config.startsWith("abcde", "de"));
}

TEST(Configuration, MergeMap)
{
    YAML::Node girl_node = YAML::Load("{'name':'mary','age':10, 'color':'red','school':{'address':'beijing', 'level': [1,2,3]}}");
    YAML::Node boy_node = YAML::Load("{'name':'john','age':13,'school':{'address':'shanghai', 'level': [4,5], 'other':'other'}}");

    Configuration config;
    config.MergeMap(girl_node, boy_node);

    ASSERT_EQ(girl_node["name"], boy_node["name"]); 
    ASSERT_EQ(girl_node["school"]["level"], boy_node["school"]["level"]); 
    ASSERT_EQ("other", boy_node["school"]["other"].as<std::string>());
    ASSERT_EQ("red", boy_node["color"].as<std::string>()); 
 
}

TEST(Configuration, MergeNode_Scalar)
{
    YAML::Node girl_node = YAML::Load("{'name':'mary','age':10,'school':{'address':'beijing', 'level': [1,2,3]}}");
    YAML::Node boy_node = YAML::Load("{'name':'john','age':13,'school':{'address':'shanghai', 'level': [1,2,3], 'other':'other'}}");

    Configuration config;

    config.MergeNode(girl_node["age"], boy_node["age"]);
    ASSERT_TRUE(boy_node["age"].IsScalar());    
    ASSERT_EQ(10, boy_node["age"].as<uint16_t>()); 
}

TEST(Configuration, MergeNode_Sequece)
{
    YAML::Node girl_node = YAML::Load("{'name':'mary','age':10,'school':{'address':'beijing', 'level': [1,2,3]}}");
    YAML::Node boy_node = YAML::Load("{'name':'john','age':13,'school':{'address':'shanghai', 'level': [4,5], 'other':'other'}}");

    Configuration config;

    config.MergeNode(girl_node["school"]["level"], boy_node["school"]["level"]);
    ASSERT_TRUE(boy_node["school"]["level"].IsSequence());  
    ASSERT_EQ(3, boy_node["school"]["level"].size()); 
    ASSERT_EQ(1, boy_node["school"]["level"][0].as<uint16_t>()); 

    config.MergeNode(girl_node["age"], boy_node["school"]["level"]);
    ASSERT_TRUE(boy_node["school"]["level"].IsScalar());    
    ASSERT_EQ(10, boy_node["school"]["level"].as<uint16_t>()); 

    ASSERT_TRUE(girl_node["school"]["level"].IsSequence());  
    ASSERT_EQ(3, girl_node["school"]["level"].size()); 
    ASSERT_EQ(1, girl_node["school"]["level"][0].as<uint16_t>()); 
}

TEST(Configuration, MergeNode_null)
{
    YAML::Node girl_node = YAML::Load("{'name':'mary','age':10,'school':{'address':'beijing', 'level': null}}");
    YAML::Node boy_node = YAML::Load("{'name':'john','age':13,'school':{'address':'shanghai', 'level': [4,5], 'other':'other'}}");

    Configuration config;

    config.MergeNode(girl_node["school"]["level"], boy_node["school"]["level"]);
    ASSERT_TRUE(boy_node["school"]["level"].IsNull());  
}

TEST(Configuration, MergeNode_Map_1)
{

    YAML::Node girl_node = YAML::Load("{'name':'mary','age':10, 'color':'red','school':{'address':'beijing', 'level': [1,2,3]}}");
    YAML::Node boy_node = YAML::Load("{'name':'john','age':13,'school':{'address':'shanghai', 'level': [4,5], 'other':'other'}}");

    Configuration config;
    config.MergeNode(girl_node, boy_node);

    ASSERT_EQ(girl_node["name"], boy_node["name"]); 
    ASSERT_EQ(girl_node["school"]["level"], boy_node["school"]["level"]); 
    ASSERT_EQ("other", boy_node["school"]["other"].as<std::string>());
    ASSERT_EQ("red", boy_node["color"].as<std::string>()); 
}

TEST(Configuration, MergeNode_Map_2)
{

    YAML::Node girl_node = YAML::Load("{'name':'mary','age':10, 'color':'red','school':{'address':'beijing', 'level': [1,2,3]}}");
    YAML::Node boy_node = YAML::Load("{'name':'john','age':13,'school':{'address':'shanghai', 'level': [4,5], 'other':'other'}}");

    Configuration config;
    config.MergeNode(girl_node["name"], boy_node);
    ASSERT_EQ(boy_node, girl_node["name"]); 
}

TEST(Configuration, MergeNode_Map_3)
{

    YAML::Node girl_node = YAML::Load("{'name':'mary','age':10, 'color':'red','school':{'address':'beijing', 'level': [1,2,3]}}");
    YAML::Node boy_node = YAML::Load("{'name':'john','age':13,'school':{'address':'shanghai', 'level': [4,5], 'other':'other'}}");

    Configuration config;
    config.MergeNode(girl_node, boy_node["name"]);
    ASSERT_EQ(girl_node, boy_node["name"]); 
}

TEST(Configuration, loadFileToNode)
{
    Configuration config;
    config.loadFileToNode("/home/holo/A_config/config/test.yaml");
}

TEST(Configuration, loadFileToNode_2)
{
    Configuration config;
    EXPECT_THROW(config.loadFileToNode("/home/holo/A_config/config"), holo::utils::exception::LoadFileErrorException);
}
#endif
#if 0
TEST(Configuration, LoadConfiguration_HOLO_CONFIG_ROOT)
{
    char env[] = "HOLO_CONFIG_ROOT=/home/holo/test_workspace4/output/native/relwithdebinfo/target/config";
    putenv(env);

    Configuration config;
    config.LoadConfiguration();
}

TEST(Configuration, LoadConfiguration_HOLO_ROOT)
{
    char env[] = "HOLO_ROOT=/home/holo/test_workspace4/output/native/relwithdebinfo/target";
    putenv(env); 

    Configuration config;
    config.LoadConfiguration();
    unsetenv("HOLO_ROOT");
}

TEST(Configuration, LoadConfiguration_No_Environment)
{
    Configuration config;
    EXPECT_THROW(config.LoadConfiguration(), holo::exception::RuntimeErrorException);
}

TEST(Configuration, LoadConfiguration_SinglePath)
{
    Configuration config;
    config.LoadConfiguration("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config");

    Configuration config2;
    config2.LoadConfiguration("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/record_topics.yaml");
}

TEST(Configuration, LoadConfiguration_SinglePath_2)
{
    Configuration config;
    config.LoadConfiguration("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config/record_topics.yaml");
}

TEST(Configuration, LoadConfiguration_MultiPath)
{
    Configuration config;
    std::vector<std::string> v;
    v.push_back("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config2");
    v.push_back("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config3/record_topics.yaml");
    v.push_back("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config3/a1");

    config.LoadConfiguration(v);
}

TEST(Configuration, LoadConfiguration_MultiPath_2)
{
    Configuration config;
    std::vector<std::string> v;
    v.push_back("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config2");
    v.push_back("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config3/record_topics11.yaml");
    v.push_back("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config3/a1");

    EXPECT_THROW(config.LoadConfiguration(v), holo::exception::RuntimeErrorException);
}

TEST(Configuration, GetConfig)
{
    Configuration config;
    config.LoadConfiguration("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config");
    YAML::Node node = config.GetConfig("participants/default/discovery/accept_unknown_peers");
    ASSERT_EQ(true, node.as<bool>());

    YAML::Node node2 = config.GetConfig("components/writer_history/name");
    ASSERT_EQ("wh", node2.as<std::string>());
    node2 = "heduo";
    ASSERT_EQ("heduo", config.GetConfig("components/writer_history/name").as<std::string>());
}
#endif
TEST(Configuration, GetConfig_template)
{
    Configuration config;
    config.LoadConfiguration("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config");
    std::string str = config.GetConfig<std::string>("components/writer_history/name");
    ASSERT_EQ("wh", str);

    // Timestamp timestamp = config.GetConfig<Timestamp>("timestamp");
    // ASSERT_EQ(1, timestamp.GetSec());
    // ASSERT_EQ(2, timestamp.GetNsec());

    // EXPECT_THROW(config.GetConfig<Alarm>("timestamp"), YAML::InvalidNode);
}
#if 0
TEST(Configuration, GetConfig_DefaultValue)
{
    Configuration config;
    config.LoadConfiguration("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config");
    std::string ret = config.GetConfig<std::string>("components/xxx", "heduo");
    ASSERT_EQ("heduo", ret);

    // Timestamp timestamp = config.GetConfig<Timestamp>("timestamp11", Timestamp(3, 4));
    // ASSERT_EQ(3, timestamp.GetSec());
    // ASSERT_EQ(4, timestamp.GetNsec());
}

TEST(Configuration, SetConfig)
{
    Configuration config;
    config.LoadConfiguration("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config");

    config.SetConfig<std::string>("components/reader_history/name", "mary");
    ASSERT_EQ("mary", config.GetConfig("components/reader_history/name").as<std::string>());

    config.SetConfig("components/reader_history", 5);
    ASSERT_EQ(5, config.GetConfig("components/reader_history").as<uint16_t>());

    config.SetConfig("components/reader_history", 5);
    ASSERT_EQ(5, config.GetConfig("components/reader_history").as<uint16_t>());

    // Timestamp timestamp = Timestamp(40U, 80U);
    // Timestamp timestamp_expected;

    // config.SetConfig("components/reader_history", timestamp);
    // timestamp_expected = config.GetConfig("components/reader_history").as<Timestamp>();
    // ASSERT_EQ(timestamp.GetSec(), timestamp_expected.GetSec());
    // ASSERT_EQ(timestamp.GetNsec(), timestamp_expected.GetNsec());

    // timestamp_expected = config.GetConfig<Timestamp>("components/reader_history");
    // ASSERT_EQ(timestamp.GetSec(), timestamp_expected.GetSec());
    // ASSERT_EQ(timestamp.GetNsec(), timestamp_expected.GetNsec());
}

TEST(Configuration, SaveConfig)
{
    Configuration config;
    config.LoadConfiguration("/home/holo/test_workspace4/output/native/relwithdebinfo/target/config");

    config.SaveConfig("components/reader_history/name",
                      "/home/holo/test_workspace4/output/native/relwithdebinfo/target/config4/xxx.yaml");
    config.SaveConfig("heduo", "/home/holo/test_workspace4/output/native/relwithdebinfo/target/config4/xxx.yaml");
}
#endif
int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
