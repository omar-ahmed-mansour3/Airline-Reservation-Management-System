#include "ConsoleUI.hpp"

int main()
{
    std::cout << "5\n";
    AirlineSystem system;
    ConsoleUI ui(system);
    ui.startApp();
    return 0;
}