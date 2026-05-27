#include "ConsoleUI.hpp"

int main()
{
    std::cout<<"welcome to the airline reservation system\n";
    AirlineSystem system;
    system.loadData();
    ConsoleUI ui(system);
    ui.startApp();
    system.saveData();  

    return 0;
}