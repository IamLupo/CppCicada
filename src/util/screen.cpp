#include <limits>
#include <cstdlib>
#include <iostream>

namespace util::screen
{
void clear()
{
#ifdef _WIN32
    int r = std::system("cls");
#else
    int r = std::system("clear");
#endif
}

void wait_for_enter()
{
    std::cout << "Press Enter to continue...";

    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

}