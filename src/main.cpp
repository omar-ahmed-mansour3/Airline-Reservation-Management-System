#include "ConsoleUI.hpp"

int main()
{
    std::cout << "18\n";
    AirlineSystem system;
    system.seedMockData();
    ConsoleUI ui(system);
    ui.startApp();
    return 0;
}