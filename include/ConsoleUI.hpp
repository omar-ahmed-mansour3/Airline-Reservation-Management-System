#ifndef CONSOLEUI_H
#define CONSOLEUI_H
#include"AirlineSystem.hpp"
#include"Passenger.hpp"
#include"BookingAdmin.hpp"
#include"Administrators.hpp"

class ConsoleUI {
private:

    AirlineSystem& system; 
    std::shared_ptr<User> loggedInUser;

    // ************ MENU STATES ************
    void displayMainMenu();       
    void handleLogin();          
    void handleRegistration();    
// ************ ROLE-BASED DASHBOARDS ************
    void displayAdminMenu();     
    void displayPassengerMenu(); 
    void displayBookingAgentMenu(); 


public:

    //constructor 
    ConsoleUI(AirlineSystem& sys);

    void startApp();


};

#endif