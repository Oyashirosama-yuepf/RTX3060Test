#include <assert.h>
#include <holo/log/hololog.h>
#include <iostream>

using namespace holo;
using namespace log;

// enum class Color : holo::uint32_t
//{
//    BLACK        = 0U,
//    LIGHT_BLACK  = 1U,
//    RED          = 2U,
//    LIGHT_RED    = 3U,
//    GREEN        = 4U,
//    LIGHT_GREEN  = 5U,
//    YELLOW       = 6U,
//    LIGHT_YELLOW = 7U,
//    BLUE         = 8U,
//    LIGHT_BLUE   = 9U,
//    PINK         = 10U,
//    LIGHT_PINK   = 11U,
//    CYAN         = 12U,
//    LIGHT_CYAN   = 13U,
//    WHITE        = 14U,
//    LIGHT_WHITE  = 15U,
//    NONE         = 16U,
//};

int main(int argc, char* argv[])
{
    (void)argc;
    (void)argv;

    std::size_t black  = std::hash<Color>{}(Color::BLACK);
    std::size_t red    = std::hash<Color>{}(Color::RED);
    std::size_t green  = std::hash<Color>{}(Color::GREEN);
    std::size_t yellow = std::hash<Color>{}(Color::YELLOW);
    std::size_t blue   = std::hash<Color>{}(Color::BLUE);
    std::size_t pink   = std::hash<Color>{}(Color::PINK);
    std::size_t cyan   = std::hash<Color>{}(Color::CYAN);
    std::size_t white  = std::hash<Color>{}(Color::WHITE);
    std::size_t none   = std::hash<Color>{}(Color::NONE);

    std::size_t light_black  = std::hash<Color>{}(Color::LIGHT_BLACK);
    std::size_t light_red    = std::hash<Color>{}(Color::LIGHT_RED);
    std::size_t light_green  = std::hash<Color>{}(Color::LIGHT_GREEN);
    std::size_t light_yellow = std::hash<Color>{}(Color::LIGHT_YELLOW);
    std::size_t light_blue   = std::hash<Color>{}(Color::LIGHT_BLUE);
    std::size_t light_pink   = std::hash<Color>{}(Color::LIGHT_PINK);
    std::size_t light_cyan   = std::hash<Color>{}(Color::LIGHT_CYAN);
    std::size_t light_white  = std::hash<Color>{}(Color::LIGHT_WHITE);

    assert(black == 0);
    assert(light_black == 1);
    assert(red == 2);
    assert(light_red == 3);
    assert(green == 4);
    assert(light_green == 5);
    assert(yellow == 6);
    assert(light_yellow == 7);
    assert(blue == 8);
    assert(light_blue == 9);
    assert(pink == 10);
    assert(light_pink == 11);
    assert(cyan == 12);
    assert(light_cyan == 13);
    assert(white == 14);
    assert(light_white == 15);
    assert(none == 16);
    std::cout << "black :" << black << std::endl;
    std::cout << "red :" << red << std::endl;
    std::cout << "green :" << green << std::endl;
    std::cout << "yellow:" << yellow << std::endl;
    std::cout << "blue :" << blue << std::endl;
    std::cout << "pink :" << pink << std::endl;
    std::cout << "cyan :" << cyan << std::endl;
    std::cout << "white :" << white << std::endl;
    std::cout << "none :" << none << std::endl;

    std::cout << "light_black :" << light_black << std::endl;
    std::cout << "light_red :" << light_red << std::endl;
    std::cout << "light_green :" << light_green << std::endl;
    std::cout << "light_yellow:" << light_yellow << std::endl;
    std::cout << "light_blue :" << light_blue << std::endl;
    std::cout << "light_pink :" << light_pink << std::endl;
    std::cout << "light_cyan :" << light_cyan << std::endl;
    std::cout << "light_white :" << light_white << std::endl;

    return 0;
}
