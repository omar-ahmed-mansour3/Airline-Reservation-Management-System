#include "ConsoleUI.hpp"

int main()
{
    std::cout << "12\n";
    AirlineSystem system;
    system.seedMockData();
    ConsoleUI ui(system);
    ui.startApp();
    return 0;
}