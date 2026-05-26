#include "ConsoleUI.hpp"

int main()
{
    std::cout << "2\n";
    AirlineSystem system;
    ConsoleUI ui(system);
    ui.startApp();
    return 0;
}