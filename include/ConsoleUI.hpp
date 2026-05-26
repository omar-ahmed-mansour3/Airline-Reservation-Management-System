#ifndef CONSOLEUI_H
#define CONSOLEUI_H
#include"AirlineSystem.hpp"
#include"Passenger.hpp"
#include"BookingAdmin.hpp"
#include"Administrators.hpp"
#include "Flight.hpp"
#include "Aircraft.hpp"
#include "Maintenance.hpp"

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

//*************Admin Functions *************/
void handleFlightManagement();
void handleFleetManagement();
void handleCrewAssignment();
void handleUserManagement();
void handleCreateUser();
void handleMaintenanceManagement();

//***********BOOKING FUNCTIONs***************/
void handleFlightBooking();
void handleBookingManagement();

std::shared_ptr<User> resolvePassenger();

public:

    //constructor 
    ConsoleUI(AirlineSystem& sys);

    void startApp();


};

#endif