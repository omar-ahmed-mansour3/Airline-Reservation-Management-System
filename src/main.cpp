#include "ConsoleUI.hpp"

int main()
{
    std::cout << "20c\n";
    
    AirlineSystem system;
    system.loadData();
    system.seedMockData();
    ConsoleUI ui(system);
    ui.startApp();
    system.saveData();  

    return 0;
}