#include "ConsoleUI.hpp"

int main()
{
    AirlineSystem system;
    ConsoleUI ui(system);
    ui.startApp();
    return 0;
}