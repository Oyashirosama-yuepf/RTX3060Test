#include <holo/thread/thread_pool.h>
#include <atomic>
#include <iostream>

using namespace holo::thread;

std::atomic<uint32_t> g_index{0U};

std::atomic<uint32_t> g_index_test_task1{0U};
std::atomic<uint32_t> g_index_test_task2{0U};
std::atomic<uint32_t> g_index_test_task3{0U};
std::atomic<uint32_t> g_index_test_task4{0U};

int test_task1()
{
    std::cout << "test_task1" << std::endl;
    ++g_index;
    ++g_index_test_task1;
    return 1;
}

int test_task2(int a, float f)
{
    (void)a;
    (void)f;
    std::cout << "test_task2  "
              << "a=" << a << "  f=" << f << std::endl;
    ++g_index;
    ++g_index_test_task2;
    return 2;
}
std::string test_task3(std::string s)
{
    (void)s;
    std::cout << "test_task3  "
              << "s=" << s << std::endl;
    ++g_index;
    ++g_index_test_task3;
    return s;
}
float test_task4(int a, std::string s)
{
    (void)a;
    (void)s;
    std::cout << "test_task4  "
              << "a=" << a << "  s=" << s << std::endl;
    ++g_index;
    ++g_index_test_task4;
    return 2.6;
}

class TestTask5
{
public:
    TestTask5()
    {
    }

    void test1()
    {
        std::cout << "TestTask5   test1  " << std::endl;
        ++g_index;
    }

    int test2(int a, int b)
    {
        std::cout << "TestTask5   test2  "
                  << "a=" << a << "  b=" << b << std::endl;
        ++g_index;
        return 100;
    }

    std::string test3(std::string const& s, float f)
    {
        std::cout << "TestTask5   test3  "
                  << "s=" << s << "  f=" << f << std::endl;
        ++g_index;
        return "ssss1000";
    }
};

// class TestTask6
//{
// public:
//    TestTask6(ThreadPool& pool) : pool_{pool}
//    {
//        pool.AddTask(&TestTask6::test4, this);
//        pool.AddTask(&TestTask6::test5, this, 666, 777);
//        pool.AddTask(&TestTask6::test6, this, "xxxxxxx", 55555.55555);
//    }
//
//    void test4()
//    {
//        std::cout << "TestTask6   test4  " << std::endl;
//    }
//
//    int test5(int a, int b)
//    {
//        std::cout << "TestTask6   test5  "
//                  << "a=" << a << "  b=" << b << std::endl;
//        return 100;
//    }
//
//    std::string test6(std::string const& s, float f)
//    {
//        std::cout << "TestTask6   test6  "
//                  << "s=" << s << "  f=" << f << std::endl;
//        return "ssss1000";
//    }
//
// private:
//    ThreadPool& pool_;
//};

int main(int argc, char** argv)
{
    (void)argc;
    (void)argv;

    ThreadPool pool{2, 32};

    std::chrono::milliseconds start_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    holo::uint32_t i{0U};
    while (i < 1'000'000U)
    {
        try
        {
            pool.AddTask(test_task1);
            i++;
            pool.AddTask(test_task2, 3, 9.6);
            i++;
            pool.AddTask(test_task3, "shjdsjjfkjk");
            i++;
            pool.AddTask(test_task4, 6, "68784874387");
            i++;

            // TestTask5 t5;
            // pool.AddTask(iterstr + "-task5-1", &TestTask5::test1, &t5);
            // i++;
            // pool.AddTask(iterstr + "-task5-2", &TestTask5::test2, &t5, 88, 99);
            // i++;
            // pool.AddTask(iterstr + "-task5-3", &TestTask5::test3, &t5, "1000000x20000", 10099.87);
            // i++;

            //            TestTask6 t6(pool);
            // i += 3;
        }
        catch (ThreadPoolPauseStatusException const& e)
        {
            break;
            // std::cout << e.what() << std::endl;
        }
        catch (TaskQueueIsFullException const& e)
        {
            // std::cout << e.what() << std::endl;
        }
    }

    std::chrono::milliseconds end_ms =
        std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());

    pool.WaitAndDestroy();

    std::cout << "count:" << i << std::endl;
    std::cout << "global index:" << g_index.load() << std::endl;
    std::cout << "global index test task1:" << g_index_test_task1.load() << std::endl;
    std::cout << "global index test task2:" << g_index_test_task2.load() << std::endl;
    std::cout << "global index test task3:" << g_index_test_task3.load() << std::endl;
    std::cout << "global index test task4:" << g_index_test_task4.load() << std::endl;
    std::cout << "start:" << start_ms.count() << std::endl;
    std::cout << "end:" << end_ms.count() << std::endl;
    std::cout << "end-start:" << end_ms.count() - start_ms.count() << std::endl;

    return 0;
}
