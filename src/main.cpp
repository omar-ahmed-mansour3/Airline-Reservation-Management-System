#include "ConsoleUI.hpp"

int main()
{
    std::cout << "17\n";
    AirlineSystem system;
    system.seedMockData();
    ConsoleUI ui(system);
    ui.startApp();
    return 0;
}