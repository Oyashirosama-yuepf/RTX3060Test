#include <assert.h>
#include <holo/log/log4cplus/ostream.h>
#include <string.h>
#include <iostream>

using namespace holo::log::log4cplus;

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    static constexpr holo::uint32_t SIZE = 1024;

    char buf[SIZE] = {0};
    memset(buf, 'a', SIZE);

    OStream ostream{SIZE};

    std::cout << buf << std::endl;

    std::cout << ostream.Count() << std::endl;
    std::cout << ostream.str() << std::endl;

    ostream << "1234567890";

    // ostream.Trunc();

    std::cout << ostream.Count() << std::endl;
    std::cout << ostream.str() << std::endl;

    std::streambuf* backup;

    backup = std::cout.rdbuf(ostream.rdbuf());
    std::cout << "This is a test msg";
    std::cout.rdbuf(backup);

    std::cout << ostream.Count() << std::endl;
    ostream.Trunc();
    std::cout << ostream.str() << std::endl;
    std::cout << buf << std::endl;

    ostream.Reset();
    ostream << "Test seekp  pos=0";
    std::cout << ostream.str() << std::endl;
    ostream.Trunc();
    std::cout << ostream.str() << std::endl;

    return 0;
}
