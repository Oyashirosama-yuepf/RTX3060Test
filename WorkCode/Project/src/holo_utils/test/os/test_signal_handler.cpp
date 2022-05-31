#include <holo/os/signal_handler.h>
#include <signal.h>
#include <cstdlib>
#include <iostream>

using namespace holo::os;

HandlerAction shutdown0()
{
    std::cout << "HandlerAction shutdown0()" << std::endl;
    return HandlerAction::CONTINUE;
}

HandlerAction  g = HandlerAction::CONTINUE;
HandlerAction& shutdown1()
{
    std::cout << "HandlerAction& shutdown1()" << std::endl;
    return g;
}

HandlerAction shutdown2(int a, int b)
{
    (void)a;
    (void)b;
    std::cout << "a=" << a << "  b=" << b << std::endl;
    std::cout << "HandlerAction shutdown2(int a, int b)" << std::endl;
    return HandlerAction::CONTINUE;
}

HandlerAction shutdown3(std::string const& s1, std::string const& s2, std::string const& s3)
{
    (void)s1;
    (void)s2;
    (void)s3;
    std::cout << "s1=" << s1 << "  s2=" << s2 << "  s3=" << s3 << std::endl;
    std::cout << "HandlerAction shutdown3(std::string const& s1, std::string const& s2, std::string const& s3)"
              << std::endl;
    return HandlerAction::CONTINUE;
}

class TestA
{
public:
    TestA()
    {
        std::cout << "TestA()" << std::endl;
        SignalHandler::RegisterHandler(SIGFPE, "TestA_1", 6, std::bind(&TestA::shutdownA, this, 6, 6));
        SignalHandler::RegisterHandler(SIGFPE, "TestA_2", 7, std::bind(&TestA::shutdownA, this, 2, 9));
    }

    HandlerAction shutdownA(int c, int d)
    {
        (void)c;
        (void)d;
        std::cout << "c=" << c << "  d=" << d << std::endl;
        std::cout << "HandlerAction shutdownA(int c, int d)" << std::endl;
        return HandlerAction::CONTINUE;
    }

    ~TestA()
    {
        std::cout << "~TestA()" << std::endl;
        SignalHandler::CleanHandler(SIGFPE, "TestA_1");
        SignalHandler::CleanHandler(SIGFPE, "TestA_2");
    }
};

int main()
{
    {
        TestA a_object;
    }

    SignalHandler::RegisterTermGroupHandler("term_group_func0", 1, shutdown0);
    SignalHandler::RegisterTermGroupHandler("term_group_func1", 2, shutdown1);
    SignalHandler::RegisterTermGroupHandler("term_group_func2", 3, shutdown2, 11, 0);
    SignalHandler::RegisterTermGroupHandler("term_group_func3", 4, shutdown3, "abc", "cde", "efg");

    SignalHandler::RegisterCoreGroupHandler("core_group_func0", 1, shutdown0);
    SignalHandler::RegisterCoreGroupHandler("core_group_func1", 2, shutdown1);
    SignalHandler::RegisterCoreGroupHandler("core_group_func2", 3, shutdown2, 22, 0);
    SignalHandler::RegisterCoreGroupHandler("core_group_func3", 4, shutdown3, "opq", "rst", "xyz");

    // SignalHandler::RegisterHandler(SIGFPE, "func0", 1, shutdown0);
    // SignalHandler::RegisterHandler(SIGFPE, "func1", 2, shutdown1);
    // SignalHandler::RegisterHandler(SIGFPE, "func2", 3, shutdown2, 2, 3);
    // SignalHandler::RegisterHandler(SIGFPE, "func3", 4, shutdown3, "abc", "cde", "efg");

    std::getchar();

    int c = 0;
    int b = 1 / c;
    (void)b;
    (void)c;

    int* a = nullptr;
    *a     = 10;

    std::getchar();

    return 0;
}
